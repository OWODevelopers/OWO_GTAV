#include "MusclesGroup.h"

OWOGame::MusclesGroup OWOGame::MusclesGroup::WithIntensity(int intensity)
{
    owoVector<OWOGame::Muscle> result;

    for (OWOGame::Muscle muscle : muscles)
    {
        result.push_back(muscle.WithIntensity(intensity));
    }

    return OWOGame::MusclesGroup(result);
}

owoString OWOGame::MusclesGroup::ToString()
{
    owoStringStream result;
    result << muscles[0].ToString();

    for (int i = 1; i < muscles.size(); i++)
    {
        result << (",") << (muscles[i].ToString());
    }

    return result.str();
}

OWOGame::MusclesGroup OWOGame::MusclesGroup::Front()
{
    return MusclesGroup({ Muscle::Pectoral_R(),Muscle::Pectoral_L(),
    Muscle::Abdominal_R(),Muscle::Abdominal_L(),
    Muscle::Arm_R(),Muscle::Arm_L() });
}

OWOGame::MusclesGroup OWOGame::MusclesGroup::Back()
{
    return  MusclesGroup({ Muscle::Dorsal_R(),Muscle::Dorsal_L(),
            Muscle::Lumbar_R(),Muscle::Lumbar_L() });
}

OWOGame::MusclesGroup OWOGame::MusclesGroup::All()
{
    return  MusclesGroup({ Muscle::Pectoral_R(),Muscle::Pectoral_L(),
     Muscle::Abdominal_R(),Muscle::Abdominal_L(),
     Muscle::Arm_R(),Muscle::Arm_L(),
     Muscle::Dorsal_R(),Muscle::Dorsal_L(),
     Muscle::Lumbar_R(),Muscle::Lumbar_L() });
}