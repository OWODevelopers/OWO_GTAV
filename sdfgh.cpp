#include "sdfgh.h"
#include "../OWOAPI/Domain/SensationsFactory.h"


void sdfgh::Execute(int hp)
{
	owo->Send(OWOGame::SensationsFactory::Create());
}