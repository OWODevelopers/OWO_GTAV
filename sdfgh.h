#pragma once
#include "OWOAPI/Controller/OWO.h"

class sdfgh {
private:
	sharedPtr<OWOGame::OWO> owo = nullptr;
	short lastHealth = 0;
public:
	sdfgh(sharedPtr<OWOGame::OWO> owoPtr) { owo = owoPtr; }

	void Execute(int hp);
};