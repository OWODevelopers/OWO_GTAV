#include "BakedSensationsParser.h"

bool OWOGame::BakedSensationsParser::CanParse(owoString value)
{
    return (!OWOGame::String::Contains(value, ',') && !OWOGame::String::Contains(value, '|')) ||
        OWOGame::String::Contains(value, '~');
}

owoString GetIcon(owoString value)
{
    auto parameters = OWOGame::String::Split(value, '~');

    return parameters.size() >= 4 ? parameters[3] : "";
}

uniquePtr<OWOGame::BakedSensation> OWOGame::BakedSensationsParser::Parse(owoString value)
{
    if (!OWOGame::String::Contains(value, '~'))
        return CreateNewUnique(OWOGame::BakedSensation, OWOGame::BakedSensation(stoi(value), (owoString)"", SensationsFactory::Create()));

    auto parameters = OWOGame::String::Split(value, '~');

    return CreateNewUnique(OWOGame::BakedSensation, OWOGame::BakedSensation(stoi(parameters[0]), parameters[1], OWOGame::SensationsParser::Parse(parameters[2]), GetIcon(value), parameters.size() < 5 ? "" : parameters[4]));
}