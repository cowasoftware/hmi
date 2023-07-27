#pragma once

#include <functional>
#include <sstream>
#include <cstdio>
#include <cstdint>

class ClockUtil
{
public:
	using RunCall = std::function<void()>;

public:
	static std::string runTime(RunCall call, int count = 1);
	static int64_t fps();
};