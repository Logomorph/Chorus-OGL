#pragma once

#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
#ifdef _WIN32
#include <crtdbg.h>
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "../Chorus.h"
#ifdef _WIN32
#include <strsafe.h>
#endif
#include <SDL.h>


#pragma comment(lib,"SDL.lib")
#pragma comment(lib,"SDLmain.lib")
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

using namespace std;

namespace Chorus
{
  namespace keyboard {
    struct KeyboardState
    {
      vector<SDLKey> keys;
    };
  }
  class Content;
  class SpriteBatch;
  class Console;

  class ChorusApp
  {
  public:
    ChorusApp(string title,const int scrW,const int scrH,const bool fullScreen);
    ~ChorusApp(void);
    virtual void	preLoad();
    virtual void	Load(void *ch) { loading=0;};
    virtual void	Update();
    virtual void	Draw();
    virtual void onShutDown();
    void	ShutDown() { closing=true; }

    void killApp() { 
      onShutDown();
      SafeDelete<Content>(content);
      SafeDelete<SpriteBatch>( batch);
      SafeDelete<Console>( console);
      Debug::Log("[CHORUS] Shutting down...");
      SDL_Quit();
    }


    // The update loop
    void bubble();

    // Window size-independant screen size
    static void setVScreenSize(int w, int h);
    // Return time
    static Uint32 getTime()	{ return SDL_GetTicks();	}
    // Return current time
    static double curTime()		{ return g_dCurTime;		}
    // Return elapsed time
    static double elapsedTime()	{ return g_fElpasedTime;	}
    // Return the SDL event handle
    SDL_Event getEventH()	{ return event;  }
    // Return the console keys pressed
    static vector<conKey> getKeySt() { return pressedKeys; }

    // Check if the window has focus
    static bool hasFocus() { return focused; }

    // Check if a key is pressed
    static bool keyDown( SDLKey key);
    // Check if a key is pressed only once
    static bool keyDownSingle( SDLKey key);
    // Check if a mouse button was clicked
    static bool mouseClick( uint8 btn);
    //Get the mouse position
    static inline Vec2D getMouse() { return mouse; }


    static Content *content;
    static SpriteBatch *batch;
    static Console *console;

    static int m_scrW,m_scrH,m_VscrW,m_VscrH;

    int loading;
  private:

    // global declarations
    SDL_Event				event; //used for processing events and handling input

    static bool focused;
    bool closing,fs;

    //timer declaration stuff
    static double  g_fElpasedTime;
    static double g_dCurTime;
    double g_dLastTime;

    static vector<conKey> pressedKeys;
    static vector<SDLKey> keys;

    static keyboard::KeyboardState oldState,newState;
    static vector<uint8> mouseBtn;


    static Vec2D mouse;

    string title;

    int initSDL();
    int initOGL();
  };

}