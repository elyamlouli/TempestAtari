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
void transfo2D(std::pair<int, int> A, std::pair<int, int> B, int px, int py, double &new_px, double &new_py, double depth_coef, bool middle);

#define CHECK_SNPRINFT(n) do {if(n<0||n>=BUFF_SIZE)handle_perror(#n);}while(0)

/*!
* \brief exit program with a given error message
* \param msg : message to print in stderr
*/
[[ noreturn ]] void handle_error(const char * msg, ...);

/*!
* \brief exit program with a given error message
* \param msg : message to print in stderr
*/
[[ noreturn ]] void handle_perror(const char * msg, ...);

#endif