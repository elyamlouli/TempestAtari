/**
* \file admin.hpp
* \brief Class Admin
* \date 04/02/2022
* \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
*/
#ifndef _ADMIN_HPP_
#define _ADMIN_HPP_

#include "constants.hpp"
#include "utils.hpp"

/**
* \class Admin
* \brief Admin class handling menus and games
*/
class Admin
{
private:
    /*!< status of the game IN_GAME, QUIT, PLAY, MENU, HELP */
    status_t status;

    /*!< SDL renderer */
    SDL_Renderer *renderer;

    /*!< SDL window */
    SDL_Window *window;

    /*!< SDL event */
    SDL_Event event;

    /*!< SDL soundtrack */
    Mix_Music *soundtrack;

    /*!< SDL shoot sound */
    Mix_Music *shoot_sound;

    /*!< normal text font */
    TTF_Font *font;

    /*!< small text font */
    TTF_Font *font_small;

public:
    /*!
     * \brief Constructor of the class Admin
     */
    Admin();

    /*!
     * \brief Destructor of the class Admin
     */
    ~Admin();

    /*!
     * \brief Load text font
     */
    void load_font();

    /*!
     * \brief start the game
     */
    void start();

    /*!
     * \brief main menu
     */
    void menu();

    /*!
     * \brief help menu
     */
    void help();
};

#endif