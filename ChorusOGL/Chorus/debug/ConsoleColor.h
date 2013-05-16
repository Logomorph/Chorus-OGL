#pragma once
#include <iostream>

#ifdef _WIN32
#define COLOR
#endif

#ifdef COLOR

#include <windows.h>

#endif

//namespace Chorus
//{


inline std::ostream& blue(std::ostream &s)
{
#ifdef COLOR
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
  SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
    |FOREGROUND_GREEN|FOREGROUND_INTENSITY);
#endif
  return s;
}

inline std::ostream& red(std::ostream &s)
{
#ifdef COLOR
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
  SetConsoleTextAttribute(hStdout, 
    FOREGROUND_RED|FOREGROUND_INTENSITY);
#endif
  return s;
}

inline std::ostream& green(std::ostream &s)
{
#ifdef COLOR
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
  SetConsoleTextAttribute(hStdout, 
    FOREGROUND_GREEN|FOREGROUND_INTENSITY);
#endif
  return s;
}

inline std::ostream& yellow(std::ostream &s)
{
#ifdef COLOR
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
  SetConsoleTextAttribute(hStdout, 
    FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
#endif
  return s;
}

inline std::ostream& white(std::ostream &s)
{
#ifdef COLOR
  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
  SetConsoleTextAttribute(hStdout, 
    FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
#endif
  return s;
}

struct color {
  color(short attribute):m_color(attribute){};
  short m_color;
};

template <class _Elem, class _Traits>
std::basic_ostream<_Elem,_Traits>& 
operator<<(std::basic_ostream<_Elem,_Traits>& i, color& c)
{
#ifdef COLOR
  HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE); 
  SetConsoleTextAttribute(hStdout,c.m_color);
#endif
  return i;
}

//}

// Copyleft Vincent Godin