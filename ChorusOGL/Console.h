#pragma once
#include "SpriteBatch.h"
#include "definitions.h"
#include <sdl.h>
#include "ChorusCore.h"
#include "ChorusApp.h"
#include "CommandInterpreter.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

namespace Chorus
{

	class Console
	{
	public:
		Console(int w, int h);
		~Console(void);

		float scrW,scrH;
		static uint lToSkip;

		void Update();
		void Draw(SpriteBatch *batch, Font *fnt,Texture *tex);
		void setScreenSize(int w, int h);
		static void output(string text);
		static void output(char text[]);
		static void reset();
	private:
		double lastTime;
		static int location;
		string current;
		static vector<string> lines;
		static vector<string> commands;
		bool shouldUpdate;
	};

}
