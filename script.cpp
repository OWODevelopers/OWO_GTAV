#include "OWOAPI/Controller/OWO.h"
#include "script.h"
#include "OWOAPI/Domain/SensationsFactory.h"
#include "consoleLogger.h"

int main() {

	CConsoleLoggerEx logger = CConsoleLoggerEx();
	logger.Create("Logger");
	sharedPtr<OWOGame::OWO> instance = OWOGame::OWO::Create<OWOGame::UDPNetwork>();
	instance->Configure(OWOGame::GameAuth::Parse("0~Melee~100,3,90,0,200,0,~impact-2~Impacts#1~Bullet~30, 1, 100, 0, 0, 0, & 20, 1, 100, 0, 0, 0, ~impact - 8~Impacts#2~Explosive~60, 8, 90, 200, 200, 0, | 0 % 100, 1 % 100, 5 % 100, 2 % 100, 3 % 100, 4 % 100, 6 % 100, 7 % 100, 8 % 100, 9 % 100~impact - 6~Impacts#3~Fall~100, 2, 80, 0, 0, 1, & 40, 3, 50, 0, 300, 0, ~environment - 5~Impacts#4~Drown~100, 2, 80, 100, 100, 0, | 0 % 100, 1 % 100, 3 % 100, 2 % 100~environment - 0~Impacts#5~Default~100, 1, 50, 0, 0, 1, | 9 % 100, 8 % 100 & 100, 1, 50, 0, 0, 0, | 9 % 100, 8 % 100~alert - 3~Impacts"));
	while (true)
	{
		WAIT(0);
	}

	return 0;
}

void ScriptMain() {
	srand(GetTickCount());
	throw main();
}