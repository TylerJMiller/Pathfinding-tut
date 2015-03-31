#ifndef _UTIL_H
#define _UTIL_H

#include <glm\glm.hpp>
#include <string>
#include <vector>
#include <queue>
#include <math.h>
#include <iterator>
#include "AIE.h"
#include "KeyStater.h"
#include "Tank.h"
#include <time.h>
#include <list>

const int WINDOWWIDTH = 1024;
const int WINDOWHEIGHT = 720;

const int TILESIZE = 30;

const int GRAPHWIDTH = 10;
const int GRAPHHEIGHT = 10;

const int GRAPHX = 300;
const int GRAPHY = 300;

void Load(), Update(), Draw();

#endif