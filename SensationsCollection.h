#pragma once
#include <string>
#include "OWOAPI/Domain/Sensation.h"
#include "OWOAPI/Domain/GameAuth.h"

using namespace std;
using namespace OWOGame;

class SensationsCollection
{
public:
	static const string AuthId;

	static const string Default;
	static const string Death;
	static const string Warning;

	// Impacts
	static const string Bullet;
	static const string Drowning;
	static const string Explosive;
	static const string Fall;
	static const string Melee;
	static const string Vehicle;


	// Recoil
	static const string Heavy;
	static const string Pistol;
	static const string Shoot;
	static const string Shotgun;
	static const string SMG;
	static const string Assault;
	static const string Launcher;


	static owoVector<owoString> All;
	static uniquePtr<Sensation> Get(owoString theSensation, int priority = 0);
	static sharedPtr<GameAuth> Auth();
};