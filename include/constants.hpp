
/**
* \file constants.hpp
* \brief Declaration file of constants
* \date 08/04/2022
* \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
*/
#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SDL2/SDL_mixer.h"
#include <random>
#include <algorithm>


/** 
 * \def DEPTH_TUBE_COEF
 * \brief Coeffient that indicates the depth of the tube
 */
#define DEPTH_TUBE_COEF 0.07


/** 
 * \def MISSILE_VELOCITY_COEF
 * \brief Coefficient that indicates the velocity of a missile
 */
#define MISSILE_VELOCITY_COEF 0.05


/** 
 * \def ENNEMY_VELOCITY_COEF
 * \brief Coefficient that indicates the velocity of an ennemy
 */
#define ENNEMY_VELOCITY_COEF 0.007


/** 
 * \def NUMBER_ENNEMIES_PER_LEVEL
 * \brief Number of ennemies per level
 */
#define NUMBER_ENNEMIES_PER_LEVEL 20

/** 
 * \def MAX_TIME_LEVEL
 * \brief Maximum duration of a level
 */
#define MAX_TIME_LEVEL 20

/** 
 * \def WINDOW_W
 * \brief Window width
 */
#define WINDOW_W 800

/** 
 * \def WINDOW_H
 * \brief Window height
 */
#define WINDOW_H 800


/** 
 * \def status_t
 * \brief Represent of the game IN_GAME, QUIT, PLAY, MENU, HELP
 */
enum status_t {IN_GAME, QUIT, PLAY, MENU, HELP}; 


/** 
 * \def BUFF_SIZE
 * \brief Buffer size for static allocation
 */
#define BUFF_SIZE 1024

#endif