#include "sdfgh.h"
#include "../OWOAPI/Domain/SensationsFactory.h"


void sdfgh::Execute(int hp)
{
	if (hp < lastHealth)
	{
		owo->Send(OWOGame::SensationsFactory::Create());
	}
	lastHealth = hp;
}