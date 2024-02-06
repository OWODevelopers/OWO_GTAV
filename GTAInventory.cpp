#include "GTAInventory.h"
#include "script.h"

int GTAInventory::CurrentAmmo()
{
    int ammo;
    WEAPON::GET_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), CurrentWeapon(), &ammo);

    return ammo;
}

int GTAInventory::CurrentWeapon()
{
    return WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::PLAYER_PED_ID());
}