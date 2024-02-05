#include "Authenticate.h"

OWOGame::Authenticate::Authenticate(OWOGame::Client* client) : client(client){}

void OWOGame::Authenticate::Configure(sharedPtr<OWOGame::GameAuth> newGame) { this->game = newGame; }

OWOGame::ConnectionState OWOGame::Authenticate::ManualConnect(owoVector<owoString> ip)
{
    if (client->State() == ConnectionState::Connected) return client->State();

    client->StartConnection(ip , AuthMessage(), game->id);
    return OWOGame::ConnectionState::Connecting;
}

OWOGame::ConnectionState OWOGame::Authenticate::AutoConnect() { return ManualConnect({ "255.255.255.255" }); }

owoString OWOGame::Authenticate::AuthMessage() { return game->id + "*AUTH*" + game->ToString(); }