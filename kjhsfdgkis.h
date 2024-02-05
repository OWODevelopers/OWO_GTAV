#pragma once
#include <vector>
#include <types.h>
#include "../OWOAPI/Domain/Sensation.h"

class SensationOfWeapons 
{
public:
	std::vector<Hash> weapons = { };
	uniquePtr<OWOGame::Sensation> toBeFelt = nullptr;

	SensationOfWeapons(std::vector<Hash> weapons, uniquePtr<OWOGame::Sensation> sensation) 
		:  weapons(weapons), toBeFelt(movePtr(sensation)) {}

	bool HasSensationFor(Hash weapon);
};