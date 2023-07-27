#include <sstream>

#include "./color.h"


Color::Color()
	: r_(0.0f),
	g_(0.0f),
	b_(0.0f)
{
}

Color::Color(const Color& color)
	: r_(color.r_),
	g_(color.g_),
	b_(color.b_)
{
}

Color::Color(Color&& color)
	: r_(color.r_),
	g_(color.g_),
	b_(color.b_)
{
	color.r_ = 0.0f;
	color.g_ = 0.0f;
	color.b_ = 0.0f;
}

Color::Color(float r, float g, float b)
	: r_(r),
	g_(g),
	b_(b)
{
}

Color::~Color()
{
}

Color& Color::operator=(const Color& color)
{
	r_ = color.r_;
	g_ = color.g_;
	b_ = color.b_;
	return *this;
}

Color& Color::operator=(Color&& color)
{
	r_ = color.r_;
	g_ = color.g_;
	b_ = color.b_;

	color.r_ = 0.0f;
	color.g_ = 0.0f;
	color.b_ = 0.0f;
	return *this;
}

Color Color::operator*(float scalar)
{
	return Color(r_ * scalar, g_ * scalar, b_ * scalar);
}

Color& Color::operator*=(float scalar)
{
	r_ *= scalar;
	g_ *= scalar;
	b_ *= scalar;
	return *this;
}

Color Color::operator+(const Color& color)
{
	return Color(r_ + color.r_, g_ + color.g_, b_ + color.b_);
}

Color& Color::operator+=(const Color& color)
{
	r_ += color.r_;
	g_ += color.g_;
	b_ += color.b_;
	return *this;
}

std::string Color::to_string() const
{
	std::stringstream ss;
	ss << "(" << r_ << ", " << g_ << ", " << b_ << ")";
	return ss.str();
}

vec3 Color::ToVec3() const
{
	return vec3(r_, g_, b_);
}

std::ostream& operator<<(std::ostream& lhs, const Color& rhs)
{
	lhs << rhs.to_string();
	return lhs;
}