#pragma once
#include "../OWOAPI/Controller/OWO.h"

using namespace OWOGame;

class MockDevice : public OWO 
{
public:
    MockDevice() : OWO(nullptr) {}
    ~MockDevice() {}
    uniquePtr <Sensation> WhatFelt;
    MusclesGroup WhereFelt = MusclesGroup({});

    void Configure(sharedPtr<GameAuth> auth) override;
    void Send(uniquePtr<OWOGame::Sensation> sensation) override;
    void Stop() override;
    OWOGame::ConnectionState UpdateStatus(uint64_t timeInMs) override;
    OWOGame::ConnectionState AutoConnect() override;
    OWOGame::ConnectionState Connect(owoVector<owoString> ip) override;
    owoVector<owoString> DiscoveredApps() override;
    void Scan(uint64_t timeInMs) override;
    void Disconnect() override;
    ConnectionState State() override;

    void ChangeUpdateFrequency(uint64_t newFrequency) override;

    bool DidFeelIn(Muscle muscle);
    bool DidFeelWithoutMuscles(uniquePtr<Sensation> sensation);
};