#include "ScanAvailableServers.h"

void OWOGame::NotifyPresence::Execute(owoString addressee)
{
    network->SendTo(PRESENCE_MESSAGE, addressee);
}
