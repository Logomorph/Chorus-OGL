#include "CommandInterpreter.h"
#include "Console.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace Chorus
{

	void CommandInterpreter::Init()
	{
	}
	void CommandInterpreter::parseString(std::string command)
	{
		if(command=="ClearConsole")
		{
			//Console::output("Comm OK");
			Console::reset();
		}
		else
		if(command=="/help")
		{
			Console::output("Commands:");
			Console::output("Page UP/Page Down to scroll");
			Console::output("ClearConsole");
		}
		else
		{
			Console::output("unknown command. use /help for more info");
		}
	}
}
