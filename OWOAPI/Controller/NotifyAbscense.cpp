#include "NotifyAbscense.h"

void OWOGame::NotifyAbscense::Execute(owoString gameId)
{
    for (owoString candidate : keys->GetCandidates())
    {
        network->SendTo(gameId + "*GAMEUNAVAILABLE", candidate);
    }
}