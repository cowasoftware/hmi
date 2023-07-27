#pragma once

#include <vector>
#include <cppgl.h>

#include "../math/matrix.h"

class EventListener;

class Geometry;

namespace three
{
	class Object;
	class Scene;
	class Camera;
	class Material;

	namespace gl
	{
		class RenderState;
		class RenderList;
		class RenderListItem;
		class Program;
		class RenderStates;
		class RenderState;
		class Extensions;
		class Capabilities;
		class State;
		class Info;
		class Buffers;
		class BindingStates;
		class Geometries;
		class Objects;
		class Background;
		class RenderLists;
		class RenderList;
		class RenderItem;
		class BufferRenderer;
		class IndexBufferRenderer;
		class Programs;
		class Properties;
	}

	class Renderer
	{
	public:
		Renderer(cppgl::CppGL& gl);
		virtual ~Renderer();

	public:
		void Render(Scene& scene, Camera& camera);
		void Clear();

	private:
		void ProjectObject(Object& obj, Camera& camera, uint64_t group_order, bool sort);
		void RenderScene(gl::RenderList& list, Scene& scene, Camera& camera);
		void RenderObjects(std::vector<gl::RenderItem*>& items, Scene& scene, Camera& camera);
		void RenderObject(Scene& scene, Object& object, Geometry& geometry, Material& material, Camera& camera);
		void RenderDirect(Scene& scene, Object& object, Geometry& geometry, Material& material, Camera& camera);
		gl::Program* SetProgram(Scene& scene, Object& object, Geometry& geometry, Material& material, Camera& camera);
		gl::Program* GetProgram(Material& material, Scene& scene, Object& object);

	public:
		void EnableSortObjects(bool enabled) { sort_objects_ = enabled; }

	public:
		// RenderState *current_render_state_;
		// RenderList *current_render_list_;
		// GLRenderer *glrenderer_;
		// std::map<Material*, GLProgram *> programs_;
		//   std::map<Geometry*,GLBuffer*> buffers_;
		cppgl::CppGL& gl_;
		gl::Extensions* extensions_;
		gl::Capabilities* capabilities_;

		gl::State* state_;
		gl::Info* info_;
		gl::Buffers* buffers_;
		gl::BindingStates* binding_states_;
		gl::Geometries* geometries_;
		gl::Objects* objects_;
		gl::RenderState* current_render_state_;
		gl::RenderStates* render_states_;
		gl::Background* background_;
		gl::RenderList* current_render_list_;
		gl::RenderLists* render_lists_;
		gl::BufferRenderer* buffer_renderer_;
		gl::IndexBufferRenderer* index_buffer_renderer_;
		gl::Programs* program_cache_;
		gl::Properties* properties_;

		EventListener* material_listener_;

		mat4 projection_screen_matrix_;
		bool sort_objects_;
	};

}
