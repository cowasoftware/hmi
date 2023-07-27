#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include <tuple>
#include <functional>

#include "../constants.h"
#include "./array.h"

namespace three
{

	class UpdateRange
	{
	public:
		UpdateRange();

	public:
		uint32_t offset;
		int32_t count;
	};

	class GeometryAttribute
	{
	public:
		GeometryAttribute();
		GeometryAttribute(GeometryAttribute const& attribute);
		GeometryAttribute(GeometryAttribute&& attribute);
		GeometryAttribute(Array const& array, size_t size, bool normalized = false, Usage usage= Usage::STATIC_DRAW);
		virtual ~GeometryAttribute();

	public:
		GeometryAttribute& operator=(GeometryAttribute const&);
		GeometryAttribute& operator=(GeometryAttribute&&);
		operator bool();

	public:
		void NeedUpdate(bool update);
		size_t BytesPerElement() const;

	public:
		inline std::string const& get_type() const { return type_; }

	public:
		uint32_t size;
		bool normalized;
		Array array;
		Usage usage;
		uint64_t version;
		uint32_t count;
		UpdateRange update_range;

	protected:
		std::string type_;

	};

}