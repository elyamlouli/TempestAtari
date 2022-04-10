/**
 * \file game.hpp
 * \brief Declaration file of the Game class
 * \date 08/04/2022
 * \author Vagnona ANDRIANANDRASANA-DINA and Théo BASTIEN
 */
#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "constants.hpp"
#include "tube.hpp"
#include "starship.hpp"
#include "missile.hpp"
#include "ennemy.hpp"

/**
 * \class Game
 * \brief Game class, represent a Tempest game
 */
class Game
{
private:
    /*!< SDL event */
    SDL_Event event;

    /*!< SDL renderer */
    SDL_Renderer *renderer;

    /*!< SDL window */
    SDL_Window *window;

    /*!< normal text font */
    TTF_Font *font;

    /*!< small text font */
    TTF_Font *font_small;

    /*!< tube */
    Tube *tube;

    /*!< starship */
    Starship *starship;

    /*!< missiles */
    std::vector<Missile *> missiles;

    /*!< ennemies */
    std::vector<Ennemy *> ennemies;

    /*!< score */
    int score;

    /*!< level */
    int level;

    /*!< lives remaining */
    int lives;

    /*!< usability of the superzapper */
    bool superzapper;

    /*!
     * \brief Loop that handles the operation of the game
     * \param status status of the game
     * \param counter time from the begining od the launched game
     * \return boolean to know if the game is over
     */
    bool game_loop(status_t *status,
                   double *counter);

    /*!
     * \brief Create a level by creating the tube, the starship, the
     * ennemies and the superzapper
     */
    void create_level();

    /*!
     * \brief If the superzapper is usable, destroy all the ennemies
     * \param counter time from the begining od the launched game
     */
    void superzapper_management(int counter);

    /*!
     * \brief Move the ennemies
     * \param counter time from the begining od the launched game
     */
    void move_ennemies(int counter);

    /*!
     * \brief Move the missiles
     */
    void move_missiles();

    /*!
     * \brief Manage destructions of ennemies by missiles
     */
    void manage_destructions();

    /*!
     * \brief Display infos of the game (score, level, lives and superzapper)
     */
    void display_infos();

    /*!
     * \brief Loop that handles the display of the end the game
     * \param status status of the game
     */
    void display_scores_loop(status_t *status);

public:
    /*!
     * \brief Constructor of the class Game
     * \param window SDL window
     * \param renderer SDL renderer
     * \param font normal text font
     * \param font_small small text font
     */
    Game(SDL_Window *window, SDL_Renderer *renderer,
         TTF_Font *font, TTF_Font *font_small);

    /*!
     * \brief Destructor of the class Game
     */
    ~Game();

    /*!
     * \brief Launch a game
     * \return status of the game
     */
    status_t play();
};

#endif