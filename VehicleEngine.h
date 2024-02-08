#pragma once

struct VehicleEngine {

	double minVelocity = 0;
	double maxVelocity = 100;
	double minIntensity = 0;
	double maxIntensity = 0;

	VehicleEngine(double minVelocity, double maxVelocity, double minIntensity, double maxIntensity)
		: minVelocity(minVelocity), maxVelocity(maxVelocity), minIntensity(minIntensity), maxIntensity(maxIntensity) {}

};