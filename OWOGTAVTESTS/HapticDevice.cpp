#include "HapticDevice.h"
#include "../OWOAPI/Domain/String.h"

bool MockDevice::HasMuscles()
{
	return WhatFelt->ToString().find('|') != -1;
}

void MockDevice::Configure(sharedPtr<GameAuth> auth)
{

}

void MockDevice::Send(uniquePtr<OWOGame::Sensation> sensation)
{
	WhatFelt = movePtr(sensation);
	if (HasMuscles())
		WhereFelt = dynamic_cast<SensationWithMuscles*>(WhatFelt.get())->muscles;

	sensationsFelt++;
}

void MockDevice::Stop()
{
}

OWOGame::ConnectionState MockDevice::UpdateStatus(uint64_t timeInMs)
{
	return OWOGame::ConnectionState::Connected;
}

OWOGame::ConnectionState MockDevice::AutoConnect()
{
	return OWOGame::ConnectionState::Connected;
}

OWOGame::ConnectionState MockDevice::Connect(owoVector<owoString> ip)
{
	return OWOGame::ConnectionState::Connected;
}

owoVector<owoString> MockDevice::DiscoveredApps()
{
	return owoVector<owoString>();
}

void MockDevice::Scan(uint64_t timeInMs)
{
}

void MockDevice::Disconnect()
{
}

ConnectionState MockDevice::State()
{
	return ConnectionState::Connected;
}

void MockDevice::ChangeUpdateFrequency(uint64_t newFrequency)
{
}

bool MockDevice::DidFeelIn(Muscle aMuscle)
{
	for (Muscle muscle : (owoVector<Muscle>)WhereFelt)
	{
		if (muscle.ToString()[0] == aMuscle.ToString()[0])
			return true;
	}

	return false;
}

bool MockDevice::DidFeelInEvery(MusclesGroup allMuscles)
{
	return WhereFelt.ToString()[0] == allMuscles.ToString()[0];
}

bool MockDevice::DidFeelWithoutMuscles(uniquePtr<Sensation> sensation)
{
	if (HasMuscles())
		return dynamic_cast<SensationWithMuscles*>(WhatFelt.get())->reference->ToString() == sensation->ToString();

	return WhatFelt->ToString() == sensation->ToString();
}

bool MockDevice::DidFeelAnything()
{
	return WhatFelt != nullptr;
}

int MockDevice::IntensityOfLastFelt()
{
	return std::stoi(OWOGame::String::Split(WhatFelt->ToString(), ',')[2]);
}

int MockDevice::HowManyFelt()
{
	return sensationsFelt;
}

int MockDevice::IntensityOf(Muscle muscle)
{
	for (auto aMuscle : (std::vector<Muscle>)WhereFelt) {

		if (aMuscle.ToString()[0] == muscle.ToString()[0]) 
			return std::stoi(OWOGame::String::Split(aMuscle.ToString(), '%')[1]);
	}

	throw std::exception("No hay músculo");
}
