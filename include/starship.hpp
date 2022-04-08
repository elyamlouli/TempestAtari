/**
* \file starship.hpp
* \brief Declaration file of the Starship class
* \date 08/04/2022
* \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
*/
#ifndef _STARSHIP_HPP_
#define _STARSHIP_HPP_

#include "constants.hpp"
#include "tube.hpp"
#include "utils.hpp"

/**
* \class Starship
* \brief Starship class, represent the player starship
*/
class Starship
{
private:
    /*!< SDL renderer */
    SDL_Renderer *renderer;

    /*!< tube */
    Tube *tube;

    /*!< starship position */
    int position;

public:
    /*!
     * \brief Constructor of the class Starship
     * \param renderer SDL renderer
     * \param tube tube
     */
    Starship(SDL_Renderer *renderer, Tube *tube);

    /*!
     * \brief Display the starship
     */
    void display();

    /*!
     * \brief Move the ennemy in the left direction
     */
    void move_left();

    /*!
     * \brief Move the ennemy in the right direction
     */
    void move_right();

    /*!
     * \brief Get attribute position
     * \return the position of the starship on the tube
     */
    int get_position();
};


    
#endif