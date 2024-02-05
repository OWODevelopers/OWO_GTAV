#include "BakedSensation.h"

OWOGame::BakedSensation::BakedSensation(int id, owoString name, uniquePtr< Sensation> reference, owoString icon, owoString family)
    : id(id), name(name), reference(movePtr(reference)), icon(icon), family(family) {}

uniquePtr< OWOGame::BakedSensation> OWOGame::BakedSensation::WithIcon(owoString newIcon)
{
    return CreateNewUnique(OWOGame::BakedSensation, OWOGame::BakedSensation(id, name, movePtr(reference), newIcon));
}

owoString OWOGame::BakedSensation::ToString() {
    return owoToString(id);
}

uniquePtr<OWOGame::Sensation> OWOGame::BakedSensation::WithMuscles(owoVector<Muscle> muscles)
{
    if (muscles.size() <= 0) return uniquePtr<Sensation>(this);

    auto result = CreateNewUnique(OWOGame::SensationWithMuscles, OWOGame::SensationWithMuscles(this->Clone(), MusclesGroup(muscles)));
    result->SetPriority(this->GetPriority());
    return result;
}

float OWOGame::BakedSensation::TotalDuration()
{
    return reference->TotalDuration();
}

uniquePtr<OWOGame::Sensation> OWOGame::BakedSensation::Clone()
{
    auto result = CreateNewUnique(BakedSensation, BakedSensation(id, name, movePtr(reference), icon));
    result->SetPriority(this->GetPriority());
    return result;
}

owoString OWOGame::BakedSensation::Stringify()
{
    owoStringStream result;

    result << owoToString(id) << ("~") << (name) << ("~") << (reference->ToString()) << ("~") << (icon) << ("~") << family;

    return result.str();
}