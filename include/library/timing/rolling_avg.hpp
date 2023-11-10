#ifndef LIBRARY_TIMING_ROLLING_AVG_HPP
#define LIBRARY_TIMING_ROLLING_AVG_HPP

#include "timer.hpp"
#include <functional>
#include <numeric>
#include <vector>

namespace library
{
class RollingAvg
{
public:
	using time_t = Timer::time_t;
	using callback_t = std::function<void(RollingAvg&)>;

	RollingAvg() = default;

	/// @brief Report measurements after given sample count
	/// @param samples Sample count before report
	/// @param cb Callback to invoke after sample count reached
	RollingAvg(size_t samples, callback_t cb)
		: m_count(samples), m_cb(std::move(cb)) {}

	//! \brief start measuring
	void begin();
	//! \brief take measurement, in high-precision seconds
	void measure();

	//! \brief returns average seconds elapsed
	time_t average() const noexcept;

	//! \brief Sorts samples and returns median seconds elapsed
	time_t median();

	time_t highest() const noexcept;

	time_t lowest() const noexcept;

	void clear_samples() noexcept { samples.clear(); }
	size_t sample_count() const noexcept { return samples.size(); }

private:
	std::vector<time_t> samples;
	Timer      m_timer;
	size_t     m_count = 0;
	callback_t m_cb = nullptr;
};

class ScopedRollingAvg
{
public:
	ScopedRollingAvg(RollingAvg& ra) : m_ra(ra) { m_ra.begin(); }
	~ScopedRollingAvg() {
		m_ra.measure();
	}

private:
	RollingAvg& m_ra;
};

inline void RollingAvg::begin() { m_timer.restart(); }

// returns time elapsed in high-precision seconds
inline void RollingAvg::measure() {
	samples.push_back(m_timer.getTime());

	if (this->m_count > 0 && samples.size() % this->m_count == 0) {
		this->m_cb(*this);
	}
}

inline RollingAvg::time_t RollingAvg::average() const noexcept
{
	if (samples.empty()) return 0.0;
	return std::accumulate(samples.begin(), samples.end(), 0.0) / samples.size();
}

inline RollingAvg::time_t RollingAvg::median()
{
	std::sort(samples.begin(), samples.end());
	return samples.at(samples.size() / 2);
}

inline RollingAvg::time_t RollingAvg::highest() const noexcept
{
	return *std::max_element(samples.begin(), samples.end());
}

inline RollingAvg::time_t RollingAvg::lowest() const noexcept
{
	return *std::min_element(samples.begin(), samples.end());
}

} // library

#endif
