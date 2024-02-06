#include "HapticDevice.h"

void MockDevice::Configure(sharedPtr<GameAuth> auth)
{

}

void MockDevice::Send(uniquePtr<OWOGame::Sensation> sensation)
{
	WhatFelt = movePtr(sensation);
	if(WhatFelt->ToString().find('|') != -1)
		WhereFelt = dynamic_cast<SensationWithMuscles*>(WhatFelt.get())->muscles;
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
		if (muscle.ToString() == aMuscle.ToString()) 
			return true;
	}

	return false;
}

bool MockDevice::DidFeelWithoutMuscles(uniquePtr<Sensation> sensation)
{
	if (WhatFelt->ToString().find('|') != -1)
		return dynamic_cast<SensationWithMuscles*>(WhatFelt.get())->reference->ToString() == sensation->ToString();

	return WhatFelt->ToString() == sensation->ToString();
}

bool MockDevice::DidFeelAnything()
{
	return WhatFelt != nullptr;
}
