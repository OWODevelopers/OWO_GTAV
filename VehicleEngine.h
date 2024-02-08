#pragma once

struct VehicleEngine {

	double minVelocity = 0;
	double maxVelocity = 100;
	int minIntensity = 0;
	int maxIntensity = 0;

	VehicleEngine(double minVelocity, double maxVelocity, int minIntensity, int maxIntensity)
		: minVelocity(minVelocity), maxVelocity(maxVelocity), minIntensity(minIntensity), maxIntensity(maxIntensity) {}

	float lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	float PercentageFrom(double velocity) 
	{
		return OWOGame::Math::Clamp(((velocity - minVelocity) / (maxVelocity - minVelocity)), (double) 0, (double) 1);
	}

	int IntensityAt(double velocity) 
	{
		if (velocity < minVelocity) return 0;
		if (velocity == minVelocity) return minIntensity;
		 
		return lerp(minIntensity, maxIntensity, PercentageFrom(velocity));
	}
};