#include "FeelDamage.h"
#include "../OWOAPI/Domain/SensationsFactory.h"

int IntensityOf(int healthDifference) {
	return OWOGame::Math::Clamp(healthDifference, 65, 100);
}

void FeelDamage::Execute(int health)
{
	if (health < lastHealth)
	{
		auto sensation = body->DamageFelt()->WithMuscles(body->LastHit().WithIntensity(IntensityOf(lastHealth - health)));
		sensation->SetPriority(FeelDamage::Priority);
		owo->Send(movePtr(sensation));
	}

	lastHealth = health;
}