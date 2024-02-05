// Copyright (C) 2023 OWO Games - All Rights Reserved
#include "ClientFactory.h"
#include "Controller/Client.h"

OWOGame::Client* OWOGame::ClientFactory::Create(OWOGame::Network* network)
{
    auto candidates = CreateNew(ConnectionCandidatesCollection());
    auto sendMessage = CreateNew(SendEncryptedMessage(network));
    auto notifyAbscense = CreateNew(NotifyAbscense(network, candidates));
    auto sendAuthMessage = CreateNew(SendAuthMessage(network, candidates));
    auto scanServers = CreateNew(NotifyPresence(network, candidates));

    auto findServer = CreateNew(FindServer
    (
        network, scanServers,
        notifyAbscense, sendAuthMessage, candidates
    ));

    return CreateNew(Client(network, sendMessage, findServer, candidates));
}