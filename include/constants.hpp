
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
 * \def DEPTH_TUBE_COEF
 * \brief coeffient that indicates the depth of the tube
 */
#define DEPTH_TUBE_COEF 0.07


/** 
 * \def MISSILE_VELOCITY_COEF
 * \brief coefficient that indicates the velocity of a missile
 */
#define MISSILE_VELOCITY_COEF 0.005


/** 
 * \def ENNEMY_VELOCITY_COEF
 * \brief coefficient that indicates the velocity of an ennemy
 */
#define ENNEMY_VELOCITY_COEF 0.0004


/** 
 * \def NUMBER_ENNEMIES_PER_LEVEL
 * \brief represent the status of the game, in menu, in game, in help, etc ...
 */
#define NUMBER_ENNEMIES_PER_LEVEL 50

/** 
 * \def MAX_TIME_LEVEL
 * \brief maximum duration of a level
 */
#define MAX_TIME_LEVEL 30

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
 * \def status_t
 * \brief represent the status of the game, in menu, in game, in help, etc ...
 */
enum status_t {IN_GAME, QUIT, PLAY, MENU, HELP}; 


/** 
 * \def BUFF_SIZE
 * \brief buff size for static allocation
 */
#define BUFF_SIZE 1024

#endif