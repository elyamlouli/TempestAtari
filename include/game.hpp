/**
 * \file game.hpp
 * \brief Declaration file of the Game class
 * \date 09/02/2021
 * \author Antoine BALZANO and Hugo LAULLIER
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
 * \brief Game class, represent a tetris game
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

    int score;

    int level;

    int lives;

public:
    /*!
     * \brief Constructor of the class Game
     */
    Game(SDL_Window *window, SDL_Renderer *renderer,
         TTF_Font *font, TTF_Font *font_small);

    /*!
     * \brief Destructor of the class Game
     */
    ~Game();

    /*!
     * \brief method handling inputs of players, board and all other attributes
     */
    bool game_loop(status_t *status,
                   double *delta_t,
                   double *counter,
                   double *counter_input_delay);

    /*!
     * \brief create a loop wanting for a key press to exit the score screen
     * \param status : status of the game
     */
    void score_screen_loop(status_t *status);
    void display_infos();

    /*!
     * \brief launch a game
     */
    status_t play();
};

#endif