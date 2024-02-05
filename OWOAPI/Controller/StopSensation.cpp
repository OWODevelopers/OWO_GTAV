#include "StopSensation.h"

OWOGame::StopSensation::StopSensation(OWOGame::Client* client) : client(client) {}

void OWOGame::StopSensation::Execute()
{
    if (!client->IsConnected()) return;

    client->Send(game->id + "*STOP");
}

void OWOGame::StopSensation::Configure(sharedPtr<OWOGame::GameAuth> newGame) { this->game = newGame; }