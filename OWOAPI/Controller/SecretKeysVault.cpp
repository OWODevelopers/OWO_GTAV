#include "SecretKeysVault.h"

using namespace OWOGame;

void ConnectionCandidatesCollection::Store(owoString addressee)
{
    if (!addressee.empty())
        appCandidates.insert(addressee);
}

bool ConnectionCandidatesCollection::ContainsCandidate(owoString candidate) { return appCandidates.count(candidate) > 0; }

owoVector<owoString> ConnectionCandidatesCollection::GetCandidates()
{
    owoVector<owoString> result;

    for (auto const& address : appCandidates) {
        result.push_back(address);
    }

    return result;
}

void OWOGame::ConnectionCandidatesCollection::Clear()
{
    appCandidates.clear();
}
