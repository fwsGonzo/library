#include <library/timing/integrator.hpp>

namespace library
{
	Integrator::Integrator(double timestep)
	{
		this->timestep = timestep;
		this->currentTime = timer.getDeltaTime();
	}
	
	void Integrator::integrate()
	{
		double timeElapsed = timer.getDeltaTime();
		
		while (timeElapsed >= currentTime + timestep)
		{
			timeStep(this->timestep, timeElapsed);
			
			this->currentTime += this->timestep;
		}
	}
	
}