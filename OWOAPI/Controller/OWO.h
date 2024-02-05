#pragma once
#include "../Domain/GameAuth.h"
#include "Authenticate.h"
#include "SendSensation.h"
#include "StopSensation.h"
#include "../ClientFactory.h"
#include "../Infraestructure/UDPNetwork.h"



namespace OWOGame {

    class OWO
    {
    private:
        Client* client;
        Authenticate connect;
        SendSensation send;
        StopSensation stop;
        uint64_t lastUpdate = 0;
        uint64_t lastUpdateScan = 0;
        uint64_t timeInMs = 0;
        uint64_t UPDATE_FREQUENCY = 500;

    public:
        OWO(Client* client);
        ~OWO();

        virtual void Configure(sharedPtr<GameAuth> auth);
        virtual void Send(uniquePtr<OWOGame::Sensation> sensation);
        virtual void Stop();
        virtual OWOGame::ConnectionState UpdateStatus(uint64_t timeInMs);
        virtual OWOGame::ConnectionState AutoConnect();
        virtual OWOGame::ConnectionState Connect(owoVector<owoString> ip);
        virtual owoVector<owoString> DiscoveredApps();
        virtual void Scan(uint64_t timeInMs);
        virtual void Disconnect();
        virtual ConnectionState State();

        virtual void ChangeUpdateFrequency(uint64_t newFrequency);

        template<typename T = Network> static uniquePtr<OWO> Create()
        {
            return CreateNewUnique(OWO, OWO(ClientFactory::Create(CreateNew(T))));
        };
    };
}