#include "SendAuthMessage.h"

void OWOGame::SendAuthMessage::Execute(owoString auth, owoString addressee)
{
    if (addressee == "255.255.255.255")
    {
        for (owoString address : keys->GetCandidates())
        {
            network->SendTo(auth, address);
        }
    } else if (keys->ContainsCandidate(addressee))
        network->SendTo(auth, addressee);
}