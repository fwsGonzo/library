#include <library/timing/integrator.hpp>

namespace library
{
Integrator::Integrator(double timestep)
{
    this->timestep = timestep;
    this->timeZero = timer.getTime();
}

void Integrator::integrator_resume()
{
    // set timer.getTime() - timeZero == currentTime
    // NOTE: don't modify currentTime
    this->timeZero = timer.getTime() - currentTime;
}

void Integrator::integrator_restart()
{
    this->timeZero = timer.getTime();
    this->currentTime = 0.0;
}

void Integrator::integrate()
{
    double elapsed = timer.getTime() - this->timeZero;

    const double step = this->timestep / game_speed;
    while (elapsed >= currentTime + step)
    {
        if (timeStep(step, this->currentTime)) break;

        this->currentTime += step;
    }
}

} // namespace library
