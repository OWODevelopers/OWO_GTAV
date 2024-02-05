#include "GTAPlayer.h"
#include "../OWOAPI/Domain/SensationsFactory.h"
#include <natives.h>
#include <types.h>

//1. Sentir daño por arma
//2. Sentir daño por vehículo
//3. Sentir daño por caída
//4. Sentir por ahogamiento
//5. Sentir aviso de no implementada

using namespace OWOGame;

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

MusclesGroup GTAPlayer::LastHit()
{
    Hash bone = 0;
    PED::GET_PED_LAST_DAMAGE_BONE(PLAYER::PLAYER_PED_ID(), &bone);

    return GetMusclesFrom(bone);
}

uniquePtr<Sensation> GTAPlayer::DamageFelt()
{

    if (WEAPON::HAS_PED_BEEN_DAMAGED_BY_WEAPON(PLAYER::PLAYER_PED_ID(), 0, 2)) {
        for (auto weaponTypes : weapons)
        {
            for (auto weapon : weaponTypes.weapons)
            {
                if (WEAPON::HAS_PED_BEEN_DAMAGED_BY_WEAPON(PLAYER::PLAYER_PED_ID(), weapon, 0))
                    return movePtr(weaponTypes.toBeFelt);
            }
        }
    }

    
}