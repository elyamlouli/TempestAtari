/**
 * \file missile.hpp
 * \brief Declaration file of the Missile class
 * \date 08/04/2022
 * \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
 */
#ifndef _MISSILE_HPP_
#define _MISSILE_HPP_

#include "constants.hpp"
#include "tube.hpp"

/**
 * \class Missile
 * \brief Missile class, represent a missile
 */
class Missile
{
private:
    /*!< SDL renderer */
    SDL_Renderer *renderer;

    /*!< tube */
    Tube *tube;

    /*!< Missile position on the tube */
    int position;

    /*!< Missile depth */
    double depth;

    /*!< Quadratic coefficient for the velocity */
    double z;

public:
    /*!
     * \brief Constructor of the class Missile
     * \param tube tube
     * \param position missile position on the tube
     */
    Missile(SDL_Renderer *renderer, Tube *tube, int position);

    /*!
     * \brief Display the missile
     */
    void display();

    /*!
     * \brief Move the missile to the center
     */
    void move();

    /*!
     * \brief Get attribute depth
     * \return the depth of the missile
     */
    double get_depth();

    /*!
     * \brief Get attribute position
     * \return the position of the missile on the tube
     */
    int get_position();
};

#endif