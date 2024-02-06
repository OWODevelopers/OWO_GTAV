#include "SensationOfWeapons.h"
#include "../OWOAPI/Domain/SensationsParser.h"

bool SensationOfWeapons::ContainsWeapon(int which) {
    return true;
}

uniquePtr<OWOGame::Sensation> SensationOfWeapons::ToBeFelt()
{
    return OWOGame::SensationsParser::Parse(toBeFelt);
}
