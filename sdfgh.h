#pragma once
#include "OWOAPI/Controller/OWO.h"

class sdfgh {
private:
	sharedPtr<OWOGame::OWO> owo;
public:
	sdfgh(sharedPtr<OWOGame::OWO> owoPtr) { owo = owoPtr; }

	void Execute(int hp);
};