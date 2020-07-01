#pragma once
#pragma once
#include <iostream>    // printf()
#include <chrono>
using namespace std;

class muTimer
{
	using Clock = std::chrono::high_resolution_clock;
	bool active = false;
	Clock::duration   duration_;
	Clock::time_point start_ = Clock::now(), stop_ = Clock::now();

	muTimer(const muTimer&) = delete;
	muTimer& operator=(const muTimer&) = delete;
public:
	using ns = std::chrono::nanoseconds;
	using mks = std::chrono::microseconds;
	using ms = std::chrono::milliseconds;
	muTimer() { reset(); start(); }
	~muTimer() = default;
	muTimer& reset()
	{
		duration_ = std::chrono::nanoseconds(0);
		active = false;
		return *this;
	}
	muTimer& start()
	{
		if (!active)
		{
			start_ = Clock::now();
			active = true;
		}
		return *this;
	}
	muTimer& stop()
	{
		if (active)
		{
			stop_ = Clock::now();
			duration_ += stop_ - start_;
			active = false;
		}
		return *this;
	}
	template<typename T = mks>
	unsigned long long duration()
	{
		return static_cast<unsigned long long>
			(std::chrono::duration_cast<T>(stop_ - start_).count());
	}
};