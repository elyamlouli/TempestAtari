
/**
* \file constants.hpp
* \brief Declaration file of constants
* \date 04/02/2022
* \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
*/
#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#include <vector>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SDL2/SDL_mixer.h"
#include <random>
#include <algorithm>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <climits>

/** 
 * \def status_t
 * \brief represent the status of the game, in menu, in game, in help, etc ...
 */
enum status_t {IN_GAME, QUIT, PLAY, MENU, HELP}; 


#define MIN_DEPTH_COEF 0.07

#define MAX_NUMBER_ENNEMIES 50

#define TIME_LEVEL 30

/** 
 * \def WINDOW_W
 * \brief window width
 */
#define WINDOW_W 800

/** 
 * \def WINDOW_H
 * \brief window height
 */
#define WINDOW_H 800


/** 
 * \def BUFF_SIZE
 * \brief buff size for static allocation
 */
#define BUFF_SIZE 1024

#endif