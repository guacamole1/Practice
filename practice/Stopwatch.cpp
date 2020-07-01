#include "Stopwatch.h"

Stopwatch& Stopwatch::reset()
{
	duration_ = std::chrono::nanoseconds(0);
	active = false;
	return *this;
}

Stopwatch& Stopwatch::start()
{
	if (!active)
	{
		start_ = Clock::now();
		active = true;
	}
	return *this;
}

Stopwatch& Stopwatch::stop()
{
	if (active)
	{
		stop_ = Clock::now();
		duration_ += stop_ - start_;
		active = false;
	}
	return *this;
}