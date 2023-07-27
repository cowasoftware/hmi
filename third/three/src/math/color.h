#pragma once

#include <cstdint>
#include <iostream>
#include "./vector.h"

class Color
{
public:
	Color();
	Color(const Color& color);
	Color(Color&& color);
	explicit Color(float r, float g, float b);
	virtual ~Color();

public:
	float GetR() const { return r_; };
	float GetG() const { return g_; };
	float GetB() const { return b_; };

public:
	Color& operator=(const Color& color);
	Color& operator=(Color&& color);
	Color operator*(float scalar);
	Color& operator*=(float scalar);
	Color operator+(const Color& color);
	Color& operator+=(const Color& color);

public:
	std::string to_string() const;
	vec3 ToVec3() const;

private:
	float r_;
	float g_;
	float b_;
};

std::ostream& operator<<(std::ostream& lhs, const Color& rhs);