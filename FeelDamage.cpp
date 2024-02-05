#include "FeelDamage.h"
#include "../OWOAPI/Domain/SensationsFactory.h"

int IntensityOf(int healthDifference) {
	return OWOGame::Math::Clamp(healthDifference, 20, 100);
}

void FeelDamage::Execute(int health)
{
	if (health < lastHealth)
	{
		owo->Send(body->DamageFelt()->WithMuscles(body->LastHit().WithIntensity(IntensityOf(lastHealth - health))));
	}

	lastHealth = health;
}