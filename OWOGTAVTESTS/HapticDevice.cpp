#include "HapticDevice.h"

void HapticDevice::Configure(sharedPtr<GameAuth> auth)
{

}

void HapticDevice::Send(uniquePtr<OWOGame::Sensation> sensation)
{
}

void HapticDevice::Stop()
{
}

OWOGame::ConnectionState HapticDevice::UpdateStatus(uint64_t timeInMs)
{
	return OWOGame::ConnectionState::Connected;
}

OWOGame::ConnectionState HapticDevice::AutoConnect()
{
	return OWOGame::ConnectionState::Connected;
}

OWOGame::ConnectionState HapticDevice::Connect(owoVector<owoString> ip)
{
	return OWOGame::ConnectionState::Connected;
}

owoVector<owoString> HapticDevice::DiscoveredApps()
{
	return owoVector<owoString>();
}

void HapticDevice::Scan(uint64_t timeInMs)
{
}

void HapticDevice::Disconnect()
{
}

ConnectionState HapticDevice::State()
{
	return ConnectionState::Connected;
}

void HapticDevice::ChangeUpdateFrequency(uint64_t newFrequency)
{
}