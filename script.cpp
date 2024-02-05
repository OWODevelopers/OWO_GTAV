#include "OWOAPI/Controller/OWO.h"
#include "script.h"
#include "OWOAPI/Domain/SensationsFactory.h"
#include "consoleLogger.h"

int main() {

	CConsoleLoggerEx logger = CConsoleLoggerEx();
	logger.Create("Logger");
	sharedPtr<OWOGame::OWO> instance = OWOGame::OWO::Create<OWOGame::UDPNetwork>();
	
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