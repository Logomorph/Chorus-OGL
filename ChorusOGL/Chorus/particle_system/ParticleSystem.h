#pragma once
#include "../app/ChorusApp.h"
using namespace Chorus;

struct Particle
{
  Vec3D position;
  Vec3D velocity;
  float initTime, life;
  bool alive;
};
class ParticleSystem
{
private:
  vector<Particle> particles;
  vector<int> freeParticles;
  double releaseTime,lastRelease;
  double releaseNo;
  Vec3D direction,velocity;
  double speed;
  float life;
  float velocityVariation1,velocityVariation2;
public:
  ParticleSystem(void);
  ~ParticleSystem(void);

  void SetLife(float Life) { life=Life; }
  void SetReleaseInterval(double Release) { releaseTime=Release; }
  void SetReleaseNumber(double No) { releaseNo=No; }
  void SetVelocityVariation(double Var) { speed=Var; }
  void SetDirection(Vec3D Direction) { direction=Direction; }
  void SetVelocity(Vec3D Velocity) { velocity=Velocity; }
  void SetVelocityVariation(float v1,float v2) { velocityVariation1=v1; velocityVariation2=v2; }

  void Update();
  void Draw();
};

