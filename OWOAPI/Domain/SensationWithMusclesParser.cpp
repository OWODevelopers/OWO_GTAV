#include "SensationWithMusclesParser.h"

bool OWOGame::SensationWithMusclesParser::CanParse(owoString value)
{
    return OWOGame::String::Contains(value, '|');
}

uniquePtr<OWOGame::SensationWithMuscles> OWOGame::SensationWithMusclesParser::Parse(owoString value)
{
    auto parameters = OWOGame::String::Split(value, '|');

    return CreateNewUnique(OWOGame::SensationWithMuscles, OWOGame::SensationWithMuscles(OWOGame::SensationsParser::Parse(parameters[0]),
        OWOGame::MusclesParser::Parse(parameters[1])));
}