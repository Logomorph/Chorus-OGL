#pragma once
#include <math.h>
#include <SDL.h>
#include <string>
#include <stdio.h> 
#include <vector>
using namespace std;


namespace Chorus
{
  //this basically spells "I am GOD!"
#define elif else if

#define DegToRad(degree) ((3.1416f / 180.0f) * (degree)) // converts from degrees to radians
#define RadToDeg(radian) ((180.0f / 3.1416f) * (radian)) // converts from radians to degrees
#define ROUND_FACTOR 10000.0
  //distance between 2 points 3D
  static float Distance3D(float x1,float y1,float z1,float x2,float y2,float z2)
  {
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2)+pow(z2-z1,2));
  }
  //distance between 2 points 3D squared
  static float Distance3D2(float x1,float y1,float z1,float x2,float y2,float z2)
  {
    return pow(x2-x1,2)+pow(y2-y1,2)+pow(z2-z1,2);
  }

  //distance between 2 points
  static float Distance(float x1,float y1,float x2,float y2)
  {
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
  }
  //distance between 2 points squared
  static float Distance2(float x1,float y1,float x2,float y2)
  {
    return pow(x2-x1,2)+pow(y2-y1,2);
  }

  struct conKey
  {
    Uint16 code;
    char key;
    bool arrow;
  };

  static inline string iToa(int a)
  {
    char b[10];
    #ifdef _WIN32
    _itoa_s(a,b,10,10);
    #endif
    #ifdef _unix_
    sprintf(b,"%d",a);
    #endif

    string out = string(b);
    return out;
  }
  static inline string dToa(double a, int decTresh=-1)
  {
    char b[256];   //To hold . and null

    #ifdef _WIN32
    if(decTresh!=-1)
      sprintf_s(b,256,"%.*f",decTresh,a);
    else
      sprintf_s(b,256,"%f",a);
    #endif
    #ifdef _unix_
    if(decTresh!=-1)
      sprintf(b,"%.*f",decTresh,a);
    else
      sprintf(b,"%f",a);
    #endif

    string out = string(b);
    return out;
  }
  template <typename T>T sign (T a)
  {
    if(a > 0)
      return T(1);
    if(a < 0)
      return T(-1);
    else
      return T(0);
  }

  template< class T > inline void SafeDelete( T*& pVal )
  {
    delete pVal;
    pVal = NULL;
  }

  template< class T > inline void SafeDeleteArray( T*& pVal )
  {
    delete[] pVal;
    pVal = NULL;
  }
}