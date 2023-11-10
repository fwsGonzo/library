#ifndef LIBRARY_TIMING_TIMER_HPP
#define LIBRARY_TIMING_TIMER_HPP

#include <chrono>
#ifdef __linux__
#include <time.h>
#endif

namespace library
{
class Timer
{
public:
    typedef double time_t;

    //! \brief constructor sets t0 to the current time
    Timer() { this->restart(); }

    //! \brief returns the time (in seconds) since construction
    time_t getTime() const;

    //! \brief sets new time t0
    void restart();

#ifdef __linux__
	static timespec time_now()
	{
		timespec t;
		clock_gettime(CLOCK_MONOTONIC_RAW, &t);
		return t;
	}
	static double nanodiff(timespec start_time, timespec end_time)
	{
		return (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) * 1e-9;
	}
#endif

private:
#ifdef __linux__
	timespec t0;
#else
    std::chrono::high_resolution_clock::time_point t0;
#endif
};

// returns time elapsed in high-precision seconds
inline Timer::time_t Timer::getTime() const
{
#ifdef __linux__
	return nanodiff(t0, time_now());
#else
    using namespace std::chrono;
    auto t1 = high_resolution_clock::now();

    // return high-precision seconds
    return duration<double>{t1 - t0}.count();
#endif
}

// defines an interval change, and returns the time between last call
// in high-precision seconds
inline void Timer::restart()
{
    using namespace std::chrono;
#ifdef __linux__
	t0 = time_now();
#else
    t0 = high_resolution_clock::now();
#endif
}
} // library

#endif
