#include <algorithm>

#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "./object.h"

namespace three
{

	static size_t s_id = 0;
	static const vec3 DEFAULT_UP(0.0f, 1.0f, 0.0f);
	static const vec3 AXIS_X(1.0f, 0.0f, 0.0f);
	static const vec3 AXIS_Y(0.0f, 1.0f, 0.0f);
	static const vec3 AXIS_Z(0.0f, 0.0f, 1.0f);
	static const std::string TYPE("Object");

	static mat4 compose(vec3 position, quat quaternition, vec3 scale)
	{
		return glm::translate(mat4(1.0), position) * glm::mat4_cast(quaternition) * glm::scale(mat4(1.0), scale);
	}

	Object::Object()
		: visible(true),
		render_order(0),
		position(0.0f),
		scale(1.0f),
		quaternion(1.0f, 0.0f, 0.0f, 0.0f),
		matrix(1.0f),
		world_matrix(1.0f),
		up(DEFAULT_UP),
		type_(TYPE),
		parent_(nullptr)
	{
		id_ = ++s_id;
	}

	Object::~Object()
	{
	}

	bool Object::IsScene() const
	{
		return false;
	}

	bool Object::IsLight() const
	{
		return false;
	}

	bool Object::IsGroup() const
	{
		return false;
	}

	bool Object::IsCamera() const
	{
		return false;
	}

	bool Object::IsModel() const
	{
		return false;
	}

	void Object::OnBeforeRender()
	{
	}

	void Object::OnAfterRender()
	{
	}

	Object& Object::Add(Object& object)
	{
		assert(&object != nullptr);

		if (&object != this)
		{
			if (object.parent_ != nullptr)
			{
				object.parent_->Remove(object);
			}

			object.parent_ = this;
			children_.push_back(&object);
		}

		return *this;
	}

	Object& Object::Remove(Object& object)
	{
		assert(&object != nullptr);

		auto iter = std::find(children_.begin(), children_.end(), &object);

		if (iter != children_.end())
		{
			children_.erase(iter);
		}

		return *this;
	}

	Object& Object::Scale(float rate)
	{
		scale *= rate;
		return *this;
	}

	Object& Object::ScaleTo(float rate)
	{
		scale = vec3(rate);
		return *this;
	}

	Object& Object::Rotate(quat const& q)
	{
		quaternion *= q;
		return *this;
	}

	Object& Object::RotateTo(quat const& q)
	{
		quaternion = q;
		return *this;
	}

	Object& Object::RotateX(float angle)
	{
		return RotateOnAxis(AXIS_X, angle);
	}

	Object& Object::RotateY(float angle)
	{
		return RotateOnAxis(AXIS_Y, angle);
	}

	Object& Object::RotateZ(float angle)
	{
		return RotateOnAxis(AXIS_Z, angle);
	}

	Object& Object::RotateOnAxis(vec3 const& axis, float angle)
	{
		quaternion *= (glm::angleAxis(angle, axis));
		return *this;
	}

	Object& Object::Translate(vec3 const& offset)
	{
		position += offset;
		return *this;
	}

	Object& Object::Translate(float x, float y, float z)
	{
		position += vec3(x, y, z);
		return *this;
	}

	Object& Object::TranslateTo(vec3 const& _position)
	{
		position = _position;
		return *this;
	}

	Object& Object::TranslateTo(float x, float y, float z)
	{
		position = vec3(x, y, z);
		return *this;
	}

	Object& Object::TranslateX(float distance)
	{
		TranslateOnAxis(AXIS_X, distance);
		return *this;
	}

	Object& Object::TranslateY(float distance)
	{
		TranslateOnAxis(AXIS_Y, distance);
		return *this;
	}

	Object& Object::TranslateZ(float distance)
	{
		TranslateOnAxis(AXIS_Z, distance);
		return *this;
	}

	Object& Object::TranslateOnAxis(vec3 const& axis, float distance)
	{
		position += (quaternion * axis * distance);
		return *this;
	}

	Object& Object::LookAt(vec3 const& target)
	{
		UpdateWorldMatrix(true, false);

		vec3 world_position = WorldPosition();
		mat4 look_mat(1.0f);

		if (IsCamera())
		{
			look_mat = glm::lookAtRH(world_position, target, up);
		}
		else
		{
			look_mat = glm::lookAtRH(target, world_position, up);
		}

		quaternion = glm::quat_cast(inverse(look_mat));
		return *this;
	}

	Object& Object::Traverse(std::function<void(Object&)> const& callback)
	{
		callback(*this);

		for (auto& child : children_)
		{
			child->Traverse(callback);
		}

		return *this;
	}

	Object& Object::TraverseVisible(std::function<void(Object&)> const& callback)
	{
		if (visible)
		{
			callback(*this);

			for (auto& child : children_)
			{
				child->Traverse(callback);
			}
		}

		return *this;
	}

	Object& Object::TraverseAncestors(std::function<void(Object&)> const& callback)
	{
		if (parent_)
		{
			callback(*parent_);
		}

		return *this;
	}

	Object& Object::UpdateMatrix()
	{
		matrix = glm::translate(mat4(1.0), position) * glm::mat4_cast(quaternion) * glm::scale(mat4(1.0), scale);
		return *this;
	}

	Object& Object::UpdateWorldMatrix()
	{
		UpdateMatrix();

		if (parent_)
		{
			world_matrix = matrix * parent_->world_matrix;
		}
		else
		{
			world_matrix = matrix;
		}

		for (auto& child : children_)
		{
			child->UpdateWorldMatrix();
		}

		return *this;
	}

	Object& Object::UpdateWorldMatrix(bool update_parent, bool update_children)
	{
		if (update_parent && parent_)
		{
			parent_->UpdateWorldMatrix(true, false);
		}

		UpdateMatrix();

		if (parent_)
		{
			world_matrix = matrix * parent_->world_matrix;
		}
		else
		{
			world_matrix = matrix;
		}

		if (update_children)
		{
			for (auto child : children_)
			{
				UpdateWorldMatrix(false, true);
			}
		}

		return *this;
	}
	vec3 Object::LocalToWorld(vec3 const& v)
	{
		return world_matrix * vec4(v.x, v.y, v.z, 1.0f);
	}

	vec3 Object::WorldToLocal(vec3 const& v)
	{
		return glm::inverse(world_matrix) * vec4(v.x, v.y, v.z, 1.0f);
	}

	vec3 Object::WorldPosition()
	{
		UpdateWorldMatrix(true, false);
		return LocalToWorld(vec3(0, 0, 0));
	}

	quat Object::WorldQuaternion()
	{
		vec3 skew, s, t;
		vec4 p;
		quat q;

		UpdateWorldMatrix(true, false);
		glm::decompose(world_matrix, s, q, t, skew, p);
		return q;
	}

	vec3 Object::WorldScale()
	{
		vec3 skew, s, t;
		vec4 p;
		quat q;

		UpdateWorldMatrix(true, false);
		glm::decompose(world_matrix, s, q, t, skew, p);
		return s;
	}

	vec3 Object::WorldDirection()
	{
		UpdateWorldMatrix(true, false);
		return glm::normalize(vec3(world_matrix[2]));
	}
}