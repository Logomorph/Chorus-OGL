#pragma once

#define NO_SDL_GLEXT
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include "../core/ChorusCore.h"
#include "../debug/Debug.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "../XML/tinyxml.h"
#include "objModel.h"

#pragma comment (lib,"SDL_image.lib")
#pragma comment (lib,"glu32.lib")
//#pragma comment (lib,"tinyxml.lib")
#pragma comment (lib,"glew32.lib")

using namespace std;

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

namespace Chorus
{
  //Holds a shader
  struct Shader 
  {
    GLuint v,f,p;
    bool loaded;

    void Use() { glUseProgram(p); }
    void Clear() { glUseProgram(0); }
    void SetUniformParameter3f(const char *pszParameter, float p1, float p2, float p3)
    {
      glUniform3fARB(glGetUniformLocationARB(p,pszParameter), p1, p2, p3);
    }
    void SetUniformParameter1f(const char *pszParameter, float p1)
    {
      glUniform1fARB(glGetUniformLocationARB(p,pszParameter), p1);
    }
    void SetUniformParameter1i(const char *pszParameter, int p1)
    {
      glUniform1iARB(glGetUniformLocationARB(p,pszParameter), p1);
    }
  };
  //Holds info about a texture
  struct Texture
  {
    GLuint texID;					//Texture ID
    uint w,h;						//Texture width & height
    bool loaded,renderAttempted;	//was texture loaded & was a render attempted
  };

  //Holds a render target
  struct RenderTarget
  {
    Texture tex;
    GLuint FramebufferName;
    GLuint depthrenderbuffer;
    void Use() { glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName); }
    void Clear() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
  };

  //Holds info about a character in a font
  struct charDescript
  {
    ushort id;				//char id
    float rX,rY,rB,rR;		//the character rectangle
    float xOff,yOff,xAdv;	//offsets for character and how much to advance for next char
    int W,H;				//width & height of the character, used for rendering
  };

  //Holds info about a font
  struct Font
  {
    Texture tex;					//character atlas
    bool loaded;
    int lineH;						//height of a line of text
    vector<charDescript> chars;		//info about each char

    int measureText(string text)
    {
      int offX=0;
      for(uint i=0;i<text.length();i++)
        offX+=int(chars[int(text[i])-32].xAdv);

      return offX;
    }
  };

  //The content loader
  class Content
  { 
  public:
    Content(void);
    ~Content(void);

    Texture  loadTex(string file);
    Texture  createTex(string name, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    RenderTarget  createRenderTarget(uint Width, uint Height);
    Font	 loadFnt(string file);
    Model3D* loadObj(string file);
    Shader   loadShader(string vertex,string fragment);
  private:
    Texture postToOGL(SDL_Surface* ImageData);

    map<string,Texture> textures;

    void printShaderInfoLog(GLuint obj);
    void printProgramInfoLog(GLuint obj);
  };

}