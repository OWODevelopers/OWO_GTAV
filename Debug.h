#pragma once
#include "ConsoleLogger.h"
#include <string>

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

	static void LogString(std::string text) 
	{
		text += "\n";
		logger.cprintf(text.c_str());
	}
};