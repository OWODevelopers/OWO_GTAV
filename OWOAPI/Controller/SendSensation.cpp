#include "SendSensation.h"

OWOGame::SendSensation::SendSensation(OWOGame::Client* client) : client(client) {}

bool OWOGame::SendSensation::IsPlaying(uint64_t timeSinceStart) { return  timeSinceStart < whenPreviousSensationEnds; }

void OWOGame::SendSensation::Execute(uniquePtr<OWOGame::Sensation> sensation, uint64_t timeSinceStart)
{
    if (!client->IsConnected()) return;
    if (sensation->GetPriority() < lastPriority && IsPlaying(timeSinceStart)) return;

    lastPriority = sensation->GetPriority();
    whenPreviousSensationEnds = timeSinceStart + (uint64_t)(sensation->TotalDuration() * 1000);
    client->Send(game->id + "*SENSATION*" + sensation->ToString());
}

void OWOGame::SendSensation::ResetPriority() { whenPreviousSensationEnds = 0; }

void OWOGame::SendSensation::Configure(sharedPtr<OWOGame::GameAuth> newGame) { this->game = newGame; }