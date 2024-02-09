#include "OWOAPI/Controller/OWO.h"
#include "script.h"
#include "OWOAPI/Domain/SensationsFactory.h"
#include "consoleLogger.h"
#include "GTAPlayer.h"
#include "GTAVehicle.h"
#include "FeelDamage.h"
#include "GTAInventory.h"
#include "FeelRecoil.h"
#include "FeelDriving.h"
#include "Debug.h"
#include "OWOAPI/Domain/MusclesParser.h"
#include "SensationsCollection.h"

using namespace OWOGame;

int main() {
	sharedPtr<OWOGame::OWO> instance = OWOGame::OWO::Create<OWOGame::UDPNetwork>();
	instance->Configure(SensationsCollection::Auth());
	
	auto player = std::shared_ptr<GTAPlayer>(new GTAPlayer({ SensationOfWeapons::Melee(), SensationOfWeapons::Bullet(), SensationOfWeapons::Explosive() }));
	auto inventory = std::shared_ptr<GTAInventory>(new GTAInventory());
	auto vehicle = std::shared_ptr<GTAVehicle>(new GTAVehicle());
	auto feelDamage = FeelDamage(instance, player);
	auto feelRecoil = FeelRecoil(instance, inventory, {SensationOfWeapons::Pistol(),  SensationOfWeapons::SMG(), SensationOfWeapons::Heavy(), SensationOfWeapons::MiniGun(), SensationOfWeapons::Shotgun()});
	auto feelDriving = FeelDriving(instance, vehicle, IntensityLerp(3, 50, 10, 50), IntensityLerp(10, 50, 20, 90), IntensityLerp(1, 6, 40, 90));
	Debug::Start();

	bool isDead = false;

	while (true)
	{
		if (IsKeyDown(VK_F3)) 
		{
			Debug::Log("Connecting...");
			instance->AutoConnect();
		}

		if (instance->State() == OWOGame::ConnectionState::Connected) 
		{
			int playerPed = PLAYER::PLAYER_PED_ID();
			feelDamage.Execute(ENTITY::GET_ENTITY_HEALTH(playerPed) + PED::GET_PED_ARMOUR(playerPed));
			feelRecoil.Execute();
			feelDriving.Execute();

			if (PLAYER::IS_PLAYER_DEAD(PLAYER::GET_PLAYER_INDEX()) && !isDead)
			{
				auto sensation = SensationsCollection::Get(SensationsCollection::Death);
				sensation->SetPriority(5);
				instance->Send(movePtr(sensation));
				isDead = true;
			}
			else if(!PLAYER::IS_PLAYER_DEAD(PLAYER::GET_PLAYER_INDEX())) 
			{
				isDead = false;
			}
		}		

		instance->UpdateStatus(GetTickCount64());

		WAIT(80);
	}

	return 0;
}

void ScriptMain() {
	srand(GetTickCount());
	throw main();
}