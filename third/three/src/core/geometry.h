#pragma once

#include <map>
#include <tuple>
#include <string>

#include "../constants.h"
#include "./event_dispatcher.h"

namespace three
{
	class GeometryAttribute;
}

using namespace three;

class Geometry : public EventDispatcher
{
public:
	Geometry();
	Geometry(const Geometry&) = delete;
	Geometry(Geometry&&) = delete;
	virtual ~Geometry();

public:
	Geometry& operator=(const Geometry&) = delete;
	Geometry& operator=(Geometry&&) = delete;

public:
	GeometryAttribute* GetAttribute(const std::string& name);
	GeometryAttribute const* GetAttribute(const std::string& name) const;
	void SetAttribute(const std::string& name, GeometryAttribute& attribute);
	bool HasAttribute(const std::string& name);
	void DeleteAttribute(const std::string& name);
	void SetIndex(GeometryAttribute& index);
	GeometryAttribute* GetIndex();
	GeometryAttribute const* GetIndex() const;
	std::map<std::string, GeometryAttribute*> const& GetAttributes() const { return attributes_; }
	size_t GetId() const { return id_; }

public:
	inline std::string const& get_type() const { return type_; }
	inline uint64_t get_id() const { return id_; }

protected:
	size_t id_;
	GeometryAttribute* index_;
	std::map<std::string, GeometryAttribute*> attributes_;
	std::tuple<size_t, size_t> draw_range; // [start, count]
	std::string type_;
};
