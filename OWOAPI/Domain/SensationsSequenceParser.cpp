#include "SensationsSequenceParser.h"

bool OWOGame::SensationsSequenceParser::CanParse(owoString value)
{
    return OWOGame::String::Contains(value, '&');
}

uniquePtr<OWOGame::SensationsSequence> OWOGame::SensationsSequenceParser::Parse(owoString value)
{
    owoVector<owoString> parameters = OWOGame::String::Split(value, '&');
    owoVector<sharedPtr<OWOGame::Sensation>> sensations;

    for (owoString sensation : parameters)
    {
       sensations.push_back(uniquePtr<Sensation>(OWOGame::SensationsParser::Parse(sensation)));
    }

    return CreateNewUnique(OWOGame::SensationsSequence, OWOGame::SensationsSequence(sensations));
}