#include "SpriteBatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace Chorus
{

  SpriteBatch::SpriteBatch(int scrW, int scrH)
  {
    m_scrW=scrW;
    m_scrH=scrH;
    lastTex=0;
    shouldCenterText=true;
    shouldOptimizeBind=true;
  }

  SpriteBatch::~SpriteBatch(void)
  {
  }
  void SpriteBatch::setScale(int scrW, int scrH)
  {
    m_scrW=scrW;
    m_scrH=scrH;
  }
  void SpriteBatch::ScaleScreen()
  {
    //Set projection
    glLoadIdentity();
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, m_scrW, m_scrH, 0, -1, 1 );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
  }


  void SpriteBatch::Begin(float mode)
  {
    glEnable (GL_BLEND); 	
    glEnable(GL_TEXTURE_2D);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    // draw our background image
    glDisable(GL_LIGHTING);

    if(mode==0)
    {
      ScaleScreen();
    }
    else
      if(mode!=0)
      {
        //Set projection
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( -m_vScrH/2/mode, m_vScrW/2/mode, m_vScrH/2/mode, -m_scrH/2/mode, -1, 1 );

        //Initialize modelview matrix
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
      }
  }

  void SpriteBatch::End()
  {
    //glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix

    gluPerspective(45.0f,(GLfloat)m_vScrW/(GLfloat)m_vScrH,0.1f,100.0f);

    glMatrixMode(GL_MODELVIEW);	

    glDisable(GL_BLEND); 	
  }
  void SpriteBatch::Draw(Texture &tex,const Vec2D& pos)
  {
    Draw(tex,pos,Vec2D(1,1),0);
  }

  void SpriteBatch::Draw(Texture &tex,const Vec2D& pos, const float angle)
  {
    Draw(tex,pos,Vec2D(1,1),angle);
  }

  void SpriteBatch::Drawd(Texture &tex,const Vec2D& pos, const double angle)
  {
    Draw(tex,pos,Vec2D(1,1),(float)angle);
  }

  void SpriteBatch::Draw(Texture &tex,const Vec2D& pos,const Vec2D& scale)
  {
    Draw(tex, pos, scale, 0);
  }

  void SpriteBatch::Drawd(Texture &tex, const Vec2D& pos, const Vec2D& scale, const double angle)
  {
    if(!tex.loaded)
    {
      if(!tex.renderAttempted)
      {
        ERR("[SpriteBatch] Trying to render a texture that doesn't exist!");
        tex.renderAttempted=true;
      }
      return;
    }
    glPushMatrix();

    //glLoadIdentity();

    if(shouldOptimizeBind)
    {
      if(lastTex!=tex.texID)
      {
        glBindTexture(GL_TEXTURE_2D, tex.texID);
        lastTex=tex.texID;
      }
    }
    else
    {
      glBindTexture(GL_TEXTURE_2D, tex.texID);
      lastTex=tex.texID;
    }
    //int offX=(tex.w/2),offY=(tex.h/2);

    glTranslatef(pos.x, pos.y, 0);
    glRotated(angle, 0, 0, 1);
    glScalef(scale.x, scale.y, 1);
    //glTranslatef(-offX, -offY, 0);

    float halfWidth = tex.w*0.5f;
    float halfHeight = tex.h*0.5f;

    glBegin(GL_QUADS);

    glTexCoord2f(0,0);
    glVertex2f(-halfWidth,-halfHeight);

    glTexCoord2f(1,0);
    glVertex2f(halfWidth,-halfHeight);

    glTexCoord2f(1,1);
    glVertex2f(halfWidth,halfHeight);

    glTexCoord2f(0,1);
    glVertex2f(-halfWidth,halfHeight);

    glEnd();
    glPopMatrix();
  }

  void SpriteBatch::Draw(Texture &tex, const Vec2D& pos, const Vec2D& scale, const float angle)
  {
    if(!tex.loaded)
    {
      if(!tex.renderAttempted)
      {
        ERR("[SpriteBatch] Trying to render a texture that doesn't exist!");
        tex.renderAttempted=true;
      }
      return;
    }
    glPushMatrix();

    //glLoadIdentity();

    if(shouldOptimizeBind)
    {
      if(lastTex!=tex.texID)
      {
        glBindTexture(GL_TEXTURE_2D, tex.texID);
        lastTex=tex.texID;
      }
    }
    else
    {
      glBindTexture(GL_TEXTURE_2D, tex.texID);
      lastTex=tex.texID;
    }
    //int offX=(tex.w/2),offY=(tex.h/2);

    glTranslatef(pos.x, pos.y, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(scale.x, scale.y, 1);
    //glTranslatef(-offX, -offY, 0);

    float halfWidth = tex.w*0.5f;
    float halfHeight = tex.h*0.5f;

    glBegin(GL_QUADS);

    glTexCoord2f(0,0);
    glVertex2f(-halfWidth,-halfHeight);

    glTexCoord2f(1,0);
    glVertex2f(halfWidth,-halfHeight);

    glTexCoord2f(1,1);
    glVertex2f(halfWidth,halfHeight);

    glTexCoord2f(0,1);
    glVertex2f(-halfWidth,halfHeight);

    glEnd();
    glPopMatrix();
  }

  void SpriteBatch::Draw(Texture &tex,const Vec2D& pos,const Vec2D& scale,const Rectangle2D& source,const float angle)
  {
    if(!tex.loaded)
    {
      if(!tex.renderAttempted)
      {
        ERR("[SpriteBatch] Trying to render a texture that doesn't exist!");
        tex.renderAttempted=true;
      }
      return;
    }
    glPushMatrix();

    //glLoadIdentity();

    if(shouldOptimizeBind)
    {
      if(lastTex!=tex.texID)
      {
        glBindTexture(GL_TEXTURE_2D, tex.texID);
        lastTex=tex.texID;
      }
    }
    else
    {
      glBindTexture(GL_TEXTURE_2D, tex.texID);
      lastTex=tex.texID;
    }
    //int offX=(tex.w/2),offY=(tex.h/2);

    glTranslatef(pos.x, pos.y, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(scale.x, scale.y, 1);
    //glTranslatef(-offX, -offY, 0);

    float halfWidth = source.width*0.5f;
    float halfHeight = source.height*0.5f;


    glBegin(GL_QUADS);

    glTexCoord2f(source.origin.x/tex.w,
      source.origin.y/tex.h);
    glVertex2f(-halfWidth,-halfHeight);

    glTexCoord2f((source.origin.x+source.width)/tex.w,
      source.origin.y/tex.h);
    glVertex2f(halfWidth,-halfHeight);

    glTexCoord2f((source.origin.x+source.width)/tex.w,
      ((source.origin.y+source.height)/tex.h));
    glVertex2f(halfWidth,halfHeight);

    glTexCoord2f(source.origin.x/tex.w,
      (source.origin.y+source.height)/tex.h);
    glVertex2f(-halfWidth,halfHeight);

    glEnd();
    glPopMatrix();
  }


  void SpriteBatch::Drawd(Texture &tex,const Vec2D& pos,const Vec2D& scale,const Rectangle2D& source,const double angle)
  {
    if(!tex.loaded)
    {
      if(!tex.renderAttempted)
      {
        ERR("[SpriteBatch] Trying to render a texture that doesn't exist!");
        tex.renderAttempted=true;
      }
      return;
    }
    glPushMatrix();

    //glLoadIdentity();

    if(shouldOptimizeBind)
    {
      if(lastTex!=tex.texID)
      {
        glBindTexture(GL_TEXTURE_2D, tex.texID);
        lastTex=tex.texID;
      }
    }
    else
    {
      glBindTexture(GL_TEXTURE_2D, tex.texID);
      lastTex=tex.texID;
    }
    //int offX=(tex.w/2),offY=(tex.h/2);

    glTranslatef(pos.x, pos.y, 0);
    glRotatef((GLfloat)angle, 0, 0, 1);
    glScalef(scale.x, scale.y, 1);
    //glTranslatef(-offX, -offY, 0);

    float halfWidth = source.width*0.5f;
    float halfHeight = source.height*0.5f;


    glBegin(GL_QUADS);

    glTexCoord2f(source.origin.x/tex.w,
      source.origin.y/tex.h);
    glVertex2f(-halfWidth,-halfHeight);

    glTexCoord2f((source.origin.x+source.width)/tex.w,
      source.origin.y/tex.h);
    glVertex2f(halfWidth,-halfHeight);

    glTexCoord2f((source.origin.x+source.width)/tex.w,
      ((source.origin.y+source.height)/tex.h));
    glVertex2f(halfWidth,halfHeight);

    glTexCoord2f(source.origin.x/tex.w,
      (source.origin.y+source.height)/tex.h);
    glVertex2f(-halfWidth,halfHeight);

    glEnd();
    glPopMatrix();
  }

  void SpriteBatch::BeginLines()
  {
    glDisable(GL_TEXTURE_2D);
  }
  void SpriteBatch::EndLines()
  {
    glEnable(GL_TEXTURE_2D);
  }

  void SpriteBatch::DrawLine(const Vec2D& p1,const Vec2D& p2, float width)
  {
    //glLoadIdentity();
    glPushMatrix();
    glLineWidth(width);

    glBegin(GL_LINES);
    glVertex2f( p1.x, p1.y);
    glVertex2f( p2.x, p2.y);
    glEnd();
    glPopMatrix();
  }

  void SpriteBatch::DrawText(Font fnt,string text,const Vec2D& pos)
  {
    DrawText(fnt,text,pos,Vec2D(1,1),0);
  }

  void SpriteBatch::DrawText(Font fnt,string text,const Vec2D& pos,const Vec2D& scale)
  {
    DrawText(fnt,text,pos,scale,0);
  }

  void SpriteBatch::DrawText(Font fnt,string text,const Vec2D& pos,float angle)
  {
    DrawText(fnt,text,pos,Vec2D(1,1),angle);
  }

  void SpriteBatch::DrawText(Font fnt,string text,const Vec2D& pos,const Vec2D& scale,float angle)
  {
    glPushMatrix();

    //glLoadIdentity();

    if(shouldOptimizeBind)
    {
      if(lastTex!=fnt.tex.texID)
      {
        glBindTexture(GL_TEXTURE_2D, fnt.tex.texID);
        lastTex=fnt.tex.texID;
      }
    }
    else
    {
      glBindTexture(GL_TEXTURE_2D, fnt.tex.texID);
      lastTex=fnt.tex.texID;
    }

    glTranslatef(pos.x, pos.y, 0);
    glRotatef(angle, 0, 0, 1);

    if(shouldCenterText)
    {
      float offX=0;

      offX=fnt.measureText(text)*scale.x;
      offX/=2;

      glTranslatef(-offX, -(fnt.lineH*scale.y*0.5f), 0.0f);
    }

    for(uint i=0;i<text.length();i++)
    {
      if( (int(text[i]))>=fnt.chars[0].id && (int(text[i]))<=fnt.chars[fnt.chars.size()-1].id)
      {
        glPushMatrix();

        glTranslatef(fnt.chars[int(text[i])-32].xOff*scale.x, fnt.chars[int(text[i])-32].yOff*scale.y, 0);

        glBegin(GL_QUADS);

        glTexCoord2f(fnt.chars[int(text[i])-32].rX,fnt.chars[int(text[i])-32].rY);
        glVertex2f(0,0);

        glTexCoord2f(fnt.chars[int(text[i])-32].rX,fnt.chars[int(text[i])-32].rB);
        glVertex2f(0,fnt.chars[int(text[i])-32].H*scale.y);

        glTexCoord2f(fnt.chars[int(text[i])-32].rR,fnt.chars[int(text[i])-32].rB);
        glVertex2f(fnt.chars[int(text[i])-32].W*scale.x,fnt.chars[int(text[i])-32].H*scale.y);

        glTexCoord2f(fnt.chars[int(text[i])-32].rR,fnt.chars[int(text[i])-32].rY);
        glVertex2f(fnt.chars[int(text[i])-32].W*scale.x,0);

        glEnd();

        glPopMatrix();
        glTranslatef(fnt.chars[int(text[i])-32].xAdv*scale.x, 0, 0);
      }
    }
    glPopMatrix();
  }

}