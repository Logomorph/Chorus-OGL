#include "Console.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace Chorus
{
  vector<string> Console::lines;
  vector<string> Console::commands;
  int Console::location;
  uint Console::lToSkip;

  Console::Console(int w, int h)
  {
    lines.clear();
    string name = "Chorus console v1.0";
    lines.push_back(name);
    shouldUpdate=false;
    scrW=(float)w;
    scrH=(float)h;
    location=-1;
    lToSkip=0;
    lastTime=0;
  }

  Console::~Console(void)
  {
    reset();
  }

  void Console::setScreenSize(int w, int h)
  {
    scrW=(float)w;
    scrH=(float)h;
  }
  void Console::reset()
  {
    lines.clear();
    commands.clear();
    location=-1;
    lToSkip=0;
  }

  void Console::Update()
  {
    vector<conKey> keys = ChorusApp::getKeySt();
    if(shouldUpdate)
    {
      //scrolling up and down through the previus stuff in the console
      if(ChorusApp::keyDownSingle(SDLK_PAGEUP))
      {
        //Debug::Log("up");
        if(lToSkip<lines.size()-1)
          lToSkip++;
      }
      if(ChorusApp::keyDownSingle(SDLK_PAGEDOWN))
      {
        //Debug::Log("down");
        if(lToSkip>0)
          lToSkip--;
      }
    }
    for(uint i=0;i<keys.size();i++)
    {
      // the ~ key which turns the console on and off
      if(keys[i].code==96)
      {
        shouldUpdate=!shouldUpdate;
      }
      else
        if(shouldUpdate)
        {
          //going back & forth through previous commands
          if(keys[i].arrow==true)
          {
            if(keys[i].key=='H')//up
            {
              location++;
              if(location>=commands.size())
                location=commands.size()-1;
              if(location!=-1)
                current=commands[commands.size()-1-location];
            }
            else
              if(keys[i].key=='P')//down
              {
                location--;
                if(location<0)
                {
                  location=-1;
                  current.clear();
                }
                else
                  current=commands[commands.size()-1-location];
              }
          }
          else
          {
            //do something with th current command
            if(keys[i].code==13 && current.size()>0)
            {
              lines.push_back(current);
              commands.push_back(current);

              CommandInterpreter::parseString(current);
              /*if(Lua->executeString(current)==0)
              {
              //output("Lua ok");
              }
              else
              {
              string err("Error: ");
              err.append(lua_tostring(Lua->getState(), -1));
              output(err);
              }*/
              current.clear();
              location=-1;
              lToSkip=0;
            }
            else
              //backspace
              if(keys[i].code==8 && current.size()>0)
              {
                current.erase(current.begin()+current.size()-1);
              }
              else
                //other keys pressed
                if(int(keys[i].key)>26)
                {
                  current.push_back(keys[i].key);
                }
          }
        }
    }
  }

  void Console::Draw(SpriteBatch *batch, Font *fnt,Texture *tex)
  {
    if(shouldUpdate)
    {
      int h=ChorusApp::m_VscrH;
      int w=ChorusApp::m_VscrW;

      ChorusApp::setVScreenSize(800,600);
      /*LOG(scrW);
      LOG(scrH);*/
      batch->setTextCentered(false);
      //draw the background sprite
      batch->Draw(*tex,Vec2D(scrW/2,(scrH*0.05f)),Vec2D(scrW/10,scrH*0.4f/10));
      //batch->Begin(0);

      //
      batch->DrawText(*fnt,">",Vec2D(0,scrH*0.4f),Vec2D(0.7f,0.7f));

      //draw the current command
      batch->DrawText(*fnt,current,Vec2D(16,scrH*0.4f),Vec2D(0.7f,0.7f));

      //draw what already happened in the console
      for(int i=lines.size()-1-lToSkip;i>-1;i--)
      {
        if((scrH/2-(lines.size()-i-lToSkip)*18-10)<0)
          break;
        batch->DrawText(*fnt,lines[i],
          Vec2D(0,scrH*0.4f-(lines.size()-i-lToSkip)*18-10),
          Vec2D(0.7f,0.7f));
      }

      //calculate & draw FPS
      //double cTime=ChorusApp::curTime();
      string fps("FPS:");
      int result = (int)(1000.f/(ChorusApp::elapsedTime()));
      fps.append(iToa(result));
      batch->DrawText(*fnt,fps,Vec2D(scrW*0.85f,10),Vec2D(0.7f,0.7f));
     // lastTime=cTime;

      ChorusApp::setVScreenSize(w,h);
    }
  }

  void Console::output(string text)
  {
    lines.push_back(text);
  }
  void Console::output(char text[])
  {
    lines.push_back(string(text));
  }

}