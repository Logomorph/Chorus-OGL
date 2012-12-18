#include "ChorusApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace Chorus
{

  vector<conKey> ChorusApp::pressedKeys;
  vector<SDLKey> ChorusApp::keys;
  vector<uint8> ChorusApp::mouseBtn;
  Vec2D ChorusApp::mouse;
  double ChorusApp::g_dCurTime;
  double  ChorusApp::g_fElpasedTime;
  bool ChorusApp::focused;
  keyboard::KeyboardState ChorusApp::oldState,
    ChorusApp::newState;

  Content *ChorusApp::content=NULL;
  SpriteBatch *ChorusApp::batch=NULL;
  Console *ChorusApp::console=NULL;
  int ChorusApp::m_scrW,
    ChorusApp::m_scrH,
    ChorusApp::m_VscrW,
    ChorusApp::m_VscrH;

  ChorusApp::ChorusApp(string title,const int scrW,const int scrH,const bool fullScreen)
  {
    LOG("[CHORUS] Starting up...");

    this->title=title;

    mouse = Vec2D(0,0);
    loading=-1;
    fs=fullScreen;
    closing=false;
    focused=true;
    m_VscrW=m_scrW=scrW;
    m_VscrH=m_scrH=scrH;
    g_dLastTime = g_dCurTime =0 ;
    initSDL();
    initOGL();


    content = new Content();
    batch = new SpriteBatch(m_scrW,m_scrH); 
    console = new Console(m_scrW,m_scrH); 

    preLoad();
    Load(NULL);

    LOG("[CHORUS] Startup complete!");
  }

  ChorusApp::~ChorusApp(void)
  {
    SafeDelete<Content>(content);
    SafeDelete<SpriteBatch>( batch);
    SafeDelete<Console>( console);
  }

  int ChorusApp::initSDL()
  {
    LOG("[CHORUS] Starting SDL...");
    //creating window
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER  ) < 0 || !SDL_GetVideoInfo() ) 
    {
      ERR("[CHORUS] SDL error!" + std::string( SDL_GetError() ) );
      return 0;
    }

    // Start graphic system with OGL 
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // VSync
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);

    if(!fs)
      SDL_SetVideoMode( m_scrW, m_scrH, SDL_GetVideoInfo()->vfmt->BitsPerPixel, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_OPENGL
      /*|SDL_FULLSCREEN*/ );
    if(fs)
      SDL_SetVideoMode( m_scrW, m_scrH, SDL_GetVideoInfo()->vfmt->BitsPerPixel, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_OPENGL
      |SDL_FULLSCREEN );
    SDL_WM_SetCaption(title.c_str(),"");
    SDL_WM_SetIcon(SDL_LoadBMP("Data/gfx/icon.bmp"),NULL);
    //SDL_EnableKeyRepeat(20, 10);
    SDL_EnableUNICODE(1);

    SDL_ShowCursor(SDL_ENABLE);

    return 1;
  }
  int ChorusApp::initOGL()
  {
    LOG("[CHORUS] Starting OGL...");

    //Set clear color
    glClearColor( 1, 0, 0, 0 );

    //If there was any errors
    if( glGetError() != GL_NO_ERROR )
    {
      ERR("[CHORUS] OGL error!");
      return 0;
    }

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      /* Problem: glewInit failed, something is seriously wrong. */

      ERR("[CHORUS] GLEW error!");
      //fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    return 1;
  }

  void ChorusApp::setVScreenSize(int w, int h)
  {
    m_VscrW=w;
    m_VscrH=h;

    batch->setScale(m_VscrW,m_VscrH);
    batch->ScaleScreen();

    console->setScreenSize(m_VscrW,m_VscrH);
  }

  void ChorusApp::bubble()
  {
    LOG("[CHORUS] Bubbling...");
    while(true)
    {
      //timer - start
      g_dCurTime     = SDL_GetTicks();
      g_fElpasedTime = (g_dCurTime - g_dLastTime);

      g_dLastTime    = g_dCurTime;
      //timer - end

      //Keep a copy of the keyboard state
      oldState=newState;
      pressedKeys.clear();

      while( SDL_PollEvent( &event ) ) 
      {
        if(loading==0)
        {

          switch( event.type ) 
          {
          case SDL_ACTIVEEVENT:
            {
              if( (event.active.state & SDL_APPACTIVE) || (event.active.state & SDL_APPINPUTFOCUS)) 
              {
                if( event.active.gain == 0 ) 
                {
                  focused=false;
                }
                else 
                {
                  focused=true;
                }
              }
            }break;
          case SDL_MOUSEMOTION:
            {
              //we want to scale the mouse position to the virtual screen size
              mouse.Set((float)event.motion.x*m_VscrW/m_scrW,(float)event.motion.y*m_VscrH/m_scrH);
            }
            break;
          case SDL_QUIT:
            killApp();
            return ;
            break;
          case SDL_MOUSEBUTTONDOWN:
            { 
              mouseBtn.push_back(event.button.button);
            }break;
          case SDL_MOUSEBUTTONUP:
            { 
              for(uint i=0;i<mouseBtn.size();i++)
              {
                if(mouseBtn[i]==event.button.button)
                {
                  mouseBtn.erase(mouseBtn.begin()+i);
                  break;
                }
              }
            }break;
          case SDL_KEYDOWN:
            {
              keys.push_back(event.key.keysym.sym);

              //this is for the console
              if(event.key.keysym.scancode == 'H' || event.key.keysym.scancode == 'K'
                || event.key.keysym.scancode == 'M' ||event.key.keysym.scancode == 'P')
              {
                conKey buff;
                buff.arrow=true;
                buff.key=event.key.keysym.scancode;
                pressedKeys.push_back(buff);
              }
              if(event.key.keysym.unicode!=0 && event.key.keysym.unicode!=27)
              {
                conKey buf;
                buf.arrow=false;
                buf.code=event.key.keysym.unicode;
                buf.key=char(event.key.keysym.unicode);

                //Debug::Log(event.key.keysym.unicode);
                pressedKeys.push_back(buf);
              }
            }break;
          case SDL_KEYUP:
            {
              for(uint i=0;i<keys.size();i++)
              {
                if(keys[i]==event.key.keysym.sym)
                {
                  keys.erase(keys.begin()+i);
                  break;
                }
              }
            }break;
          }
        }
      }

      //Store the pressed keys in the new state
      newState.keys=keys;

      if(focused)
      {
        if(closing)
        {
          killApp();
          return;
        }
        if(loading==0)
        {
          Update();

          Draw();
        }
      }
      else
        Sleep(10);
    }
  }

  bool ChorusApp::keyDown( SDLKey key)
  {
    for(uint i=0;i<ChorusApp::newState.keys.size();i++)
    {
      if(ChorusApp::newState.keys[i]==key)
        return true;
    }
    return false;
  }

  bool ChorusApp::keyDownSingle( SDLKey key)
  {
    // Check if the key is present in the new state
    bool foundNew=0;
    for(uint i=0;i<ChorusApp::newState.keys.size();i++)
    {
      if(ChorusApp::newState.keys[i]==key)
        foundNew=true;
    }

    // Check if the key isn't present in the old state
    bool foundOld=false;
    for(uint i=0;i<ChorusApp::oldState.keys.size();i++)
    {
      if(ChorusApp::oldState.keys[i]==key)
        foundOld=true;
    }

    if(!foundOld && foundNew)
      return true;
    return false;
  }

  bool ChorusApp::mouseClick(uint8 btn)
  {
    for(uint i=0;i<ChorusApp::mouseBtn.size();i++)
    {
      if(ChorusApp::mouseBtn[i]==btn)
        return true;
    }
    return false;
  }

}