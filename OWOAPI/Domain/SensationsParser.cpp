#include "SensationsParser.h"
#include "BakedSensationsParser.h"
#include "SensationWithMusclesParser.h"
#include "SensationsSequenceParser.h"
#include "MicroSensationParser.h"

uniquePtr<OWOGame::Sensation> CreateFrom(owoString value)
{
    if (OWOGame::BakedSensationsParser::CanParse(value))
    {
        return OWOGame::BakedSensationsParser::Parse(value);
    }
    else if (OWOGame::SensationsSequenceParser::CanParse(value))
    {
        return OWOGame::SensationsSequenceParser::Parse(value);
    }
    else if (OWOGame::SensationWithMusclesParser::CanParse(value))
    {
        return OWOGame::SensationWithMusclesParser::Parse(value);
    }

    return OWOGame::MicroSensationParser::Parse(value);
}

uniquePtr<OWOGame::Sensation> OWOGame::SensationsParser::Parse(owoString value, int priority)
{
    auto sensation = CreateFrom(value);
    sensation->SetPriority(priority);
    return sensation;
}