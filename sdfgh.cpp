#include "sdfgh.h"
#include "../OWOAPI/Domain/SensationsFactory.h"


void sdfgh::Execute(int hp)
{
	if (hp < lastHealth)
	{
		owo->Send(OWOGame::SensationsFactory::Create()->WithMuscles(body->LastHit().WithIntensity(20)));
	}

	lastHealth = hp;
}