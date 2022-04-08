/**
* \file tube.hpp
* \brief Declaration file of the class Tube
* \date 08/04/2022
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
     * \param renderer SDL renderer
     * \param level level
     */
    Tube(SDL_Renderer *renderer, int level);

    /*!
     * \brief Display the tube
     */
    void display();

    /*!
     * \brief Get coordinates that indicates the vertex position on the screen
     * \param position position of the vertex on the tube
     * \return coordinates of the left corner of the peripheric segment at 
     * the periphery of a vertex of the tube
     */
    std::pair<int, int> get_vertex(int position);

    /*!
     * \brief Get the size of the attribute vertices
     * \return the number of vertices in the tube
     */
    int get_size();
};


    
#endif