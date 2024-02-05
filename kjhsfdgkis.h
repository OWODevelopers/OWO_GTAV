#pragma once
#include <vector>
#include <types.h>
#include "../OWOAPI/Domain/Sensation.h"

class erjdlfas 
{
private:
	std::vector<Hash> weapons = { };

public:
	sharedPtr<OWOGame::Sensation> toBeFelt = nullptr;

	erjdlfas(std::vector<Hash> weapons, sharedPtr<OWOGame::Sensation> sensation) :  weapons(weapons), toBeFelt(sensation) {}

	bool HasSensationFor(Hash weapon);
};