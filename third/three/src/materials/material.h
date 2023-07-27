#pragma once

#include "../core/event_dispatcher.h"

namespace three
{
	class Material : public EventDispatcher
	{
	public:
		Material();
		Material(const Material&) = delete;
		Material(Material&&) = delete;
		virtual ~Material();

	public:
		Material& operator=(const Material&) = delete;
		Material& operator=(Material&&) = delete;

	public:
		virtual void OnBeforeRender();

	public:
		void NeedUpdate(bool update);

	public:
		inline uint64_t get_id() const { return id_; }
		inline std::string const& get_type() const { return type_; }

	public:
		std::string name;

		bool wireframe;

		bool vertex_colors;

		bool transparent;
		float opacity;

		uint64_t version;

	protected:
		uint64_t id_;
		std::string type_;
	};

}
