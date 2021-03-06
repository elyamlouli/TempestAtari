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
    create_level();
}

Game::~Game()
{
    delete starship;
    for (auto &ennemy : ennemies)
    {
        delete ennemy;
    }
    delete tube;
}

status_t Game::play()
{
    Uint64 prev, now = SDL_GetPerformanceCounter();
    double delta_t;
    double counter = 0;

    status_t status = IN_GAME;
    bool game_over = false;

    // Game
    while (status == IN_GAME)
    {
        prev = now;
        now = SDL_GetPerformanceCounter();
        delta_t = (double)((now - prev) /
                           (double)SDL_GetPerformanceFrequency());
        counter += delta_t;

        // Game loop
        game_over = game_loop(&status, &counter);

        // Set to 60 fps to manage the fluidity
        int delay_ms = (int)floor(16.666f - delta_t);
        if (delay_ms < 100 && delay_ms > 0)
            SDL_Delay(delay_ms);

        if (game_over)
            break;
    }

    // Results
    while (status == IN_GAME)
    {
        display_scores_loop(&status);

        // Set to 60 fps to manage the fluidity
        int delay_ms = (int)floor(16.666f - delta_t);
        if (delay_ms < 100 && delay_ms > 0)
            SDL_Delay(delay_ms);
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
            case SDLK_SPACE:
                missiles.push_back(new Missile(renderer, tube, starship->get_position()));
                continue;
            case SDLK_z:
                superzapper_management(*counter);
                continue;
            }
            break;
        default:
            break;
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Manage ennemies and missiles
    move_ennemies(*counter);
    move_missiles();
    manage_destructions();

    // Manage tube and starship
    tube->display();
    starship->display();

    // Display infos
    display_infos();

    SDL_RenderPresent(renderer);

    // If end of level
    if (ennemies.size() == 0)
    {
        // Delete missiles, tube and starship
        for (auto &missile : missiles)
        {
            delete missile;
        }
        missiles.clear();
        delete tube;
        delete starship;

        // Create the next level
        level += 1;
        *counter = 0;
        create_level();
    }

    // Condition end of the game
    if (lives == 0 or level == 4)
        return true;

    return false;
}

void Game::create_level()
{
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

void Game::superzapper_management(int counter)
{
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
            if (ennemy->get_time() <= counter)
            {
                delete ennemy;
                ennemy = nullptr;
                score += 100;
            }
        }
        ennemies.erase(std::remove(ennemies.begin(), ennemies.end(), nullptr), ennemies.end());

        superzapper = false;
    }
}

void Game::move_ennemies(int counter)
{
    for (auto &ennemy : ennemies)
    {
        if (ennemy->get_time() <= counter)
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
                ennemy->display();
        }
    }
    ennemies.erase(std::remove(ennemies.begin(), ennemies.end(), nullptr), ennemies.end());
}

void Game::move_missiles()
{
    for (auto &missile : missiles)
    {
        missile->move();
        if (missile->get_depth() <= DEPTH_TUBE_COEF)
        {
            delete missile;
            missile = nullptr;
        }
        else
            missile->display();
    }
    missiles.erase(std::remove(missiles.begin(), missiles.end(), nullptr), missiles.end());
}

void Game::manage_destructions()
{
    // Find the first ennemy of each vertex
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

    // Manage destruction of an ennemy by a missile
    bool first_missile_alive_id[tube->get_size()];
    for (int i = 0; i < tube->get_size(); i++)
    {
        first_missile_alive_id[i] = true;
    }

    for (int i = 0; i < missiles.size(); i++)
    {
        int id = missiles[i]->get_position();

        if (first_ennemies_alive_id[id] != -1 && first_missile_alive_id[id] && missiles[i]->get_depth() <= first_ennemies_alive_depth[id])
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

void Game::display_scores_loop(status_t *status)
{
    // Key management
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

    // Display scores
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