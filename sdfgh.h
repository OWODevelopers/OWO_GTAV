#pragma once
#include "OWOAPI/Controller/OWO.h"
#include "PlayerBody.h"

class sdfgh {
private:
	sharedPtr<OWOGame::OWO> owo = nullptr;
	sharedPtr<PlayerBody> body = nullptr;
	short lastHealth = 0;
public:
	sdfgh(sharedPtr<OWOGame::OWO> device, sharedPtr<PlayerBody> body) : owo(device), body(body){}

	void Execute(int hp);
};