#include "../include/game.hpp"

Game::Game(SDL_Window *window, SDL_Renderer *renderer,
           TTF_Font *font, TTF_Font *font_small) : window(window),
                                                   renderer(renderer),
                                                   font(font),
                                                   font_small(font_small)
{
    score = 0;
    level = 1;
    lives = 5;
    superzapper = true;
    tube = new Tube(renderer, level);
    starship = new Starship(renderer, tube);
    for (int i = 0; i < NUMBER_ENNEMIES_PER_LEVEL; i++)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib_pos(0, tube->get_size() - 1);
        std::uniform_real_distribution<> distrib_time(0, MAX_TIME_LEVEL);
        int position_ennnemy = distrib_pos(gen);
        double time_ennnemy = distrib_time(gen);
        ennemies.push_back(new Ennemy(renderer, tube, position_ennnemy, time_ennnemy));
    }
}

Game::~Game()
{
    delete tube;
    delete starship;
}

status_t Game::play()
{
    Uint64 prev, now = SDL_GetPerformanceCounter(); // timers
    double delta_t;                                 // frame duration in ms
    double counter = 0;

    status_t status = IN_GAME;
    bool game_over = false;

    while (status == IN_GAME)
    {
        prev = now;
        now = SDL_GetPerformanceCounter();
        delta_t = (double)((now - prev) /
                           (double)SDL_GetPerformanceFrequency());
        counter += delta_t;
        game_over = game_loop(&status, &counter);

        if (game_over)
        {
            break;
        }
    }
    while (status == IN_GAME)
    {
        score_screen_loop(&status);
    }
    return status;
}

bool Game::game_loop(status_t *status, double *counter)
{
    // Key management
    while (*status == IN_GAME && SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            *status = QUIT;
            return false;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                *status = QUIT;
                return false;
            case SDLK_m:
                *status = MENU;
                return false;
            case SDLK_s:
                Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                starship->move_left();
                continue;
            case SDLK_RIGHT:
                starship->move_right();
                continue;
            case SDLK_z:
                if (superzapper)
                {
                    for (auto &missile : missiles)
                    {
                        delete missile;
                        missile = nullptr;
                    }
                    missiles.erase(std::remove(missiles.begin(), missiles.end(), nullptr), missiles.end());

                    for (auto &ennemy : ennemies)
                    {
                        if (ennemy->get_time() <= *counter)
                        {
                            delete ennemy;
                            ennemy = nullptr;
                            score += 100;
                        }
                    }
                    ennemies.erase(std::remove(ennemies.begin(), ennemies.end(), nullptr), ennemies.end());

                    superzapper = false;
                    continue;
                }
                break;
            case SDLK_SPACE:
                missiles.push_back(new Missile(renderer, tube, starship->get_position()));
                continue;
            }
            break;
        default:
            break;
        }
    }

    // Background color (black)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    tube->display();
    starship->display();

    for (auto &ennemy : ennemies)
    {
        if (ennemy->get_time() <= *counter)
        {
            ennemy->move();
            if (ennemy->get_depth() >= 1)
            {
                delete ennemy;
                ennemy = nullptr;
                if (lives > 0)
                    lives--;
            }
            else
            {
                ennemy->display();
            }
        }
    }
    ennemies.erase(std::remove(ennemies.begin(), ennemies.end(), nullptr), ennemies.end());

    for (auto &missile : missiles)
    {
        missile->move();
        if (missile->get_depth() <= DEPTH_TUBE_COEF)
        {
            delete missile;
            missile = nullptr;
        }
        else
        {
            missile->display();
        }
    }
    missiles.erase(std::remove(missiles.begin(), missiles.end(), nullptr), missiles.end());

    int first_ennemies_alive_id[tube->get_size()];
    double first_ennemies_alive_depth[tube->get_size()];

    for (int i = 0; i < tube->get_size(); i++)
    {
        first_ennemies_alive_id[i] = -1;
        first_ennemies_alive_depth[i] = -1;
    }

    for (int i = 0; i < ennemies.size(); i++)
    {
        int id = ennemies[i]->get_position();
        if (first_ennemies_alive_id[id] == -1)
        {
            first_ennemies_alive_id[id] = i;
            first_ennemies_alive_depth[id] = ennemies[i]->get_depth();
        }
        else
        {
            if (first_ennemies_alive_depth[id] <= ennemies[i]->get_depth())
            {
                first_ennemies_alive_id[id] = i;
                first_ennemies_alive_depth[id] = ennemies[i]->get_depth();
            }
        }
    }

    bool first_missile_alive_id[tube->get_size()];
    for (int i = 0; i < tube->get_size(); i++)
    {
        first_missile_alive_id[i] = true;
    }

    for (int i = 0; i < missiles.size(); i++)
    {
        int id = missiles[i]->get_position();

        if (first_missile_alive_id[id] && missiles[i]->get_depth() <= first_ennemies_alive_depth[id])
        {
            first_missile_alive_id[id] = false;

            delete missiles[i];
            missiles[i] = nullptr;

            delete ennemies[first_ennemies_alive_id[id]];
            ennemies[first_ennemies_alive_id[id]] = nullptr;

            score += 100;
        }
    }
    missiles.erase(std::remove(missiles.begin(), missiles.end(), nullptr), missiles.end());
    ennemies.erase(std::remove(ennemies.begin(), ennemies.end(), nullptr), ennemies.end());
    display_infos();

    SDL_RenderPresent(renderer);
    if (ennemies.size() == 0)
    {
        level += 1;
        *counter = 0;
        delete tube;
        delete starship;
        tube = new Tube(renderer, level);
        starship = new Starship(renderer, tube);
        for (int i = 0; i < NUMBER_ENNEMIES_PER_LEVEL; i++)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib_pos(0, tube->get_size() - 1);
            std::uniform_real_distribution<> distrib_time(0, MAX_TIME_LEVEL);
            int position_ennnemy = distrib_pos(gen);
            double time_ennnemy = distrib_time(gen);
            ennemies.push_back(new Ennemy(renderer, tube, position_ennnemy, time_ennnemy));    
        }
        superzapper = true;
    }
    if (lives == 0)
    {
        return true;
    }
    return false;
}

void Game::display_infos()
{
    char *text = new char[BUFF_SIZE];
    int width_text;

    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Score : %d", score));
    render_text(renderer, font_small, 40, 40, text);

    TTF_SetFontStyle(font_small, TTF_STYLE_BOLD);
    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "LEVEL %d", level));
    TTF_SizeText(font_small, text, &width_text, NULL);
    render_text(renderer, font_small, (WINDOW_W - width_text) / 2, 40, text);
    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);

    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "Lives : %d", lives));
    TTF_SizeText(font_small, text, &width_text, NULL);
    render_text(renderer, font_small, WINDOW_W - width_text - 40, 40, text);

    if (superzapper)
    {
        render_text(renderer, font_small, 40, WINDOW_H - 80, "SUPERZAPPER");
    }

    delete[] text;
}

void Game::score_screen_loop(status_t *status)
{
    while (*status == IN_GAME && SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            *status = QUIT;
            return;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                *status = QUIT;
                return;
            case SDLK_m:
                *status = MENU;
                return;
            case SDLK_s:
                Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
                break;
            }
            break;
        default:
            break;
        }
    }

    char *text = new char[BUFF_SIZE];
    int width_text;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    TTF_SizeText(font, "GAME OVER", &width_text, NULL);
    render_text(renderer, font, (WINDOW_W - width_text) / 2, 50, "GAME OVER");
    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

    TTF_SetFontStyle(font_small, TTF_STYLE_BOLD);

    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "LEVEL %d REACHED", level));
    TTF_SizeText(font_small, text, &width_text, NULL);
    render_text(renderer, font_small, (WINDOW_W - width_text) / 2, 200, text);

    CHECK_SNPRINFT(snprintf(text, BUFF_SIZE, "SCORE : %d", score));
    TTF_SizeText(font_small, text, &width_text, NULL);
    render_text(renderer, font_small, (WINDOW_W - width_text) / 2, 250, text);

    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);

    TTF_SetFontStyle(font_small, TTF_STYLE_ITALIC);

    TTF_SizeText(font_small, "Press M - menu", &width_text, NULL);
    render_text(renderer, font_small, (WINDOW_W - width_text) / 2, 525, "Press M - menu");

    TTF_SizeText(font_small, "Press Escape - quit", &width_text, NULL);
    render_text(renderer, font_small, (WINDOW_W - width_text) / 2, 600, "Press Escape - quit");

    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);

    SDL_RenderPresent(renderer);

    delete[] text;
}