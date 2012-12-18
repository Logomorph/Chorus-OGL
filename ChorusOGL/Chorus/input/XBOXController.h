#pragma once



//uncomment the following line to use xinput
//#define XIN 1

#ifdef WIN32
#ifdef XIN 

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif


// We need the Windows Header and the XInput Header
#include <windows.h>
#include <XInput.h>

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )
#define XC_MAX 0x7FFF

// Now, the XInput Library
// NOTE: COMMENT THIS OUT IF YOU ARE NOT USING
// A COMPILER THAT SUPPORTS THIS METHOD OF LINKING LIBRARIES
#pragma comment(lib, "XInput.lib")


namespace Chorus
{
	class XBOXController
	{
	private:
		XINPUT_STATE _controllerState;
		int _controllerNum;
		bool m_clamp;
	public:
		XBOXController(int playerNumber,bool clamp);
		XINPUT_STATE GetState();
		bool IsConnected();
		void Vibrate(int leftVal = 0, int rightVal = 0);

	};
}
#endif
#endif
