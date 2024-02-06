#pragma once
#include "ConsoleLogger.h"

class Debug 
{
private:
	static CConsoleLoggerEx logger;
public:
	static void Start() {
		logger.Create("Logger");
	}

	static void Log(char* text) 
	{
		logger.cprintf(text);
	}
};