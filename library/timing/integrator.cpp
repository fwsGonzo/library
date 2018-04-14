#include <library/timing/integrator.hpp>

namespace library
{
	Integrator::Integrator(double timestep)
	{
		this->timestep = timestep;
		this->currentTime = timer.getTime();
	}

	void Integrator::restart()
	{
		timer.restart();
		this->currentTime = 0.0;
	}

	void Integrator::integrate()
	{
		double timeElapsed = timer.getTime();

    const double step = this->timestep / game_speed;
		while (timeElapsed >= currentTime + step)
		{
			if (timeStep(step, this->currentTime))
				break;

			this->currentTime += step;
		}
	}

}
