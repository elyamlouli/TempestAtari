/**
* \file missile.hpp
* \brief Declaration file of the Missile class
* \date 04/02/2022
* \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
*/
#ifndef _MISSILE_HPP_
#define _MISSILE_HPP_

#include "constants.hpp"
#include "tube.hpp"

class Missile
{
private:
    /*!< SDL renderer */
    SDL_Renderer *renderer;

    /*!< tube */
    Tube *tube;

    /*!< Missile position */
    int position;

    /*!< Missile depth */
    double depth;

    double z;

public:
    /*!
     * \brief Constructor of the class Missile
     */
    Missile(SDL_Renderer *renderer, Tube *tube, int position);

    void display();
    void move();
    double get_depth();
    int get_position();
};

#endif