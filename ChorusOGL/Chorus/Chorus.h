#pragma once

#include <iostream>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "console/Console.h"
#include "content/Content.h"
#include "core/ChorusCore.h"
#include "camera/Camera2D.h"
#include "debug/Debug.h"
#include "draw/SpriteBatch.h"
#include "input/XBOXController.h"

//#include <SDL_opengl.h>

#pragma comment(lib, "opengl32.lib")