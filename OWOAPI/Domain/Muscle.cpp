#include "Muscle.h"
#include "Muscle.h"

owoString OWOGame::Muscle::ToString()
{
    owoStringStream result;
    result << owoToString(position) << ("%") << (owoToString(intensity));
    return result.str();
}

OWOGame::Muscle OWOGame::Muscle::WithIntensity(int newIntensity) { return OWOGame::Muscle(position, OWOGame::Math::Clamp(newIntensity, 0, 100)); }

OWOGame::Muscle OWOGame::Muscle::Pectoral_R() { return  OWOGame::Muscle(0, 100); }
OWOGame::Muscle OWOGame::Muscle::Pectoral_L() { return  OWOGame::Muscle(1, 100); }
OWOGame::Muscle OWOGame::Muscle::Abdominal_R() { return  OWOGame::Muscle(2, 100); }
OWOGame::Muscle OWOGame::Muscle::Abdominal_L() { return  OWOGame::Muscle(3, 100); }
OWOGame::Muscle OWOGame::Muscle::Arm_R() { return  OWOGame::Muscle(4, 100); }
OWOGame::Muscle OWOGame::Muscle::Arm_L() { return  OWOGame::Muscle(5, 100); }
OWOGame::Muscle OWOGame::Muscle::Dorsal_R() { return  OWOGame::Muscle(6, 100); }
OWOGame::Muscle OWOGame::Muscle::Dorsal_L() { return  OWOGame::Muscle(7, 100); }
OWOGame::Muscle OWOGame::Muscle::Lumbar_R() { return  OWOGame::Muscle(8, 100); }
OWOGame::Muscle OWOGame::Muscle::Lumbar_L() { return  OWOGame::Muscle(9, 100); }

OWOGame::Muscle OWOGame::Muscle::operator+(Muscle addend)
{
    return Muscle(position).WithIntensity(intensity + addend.intensity);
}

OWOGame::Muscle OWOGame::Muscle::operator-(Muscle substracted)
{
    return Muscle(position).WithIntensity(intensity - substracted.intensity);
}
