#include "OWO.h"

OWOGame::OWO::OWO(OWOGame::Client* client)
    : client(client), connect(OWOGame::Authenticate(client)), send(OWOGame::SendSensation(client)), stop(OWOGame::StopSensation(client))
{
    Configure(sharedPtr<GameAuth>(new GameAuth({}, "0")));
}

void OWOGame::OWO::Configure(sharedPtr<OWOGame::GameAuth> auth)
{
    connect.Configure(auth);
    send.Configure(auth);
    stop.Configure(auth);
}

OWOGame::ConnectionState OWOGame::OWO::UpdateStatus(uint64_t newTimeInMs)
{
    timeInMs = newTimeInMs;
    if (timeInMs - lastUpdate >= UPDATE_FREQUENCY)
    {
        lastUpdate = timeInMs;
        client->UpdateStatus();
    }
    return State();
}

void OWOGame::OWO::Scan(uint64_t newTimeInMs)
{
    if (newTimeInMs - lastUpdateScan >= UPDATE_FREQUENCY) {
        lastUpdateScan = newTimeInMs;
        client->Scan();
    }
}

void OWOGame::OWO::Send(uniquePtr<OWOGame::Sensation>sensation) { send.Execute(movePtr(sensation), timeInMs); }
void OWOGame::OWO::Stop()
{
    stop.Execute();
    send.ResetPriority();
}
OWOGame::ConnectionState OWOGame::OWO::AutoConnect() { return connect.AutoConnect(); }
OWOGame::ConnectionState OWOGame::OWO::Connect(owoVector<owoString> ip) { return connect.ManualConnect(ip); }
void OWOGame::OWO::Disconnect() { client->Disconnect(); }
OWOGame::ConnectionState OWOGame::OWO::State() { return client->State(); }
owoVector<owoString> OWOGame::OWO::DiscoveredApps() { return client->DiscoveredApps(); }

void OWOGame::OWO::ChangeUpdateFrequency(uint64_t newFrequency) { UPDATE_FREQUENCY = newFrequency; }

OWOGame::OWO::~OWO()
{
    delete client;
}