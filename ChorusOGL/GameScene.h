#pragma once
#include "ChorusApp.h"
#include "ParticleSystem.h"

using namespace Chorus;
using namespace std;

class GameScene
{
private:
  SpriteBatch *batch;
  Content *content;

  Font fnt;
  Texture tex;
  Shader cartoon;
  Shader physics;

  GLuint FramebufferName;
  GLuint depthrenderbuffer;
  Texture rendTarget;
  RenderTarget target;
  RenderTarget target2;
public:
  GameScene(void);
  ~GameScene(void);

  void Init();
  void Update();
  void Draw();
};

