#pragma once

struct VehicleCalculator {

	double minVelocity = 0;
	double maxVelocity = 100;
	int minIntensity = 0;
	int maxIntensity = 0;
	double minImpact = 0;
	double maxImpact = 100;
	int minimumImpactForce = 20;

	VehicleCalculator(double minVelocity = 0, double maxVelocity = 100, int minIntensity = 0, int maxIntensity = 100, double minImpact = 0, double maxImpact = 100, int minimumImpactForce = 20)
		: minVelocity(minVelocity), maxVelocity(maxVelocity), minIntensity(minIntensity), maxIntensity(maxIntensity),
			minImpact(minImpact), maxImpact(maxImpact), minimumImpactForce(minimumImpactForce){}

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
		 
		return lerp(minIntensity, maxIntensity, PercentageFrom(velocity));
	}

	int ImpactIntensity(double lastVelocity, double newVelocity)
	{
		return OWOGame::Math::Clamp(lastVelocity - newVelocity, minImpact, maxImpact);
	}

	bool ImpactStrongEnough(double lastVelocity, double newVelocity) {
		return ImpactIntensity(lastVelocity, newVelocity) > minimumImpactForce;
	}
};