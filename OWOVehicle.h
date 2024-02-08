#pragma once

class OWOVehicle {

public:
	virtual int Velocity() = 0;
	virtual bool DrivingForward() = 0;
	virtual bool IsInVehicle() = 0;
};