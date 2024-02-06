#include "SensationOfWeapons.h"

bool SensationOfWeapons::HasSensationFor(Hash aWeapon)
{
    for (auto weapon : weapons)
    {
        if (weapon == aWeapon) return true;
    }

    return false;
}