#include "SensationsCollection.h"
#include "OWOAPI/Domain/SensationsParser.h"

const string SensationsCollection::AuthId = "90113769";

const string SensationsCollection::Default = "6~Deafult~40,1,50,0,0,2,|9%100,8%100,0%100,1%100,2%100,3%100,4%100,5%100,6%100,7%100&40,1,40,0,0,0,|9%100,8%100,0%100,1%100,2%100,3%100,4%100,5%100,6%100,7%100~impact-7~Impacts";
const string SensationsCollection::Bullet = "2~Bullet~30,1,100,0,0,0,&65,4,100,0,400,0,~impact-8~Impacts";
const string SensationsCollection::Drowning = "5~Drown~100,2,80,100,100,0,|0%100,1%100,3%70,2%71~environment-0~Impacts";
const string SensationsCollection::Explosive = "3~Explosive~65,8,85,0,800,0,|0%100,1%100,5%100,2%100,3%100,4%100,6%100,7%100,8%100,9%100~impact-6~Impacts";
const string SensationsCollection::Fall = "4~Fall~100,1,100,0,0,1,&40,6,50,0,600,0,~environment-5~Impacts";
const string SensationsCollection::Heavy = "11~Heavy~100,10,55,0,1000,0,|5%100,4%100~weapon-0~Recoil";
const string SensationsCollection::Melee = "1~Melee~100,3,90,0,200,0,~impact-2~Impacts";
const string SensationsCollection::Pistol = "8~Pistol~55,1,35,0,100,0,Recoil|4%100,5%72~weapon-2~Recoil";
const string SensationsCollection::Shoot = "12~Shoot~10,1,20,0,0,0,|5%100,4%100~weapon-2~Recoil";
const string SensationsCollection::Shotgun = "10~Shotgun~100,1,45,0,0,0,|5%100,4%100&57,3,45,0,300,0,|4%100,5%100~weapon-0~Recoil";
const string SensationsCollection::Vehicle= "7~Vehicle~100,1,75,0,0,0,&100,11,75,0,1100,0,~impact-7~Impacts";
const string SensationsCollection::SMG = "9~SMG~20,1,40,0,0,1,|4%100,5%100~weapon-3~Recoil";
const string SensationsCollection::Assault = "13~Assault~50,1,35,0,0,2,|0%100,5%100,4%100,1%40~weapon-3~Recoil";
const string SensationsCollection::Launcher = "14~Launcher~100,2,50,200,0,0,|5%100,4%100,1%100,0%100&100,3,70,0,300,0,|0%100,1%100,5%100,4%100~weapon-2~Recoil";
const string SensationsCollection::Warning = "0~Warning~63,1,47,0,0,2,|9%100,8%100&63,1,47,0,0,0,|9%100,8%100~weapon-0~";
const string SensationsCollection::Death = "15~Death~100,1,60,0,0,1,|0%100,1%100,2%100,3%100,4%100,5%100,6%100,7%100,8%100,9%100~health-3~";


owoVector<owoString> SensationsCollection::All =
{
    Warning,
    Melee,
    Bullet,
    Explosive,
    Fall,
    Drowning,
    Default,
    Vehicle,
    Pistol,
    SMG,
    Shotgun,
    Heavy,
    Shoot,
    Assault,
    Launcher,
    Death
};

uniquePtr<Sensation> Parse(owoString theSensation, int priority)
{
    auto sensation = SensationsParser::Parse(theSensation);
    sensation->SetPriority(priority);
    return sensation;
}

uniquePtr<Sensation> SensationsCollection::Get(owoString theSensation, int withPriority)
{
    if (theSensation.find("~") == owoString::npos)
    {
        return Parse(theSensation, withPriority);
    }

    for (auto& sensation : All)
    {
        if (sensation != theSensation) continue;

        return Parse(theSensation, withPriority);
    }

    throw std::exception("Sensation not found");
}

sharedPtr<GameAuth> SensationsCollection::Auth()
{
    owoStringStream sensations;

    for (auto sensation : All) 
    {
        sensations << sensation << "#";
    }

    return GameAuth::Parse(sensations.str(), AuthId);
}
