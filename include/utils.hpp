/**
* \file utils.hpp
* \brief Declaration file of useful general functions
* \date 08/04/2022
* \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
*/
#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include "constants.hpp"

/*!
* \brief render text in canevas at position x,y
* \param renderer : SDL renderer
* \param font : normal text font
* \param x : x position
* \param y : y position
* \param msg : message to print in stderr
*/
void render_text(SDL_Renderer *renderer, TTF_Font *font, int x, int y, const char *text);

/*!
* \brief render text in canevas at position x,y
* \param A : position of the left corner of the vertex
* \param B : position of the right corner of the vertex
* \param px : x position of the point in the window coordinate system
* \param py : y position of the point in the window coordinate system
* \param new_px : x position of the point in the vertex coordinate system
* \param new_py : y position of the point in the vertex coordinate system
* \param depth_coef : depth coefficient that indicates the depth of the point in the vertex 
* \param middle : boolean to know if, on the periphery, the point would be on the middle or in the left corner
*/
void transfo2D(std::pair<int, int> A, std::pair<int, int> B, int px, int py, double &new_px, double &new_py, double depth_coef, bool middle);

#define CHECK_SNPRINFT(n) do {if(n<0||n>=BUFF_SIZE)handle_perror(#n);}while(0)

/*!
* \brief exit program with a given error message
* \param msg : message to print in stderr
*/
[[ noreturn ]] void handle_perror(const char * msg, ...);

#endif