#pragma once

#include <string>
#include <windows.h>
#include <iostream>

#include "ChorusCore.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

namespace Chorus
{
	class Debug
	{
    private:
      static bool shouldLog;
	public:
		static void Init();
        static void ShouldLog(bool value);
		static void RedirectConsole();
		static void RedirectFile();
		static void Error(const char *string);
		static void Error(const std::string& string);
		static void Log(const char *string);
		static void Log(bool boolean);
		static void Log(int num);
		static void Log(long num);
		static void Log(float num);
		static void Log(double num);
		static void Log(const Vec2D& vec);
		static void Log(const Vec3D& vec);
		static void Log(const std::string& string);
	};
	
#define LOG Debug::Log
#define ERR Debug::Error
}
