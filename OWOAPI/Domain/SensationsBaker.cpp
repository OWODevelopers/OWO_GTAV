#include "SensationsBaker.h"

uniquePtr< OWOGame::BakedSensation> OWOGame::SensationsBaker::Bake(uniquePtr< OWOGame::Sensation> sensation, int id, owoString name)
{
    return CreateNewUnique(OWOGame::BakedSensation, OWOGame::BakedSensation(id, name, movePtr(sensation)));
}