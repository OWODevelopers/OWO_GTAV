#pragma once

struct VehicleEngine {

	double minVelocity = 0;
	double maxVelocity = 100;
	int minIntensity = 0;
	int maxIntensity = 0;

	VehicleEngine(double minVelocity, double maxVelocity, int minIntensity, int maxIntensity)
		: minVelocity(minVelocity), maxVelocity(maxVelocity), minIntensity(minIntensity), maxIntensity(maxIntensity) {}


	int IntensityAt(double velocity) 
	{
		if (velocity < minVelocity) return 0;

		return maxIntensity;
		//OWOGame::Math::Clamp(velocity, minIntensity, maxIntensity)
	}
};