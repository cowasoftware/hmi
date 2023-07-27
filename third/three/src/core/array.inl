namespace three
{
	template <typename T>
	void Array::malloc(void const *values)
	{
		values_ = new std::vector<T>(*static_cast<std::vector<T> const *>(values));
	}

	template <typename T>
	void Array::malloc(std::vector<T> const &values)
	{
		values_ = new std::vector<T>(values);
	}

	template <typename T>
	void Array::malloc(std::vector<T> &&values)
	{
		values_ = new std::vector<T>(std::move(values));
	}

	template <typename T>
	void Array::free()
	{
		delete static_cast<std::vector<T> *>(values_);
	}

	template <typename T>
	void Array::assign(void const *values)
	{
		*static_cast<std::vector<T> *>(values_) = *static_cast<std::vector<T> const *>(values);
	}

	template <typename T>
	void Array::assign(std::vector<T> const &values)
	{
		*static_cast<std::vector<T> *>(values_) = values;
	}

	template <typename T1, typename T2>
	size_t Array::copy(size_t index, std::vector<T2> const &values, size_t offset, size_t size)
	{
		std::vector<T1> &v = *static_cast<std::vector<T1> *>(values_);

		if (index >= v.size() || offset >= values.size())
		{
			return 0;
		}

		auto size2 = std::min(v.size() - index, std::min(values.size() - offset, size));

		for (size_t i = 0; i < size2; i++)
		{
			v[index++] = static_cast<T1>(values[offset++]);
		}

		return size2;
	}

	template <typename T>
	size_t Array::size() const
	{
		return static_cast<std::vector<T> *>(values_)->size();
	}

	template <typename T>
	std::vector<T> const &Array::to() const
	{
		return *static_cast<std::vector<T> const *>(values_);
	}
}