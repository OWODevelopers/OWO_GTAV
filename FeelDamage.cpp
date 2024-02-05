#include "FeelDamage.h"
#include "../OWOAPI/Domain/SensationsFactory.h"

void FeelDamage::Execute(int health)
{
	if (health < lastHealth)
	{
		owo->Send(body->DamageFelt()->WithMuscles(body->LastHit().WithIntensity(OWOGame::Math::Clamp(lastHealth - health, 20, 100))));
	}

	lastHealth = health;
}