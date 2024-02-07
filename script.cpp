#include "OWOAPI/Controller/OWO.h"
#include "script.h"
#include "OWOAPI/Domain/SensationsFactory.h"
#include "consoleLogger.h"
#include "GTAPlayer.h"
#include "FeelDamage.h"
#include "GTAInventory.h"
#include "FeelRecoil.h"
#include "Debug.h"
#include "OWOAPI/Domain/MusclesParser.h"

using namespace OWOGame;

double magnitude(double x, double y, double z) {
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

MusclesGroup JoinMuscles(MusclesGroup left, MusclesGroup right) {
	return MusclesParser::Parse(left.ToString() + "," + right.ToString());
}


int main() {

	//Colisiones desde el vehículo
	//Frenar
	// 
	//! Aceleración inicial.

	sharedPtr<OWOGame::OWO> instance = OWOGame::OWO::Create<OWOGame::UDPNetwork>();
	instance->Configure(OWOGame::GameAuth::Parse("0~Melee~100,3,90,0,200,0,~impact-2~Impacts#1~Bullet~30,1,100,0,0,0,&65,4,100,0,400,0,~impact-8~Impacts#2~Explosive~65,8,85,0,800,0,|0%100,1%100,5%100,2%100,3%100,4%100,6%100,7%100,8%100,9%100~impact-6~Impacts#3~Fall~100,1,100,0,0,1,&40,6,50,0,600,0,~environment-5~Impacts#4~Drown~100,2,80,100,100,0,|0%100,1%100,3%70,2%71~environment-0~Impacts#5~Deafult~40,1,50,0,0,2,|9%100,8%100,0%100,1%100,2%100,3%100,4%100,5%100,6%100,7%100&40,1,40,0,0,0,|9%100,8%100,0%100,1%100,2%100,3%100,4%100,5%100,6%100,7%100~impact-7~Impacts#7~Warning~63,1,47,0,0,2,|9%100,8%100&63,1,47,0,0,0,|9%100,8%100~weapon-0~#6~Vehicle~100,1,75,0,0,0,|0%100,2%100,4%100,6%100,8%100&100,11,75,0,1100,0,|0%100,2%100,4%100,6%100,8%100~impact-7~Impacts#8~Pistol~55,1,60,0,100,0,Recoil|4%100,5%72~weapon-2~Recoil#9~SMG~20,1,50,0,0,0,|4%100,5%100~weapon-3~Recoil#10~Shotgun~100,1,70,0,0,0,|5%100,4%100&57,3,69,0,300,0,|4%100,5%100~weapon-0~Recoil#11~Heavy~100,10,100,0,1000,0,|5%100,4%100~weapon-0~Recoil#12~Shoot~10,1,19,0,0,0,|5%100,4%100~weapon-2~Recoil"));
	
	auto player = std::shared_ptr<GTAPlayer>(new GTAPlayer({ SensationOfWeapons::Melee(), SensationOfWeapons::Bullet(), SensationOfWeapons::Explosive() }));
	auto inventory = std::shared_ptr<GTAInventory>(new GTAInventory());
	auto feelDamage = FeelDamage(instance, player);
	auto feelRecoil = FeelRecoil(instance, inventory, {SensationOfWeapons::Pistol(),  SensationOfWeapons::SMG(), SensationOfWeapons::Heavy(), SensationOfWeapons::MiniGun(), SensationOfWeapons::Shotgun()});

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

			if (PED::GET_VEHICLE_PED_IS_IN(playerPed, false) != 0)
			{
				Vector3 speed = ENTITY::GET_ENTITY_SPEED_VECTOR(PED::GET_VEHICLE_PED_IS_IN(playerPed, FALSE), TRUE);
				auto velocity = magnitude(speed.x, speed.y, speed.z);
				std::string log = std::to_string(speed.x) + ", " + std::to_string(speed.y) + ", " + std::to_string(speed.z) + "\n";
				Debug::Log((char*)log.c_str());

				if (velocity > 3) 
				{
					MusclesGroup left = MusclesGroup({ Muscle::Arm_L(), Muscle::Pectoral_L(), Muscle::Abdominal_L() });
					MusclesGroup right = MusclesGroup({Muscle::Arm_R(), Muscle::Pectoral_R(), Muscle::Abdominal_R()});

					if (speed.x > 1.5)
						left = left.WithIntensity(50);
					else if (speed.x < -1.5)
						right = right.WithIntensity(50);

					instance->Send(OWOGame::SensationsFactory::Create(100, .2f, (velocity / 50) * 100)->WithMuscles(JoinMuscles(left, right)));
				}
			}

			if (PLAYER::IS_PLAYER_DEAD(PLAYER::GET_PLAYER_INDEX()) && !isDead)
			{
				auto sensation = SensationsParser::Parse("100,1,100,0,0,0,Death|0%100,1%100,2%100,3%100,4%100,5%100,6%100,7%100,8%100,9%100&45,30,90,0,500,0,Death|0%100,1%100,2%100,3%100,4%100,5%100,6%100,7%100,8%100,9%100");
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