#include "GameAuth.h"
#include "BakedSensationsParser.h"

owoVector<owoString> FilterByBaked(owoVector<owoString> all)
{
    owoVector<owoString> result;

    for (owoString sensation : all)
        if (sensation.find("~") != owoStringNpos)
            result.push_back(sensation);

    return result;
}

sharedPtr<OWOGame::GameAuth> OWOGame::GameAuth::Create(owoVector<owoString> sensations, owoString id)
{
    return sharedPtr<OWOGame::GameAuth>(CreateNew(GameAuth(FilterByBaked(sensations), id == "" ? "0" : id)));
}

sharedPtr<OWOGame::GameAuth> OWOGame::GameAuth::Parse(owoString value, owoString id)
{
    owoVector<owoString> parameters = OWOGame::String::Split(value, '#');
    owoVector<owoString> sensations;

    for (owoString parameter : parameters)
        sensations.push_back(parameter);

    return OWOGame::GameAuth::Create(sensations, id);
}

owoString OWOGame::GameAuth::ToString()
{
    if (sensations.size() <= 0) return "";

    owoStringStream result;
    result << sensations[0];

    for (int i = 1; i < sensations.size(); i++)
        result << "#" << sensations[i];

    return result.str();
}
