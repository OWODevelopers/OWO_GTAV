#include "Microsensation.h"
#include "BakedSensation.h"

OWOGame::MicroSensation::MicroSensation(int frequency, float duration, int intensity, float rampUp, float rampDown, float exitTime, owoString name)
    : frequency(OWOGame::Math::Clamp(frequency, 1, 100)),
    duration(OWOGame::Math::Clamp(duration, 0.1f, 20.f)),
    intensity(OWOGame::Math::Clamp(intensity, 0, 100)),
    rampUp(OWOGame::Math::Clamp(rampUp, 0.f, 2.f)),
    rampDown(OWOGame::Math::Clamp(rampDown, 0.f, 2.f)),
    exitTime(OWOGame::Math::Clamp(exitTime, 0.f, 2.f)),
    name(name)
{}

owoString OWOGame::MicroSensation::ToString() {
    owoStringStream result;

    result << owoToString(frequency) << (",")
        << (owoToString((int)(duration * 10))) << (",")
        << (owoToString(intensity)) << (",")
        << (owoToString((int)(rampUp * 1000))) << (",")
        << (owoToString((int)(rampDown * 1000))) << (",")
        << (owoToString((int)(exitTime * 10))) << (",")
        << ((owoString)name);

    return result.str();
}

uniquePtr<OWOGame::Sensation> OWOGame::MicroSensation::WithMuscles(owoVector<OWOGame::Muscle> muscles)
{
    if (muscles.size() <= 0) return uniquePtr<OWOGame::Sensation>(this->Clone());

    auto result = CreateNewUnique(OWOGame::SensationWithMuscles, OWOGame::SensationWithMuscles(this->Clone(), OWOGame::MusclesGroup(muscles)));
    result->SetPriority(this->GetPriority());
    return result;
}

uniquePtr<OWOGame::Sensation> OWOGame::MicroSensation::Clone()
{
    auto clone = CreateNewUnique(OWOGame::Sensation, OWOGame::MicroSensation(frequency, duration, intensity, rampUp, rampDown, exitTime, name));
    clone->SetPriority(this->GetPriority());
    return clone;
}

float OWOGame::MicroSensation::TotalDuration() { return duration + exitTime; }