#include "kjhsfdgkis.h"

bool erjdlfas::HasSensationFor(Hash aWeapon)
{
    for (auto weapon : weapons)
    {
        if (weapon == aWeapon) return true;
    }

    return false;
}