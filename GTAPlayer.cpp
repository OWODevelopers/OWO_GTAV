#include "GTAPlayer.h"
#include "../OWOAPI/Domain/SensationsParser.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include <natives.h>
#include <types.h>


using namespace OWOGame;

const Ped& GTAPlayer::Player()
{
    return PLAYER::PLAYER_PED_ID();
}

MusclesGroup GetMusclesFrom(Hash bones) 
{
    switch (bones)
    {
    case 24817:
        return MusclesGroup({ Muscle::Pectoral_R(), Muscle::Pectoral_L()});
    case 40269:
        return MusclesGroup({ Muscle::Arm_R()});
    case 10706:
        return MusclesGroup({ Muscle::Arm_R() });
    case 45509:
        return MusclesGroup({ Muscle::Arm_L() });
    case 64729:
        return MusclesGroup({ Muscle::Arm_L() });
    case 24816:
        return MusclesGroup({ Muscle::Abdominal_R() });
    case 57597:
        return MusclesGroup({ Muscle::Abdominal_L() });
    case 24818:
        return MusclesGroup({ Muscle::Dorsal_R(),Muscle::Dorsal_L() });
    default:
        return MusclesGroup::All();
    }
}
MusclesGroup GetSideFrom(Hash bone) 
{
    switch (bone)
    {
    case 24817:
    case 40269:
    case 45509:
    case 24816:
    case 57597:
        return MusclesGroup::Front();
    case 10706:
        return MusclesGroup({ Muscle::Arm_R(), Muscle::Abdominal_R(), Muscle::Lumbar_R(), Muscle::Pectoral_R() });
    case 64729:
        return MusclesGroup({ Muscle::Arm_L(), Muscle::Abdominal_L(), Muscle::Lumbar_L(), Muscle::Pectoral_L() });
    case 24818:
        return MusclesGroup::Back();
    default:
        return MusclesGroup::All();
    }
}

MusclesGroup GTAPlayer::LastHit()
{
    Hash bone = 0;
    PED::GET_PED_LAST_DAMAGE_BONE(PLAYER::PLAYER_PED_ID(), &bone);

    switch (precision) {
    case Single:
        return GetMusclesFrom(bone);
    case Side:
        return GetMusclesFrom(bone);
    case General:
        return MusclesGroup::All();
    }
}

uniquePtr<Sensation> GTAPlayer::DamageFelt()
{
    if (WEAPON::HAS_PED_BEEN_DAMAGED_BY_WEAPON(PLAYER::PLAYER_PED_ID(), 0, 2)) 
    {
        precision = Single;
        for (int i = 0; i < weapons.size(); i++)
        {
            for (auto weapon : weapons[i].weapons)
            {
                if (WEAPON::HAS_PED_BEEN_DAMAGED_BY_WEAPON(PLAYER::PLAYER_PED_ID(), weapon, 0))
                    return SensationsParser::Parse(weapons[i].toBeFelt);
            }
        }

        return SensationsParser::Parse("5");
    }

    if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(Player())) 
    {
        precision = Side;
        return SensationsParser::Parse("6");
    }

    if (PED::IS_PED_RAGDOLL(Player())) 
    {
        precision = Side;
        return SensationsParser::Parse("3");
    }

    if (ENTITY::IS_ENTITY_IN_WATER(Player()))
        return SensationsParser::Parse("4");

    return SensationsParser::Parse("5");
}