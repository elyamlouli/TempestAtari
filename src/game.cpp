#include "../include/game.hpp"

Game::Game(SDL_Window *window, SDL_Renderer *renderer,
           TTF_Font *font, TTF_Font *font_small) : window(window),
                             renderer(renderer),
                             font(font),
                             font_small(font_small) {}

Game::~Game()
{
    printf("Yolo");
}

void Game::game_loop(status_t *status, double *delta_t, double *counter, double *counter_input_delay)
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

    // Background color (black)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    

    SDL_RenderPresent(renderer);
}


status_t Game::play()
{
    Uint64 prev, now = SDL_GetPerformanceCounter(); // timers
    double delta_t;                                 // frame duration in ms
    double counter = 0;
    double counter_input_delay = 0;

    status_t status = IN_GAME;
    bool game_over = false;
    int score = 0; 
    while (status == IN_GAME)
    {
        if (!game_over)
        {
            // update timers and counters
            prev = now;
            now = SDL_GetPerformanceCounter();
            delta_t = (double)((now - prev) /
                               (double)SDL_GetPerformanceFrequency());
            counter += delta_t;
            counter_input_delay += delta_t;
            game_loop(&status, &delta_t, &counter, &counter_input_delay);
        }
        else
        {
            break;
        }
        
    }
    while (status == IN_GAME)
    {
        // update timers and counters
        prev = now;
        now = SDL_GetPerformanceCounter();
        delta_t = (double)((now - prev) /
                           (double)SDL_GetPerformanceFrequency());
        score_screen_loop(&status);
        
        // Cap to 60 FPS
        int delay_ms = (int)floor(16.666f - delta_t);
        if (delay_ms < 100 && delay_ms > 0)
            SDL_Delay(delay_ms);
    }
    return status;
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
}