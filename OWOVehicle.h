#pragma once

class Vehicle {

public:
	virtual int Velocity() = 0;
	virtual bool DrivingForward() = 0;
	virtual bool IsDriving() = 0;
};