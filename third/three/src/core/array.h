#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>


namespace three
{

class Array
{
public:
	enum class Type
	{
		NONE = 0,
		UINT8,
		INT8,
		UINT16,
		INT16,
		UINT32,
		INT32,
		UINT64,
		INT64,
		FLOAT,
		DOUBLE,
	};

	Array();
	Array(Array const &array);
	Array(Array &&array);
	Array(std::vector<uint8_t> const &values);
	Array(std::vector<int8_t> const &values);
	Array(std::vector<uint16_t> const &values);
	Array(std::vector<int16_t> const &values);
	Array(std::vector<uint32_t> const &values);
	Array(std::vector<int32_t> const &values);
	Array(std::vector<uint64_t> const &values);
	Array(std::vector<int64_t> const &values);
	Array(std::vector<float> const &values);
	Array(std::vector<double> const &values);

	Array(std::vector<uint8_t> &&values);
	Array(std::vector<int8_t> &&values);
	Array(std::vector<uint16_t> &&values);
	Array(std::vector<int16_t> &&values);
	Array(std::vector<uint32_t> &&values);
	Array(std::vector<int32_t> &&values);
	Array(std::vector<uint64_t> &&values);
	Array(std::vector<int64_t> &&values);
	Array(std::vector<float> &&values);
	Array(std::vector<double> &&values);
	virtual ~Array();

public:
	Array &operator=(Array const &array);
	Array &operator=(Array &&array);
	Array &operator=(std::vector<uint8_t> const &values);
	Array &operator=(std::vector<int8_t> const &values);
	Array &operator=(std::vector<uint16_t> const &values);
	Array &operator=(std::vector<int16_t> const &values);
	Array &operator=(std::vector<uint32_t> const &values);
	Array &operator=(std::vector<int32_t> const &values);
	Array &operator=(std::vector<uint64_t> const &values);
	Array &operator=(std::vector<int64_t> const &values);
	Array &operator=(std::vector<float> const &values);
	Array &operator=(std::vector<double> const &values);

	bool operator==(Array const& rhs) const;
	bool operator!=(Array const& rhs) const;

public:
	size_t copy(size_t index, std::vector<uint8_t> const &values, size_t offset, size_t size);
	size_t copy(size_t index, std::vector<int8_t> const &values, size_t offset, size_t size);
	size_t copy(size_t index, std::vector<uint16_t> const &values, size_t offset, size_t size);
	size_t copy(size_t index, std::vector<int16_t> const &values, size_t offset, size_t size);
	size_t copy(size_t index, std::vector<uint32_t> const &values, size_t offset, size_t size);
	size_t copy(size_t index, std::vector<int32_t> const &values, size_t offset, size_t size);
	size_t copy(size_t index, std::vector<uint64_t> const &values, size_t offset, size_t size);
	size_t copy(size_t index, std::vector<int64_t> const &values, size_t offset, size_t size);
	size_t copy(size_t index, std::vector<float> const &values, size_t offset, size_t size);
	size_t copy(size_t index, std::vector<double> const &values, size_t offset, size_t size);

	size_t bytes() const;
	size_t size() const;
	Type type() const;
	const void *data(size_t index = 0) const;

private:
	template <typename T>
	void malloc(void const *values);

	template <typename T>
	void malloc(std::vector<T> const &values);

	template <typename T>
	void malloc(std::vector<T> &&values);

	template <typename T>
	void free();

	template <typename T>
	void assign(void const *values);

	template <typename T>
	void assign(std::vector<T> const &values);

	template <typename T1, typename T2>
	size_t copy(size_t index, std::vector<T2> const &values, size_t offset, size_t size);

	template <Type T1, typename T2>
	size_t copy(size_t index, std::vector<T2> const &values, size_t offset, size_t size);

	template <typename T>
	size_t size() const;

	template <typename T>
	std::vector<T> const &to() const;

private:
	void *values_;
	Type type_;
};

}
#include "./array.inl"