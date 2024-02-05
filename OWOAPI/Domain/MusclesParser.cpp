#include "MusclesParser.h"
#include "Exceptions.h"
#include "String.h"

static OWOGame::Muscle ParseMuscle(owoString value)
{
    auto parameters = OWOGame::String::Split(value, '%');

    return OWOGame::Muscle(stoi(parameters[0]), stoi(parameters[1]));
}

OWOGame::MusclesGroup OWOGame::MusclesParser::Parse(owoString value)
{
    owoVector<OWOGame::Muscle> result;
    owoVector<owoString> muscles = OWOGame::String::Split(value, ',');

    for (owoString muscle : muscles)
        result.push_back(ParseMuscle(muscle));

    return OWOGame::MusclesGroup(result);
}