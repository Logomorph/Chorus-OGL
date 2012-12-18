#pragma once

#include "../content/Content.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW new
#endif

namespace Chorus
{

  class SpriteBatch
  {
  public:
    SpriteBatch(int scrW, int scrH);
    SpriteBatch() { }
    ~SpriteBatch(void);

    void Begin(float mode=0);
    void setScale(int scrW, int scrH);
    void ScaleScreen();
    void End();

    void Draw(Texture &tex,const Vec2D& pos);
    void Draw(Texture &tex,const Vec2D& pos, const float angle);
    void Drawd(Texture &tex,const Vec2D& pos, const double angle);
    void Draw(Texture &tex,const Vec2D& pos,const Vec2D& scale);
    void Draw(Texture &tex,const Vec2D& pos,const Vec2D& scale,const float angle);
    void Drawd(Texture &tex,const Vec2D& pos,const Vec2D& scale,const double angle);


    // Due to the way I calculate the mapping for the source, having separate methods is preferred...
    // I don't want to perform divisions if not absolutely necessary
    void Draw(Texture &tex,const Vec2D& pos,const Vec2D& scale,const Rectangle2D& source,const float angle);
    void Drawd(Texture &tex,const Vec2D& pos,const Vec2D& scale,const Rectangle2D& source,const double angle);

    void BeginLines();
    void EndLines();
    void DrawLine(const Vec2D& p1,const Vec2D& p2,float width);

    void DrawText(Font fnt,string text,const Vec2D& pos);
    void DrawText(Font fnt,string text,const Vec2D& pos,const Vec2D& scale);
    void DrawText(Font fnt,string text,const Vec2D& pos,float angle);
    void DrawText(Font fnt,string text,const Vec2D& pos,const Vec2D& scale,float angle);

    bool isTextCentered() { return shouldCenterText; }
    void setTextCentered(bool opt) { shouldCenterText = opt; }

    void setTint(float r, float g, float b) { glColor3f(r,g,b); }
    void setTint(float r, float g, float b, float a) { glColor4f(r,g,b,a); }

    void setVirtualScreen(int w,int h) { m_vScrH=h; m_scrW=w; }

    void setShouldOptimizeBind(bool value) { shouldOptimizeBind = value; }

  private:
    int m_scrW,m_scrH;
    int m_vScrW,m_vScrH;
    bool shouldCenterText;
    bool shouldOptimizeBind;
    GLuint lastTex;
  };

}