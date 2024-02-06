#pragma once
#include <vector>
#include <types.h>
#include "../OWOAPI/Domain/Sensation.h"
#include "../OWOAPI/Domain/SensationsFactory.h"

class SensationOfWeapons 
{
public:
	std::vector<Hash> weapons = { };
	sharedPtr<OWOGame::Sensation> toBeFelt = nullptr;

	SensationOfWeapons(std::vector<Hash> weapons, sharedPtr<OWOGame::Sensation> sensation)
		:  weapons(weapons), toBeFelt(sensation) {}

	static SensationOfWeapons Melee() 
	{
		return SensationOfWeapons({}, OWOGame::SensationsFactory::Create());
	}
};