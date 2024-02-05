#include "SensationsSequence.h"

OWOGame::SensationsSequence::SensationsSequence(owoVector<sharedPtr<OWOGame::Sensation>> newSensations)
{
    for (const sharedPtr<Sensation>& sensation : newSensations)
    {
        sensations.push_back(sensation->Clone());
    }
}

float OWOGame::SensationsSequence::TotalDuration()
{
    float result = 0;

    for (int i = 0; i < sensations.size(); i++)
    {
        result += sensations[i]->TotalDuration();
    }

    return result;
}

owoString OWOGame::SensationsSequence::ToString()
{
    owoStringStream result;
    result << sensations[0]->ToString();

    for (int i = 1; i < sensations.size(); i++)
    {
        result << "&" << sensations[i]->ToString();
    }

    return result.str();
}

uniquePtr< OWOGame::Sensation> OWOGame::SensationsSequence::WithMuscles(owoVector<OWOGame::Muscle> muscles)
{
    owoVector<sharedPtr<Sensation>> references;

    for (const sharedPtr<Sensation>& sensation : sensations)
    {
        references.push_back(sensation->WithMuscles(muscles)->Clone());
    }

    auto result = CreateNewUnique(OWOGame::SensationsSequence, OWOGame::SensationsSequence(references));
    result->SetPriority(this->GetPriority());
    return result;
}

uniquePtr<OWOGame::Sensation> OWOGame::SensationsSequence::Clone()
{
    auto result = CreateNewUnique(SensationsSequence, SensationsSequence(sensations));
    result->SetPriority(this->GetPriority());
    return result;
}