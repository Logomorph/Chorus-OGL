#pragma once
#include "../Chorus/app/ChorusApp.h"
#include "../Chorus/particle_system/ParticleSystem.h"

using namespace Chorus;
using namespace std;

class GameScene
{
private:
  SpriteBatch *batch;
  Content *content;

  Font fnt;
  Texture tex;
  Shader physics;

  Texture rendTarget;
  RenderTarget target;
  RenderTarget target2;
public:
  GameScene(void) { }
  ~GameScene(void) { }

  void Init();
  void Update();
  void Draw();
};

