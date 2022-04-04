/**
* \file utils.hpp
* \brief Declaration file of useful general functions
* \date 04/02/2022
* \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
*/
#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include "constants.hpp"

/*!
* \brief render text in canevas at position x,y
*/
void render_text(SDL_Renderer *renderer, TTF_Font *font, int x, int y, const char *text);

#endif