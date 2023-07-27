#pragma once

template <typename MemberOfWhichClass, typename primative>
class readonly
{
	friend MemberOfWhichClass;

public:
	inline operator primative const& () const { return x; }

	inline bool operator==(const primative& y) const { return x == y; }
	inline primative operator+(const primative& y) const { return x + y; }
	inline primative operator-(const primative& y) const { return x - y; }
	inline primative operator*(const primative& y) const { return x * y; }
	inline primative operator/(const primative& y) const { return x / y; }
	inline primative operator<<(const primative& y) const { return x << y; }
	inline primative operator>>(const primative& y) const { return x >> y; }
	inline primative operator^(const primative& y) const { return x ^ y; }
	inline primative operator|(const primative& y) const { return x | y; }
	inline primative operator&(const primative& y) const { return x & y; }
	inline primative operator&&(const primative& y) const { return x && y; }
	inline primative operator||(const primative& y) const { return x || y; }
	inline primative operator~() const { return ~x; }

protected:
	inline primative* operator->() { return &x; }
	inline primative const* operator->() const { return &x; }

protected:
	inline readonly& operator=(const primative& y)
	{
		x = y;
		return *this;
	}
	inline readonly& operator+=(const primative& y)
	{
		x += y;
		return *this;
	}

	inline readonly& operator-=(const primative& y)
	{
		x -= y;
		return *this;
	}
	inline readonly& operator*=(const primative& y)
	{
		x *= y;
		return *this;
	}
	inline readonly& operator/=(const primative& y)
	{
		x /= y;
		return *this;
	}
	inline readonly& operator&=(const primative& y)
	{
		x &= y;
		return *this;
	}
	inline readonly& operator|=(const primative& y)
	{
		x |= y;
		return *this;
	}
	primative x;
};
