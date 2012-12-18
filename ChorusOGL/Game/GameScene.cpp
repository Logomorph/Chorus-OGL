#include "GameScene.h"

void GameScene::Init()
{
  batch = ChorusApp::batch;
  content = ChorusApp::content;
  target2 = content->createRenderTarget(ChorusApp::m_VscrW,ChorusApp::m_VscrH);
  target = content->createRenderTarget(ChorusApp::m_VscrW,ChorusApp::m_VscrH);

  
  //tex = content->loadTex("Data/gfx/default1.png");
  tex = content->createTex("redPix",1,1,255,255,255,255);
  physics = content->loadShader("Data/shaders/phys.vert","Data/shaders/phys.frag");

  //SDL_WarpMouse(ChorusApp::m_scrW/2,ChorusApp::m_scrH/2);
}

float xOff=0,yOff=0;
int state =0;
int swt=0;
double lastRender = ChorusApp::curTime();
void GameScene::Update()
{
  xOff+=1.0f;
  if(ChorusApp::keyDown(SDLK_o))
    xOff+=0.5f;
  if(ChorusApp::keyDown(SDLK_i))
    xOff-=0.5f;
  if(ChorusApp::keyDown(SDLK_l))
    yOff+=0.5f;
  if(ChorusApp::keyDown(SDLK_k))
    yOff-=0.5f;
  if(ChorusApp::keyDownSingle(SDLK_g))
  {
    swt=!swt;
    LOG(swt);
  }
}
void GameScene::Draw()
{
  if(state==0)
  {
    glLoadIdentity();			

    // Render to our frame buffer
    target2.Use();
    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render Scene
    glPushMatrix();


    batch->Begin();
    batch->setTint(1.0f,0.0f,0.0f,1.0f);
    batch->Draw(tex,Vec2D((float32)ChorusApp::m_VscrW/2,(float32)ChorusApp::m_VscrH/2));

    batch->setTint(0.0f,1.0f,1.0f,1.0f);
    batch->Draw(tex,Vec2D((float32)ChorusApp::m_VscrW*0.8f,(float32)ChorusApp::m_VscrH/2));

    //Done
    glPopMatrix();

    target2.Clear();
    state=1;
    lastRender = ChorusApp::curTime();
  }
  //glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
  //glLoadIdentity();									// Reset The Projection Matrix

  //gluPerspective(45.0f,(GLfloat)ChorusApp::m_VscrW/(GLfloat)ChorusApp::m_VscrH,1.0f,10000.0f);

  //glMatrixMode(GL_MODELVIEW);
  //if(ChorusApp::curTime()-lastRender>1000)
  {
    physics.Use();
    glLoadIdentity();			

    // Render to our frame buffer
    if(swt==0)
      target.Use();
    if(swt==1)
      target2.Use();
    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Render Scene
    glPushMatrix();


    batch->Begin();

    if(swt==0)
      batch->Draw(target2.tex,Vec2D((float32)ChorusApp::m_VscrW/2,(float32)ChorusApp::m_VscrH/2),Vec2D(1.0f,-1.0f));
    if(swt==1)
      batch->Draw(target.tex,Vec2D((float32)ChorusApp::m_VscrW/2,(float32)ChorusApp::m_VscrH/2),Vec2D(1.0f,-1.0f));
    batch->End();

    //Done
    glPopMatrix();

    if(swt==0)
      target.Clear();
    if(swt==1)
      target2.Clear();
    physics.Clear();
    lastRender = ChorusApp::curTime();
  }

  glDisable(GL_DEPTH_TEST);

  // Clear the screen
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glBindTexture(GL_TEXTURE_2D,rendTarget.texID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  batch->Begin();
  if(swt==0)
    batch->Draw(target.tex,Vec2D(640,400));
  if(swt==1)
    batch->Draw(target2.tex,Vec2D(640,400));
  batch->Draw(target.tex,Vec2D(640,400),Vec2D(1,-1.0f));
  batch->End();
  swt=!swt;
}