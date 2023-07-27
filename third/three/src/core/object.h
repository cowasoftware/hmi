#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "../math/vector.h"
#include "../math/matrix.h"
#include "../math/quaternion.h"
#include "./event_dispatcher.h"

namespace three
{
	class Object : public EventDispatcher
	{
	public:
		Object();
		virtual ~Object();

		Object(const Object& obj) = delete;
		Object(Object&& obj) = delete;

	public:
		Object& operator=(const Object& obj) = delete;
		Object& operator=(Object&& obj) = delete;

	public:
		virtual bool IsScene() const;
		virtual bool IsLight() const;
		virtual bool IsGroup() const;
		virtual bool IsCamera() const;
		virtual bool IsModel() const;

		virtual void OnBeforeRender();
		virtual void OnAfterRender();

	public:
		Object& Add(Object& obj);
		Object& Remove(Object& obj);
		Object& Scale(float rate);
		Object& ScaleTo(float rate);
		Object& Rotate(quat const& q);
		Object& RotateTo(quat const& q);
		Object& RotateX(float angle);
		Object& RotateY(float angle);
		Object& RotateZ(float angle);
		Object& RotateOnAxis(vec3 const& axis, float angle);
		Object& Translate(vec3 const& offset);
		Object& Translate(float x, float y, float z);
		Object& TranslateTo(vec3 const& position);
		Object& TranslateTo(float x, float y, float z);
		Object& TranslateX(float distance);
		Object& TranslateY(float distance);
		Object& TranslateZ(float distance);
		Object& TranslateOnAxis(vec3 const& axis, float distance);
		Object& LookAt(vec3 const& target);
		Object& Traverse(std::function<void(Object&)> const& callback);
		Object& TraverseVisible(std::function<void(Object&)> const& callback);
		Object& TraverseAncestors(std::function<void(Object&)> const& callback);
		Object& UpdateMatrix();
		Object& UpdateWorldMatrix();

		vec3 LocalToWorld(vec3 const& v);
		vec3 WorldToLocal(vec3 const& v);
		vec3 WorldPosition();
		quat WorldQuaternion();
		vec3 WorldScale();
		vec3 WorldDirection();

	protected:
		Object& UpdateWorldMatrix(bool update_parent, bool update_children);

	public:
		bool visible;
		uint64_t render_order;

		vec3 position;
		quat quaternion;
		vec3 scale;
		mat4 matrix;
		mat4 world_matrix;

		vec3 up;
		std::string name;

	public:
		inline std::string const get_type() const { return type_; }
		inline uint64_t get_id() const { return id_; }
		inline std::vector<Object*> get_childern() { return children_; }

	protected:
		uint64_t id_;
		std::string type_;
		Object* parent_;
		std::vector<Object*> children_;
	};

}