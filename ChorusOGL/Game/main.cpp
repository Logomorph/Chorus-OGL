#include "stuff.h"

int main(int argc, char *argv[])
{
  Debug::Init();
  Debug::RedirectConsole();
  Debug::ShouldLog(true);

  _putenv("SDL_VIDEO_WINDOW_POS=center");
  _putenv("SDL_VIDEO_CENTERED=1");


  chApp = new ChorusApp("Ludum Dare prep",SCREEN_WIDTH,SCREEN_HEIGHT,FULLSCREEN);

  chApp->bubble();
  //SteamAPI_Shutdown();

  SafeDelete<ChorusApp> (chApp);
  return 0;
}
void ChorusApp::preLoad()
{
  setVScreenSize(VSCREEN_WIDTH,VSCREEN_HEIGHT); 
  batch->setShouldOptimizeBind(true);
  scene = new GameScene();
  scene->Init();

  cam = new Camera2D();
  cam->position = Vec2D(0,0);
  tex = content->createTex("created1",20,20,25,25,25,200);

  fnt=content->loadFnt("Data/fonts/test.fnt");
  //player1 = new XBOXController(1,true);
} 

void ChorusApp::Update()
{   
  //_CrtDumpMemoryLeaks();
  if( (keyDown(SDLK_RALT) && keyDown(SDLK_F4)) || (keyDown(SDLK_LALT) && keyDown(SDLK_F4)))
    ShutDown();
  console->Update();
  scene->Update();
}

void ChorusApp::Draw()
{
  //Set clear color
  glClearColor( 0, 0, 0, 1 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


  glLoadIdentity();

  scene->Draw();



  batch->Begin();

  batch->setTint(1,1,1);
  glLoadIdentity();
  console->Draw(batch,&fnt,&tex);	

  batch->End ();
  //Reset
  glLoadIdentity();
  //Update screen
  SDL_GL_SwapBuffers();
}
void ChorusApp::onShutDown()
{
  SafeDelete<Camera2D> (cam);
  //SafeDelete<XBOXController> (player1);
  SafeDelete<GameScene> (scene);
}