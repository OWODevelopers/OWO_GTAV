#pragma once
#include "ConsoleLogger.h"
#include <string>
#include <ShlObj.h>

class Debug 
{
private:
	static CConsoleLoggerEx logger;
	static bool isLogging;

	

public:
	static std::string LoggerPath() {
		PWSTR path;
		SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path);
		int length = WideCharToMultiByte(CP_UTF8, 0, path, -1, NULL, 0, NULL, NULL);
		char* pathBuffer = new char[length];
		WideCharToMultiByte(CP_UTF8, 0, path, -1, pathBuffer, length, NULL, NULL);

		std::string loggerPath = pathBuffer;
		loggerPath += "/FiveM/FiveM.app/plugins/ConsoleLoggerHelper.exe";

		return loggerPath;
	}

	static bool Exists(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

	static void Start() {
		if(!Exists(LoggerPath())) return;

		isLogging = true;
		logger.Create("Logger");
	}

	static void Log(char* text) 
	{
		if (!isLogging) return;

		logger.cprintf(text);
	}

	static void LogString(std::string text) 
	{
		if (!isLogging) return;

		text += "\n";
		logger.cprintf(text.c_str());
	}
};