#include "SensationOfWeapons.h"
#include "../OWOAPI/Domain/SensationsParser.h"

bool SensationOfWeapons::ContainsWeapon(int which) 
{
    for (auto weapon : weapons)
    {
        if (weapon == which) 
            return true;
    }

    return false;
}

uniquePtr<OWOGame::Sensation> SensationOfWeapons::ToBeFelt()
{
    return OWOGame::SensationsParser::Parse(toBeFelt);
}