#include "MockBody.h"

OWOGame::MusclesGroup MockBody::LastHit()
{
    return muscleGroup;
}

uniquePtr<OWOGame::Sensation> MockBody::DamageFelt()
{
    return movePtr(damageSensation->Clone());
}
