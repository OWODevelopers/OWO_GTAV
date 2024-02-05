#include "MicroSensationParser.h"

owoString NameOf(owoString value)
{
    owoVector<owoString> parameters = OWOGame::String::Split(value, ',');

    return parameters.size() >= 7 ? parameters[6] : "";
}

uniquePtr< OWOGame::MicroSensation> OWOGame::MicroSensationParser::Parse(owoString value)
{
    auto parameters = OWOGame::String::Split(value, ',');

    return CreateNewUnique(OWOGame::MicroSensation, OWOGame::MicroSensation(stoi(parameters[0]),
        stof(parameters[1]) / 10,
        stoi(parameters[2]),
        stof(parameters[3]) / 1000,
        stof(parameters[4]) / 1000,
        stof(parameters[5]) / 10,
        NameOf(value)));
}