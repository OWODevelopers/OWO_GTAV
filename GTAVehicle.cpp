#include "GTAVehicle.h"
#include "script.h"
#include <corecrt_math.h>
#include <exception>
#include "Debug.h"

double magnitude(double x, double y, double z) {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

int GTAVehicle::Velocity()
{
    auto velocity = ENTITY::GET_ENTITY_SPEED_VECTOR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE), TRUE);
    return magnitude(velocity.x, velocity.y, velocity.z);
}

bool GTAVehicle::DrivingForward()
{
    auto velocity = ENTITY::GET_ENTITY_SPEED_VECTOR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE), TRUE);
    return velocity.y > 0;
}

bool GTAVehicle::IsDriving()
{
    return PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false) != 0;
}

int GTAVehicle::SteeringAmount()
{
    return ENTITY::GET_ENTITY_SPEED_VECTOR(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE), TRUE).x;
}
