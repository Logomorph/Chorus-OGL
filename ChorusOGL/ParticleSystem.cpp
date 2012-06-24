#include "ParticleSystem.h"
#include <time.h>

//-----------------------------------------------------------------------------
// Name: getRandomMinMax()
// Desc: Gets a random number between min/max boundaries
//-----------------------------------------------------------------------------
float getRandomMinMax( float fMin, float fMax )
{
  float fRandNum = (float)rand () / RAND_MAX;
  return fMin + (fMax - fMin) * fRandNum;
}

//-----------------------------------------------------------------------------
// Name: getRandomVector()
// Desc: Generates a random vector where X,Y, and Z components are between
//       -1.0 and 1.0
//-----------------------------------------------------------------------------
Vec3D getRandomVector( void )
{
  Vec3D vVector;

  // Pick a random Z between -1.0f and 1.0f.
  vVector.z = getRandomMinMax( -1.0f, 1.0f );

  // Get radius of this circle
  float radius = (float)sqrt(1 - vVector.z * vVector.z);

  // Pick a random point on a circle.
  float t = getRandomMinMax( -chPi, chPi );

  // Compute matching X and Y for our Z.
  vVector.x = (float)cosf(t) * radius;
  vVector.y = (float)sinf(t) * radius;

  return vVector;
}

ParticleSystem::ParticleSystem(void)
{
  lastRelease = 0;
  releaseTime = 200;
  releaseNo = 50;
  direction = Vec3D(0,1,0);
  velocity = Vec3D(0,10,0);
  speed = 0.0f;
  life = 2000;
  velocityVariation1=0.7f;
  velocityVariation2=1.0f;
  srand(time(NULL));
}


ParticleSystem::~ParticleSystem(void)
{
}

void ParticleSystem::Update()
{
  double cTime = ChorusApp::curTime();
  if(ChorusApp::keyDown(SDLK_z))
  {
    life--;
    if(life<0)
      life=0;
  }
  if(ChorusApp::keyDown(SDLK_x))
  {
    life++;
    if(life>3000)
      life=3000;
  }

  for(int i=0;i<particles.size();i++)
  {
    Particle part = particles[i];
    if(part.alive)
    {
      if(cTime - part.initTime>part.life)
      {
        part.alive=false;
        freeParticles.push_back(i);
      }
      else
      {
        part.position += (part.velocity*ChorusApp::elapsedTime()* 0.001);
      }
      particles[i] = part;
    }
  }

  if(cTime-lastRelease>=releaseTime)
  {
    lastRelease = cTime;
    for(int i=0;i<releaseNo;i++)
    {
      int index = -1;
      if(freeParticles.size()>0)
      {
        index = freeParticles[0];
        freeParticles.erase(freeParticles.begin(),freeParticles.begin()+1);
      }

      Particle buff;
      if(index==-1)
      {
        buff.alive=true;
        buff.initTime = cTime;
        buff.life=life;

        int angle = rand()%360;

        buff.position = Vec3D(cos(DegToRad(angle)) * getRandomMinMax(0.0f,1.0f),0,sin(DegToRad(angle)) * getRandomMinMax(0.0f,1.0f));
        buff.velocity = velocity* getRandomMinMax(velocityVariation1,velocityVariation2);
        if(speed!=0.0)
          buff.velocity += getRandomVector()*speed;
        particles.push_back(buff);
      }
      else
      {
        buff = particles[index];
        buff.alive=true;
        buff.initTime = cTime;
        buff.life=life;

        int angle = rand()%360;

        buff.position = Vec3D(cos(DegToRad(angle)) * getRandomMinMax(0.0f,1.0f),0,sin(DegToRad(angle)) * getRandomMinMax(0.0f,1.0f));
        buff.velocity = velocity* getRandomMinMax(velocityVariation1,velocityVariation2);
        if(speed!=0.0)
          buff.velocity += getRandomVector()*speed;
        particles[index] = buff;
      }
    }
  }
}

void ParticleSystem::Draw()
{
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_TEXTURE_2D );
  glDepthMask( GL_FALSE );
  // This is how will our point sprite's size will be modified by 
  // distance from the viewer.
  float quadratic[] =  { 1.0f, 0.0f, 0.01f };
  glPointParameterfvARB( GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic );

  // The alpha of a point is calculated to allow the fading of points 
  // instead of shrinking them past a defined threshold size. The threshold 
  // is defined by GL_POINT_FADE_THRESHOLD_SIZE_ARB and is not clamped to 
  // the minimum and maximum point sizes.
  glPointParameterfARB( GL_POINT_FADE_THRESHOLD_SIZE_ARB, 60.0f );


  float m_fMaxPointSize;
  glGetFloatv( GL_POINT_SIZE_MAX_ARB, &m_fMaxPointSize );
  glPointSize( 20 );

  glPointParameterfARB( GL_POINT_SIZE_MIN_ARB, 1.0f );
  glPointParameterfARB( GL_POINT_SIZE_MAX_ARB, 10 );

  // Specify point sprite texture coordinate replacement mode for each texture unit
  glTexEnvf( GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE );

  //
  // Render point sprites...
  //

  glEnable(GL_BLEND);
  glBlendFunc( GL_DST_ALPHA, GL_ONE );
  glEnable( GL_POINT_SPRITE_ARB );

  glPointSize( 20 );
  glColor3f(0.4f,0.4f,1.0f);

  glBegin( GL_POINTS );
  for(int i=0;i<particles.size();i++)
  {
    if(particles[i].alive)
    {
      glVertex3f( particles[i].position.x,particles[i].position.y,particles[i].position.z);
    }
  }
  glEnd();
  glDisable( GL_POINT_SPRITE_ARB );
  glDisable(GL_BLEND);
  glDisable( GL_DEPTH_TEST );
  glDepthMask( GL_TRUE );
  glDisable( GL_TEXTURE_2D );

  glColor3f(1,1,1);
}