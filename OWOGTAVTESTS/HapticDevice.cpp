#include "HapticDevice.h"

void MockDevice::Configure(sharedPtr<GameAuth> auth)
{

}

void MockDevice::Send(uniquePtr<OWOGame::Sensation> sensation)
{
	Received = movePtr(sensation);
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