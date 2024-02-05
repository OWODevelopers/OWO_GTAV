#include "SensationWithMuscles.h"

OWOGame::SensationWithMuscles::SensationWithMuscles(sharedPtr<OWOGame::Sensation> reference, OWOGame::MusclesGroup muscles) :
    reference(reference), muscles(muscles) {}

float OWOGame::SensationWithMuscles::TotalDuration() { return reference->TotalDuration(); }

owoString OWOGame::SensationWithMuscles::ToString()
{
    owoStringStream result;
    result << (reference->ToString()) << ("|") << (muscles.ToString());

    return result.str();
}

uniquePtr<OWOGame::Sensation> OWOGame::SensationWithMuscles::WithMuscles(owoVector<OWOGame::Muscle> newMuscles)
{
    return this->Clone();
}

uniquePtr<OWOGame::Sensation> OWOGame::SensationWithMuscles::Clone()
{
    auto result = CreateNewUnique(SensationWithMuscles, SensationWithMuscles(reference, muscles));
    result->SetPriority(this->GetPriority());
    return result;
}