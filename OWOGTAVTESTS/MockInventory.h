#pragma once
#include "../PlayerInventory.h"
#include "../OWOAPI/Domain/SensationsFactory.h"

class MockInventory : public PlayerInventory{
public:
	int ammo = 0;
	int currentWeapon = 0;
	uniquePtr<OWOGame::Sensation> toBeFelt = OWOGame::SensationsFactory::Create()->WithMuscles({OWOGame::Muscle::Pectoral_R()});

	int CurrentAmmo() override;
	int CurrentWeapon() override;
};