#ifndef LIBRARY_TIMER_HPP
#define LIBRARY_TIMER_HPP

#include <chrono>

namespace library
{
	class Timer
	{
	public:
		typedef double time_t;

		//! \brief constructor sets t0 to the current time
		inline Timer();

		//! \brief returns the time (in fractional seconds) between the last getDeltaTime()
		//! function call, or time since object was instantiated (whichever happened last)
		inline time_t getTime() const;

		//! \brief returns time elapsed, and sets new time, so
		//! all future rounds and deltas are calculated from new time point
		inline time_t restart();

	private:
		std::chrono::steady_clock::time_point t0;
	};

  inline Timer::Timer()
	{
		// the starting time, which is updated at each "interval"
		t0 = std::chrono::high_resolution_clock::now();
	}

	// returns time elapsed in high-precision seconds
	Timer::time_t Timer::getTime() const
	{
    using namespace std::chrono;
		auto t1 = high_resolution_clock::now();
		auto micros = duration_cast<microseconds>(t1 - t0);

		// return high-precision seconds
		return micros.count() / 1e6f;
	}

	// defines an interval change, and returns the time between last call
	// in high-precision seconds
	Timer::time_t Timer::restart()
	{
    using namespace std::chrono;
		auto t1 = high_resolution_clock::now();
		auto micros = duration_cast<microseconds>(t1 - t0);

		// set last time = this time
		t0 = t1;
		// return high-precision seconds
		return micros.count() / 1e6f;
	}
}

#endif
