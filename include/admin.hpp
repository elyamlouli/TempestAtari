/**
* \file admin.hpp
* \brief Class Admin
* \date 08/04/2022
* \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
*/
#ifndef _ADMIN_HPP_
#define _ADMIN_HPP_

#include "constants.hpp"
#include "utils.hpp"
#include "game.hpp"

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
     * \brief Start the game
     */
    void start();

    /*!
     * \brief Main menu
     */
    void menu();

    /*!
     * \brief Help menu
     */
    void help();

    /*!
     * \brief Launch a game
     */
    void play();
};

#endif