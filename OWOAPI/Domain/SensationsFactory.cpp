#include "SensationsFactory.h"

uniquePtr<OWOGame::MicroSensation> OWOGame::SensationsFactory::Create(int frequency, float duration, int intensity, float rampUp, float rampDown, float exitTime, owoString name, int priority)
{
    auto sensation = CreateNewUnique(OWOGame::MicroSensation, OWOGame::MicroSensation(frequency, duration, intensity, rampUp, rampDown, exitTime, name));
    sensation->SetPriority(priority);

    return sensation;
}