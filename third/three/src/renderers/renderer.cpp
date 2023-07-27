#include <sstream>

#include "../core/geometry.h"
#include "../core/geometry_attribute.h"
#include "../scenes/scene.h"
#include "../lights/light.h"
#include "../lights/ambient_light.h"
#include "../lights/directional_light.h"
#include "../lights/point_light.h"
#include "../lights/spot_light.h"
#include "../cameras/perspective_camera.h"
#include "../materials/points_material.h"
#include "../materials/mesh_basic_material.h"
#include "../materials/mesh_lambert_material.h"
#include "../materials/mesh_phong_material.h"
#include "../materials/shader_material.h"
#include "../objects/points.h"
#include "../objects/line.h"
#include "../objects/mesh.h"
#include "../objects/instanced_mesh.h"
#include "../utils/clock_util.h"

#include "./gl/extensions.h"
#include "./gl/capabilities.h"
#include "./gl/state.h"
#include "./gl/info.h"
#include "./gl/buffers.h"
#include "./gl/binding_states.h"
#include "./gl/geometries.h"
#include "./gl/objects.h"
#include "./gl/background.h"
#include "./gl/render_states.h"
#include "./gl/render_lists.h"
#include "./gl/buffer_renderer.h"
#include "./gl/index_buffer_renderer.h"
#include "./gl/program.h"
#include "./gl/programs.h"
#include "./gl/properties.h"
#include "./gl/uniforms.h"
#include "./gl/lights.h"
#include "./gl/logger.h"
#include "./renderer.h"
#include "./gl/utils.h"
#include "../utils/attenuation_util.h"
#include <fmt/core.h>

// #include <glm/gtx/string_cast.hpp>

extern bool g_pointsToLines;

using namespace three::gl;
using namespace fmt;

namespace three
{

	Renderer::Renderer(cppgl::CppGL &gl)
		: gl_(gl),
		  sort_objects_(true),
		  projection_screen_matrix_(1.0f),
		  extensions_(nullptr),
		  capabilities_(nullptr),
		  buffers_(nullptr),
		  geometries_(nullptr),
		  binding_states_(nullptr),
		  objects_(nullptr),
		  background_(nullptr),
		  render_states_(nullptr),
		  render_lists_(nullptr),
		  current_render_state_(nullptr),
		  current_render_list_(nullptr),
		  buffer_renderer_(nullptr),
		  index_buffer_renderer_(nullptr),
		  properties_(nullptr),
		  material_listener_(nullptr)
	{
		extensions_ = new Extensions(gl);
		capabilities_ = new Capabilities(gl);
		state_ = new State(gl, *extensions_, *capabilities_);
		info_ = new Info(gl);
		buffers_ = new Buffers(gl, *capabilities_);
		binding_states_ = new BindingStates(gl, *buffers_, *extensions_, *capabilities_);
		program_cache_ = new Programs(gl, *extensions_, *capabilities_, *binding_states_);
		geometries_ = new Geometries(gl, *buffers_, *binding_states_, *info_);
		objects_ = new Objects(gl, *geometries_, *buffers_, *info_);
		background_ = new Background(*this, *state_, *objects_);
		render_states_ = new RenderStates(*extensions_, *capabilities_);
		render_lists_ = new RenderLists();
		buffer_renderer_ = new BufferRenderer(gl, *extensions_, *info_, *capabilities_);
		index_buffer_renderer_ = new IndexBufferRenderer(gl, *info_, *extensions_, *capabilities_);
		properties_ = new Properties();
		material_listener_ = new EventListener();

		auto material_callback = [this](Event const &event)
		{
			auto &properties = *properties_;
			auto &program_cache = *program_cache_;
			auto &material = static_cast<Material &>(*event.GetDispatcher());

			material.RemoveEventLister("dispose", *material_listener_);
			auto &programs = properties.Get(material).programs;
			for (auto &program : programs)
			{
				program_cache.ReleaseProgram(*program.second);

				if (ShaderMaterial::IsInstance(material))
				{
					program_cache.ReleaseShaderCache(material);
				}
			}
			properties.Remove(material);
		};

		material_listener_->SetCallback(material_callback);
	}

	Renderer::~Renderer()
	{
		delete material_listener_;
		delete index_buffer_renderer_;
		delete buffer_renderer_;
		delete render_lists_;
		delete render_states_;
		delete background_;
		delete objects_;
		delete geometries_;
		delete binding_states_;
		delete buffers_;
		delete info_;
		delete state_;
		delete capabilities_;
		delete extensions_;
		delete properties_;
		delete program_cache_;
	}

	void Renderer::Render(Scene &scene, Camera &camera)
	{
		scene.UpdateWorldMatrix();
		camera.UpdateWorldMatrix();

		projection_screen_matrix_ = camera.projection_matrix * camera.world_matrix_inverse;

		auto &render_states = *render_states_;
		auto &current_render_state = *render_states.Get(scene);
		current_render_state.Init();
		current_render_state_ = &current_render_state;

		auto &render_lists = *render_lists_;
		auto &current_render_list = *render_lists.Get(scene);
		current_render_list.Init();
		current_render_list_ = &current_render_list;
		current_render_list.Init();
		ProjectObject(scene, camera, 0, sort_objects_);
		current_render_list.Finish();

		if (sort_objects_)
		{
			current_render_list.Sort();
		}

		if (info_->auto_reset)
		{
			info_->Reset();
		}

		auto &background = *background_;

		background.Render(current_render_list, scene);
		current_render_state.SetupLights();
		// ClockUtil::fps();
		RenderScene(current_render_list, scene, camera);
		binding_states_->ResetState();
		// print("fps: {}, triangles: {}\n",ClockUtil::fps(), info_->render.triangles);
	}

	void Renderer::Clear()
	{
		gl_.Clear(cppgl::CPPGL_COLOR_BUFFER_BIT | cppgl::CPPGL_DEPTH_BUFFER_BIT);
	}

	void Renderer::ProjectObject(Object &obj, Camera &camera, uint64_t group_order, bool sort)
	{
		auto &current_render_state = *current_render_state_;
		auto &current_render_list = *current_render_list_;

		if (!obj.visible)
		{
			return;
		}

		if (obj.IsGroup())
		{
			group_order = obj.render_order;
		}
		else if (obj.IsLight())
		{
			current_render_state.PushLight(static_cast<Light &>(obj));
		}
		else if (obj.IsModel())
		{
			auto &model = static_cast<Model &>(obj);
			vec4 screen_position(0.0f, 0.0f, 0.0f, 0.0f);

			if (sort)
			{
				screen_position = projection_screen_matrix_ * vec4(obj.WorldPosition(), 1.0f);
			}
			objects_->Update(model);
			current_render_list.Push(model, model.geometry, model.material, group_order, screen_position.z);
		}

		for (auto child : obj.get_childern())
		{
			ProjectObject(*child, camera, group_order, sort);
		}
	}

	void Renderer::RenderScene(RenderList &list, Scene &scene, Camera &camera)
	{
		auto &gl = gl_;

		current_render_state_->setupLightsView(camera);
		gl.Enable(cppgl::CPPGL_DEPTH_TEST);
		gl.Enable(cppgl::CPPGL_PROGRAM_POINT_SIZE);

		if (!list.GetOpaqueItems().empty())
		{
			gl.DepthMask(true);
			gl.Disable(cppgl::CPPGL_BLEND);
			RenderObjects(list.GetOpaqueItems(), scene, camera);
		}
		if (!list.GetTransparentItems().empty())
		{
			gl.DepthMask(false);
			gl.Enable(cppgl::CPPGL_BLEND);
			gl.BlendFunc(cppgl::CPPGL_SRC_ALPHA, cppgl::CPPGL_ONE_MINUS_SRC_ALPHA);
			RenderObjects(list.GetTransparentItems(), scene, camera);
		}

		gl.DepthMask(true);
	}

	void Renderer::RenderObjects(std::vector<RenderItem *> &items, Scene &scene, Camera &camera)
	{
		// asert((&scene != nullptr) && (&camera != nullptr));
		for (auto item : items)
		{
			// asert(item->geometry != nullptr && item->material != nullptr && item->obj != nullptr);
			auto &render_item = *item;
			RenderObject(scene, *render_item.obj, *render_item.geometry, *render_item.material, camera);
		}
	}

	void Renderer::RenderObject(Scene &scene, Object &object, Geometry &geometry, Material &material, Camera &camera)
	{
		// asert((&scene != nullptr) && (&object != nullptr) && (&geometry != nullptr) && (&material != nullptr) && (&camera != nullptr));
		//  object.OnBeforeRender();
		//  material.OnBeforeRender();
		// asert((&scene != nullptr) && (&object != nullptr) && (&geometry != nullptr) && (&material != nullptr) && (&camera != nullptr));
		RenderDirect(scene, object, geometry, material, camera);
		Object &obj = const_cast<Object &>(object);
		obj.OnAfterRender();
	}

	void Renderer::RenderDirect(Scene &scene, Object &object, Geometry &geometry, Material &material, Camera &camera)
	{
		// asert((&scene != nullptr) && (&object != nullptr) && (&geometry != nullptr) && (&material != nullptr) && (&camera != nullptr));

		auto &binding_states = *binding_states_;
		auto &attributes = *buffers_;
		auto &index_buffer_renderer = *index_buffer_renderer_;
		auto &buffer_renderer = *buffer_renderer_;
		auto &gl = gl_;

		auto &program = *SetProgram(scene, object, geometry, material, camera);

		auto *index = geometry.GetIndex();
		auto *position = geometry.GetAttribute("position");

		if (!index)
		{
			if (!position || position->count == 0)
			{
				return;
			}
		}
		else if (index->count == 0)
		{

			return;
		}

		auto data_count = index ? index->count : position->count;
		auto draw_count = data_count;
		auto draw_start = 0;
		uint32_t mode = 0;

		if (Mesh::IsInstance(object) || InstancedMesh::IsInstance(object))
		{
			if (InstancedMesh::IsInstance(object))
			{
				auto &instanced_mesh = static_cast<InstancedMesh &>(object);
				mode = Utils::Convert(instanced_mesh.draw_mode);
			}
			else
			{
				mode = cppgl::CPPGL_TRIANGLES;
			}

			// mode = cppgl::CPPGL_POINTS;
		}
		else if (Line::IsInstance(object))
		{
			mode = cppgl::CPPGL_LINES;
		}
		else if (Points::IsInstance(object))
		{
			mode = cppgl::CPPGL_POINTS;
			if (g_pointsToLines)
			{
				mode = cppgl::CPPGL_LINES;
			}
		}
		else
		{
			return;
		}

		if (index)
		{

			binding_states.Setup(object, material, program, geometry, *index);
			auto &buffer = *attributes.Get(*index);
			index_buffer_renderer.type = buffer.data_type;
			index_buffer_renderer.bytes_per_element = buffer.bytes_per_element;
			index_buffer_renderer.mode = mode;

			if (InstancedMesh::IsInstance(object))
			{
				auto &instanced_mesh = static_cast<InstancedMesh &>(object);
				index_buffer_renderer.RenderInstances(draw_start, draw_count, instanced_mesh.draw_count);
			}
			else
			{
				index_buffer_renderer.Render(draw_start, draw_count);
			}
		}
		else
		{
			binding_states.Setup(object, material, program, geometry);
			buffer_renderer.mode = mode;
			if (InstancedMesh::IsInstance(object))
			{
				auto &instanced_mesh = static_cast<InstancedMesh &>(object);
				buffer_renderer.RenderInstances(draw_start, draw_count, instanced_mesh.draw_count);
			}
			else
			{
				buffer_renderer.Render(draw_start, draw_count);
			}
		}
	}

	Program *Renderer::SetProgram(Scene &scene, Object &object, Geometry &geometry, Material &material, Camera &camera)
	{
		// asert((&scene != nullptr) && (&object != nullptr) && (&geometry != nullptr) && (&material != nullptr) && (&camera != nullptr));
		std::stringstream ss;
		auto &program = *GetProgram(material, scene, object);
		auto &uniforms = *program.cached_uniforms;
		auto &lights = current_render_state_->lights->state;
		state_->UseProgram(program);
		auto normal_matrix = glm::transpose(glm::inverse(camera.world_matrix_inverse * object.world_matrix));
		uniforms.SetValue("modelViewMatrix", camera.world_matrix_inverse * object.world_matrix);
		uniforms.SetValue("projectionMatrix", camera.projection_matrix);
		uniforms.SetValue("normalMatrix", mat3(normal_matrix));
		uniforms.SetValue("viewMatrix", camera.world_matrix_inverse);
		uniforms.SetValue("ambientLightColor", lights.ambient);
		uniforms.SetValue("lightProbe[0]", lights.probes[0]);

		for (size_t i = 0; i < lights.directionals.size(); i++)
		{
			ss.str("");
			ss << "directionalLights[" << i << "].";
			uniforms.SetValue(ss.str() + "direction", lights.directionals[i]->direction);
			uniforms.SetValue(ss.str() + "color", lights.directionals[i]->color);
		}

		for (size_t i = 0; i < lights.points.size(); i++)
		{
			ss.str("");
			ss << "pointLights[" << i << "].";
			uniforms.SetValue(ss.str() + "position", lights.points[i]->position);
			uniforms.SetValue(ss.str() + "color", lights.points[i]->color);
			uniforms.SetValue(ss.str() + "distance", lights.points[i]->distance);
			uniforms.SetValue(ss.str() + "decay", lights.points[i]->decay);
		}

		for (size_t i = 0; i < lights.spots.size(); i++)
		{
			ss.str("");
			ss << "spotLights[" << i << "].";
			uniforms.SetValue(ss.str() + "position", lights.spots[i]->position);
			uniforms.SetValue(ss.str() + "direction", lights.spots[i]->direction);
			uniforms.SetValue(ss.str() + "color", lights.spots[i]->color);
			uniforms.SetValue(ss.str() + "distance", lights.spots[i]->distance);
			uniforms.SetValue(ss.str() + "decay", lights.spots[i]->decay);
			uniforms.SetValue(ss.str() + "coneCos", lights.spots[i]->cone_cos);
			uniforms.SetValue(ss.str() + "penumbraCos", lights.spots[i]->penumbra_cos);
		}

		if (PointsMaterial::IsInstance(material))
		{
			auto &points_material = static_cast<PointsMaterial &>(material);
			uniforms.SetValue("diffuse", points_material.color);
			uniforms.SetValue("opacity", points_material.opacity);
			uniforms.SetValue("size", points_material.size);
		}
		else if (MeshBasicMaterial::IsInstance(material))
		{
			auto &mesh_basic_material = static_cast<MeshBasicMaterial &>(material);
			uniforms.SetValue("diffuse", mesh_basic_material.color);
			uniforms.SetValue("opacity", mesh_basic_material.opacity);
		}
		else if (MeshLambertMaterial::IsInstance(material))
		{
			auto &mesh_lambert_material = static_cast<MeshLambertMaterial &>(material);
			uniforms.SetValue("diffuse", mesh_lambert_material.diffuse_color);
			uniforms.SetValue("opacity", mesh_lambert_material.opacity);
		}
		else if (MeshPhongMaterial::IsInstance(material))
		{
			auto &mesh_phong_material = static_cast<MeshPhongMaterial &>(material);
			uniforms.SetValue("diffuse", mesh_phong_material.diffuse_color);
			uniforms.SetValue("opacity", mesh_phong_material.opacity);
			uniforms.SetValue("specular", mesh_phong_material.specular_color);
			uniforms.SetValue("shininess", mesh_phong_material.shininess);
		}

		return &program;
	}

	Program *Renderer::GetProgram(Material &material, Scene &scene, Object &object)
	{
		auto &current_render_state = *current_render_state_;
		auto &properties = *properties_;
		auto &program_cache = *program_cache_;
		auto &lights = *current_render_state.lights;
		auto &material_properties = properties.Get(material);
		auto &programs = material_properties.programs;
		auto parameters = program_cache.MakeParameters(material, lights.state, object);
		auto cache_key = program_cache.MakeProgramCacheKey(parameters);

		if (programs.empty())
		{
			material.AddEventListener("dispose", *material_listener_);
		}
		else
		{
			auto program_iter = programs.find(cache_key);

			if (program_iter != programs.end())
			{
				return program_iter->second;
			}
		}

		auto &program = *program_cache.AcquireProgram(parameters, cache_key);
		programs[cache_key] = &program;
		return &program;
	}
}