#include "Debug.h"
#include "ConsoleColor.h"

#include <iostream>
#include <stdio.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace Chorus
{
    bool Debug::shouldLog;
	void Debug::Init()
	{
      shouldLog=true;
	}
    void Debug::ShouldLog(bool value)
    {
      shouldLog=value;
    }

	void Debug::RedirectConsole()
	{
		freopen ("CON","w",stdout);
		freopen ("CON","w",stderr);
	}

	void Debug::RedirectFile()
	{
		freopen ("stdout.txt","w",stdout);
		freopen ("stderr.txt","w",stderr);
	}

	void Debug::Error(const char *outputString)
	{
		// poop stuff out to a file!

      if(shouldLog)
		std::cerr << red  << outputString << std::endl;
	}
	void Debug::Error(const std::string& string)
    {
      if(shouldLog)
		std::cerr << red << string << std::endl;
	}

	void Debug::Log(const char *outputString)
	{
		// poop stuff out to a file!

      if(shouldLog)
		std::cout << white << outputString << std::endl;
	}

	void Debug::Log(bool boolean)
    {
      if(shouldLog)
		std::cout << white << (boolean?"true":"false") << std::endl;
	}

	void Debug::Log(int num)
    {
      if(shouldLog)
		std::cout << white << num << std::endl;
	}

	void Debug::Log(long num)
    {
      if(shouldLog)
		std::cout << white << num << std::endl;
	}

	void Debug::Log(float num)
    {
      if(shouldLog)
		std::cout << white << num << std::endl;
	}

	void Debug::Log(double num)
    {
      if(shouldLog)
		std::cout << white << num << std::endl;
	}

	void Debug::Log(const Vec2D& vec)
    {
      if(shouldLog)
		std::cout << white << "Vector2: (" << vec.x << ", " << vec.y << ")" << std::endl;
	}

	void Debug::Log(const Vec3D& vec)
    {
      if(shouldLog)
		std::cout << white << "Vector3: (" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
	}

	void Debug::Log(const std::string& string)
    {
      if(shouldLog)
		std::cout << white << string << std::endl;
	}
}