#pragma once
#include <iostream>

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

namespace Chorus
{

	class CommandInterpreter
	{
	public:
		void Init();

		static void parseString(std::string command);
	};

}