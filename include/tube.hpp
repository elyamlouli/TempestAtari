/**
* \file utils.hpp
* \brief Declaration file of useful general functions
* \date 04/02/2022
* \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
*/
#ifndef _TUBE_HPP_
#define _TUBE_HPP_

#include "constants.hpp"
#include "utils.hpp"

/**
* \class Tube
* \brief Tube class, represent a tube
*/
class Tube
{
private:
    /*!< SDL renderer */
    SDL_Renderer *renderer;

    /*!< Level */
    int level;

    /*!< Vertices */
    std::vector<std::pair<int, int>> vertices;



public:
    /*!
     * \brief Constructor of the class Tube
     */
    Tube(SDL_Renderer *renderer, int level);

    /*!
     * \brief Destructor of the class Tube
     */
    ~Tube();

    void display();

    std::pair<int, int> get_vertex(int position);

    int get_size();
};


    
#endif