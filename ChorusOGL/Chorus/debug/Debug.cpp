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
	FILE* Debug::stream;
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
		#ifdef _WIN32
		freopen_s (&stream,"CON","w",stdout);
		freopen_s (&stream,"CON","w",stderr);
		#endif
		#ifdef __unix__
		freopen ("/dev/tty","w",stdout);
		freopen ("/dev/tty","w",stderr);
		#endif
	}

	void Debug::RedirectFile()
	{
		#ifdef _WIN32
		freopen_s (&stream,"stdout.txt","w",stdout);
		freopen_s (&stream,"stderr.txt","w",stderr);
		#endif
		#ifdef __unix__
		freopen ("stdout.txt","w",stdout);
		freopen ("stderr.txt","w",stderr);
		#endif
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