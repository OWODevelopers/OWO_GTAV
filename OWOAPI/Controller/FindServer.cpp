// Copyright (C) 2023 OWO Games - All Rights Reserved
#include "FindServer.h"

bool OWOGame::FindServer::Contains(owoVector<owoString> input, owoString token)
{
    bool isInList = false;

    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == token)
            isInList = true;
    }

    return isInList;
}

void OWOGame::FindServer::Connect()
{
    if (!Contains(addressee, lastServer) && !Contains(addressee, "255.255.255.255")) return;

    if (IsUniqueConnection()) notifyAbscense->Execute(gameId);
    network->Connect(lastServer);
}

void OWOGame::FindServer::Initialize(owoVector<owoString> newAddressee, owoString newAuth, owoString newGameId)
{
    this->addressee = newAddressee;
    this->auth = newAuth;
    this->gameId = newGameId;

    network->Initialize();
    network->SetState(OWOGame::ConnectionState::Connecting);

    for (owoString candidate : candidates->GetCandidates()) {
       
        if(Contains(addressee, candidate))  sendAuth->Execute(auth, candidate);
    }
}

void OWOGame::FindServer::ListenForDisconnection()
{
    if (lastResponse != "OWO_Close" || lastServer != network->GetConnectedAddressee()[0]) return;

    network->SetState(OWOGame::ConnectionState::Connecting);
}

bool OWOGame::FindServer::IsUniqueConnection()
{
    return addressee.size() == 1;
}

void OWOGame::FindServer::UpdateStatus(owoString currentAddressee)
{
    if (lastResponse.empty()) notifyPresence->Execute(currentAddressee);

    else if (lastResponse == PRESENCE_NOTIFICATION)
    {
        candidates->Store(lastServer);
        sendAuth->Execute(auth, currentAddressee);
    }
    else if (lastResponse == VERIFICATION_RESPONSE) Connect();
}

void OWOGame::FindServer::Execute()
{
    lastResponse = network->Listen(lastServer);

    if (network->GetState() == OWOGame::ConnectionState::Connected && IsUniqueConnection()) ListenForDisconnection();
    else {
        for (int i = 0; i < addressee.size(); i++)
            UpdateStatus(addressee[i]);
    }
}

void OWOGame::FindServer::Scan()
{
    network->Initialize();
    lastResponse = network->Listen(lastServer);

    if (lastResponse.empty()) notifyPresence->Execute("255.255.255.255");

    else if (lastResponse == PRESENCE_NOTIFICATION)
    {
        candidates->Store(lastServer);
    }
}

OWOGame::FindServer::~FindServer()
{
    delete notifyPresence;
    delete sendAuth;
    delete notifyAbscense;
    delete candidates;
}