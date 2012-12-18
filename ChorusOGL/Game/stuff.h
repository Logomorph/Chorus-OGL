#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include "../Chorus/app/ChorusApp.h"
#include "../Chorus/scene/GameScene.h"

using namespace std;
using namespace Chorus;


const int		SCREEN_WIDTH	=1280;
const int		SCREEN_HEIGHT	=800;
const int		VSCREEN_WIDTH	=1280;
const int		VSCREEN_HEIGHT	=800;
const bool		FULLSCREEN		=false;

ChorusApp *chApp;
Camera2D *cam;

Texture tex,tex2;
Font fnt;
float zoom=1.0f;


//XBOXController *player1;

GameScene *scene;

