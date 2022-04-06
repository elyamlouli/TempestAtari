/**
* \file utils.hpp
* \brief Declaration file of useful general functions
* \date 04/02/2022
* \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
*/
#ifndef _ENNEMY_HPP_
#define _ENNEMY_HPP_

#include "constants.hpp"
#include "tube.hpp"

class Ennemy
{
private:
    /*!< SDL renderer */
    SDL_Renderer *renderer;

    /*!< tube */
    Tube *tube;

    /*!< Ennemy position */
    int position;

    /*!< Ennemy depth */
    double depth;

    double z;

    double time;

public:
    /*!
     * \brief Constructor of the class Ennemy
     */
    Ennemy(SDL_Renderer *renderer, Tube *tube, int position, double time);

    void display();
    void move();
    double get_depth();
    double get_time();
    int get_position();
};

#endif