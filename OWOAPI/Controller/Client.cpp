// Copyright (C) 2023 OWO Games - All Rights Reserved
#include "Client.h"

void OWOGame::Client::UpdateStatus()
{
    if (State() == OWOGame::ConnectionState::Disconnected) return;

    findServer->Execute();
}

void OWOGame::Client::StartConnection(owoVector<owoString> addressee, owoString auth, owoString gameId)
{ 
    findServer->Initialize(addressee, auth, gameId);
}

void OWOGame::Client::Send(owoString message)
{
    sendMessage->Execute(message);
}

void OWOGame::Client::Scan() 
{
    if(State() != OWOGame::ConnectionState::Disconnected) return;
    
    findServer->Scan();
}

owoVector<owoString> OWOGame::Client::DiscoveredApps()
{
    return candidates->GetCandidates();
}

void OWOGame::Client::Disconnect() { network->Disconnect(); candidates->Clear(); }
bool OWOGame::Client::IsConnected() { return State() == OWOGame::ConnectionState::Connected; }
OWOGame::ConnectionState OWOGame::Client::State() { return network->GetState(); }

OWOGame::Client::~Client()
{
    delete network;
    delete sendMessage;
    delete findServer;
}