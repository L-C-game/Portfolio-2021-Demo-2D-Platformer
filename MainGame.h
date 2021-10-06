// Utilities for the main game cpp file

#pragma once
#include "Play.h"

int DISPLAY_WIDTH = 256;
int DISPLAY_HEIGHT = 224;
int DISPLAY_SCALE = 4;

struct GameState
{

};

bool HasCollided(Point2f pos1, Point2f pos2);

constexpr int S_SCREEN_LIMIT = 50;