#include "SendEncryptedMessage.h"

void OWOGame::SendEncryptedMessage::Execute(owoString message)
{
    if (network->GetConnectedAddressee().empty()) return;

    for (owoString address : network->GetConnectedAddressee())
    {
        network->SendTo(message, address);
    }
}