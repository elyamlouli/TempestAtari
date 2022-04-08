/**
* \file ennemy.hpp
* \brief Declaration file of the Ennemy class
* \date 08/04/2022
* \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
*/
#ifndef _ENNEMY_HPP_
#define _ENNEMY_HPP_

#include "constants.hpp"
#include "tube.hpp"

/**
 * \class Ennemy
 * \brief Ennemy class, represent an ennemy
 */
class Ennemy
{
private:
    /*!< SDL renderer */
    SDL_Renderer *renderer;

    /*!< tube */
    Tube *tube;

    /*!< Ennemy position on the tube */
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
     * \param renderer SDL renderer
     * \param tube tube
     * \param position enemmy position on the tube
     * \param time appearance time
     */
    Ennemy(SDL_Renderer *renderer, Tube *tube, int position, double time);

    /*!
     * \brief Display the ennemy
     */
    void display();

    /*!
     * \brief Move the ennemy to the periphery
     */
    void move();

    /*!
     * \brief Get attribute depth
     * \return the depth of the ennemy
     */
    double get_depth();

    /*!
     * \brief Get attribute time
     * \return the appearance time of the ennemy
     */
    double get_time();

    /*!
     * \brief Get attribute position
     * \return the position of the ennemy on the tube
     */
    int get_position();
};

#endif