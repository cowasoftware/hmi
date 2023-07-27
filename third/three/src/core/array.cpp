#include <iostream>

#include "./array.h"

namespace three
{

	template <typename T>
	static bool operator==(std::vector<T> const& lhs, std::vector<T> const& rhs)
	{
		if (lhs.empty() && rhs.empty())
		{
			return true;
		}
		if (lhs.size() != rhs.size())
		{
			return false;
		}

		size_t index = 0;

		while (index < lhs.size())
		{
			if (lhs[index] != rhs[index])
			{
				return false;
			}

			index++;
		}

		return true;
	}

	template <typename T>
	static bool operator!=(std::vector<T> const& lhs, std::vector<T> const& rhs)
	{
		if (lhs.size() != rhs.size())
		{
			return false;
		}
		size_t index = 0;

		while (index < lhs.size())
		{
			if (lhs[index] != rhs[index])
			{
				return true;
			}

			index++;
		}

		return false;
	}


	Array::Array() : values_(nullptr),
		type_(Type::NONE)
	{
	}

	Array::Array(Array const& array) : Array()
	{
		type_ = array.type_;

		switch (array.type_)
		{
		case Type::NONE:
			break;
		case Type::UINT8:
			malloc<uint8_t>(array.values_);
			break;
		case Type::INT8:
			malloc<int8_t>(array.values_);
			break;
		case Type::UINT16:
			malloc<uint16_t>(array.values_);
			break;
		case Type::INT16:
			malloc<int16_t>(array.values_);
			break;
		case Type::UINT32:
			malloc<uint32_t>(array.values_);
			break;
		case Type::INT32:
			malloc<int32_t>(array.values_);
			break;
		case Type::UINT64:
			malloc<uint64_t>(array.values_);
			break;
		case Type::INT64:
			malloc<int64_t>(array.values_);
			break;
		case Type::FLOAT:
			malloc<float>(array.values_);
			break;
		case Type::DOUBLE:
			malloc<double>(array.values_);
			break;
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_) << std::endl;
		}
	}

	Array::Array(Array&& array) : Array()
	{
		type_ = array.type_;
		values_ = array.values_;

		array.type_ = Type::NONE;
		array.values_ = nullptr;
	}

	Array::Array(std::vector<uint8_t> const& values) : Array()
	{
		type_ = Type::UINT8;
		malloc(values);
	}

	Array::Array(std::vector<int8_t> const& values) : Array()
	{
		type_ = Type::INT8;
		malloc(values);
	}

	Array::Array(std::vector<uint16_t> const& values) : Array()
	{
		type_ = Type::UINT8;
		malloc(values);
	}

	Array::Array(std::vector<int16_t> const& values) : Array()
	{
		type_ = Type::INT16;
		malloc(values);
	}

	Array::Array(std::vector<uint32_t> const& values) : Array()
	{
		type_ = Type::UINT32;
		malloc(values);
	}

	Array::Array(std::vector<int32_t> const& values) : Array()
	{
		type_ = Type::INT32;
		malloc(values);
	}

	Array::Array(std::vector<uint64_t> const& values) : Array()
	{
		type_ = Type::UINT64;
		malloc(values);
	}

	Array::Array(std::vector<int64_t> const& values) : Array()
	{
		type_ = Type::INT64;
		malloc(values);
	}

	Array::Array(std::vector<float> const& values) : Array()
	{
		type_ = Type::FLOAT;
		malloc(values);
	}

	Array::Array(std::vector<double> const& values) : Array()
	{
		type_ = Type::DOUBLE;
		malloc(values);
	}

	Array::Array(std::vector<uint8_t>&& values) : Array()
	{
		type_ = Type::UINT8;
		malloc(values);
	}

	Array::Array(std::vector<int8_t>&& values) : Array()
	{
		type_ = Type::INT8;
		malloc(values);
	}

	Array::Array(std::vector<uint16_t>&& values) : Array()
	{
		type_ = Type::UINT8;
		malloc(values);
	}

	Array::Array(std::vector<int16_t>&& values) : Array()
	{
		type_ = Type::INT16;
		malloc(values);
	}

	Array::Array(std::vector<uint32_t>&& values) : Array()
	{
		type_ = Type::UINT32;
		malloc(values);
	}

	Array::Array(std::vector<int32_t>&& values) : Array()
	{
		type_ = Type::INT32;
		malloc(values);
	}

	Array::Array(std::vector<uint64_t>&& values) : Array()
	{
		type_ = Type::UINT64;
		malloc(values);
	}

	Array::Array(std::vector<int64_t>&& values) : Array()
	{
		type_ = Type::INT64;
		malloc(values);
	}

	Array::Array(std::vector<float>&& values) : Array()
	{
		type_ = Type::FLOAT;
		malloc(values);
	}

	Array::Array(std::vector<double>&& values) : Array()
	{
		type_ = Type::DOUBLE;
		malloc(values);
	}

	Array::~Array()
	{
		switch (type_)
		{
		case Type::NONE:
			break;
		case Type::UINT8:
			free<uint8_t>();
			break;
		case Type::INT8:
			free<int8_t>();
			break;
		case Type::UINT16:
			free<uint16_t>();
			break;
		case Type::INT16:
			free<int16_t>();
			break;
		case Type::UINT32:
			free<uint32_t>();
			break;
		case Type::INT32:
			free<int32_t>();
			break;
		case Type::UINT64:
			free<uint64_t>();
			break;
		case Type::INT64:
			free<int64_t>();
			break;
		case Type::FLOAT:
			free<float>();
			break;
		case Type::DOUBLE:
			free<double>();
			break;
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_) << std::endl;
		}
	}

	Array& Array::operator=(Array const& array)
	{
		switch (type_)
		{
		case Type::NONE:
			break;
		case Type::UINT8:
			free<uint8_t>();
			break;
		case Type::INT8:
			free<int8_t>();
			break;
		case Type::UINT16:
			free<uint16_t>();
			break;
		case Type::INT16:
			free<int16_t>();
			break;
		case Type::UINT32:
			free<uint32_t>();
			break;
		case Type::INT32:
			free<int32_t>();
			break;
		case Type::UINT64:
			free<uint64_t>();
			break;
		case Type::INT64:
			free<int64_t>();
			break;
		case Type::FLOAT:
			free<float>();
			break;
		case Type::DOUBLE:
			free<double>();
			break;
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_) << std::endl;
		}

		switch (array.type_)
		{
		case Type::NONE:
			break;
		case Type::UINT8:
			malloc<uint8_t>(array.values_);
			break;
		case Type::INT8:
			malloc<int8_t>(array.values_);
			break;
		case Type::UINT16:
			malloc<uint16_t>(array.values_);
			break;
		case Type::INT16:
			malloc<int16_t>(array.values_);
			break;
		case Type::UINT32:
			malloc<uint32_t>(array.values_);
			break;
		case Type::INT32:
			malloc<int32_t>(array.values_);
			break;
		case Type::UINT64:
			malloc<uint64_t>(array.values_);
			break;
		case Type::INT64:
			malloc<int64_t>(array.values_);
			break;
		case Type::FLOAT:
			malloc<float>(array.values_);
			break;
		case Type::DOUBLE:
			malloc<double>(array.values_);
			break;
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_) << std::endl;
		}

		type_ = array.type_;
		return *this;
	}

	Array& Array::operator=(Array&& array)
	{
		switch (type_)
		{
		case Type::NONE:
			break;
		case Type::UINT8:
			free<uint8_t>();
			break;
		case Type::INT8:
			free<int8_t>();
			break;
		case Type::UINT16:
			free<uint16_t>();
			break;
		case Type::INT16:
			free<int16_t>();
			break;
		case Type::UINT32:
			free<uint32_t>();
			break;
		case Type::INT32:
			free<int32_t>();
			break;
		case Type::UINT64:
			free<uint64_t>();
			break;
		case Type::INT64:
			free<int64_t>();
			break;
		case Type::FLOAT:
			free<float>();
			break;
		case Type::DOUBLE:
			free<double>();
			break;
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_) << std::endl;
		}

		type_ = array.type_;
		values_ = array.values_;

		array.type_ = Type::NONE;
		array.values_ = nullptr;

		return *this;
	}

	Array& Array::operator=(std::vector<uint8_t> const& values)
	{
		assign(values);
		return *this;
	}
	Array& Array::operator=(std::vector<int8_t> const& values)
	{
		assign(values);
		return *this;
	}
	Array& Array::operator=(std::vector<uint16_t> const& values)
	{
		assign(values);
		return *this;
	}
	Array& Array::operator=(std::vector<int16_t> const& values)
	{
		assign(values);
		return *this;
	}
	Array& Array::operator=(std::vector<uint32_t> const& values)
	{
		assign(values);
		return *this;
	}
	Array& Array::operator=(std::vector<int32_t> const& values)
	{
		assign(values);
		return *this;
	}
	Array& Array::operator=(std::vector<uint64_t> const& values)
	{
		assign(values);
		return *this;
	}
	Array& Array::operator=(std::vector<int64_t> const& values)
	{
		assign(values);
		return *this;
	}
	Array& Array::operator=(std::vector<float> const& values)
	{
		assign(values);
		return *this;
	}
	Array& Array::operator=(std::vector<double> const& values)
	{
		assign(values);
		return *this;
	}


	bool Array::operator==(Array const& rhs) const
	{
		if (type_ != rhs.type_)
		{
			return false;
		}
		else if (type_ == Type::UINT8)
		{
			return *static_cast<std::vector<uint8_t> const*>(values_) == *static_cast<std::vector<uint8_t> const*>(rhs.values_);
		}
		else if (type_ == Type::INT8)
		{
			return *static_cast<std::vector<int8_t> const*>(values_) == *static_cast<std::vector<int8_t> const*>(rhs.values_);
		}
		else if (type_ == Type::UINT16)
		{
			return *static_cast<std::vector<uint16_t> const*>(values_) == *static_cast<std::vector<uint16_t> const*>(rhs.values_);
		}
		else if (type_ == Type::INT16)
		{
			return *static_cast<std::vector<int16_t> const*>(values_) == *static_cast<std::vector<int16_t> const*>(rhs.values_);
		}
		else if (type_ == Type::UINT32)
		{
			return *static_cast<std::vector<uint32_t> const*>(values_) == *static_cast<std::vector<uint32_t> const*>(rhs.values_);
		}
		else if (type_ == Type::INT32)
		{
			return *static_cast<std::vector<int32_t> const*>(values_) == *static_cast<std::vector<int32_t> const*>(rhs.values_);
		}
		else if (type_ == Type::UINT64)
		{
			return *static_cast<std::vector<uint64_t> const*>(values_) == *static_cast<std::vector<uint64_t> const*>(rhs.values_);
		}
		else if (type_ == Type::INT64)
		{
			return *static_cast<std::vector<int64_t> const*>(values_) == *static_cast<std::vector<int64_t> const*>(rhs.values_);
		}
		else if (type_ == Type::FLOAT)
		{
			return *static_cast<std::vector<float> const*>(values_) == *static_cast<std::vector<float> const*>(rhs.values_);
		}
		else if (type_ == Type::DOUBLE)
		{
			return *static_cast<std::vector<double> const*>(values_) == *static_cast<std::vector<double> const*>(rhs.values_);
		}
		else
		{
			std::cerr << "support array type: " << static_cast<uint32_t>(type_) << std::endl;
			return false;
		}


		return false;

	}
	bool Array::operator!=(Array const& rhs) const
	{
		if (type_ != rhs.type_)
		{
			return true;
		}
		else if (type_ == Type::UINT8)
		{
			return *static_cast<std::vector<uint8_t> const*>(values_) != *static_cast<std::vector<uint8_t> const*>(rhs.values_);
		}
		else if (type_ == Type::INT8)
		{
			return *static_cast<std::vector<int8_t> const*>(values_) != *static_cast<std::vector<int8_t> const*>(rhs.values_);
		}
		else if (type_ == Type::UINT16)
		{
			return *static_cast<std::vector<uint16_t> const*>(values_) != *static_cast<std::vector<uint16_t> const*>(rhs.values_);
		}
		else if (type_ == Type::INT16)
		{
			return *static_cast<std::vector<int16_t> const*>(values_) != *static_cast<std::vector<int16_t> const*>(rhs.values_);
		}
		else if (type_ == Type::UINT32)
		{
			return *static_cast<std::vector<uint32_t> const*>(values_) != *static_cast<std::vector<uint32_t> const*>(rhs.values_);
		}
		else if (type_ == Type::INT32)
		{
			return *static_cast<std::vector<int32_t> const*>(values_) != *static_cast<std::vector<int32_t> const*>(rhs.values_);
		}
		else if (type_ == Type::UINT64)
		{
			return *static_cast<std::vector<uint64_t> const*>(values_) != *static_cast<std::vector<uint64_t> const*>(rhs.values_);
		}
		else if (type_ == Type::INT64)
		{
			return *static_cast<std::vector<int64_t> const*>(values_) != *static_cast<std::vector<int64_t> const*>(rhs.values_);
		}
		else if (type_ == Type::FLOAT)
		{
			return *static_cast<std::vector<float> const*>(values_) != *static_cast<std::vector<float> const*>(rhs.values_);
		}
		else if (type_ == Type::DOUBLE)
		{
			return *static_cast<std::vector<double> const*>(values_) != *static_cast<std::vector<double> const*>(rhs.values_);
		}
		else
		{
			std::cerr << "support array type: " << static_cast<uint32_t>(type_) << std::endl;
			return false;
		}

		return false;
	}


	size_t Array::copy(size_t index, std::vector<uint8_t> const &values, size_t offset, size_t size)
	{
		switch (type_)
		{
		case Type::NONE:
			return 0;
		case Type::UINT8:
			return copy<uint8_t, uint8_t>(index, values, offset, size);
		case Type::INT8:
			return copy<int8_t, uint8_t>(index, values, offset, size);
		case Type::UINT16:
			return copy<uint16_t, uint8_t>(index, values, offset, size);
		case Type::INT16:
			return copy<int16_t, uint8_t>(index, values, offset, size);
		case Type::UINT32:
			return copy<uint32_t, uint8_t>(index, values, offset, size);
		case Type::INT32:
			return copy<int32_t, uint8_t>(index, values, offset, size);
		case Type::UINT64:
			return copy<uint64_t, uint8_t>(index, values, offset, size);
		case Type::INT64:
			return copy<int64_t, uint8_t>(index, values, offset, size);
		case Type::FLOAT:
			return copy<float, uint8_t>(index, values, offset, size);
		case Type::DOUBLE:
			return copy<double, uint8_t>(index, values, offset, size);
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return 0;
		}
	}

	size_t Array::copy(size_t index, std::vector<int8_t> const &values, size_t offset, size_t size)
	{
		switch (type_)
		{
		case Type::NONE:
			return 0;
		case Type::UINT8:
			return copy<uint8_t, int8_t>(index, values, offset, size);
		case Type::INT8:
			return copy<int8_t, int8_t>(index, values, offset, size);
		case Type::UINT16:
			return copy<uint16_t, int8_t>(index, values, offset, size);
		case Type::INT16:
			return copy<int16_t, int8_t>(index, values, offset, size);
		case Type::UINT32:
			return copy<uint32_t, int8_t>(index, values, offset, size);
		case Type::INT32:
			return copy<int32_t, int8_t>(index, values, offset, size);
		case Type::UINT64:
			return copy<uint64_t, int8_t>(index, values, offset, size);
		case Type::INT64:
			return copy<int64_t, int8_t>(index, values, offset, size);
		case Type::FLOAT:
			return copy<float, int8_t>(index, values, offset, size);
		case Type::DOUBLE:
			return copy<double, int8_t>(index, values, offset, size);
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return 0;
		}
	}

	size_t Array::copy(size_t index, std::vector<uint16_t> const &values, size_t offset, size_t size)
	{
		switch (type_)
		{
		case Type::NONE:
			return 0;
		case Type::UINT8:
			return copy<uint8_t, uint16_t>(index, values, offset, size);
		case Type::INT8:
			return copy<int8_t, uint16_t>(index, values, offset, size);
		case Type::UINT16:
			return copy<uint16_t, uint16_t>(index, values, offset, size);
		case Type::INT16:
			return copy<int16_t, uint16_t>(index, values, offset, size);
		case Type::UINT32:
			return copy<uint32_t, uint16_t>(index, values, offset, size);
		case Type::INT32:
			return copy<int32_t, uint16_t>(index, values, offset, size);
		case Type::UINT64:
			return copy<uint64_t, uint16_t>(index, values, offset, size);
		case Type::INT64:
			return copy<int64_t, uint16_t>(index, values, offset, size);
		case Type::FLOAT:
			return copy<float, uint16_t>(index, values, offset, size);
		case Type::DOUBLE:
			return copy<double, uint16_t>(index, values, offset, size);
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return 0;
		}
	}

	size_t Array::copy(size_t index, std::vector<int16_t> const &values, size_t offset, size_t size)
	{
		switch (type_)
		{
		case Type::NONE:
			return 0;
		case Type::UINT8:
			return copy<uint8_t, int16_t>(index, values, offset, size);
		case Type::INT8:
			return copy<int8_t, int16_t>(index, values, offset, size);
		case Type::UINT16:
			return copy<uint16_t, int16_t>(index, values, offset, size);
		case Type::INT16:
			return copy<int16_t, int16_t>(index, values, offset, size);
		case Type::UINT32:
			return copy<uint32_t, int16_t>(index, values, offset, size);
		case Type::INT32:
			return copy<int32_t, int16_t>(index, values, offset, size);
		case Type::UINT64:
			return copy<uint64_t, int16_t>(index, values, offset, size);
		case Type::INT64:
			return copy<int64_t, int16_t>(index, values, offset, size);
		case Type::FLOAT:
			return copy<float, int16_t>(index, values, offset, size);
		case Type::DOUBLE:
			return copy<double, int16_t>(index, values, offset, size);
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return 0;
		}
	}

	size_t Array::copy(size_t index, std::vector<uint32_t> const &values, size_t offset, size_t size)
	{
		switch (type_)
		{
		case Type::NONE:
			return 0;
		case Type::UINT8:
			return copy<uint8_t, uint32_t>(index, values, offset, size);
		case Type::INT8:
			return copy<int8_t, uint32_t>(index, values, offset, size);
		case Type::UINT16:
			return copy<uint16_t, uint32_t>(index, values, offset, size);
		case Type::INT16:
			return copy<int16_t, uint32_t>(index, values, offset, size);
		case Type::UINT32:
			return copy<uint32_t, uint32_t>(index, values, offset, size);
		case Type::INT32:
			return copy<int32_t, uint32_t>(index, values, offset, size);
		case Type::UINT64:
			return copy<uint64_t, uint32_t>(index, values, offset, size);
		case Type::INT64:
			return copy<int64_t, uint32_t>(index, values, offset, size);
		case Type::FLOAT:
			return copy<float, uint32_t>(index, values, offset, size);
		case Type::DOUBLE:
			return copy<double, uint32_t>(index, values, offset, size);
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return 0;
		}
	}

	size_t Array::copy(size_t index, std::vector<int32_t> const &values, size_t offset, size_t size)
	{
		switch (type_)
		{
		case Type::NONE:
			return 0;
		case Type::UINT8:
			return copy<uint8_t, int32_t>(index, values, offset, size);
		case Type::INT8:
			return copy<int8_t, int32_t>(index, values, offset, size);
		case Type::UINT16:
			return copy<uint16_t, int32_t>(index, values, offset, size);
		case Type::INT16:
			return copy<int16_t, int32_t>(index, values, offset, size);
		case Type::UINT32:
			return copy<uint32_t, int32_t>(index, values, offset, size);
		case Type::INT32:
			return copy<int32_t, int32_t>(index, values, offset, size);
		case Type::UINT64:
			return copy<uint64_t, int32_t>(index, values, offset, size);
		case Type::INT64:
			return copy<int64_t, int32_t>(index, values, offset, size);
		case Type::FLOAT:
			return copy<float, int32_t>(index, values, offset, size);
		case Type::DOUBLE:
			return copy<double, int32_t>(index, values, offset, size);
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return 0;
		}
	}

	size_t Array::copy(size_t index, std::vector<uint64_t> const &values, size_t offset, size_t size)
	{
		switch (type_)
		{
		case Type::NONE:
			return 0;
		case Type::UINT8:
			return copy<uint8_t, uint64_t>(index, values, offset, size);
		case Type::INT8:
			return copy<int8_t, uint64_t>(index, values, offset, size);
		case Type::UINT16:
			return copy<uint16_t, uint64_t>(index, values, offset, size);
		case Type::INT16:
			return copy<int16_t, uint64_t>(index, values, offset, size);
		case Type::UINT32:
			return copy<uint32_t, uint64_t>(index, values, offset, size);
		case Type::INT32:
			return copy<int32_t, uint64_t>(index, values, offset, size);
		case Type::UINT64:
			return copy<uint64_t, uint64_t>(index, values, offset, size);
		case Type::INT64:
			return copy<int64_t, uint64_t>(index, values, offset, size);
		case Type::FLOAT:
			return copy<float, uint64_t>(index, values, offset, size);
		case Type::DOUBLE:
			return copy<double, uint64_t>(index, values, offset, size);
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return 0;
		}
	}

	size_t Array::copy(size_t index, std::vector<int64_t> const &values, size_t offset, size_t size)
	{
		switch (type_)
		{
		case Type::NONE:
			return 0;
		case Type::UINT8:
			return copy<uint8_t, int64_t>(index, values, offset, size);
		case Type::INT8:
			return copy<int8_t, int64_t>(index, values, offset, size);
		case Type::UINT16:
			return copy<uint16_t, int64_t>(index, values, offset, size);
		case Type::INT16:
			return copy<int16_t, int64_t>(index, values, offset, size);
		case Type::UINT32:
			return copy<uint32_t, int64_t>(index, values, offset, size);
		case Type::INT32:
			return copy<int32_t, int64_t>(index, values, offset, size);
		case Type::UINT64:
			return copy<uint64_t, int64_t>(index, values, offset, size);
		case Type::INT64:
			return copy<int64_t, int64_t>(index, values, offset, size);
		case Type::FLOAT:
			return copy<float, int64_t>(index, values, offset, size);
		case Type::DOUBLE:
			return copy<double, int64_t>(index, values, offset, size);
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return 0;
		}
	}

	size_t Array::copy(size_t index, std::vector<float> const &values, size_t offset, size_t size)
	{
		switch (type_)
		{
		case Type::NONE:
			return 0;
		case Type::UINT8:
			return copy<uint8_t, float>(index, values, offset, size);
		case Type::INT8:
			return copy<int8_t, float>(index, values, offset, size);
		case Type::UINT16:
			return copy<uint16_t, float>(index, values, offset, size);
		case Type::INT16:
			return copy<int16_t, float>(index, values, offset, size);
		case Type::UINT32:
			return copy<uint32_t, float>(index, values, offset, size);
		case Type::INT32:
			return copy<int32_t, float>(index, values, offset, size);
		case Type::UINT64:
			return copy<uint64_t, float>(index, values, offset, size);
		case Type::INT64:
			return copy<int64_t, float>(index, values, offset, size);
		case Type::FLOAT:
			return copy<float, float>(index, values, offset, size);
		case Type::DOUBLE:
			return copy<double, float>(index, values, offset, size);
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return 0;
		}
	}

	size_t Array::copy(size_t index, std::vector<double> const &values, size_t offset, size_t size)
	{
		switch (type_)
		{
		case Type::NONE:
			return 0;
		case Type::UINT8:
			return copy<uint8_t, double>(index, values, offset, size);
		case Type::INT8:
			return copy<int8_t, double>(index, values, offset, size);
		case Type::UINT16:
			return copy<uint16_t, double>(index, values, offset, size);
		case Type::INT16:
			return copy<int16_t, double>(index, values, offset, size);
		case Type::UINT32:
			return copy<uint32_t, double>(index, values, offset, size);
		case Type::INT32:
			return copy<int32_t, double>(index, values, offset, size);
		case Type::UINT64:
			return copy<uint64_t, double>(index, values, offset, size);
		case Type::INT64:
			return copy<int64_t, double>(index, values, offset, size);
		case Type::FLOAT:
			return copy<float, double>(index, values, offset, size);
		case Type::DOUBLE:
			return copy<double, double>(index, values, offset, size);
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return 0;
		}
	}

	size_t Array::bytes() const
	{
		switch (type_)
		{
		case Type::NONE:
			return 0;
		case Type::UINT8:
			return sizeof(uint8_t);
		case Type::INT8:
			return sizeof(int8_t);
		case Type::UINT16:
			return sizeof(uint16_t);
		case Type::INT16:
			return sizeof(int16_t);
		case Type::UINT32:
			return sizeof(uint32_t);
		case Type::INT32:
			return sizeof(int32_t);
		case Type::UINT64:
			return sizeof(uint64_t);
		case Type::INT64:
			return sizeof(int64_t);
		case Type::FLOAT:
			return sizeof(float);
		case Type::DOUBLE:
			return sizeof(double);
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return 0;
		}
	}

	size_t Array::size() const
	{
		switch (type_)
		{
		case Type::NONE:
			return 0;
		case Type::UINT8:
			return size<uint8_t>();
		case Type::INT8:
			return size<int8_t>();
		case Type::UINT16:
			return size<uint16_t>();
		case Type::INT16:
			return size<int16_t>();
		case Type::UINT32:
			return size<uint32_t>();
		case Type::INT32:
			return size<int32_t>();
		case Type::UINT64:
			return size<uint64_t>();
		case Type::INT64:
			return size<int64_t>();
		case Type::FLOAT:
			return size<float>();
		case Type::DOUBLE:
			return size<double>();
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return 0;
		}
	}

	Array::Type Array::type() const
	{
		return type_;
	}

	const void *Array::data(size_t index) const
	{
		switch (type_)
		{
		case Type::NONE:
			return nullptr;
		case Type::UINT8:
			return to<uint8_t>().data() + index;
		case Type::INT8:
			return to<int8_t>().data() + index;
		case Type::UINT16:
			return to<uint16_t>().data() + index * 2;
		case Type::INT16:
			return to<int16_t>().data() + index * 2;
		case Type::UINT32:
			return to<uint32_t>().data() + index *4;
		case Type::INT32:
			return to<int32_t>().data() + index * 4;
		case Type::UINT64:
			return to<uint64_t>().data() + index * 8;
		case Type::INT64:
			return to<int64_t>().data() + index * 8;
		case Type::FLOAT:
			return to<float>().data() + index * 4;
		case Type::DOUBLE:
			return to<double>().data() + index * 8;
		default:
			std::cerr << "support array type: " << static_cast<uint32_t>(type_ )<< std::endl;
			return nullptr;
		}
	}
}