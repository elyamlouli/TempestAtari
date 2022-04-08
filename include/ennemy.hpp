/**
* \file ennemy.hpp
* \brief Declaration file of the Ennemy class
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

    /*!< Quadratic coefficient for the velocity */
    double z;

    /*!< Appearance time */
    double time;

public:
    /*!
     * \brief Constructor of the class Ennemy
     */
    Ennemy(SDL_Renderer *renderer, Tube *tube, int position, double time);

    /*!
     * \brief Display the ennemy
     */
    void display();

    /*!
     * \brief Move the enemy to the periphery
     */
    void move();

    /*!
     * \brief Get attribute depth
     */
    double get_depth();

    /*!
     * \brief Get attribute time
     */
    double get_time();

    /*!
     * \brief Get attribute position
     */
    int get_position();
};

#endif