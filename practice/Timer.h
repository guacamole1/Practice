#pragma once
#include <iostream>    // printf()
#include <chrono>
using namespace std;

class Stopwatch
{
	using Clock = std::chrono::high_resolution_clock;
	bool active = false;
	Clock::duration   duration_;
	Clock::time_point start_ = Clock::now(), stop_ = Clock::now();

	Stopwatch(const Stopwatch&) = delete;
	Stopwatch& operator=(const Stopwatch&) = delete;
public:
	using ns = std::chrono::nanoseconds;
	using mks = std::chrono::microseconds;
	using ms = std::chrono::milliseconds;
	Stopwatch() { reset(); start(); }
	~Stopwatch() = default;
	Stopwatch& reset();
	Stopwatch& start();
	Stopwatch& stop();
	template<typename T = mks>
	unsigned long long duration()
	{
		return static_cast<unsigned long long>
			(std::chrono::duration_cast<T>(stop_ - start_).count());
	}
};