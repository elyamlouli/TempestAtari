/**
* \file utils.hpp
* \brief Declaration file of useful general functions
* \date 04/02/2022
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
     */
    Starship(SDL_Renderer *renderer, int position, Tube *tube);

    void display();

    void move_left(void);
    void move_right(void);
    int get_position(void);
};


    
#endif