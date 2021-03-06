#include "../include/admin.hpp"

Admin::~Admin()
{
    TTF_CloseFont(font);
    TTF_CloseFont(font_small);
    TTF_Quit();
    Mix_FreeMusic(soundtrack);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Admin::load_font()
{
    // Normal font
    font = TTF_OpenFont("./font/Hursheys.ttf", 70);
    if (font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    // Small font
    font_small = TTF_OpenFont("./font/Hursheys.ttf", 30);
    if (font_small == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
}


Admin::Admin() : status(MENU)
{
    // SDL initializations
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        fprintf(stderr, "error: SDL Init\n");
        exit(EXIT_FAILURE);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) 
        == -1) 
    {
        fprintf(stderr, "%s", Mix_GetError());
        exit(EXIT_FAILURE);
    }

    soundtrack = Mix_LoadMUS("./mp3/soundtrack.mp3");
    Mix_PlayMusic(soundtrack, -1);
    Mix_PauseMusic();


    TTF_Init();

    // Window
    window = SDL_CreateWindow("Tempest",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_W,
                              WINDOW_H,
                              SDL_WINDOW_SHOWN);

    // Renderer on the window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load font
    load_font();
}

void Admin::start()
{
    Uint64 prev, now = SDL_GetPerformanceCounter(); 
    double delta_t; 

    while (status != QUIT)
    {
        prev = now;
        now = SDL_GetPerformanceCounter();
        delta_t = (double)((now-prev) / (double)SDL_GetPerformanceFrequency());

        // Menu options
        switch (status)
        {
        case MENU:
            menu();
            break;
        case PLAY:
            play();
            break;
        case HELP:
            help();
            break;
        default:
            break;
        }

        // Set to 60 fps to manage the fluidity
        int delay_ms = (int)floor(16.666f - delta_t);
        if (delay_ms < 100 && delay_ms > 0)
            SDL_Delay(delay_ms);
    }
}

void Admin::menu()
{
    // Key management
    while (status == MENU && SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            status = QUIT;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                status = QUIT;
                break;
            case SDLK_RETURN:
                status = PLAY;
                break;
            case SDLK_h:
                status = HELP;
                break;
            case SDLK_s:
                Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
                break;
            }
            break;
        default:
            break;
        }
    }

    // Display menu
    int width_text;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    TTF_SizeText(font, "TEMPEST", &width_text, NULL);
    render_text(renderer, font, (WINDOW_W - width_text)/2, 50, "TEMPEST");

    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
    TTF_SetFontStyle(font_small, TTF_STYLE_ITALIC);

    TTF_SizeText(font_small, "Press ENTER - play", &width_text, NULL);
    render_text(renderer, font_small, (WINDOW_W - width_text)/2, 300, "Press ENTER - play");


    TTF_SizeText(font_small, "Press H - display help", &width_text, NULL);
    render_text(renderer, font_small, (WINDOW_W - width_text)/2, 375, "Press H - display help");

    TTF_SizeText(font_small, "Press Escape - quit", &width_text, NULL);
    render_text(renderer, font_small, (WINDOW_W - width_text)/2, 450, "Press Escape - quit");

    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);
    SDL_RenderPresent(renderer);

}

void Admin::help()
{
    // Key management
    while (status == HELP && SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            status = QUIT;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                status = QUIT;
                break;
            case SDLK_m:
                status = MENU;
                break;
            case SDLK_s:
                Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
                break;
            }
            break;
        default:
            break;
        }
    }

    // Display help
    int offset_x = 40;
    int offset_y = 120;
    int width_text;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    TTF_SizeText(font, "HELP : CONTROLS", &width_text, NULL);
    render_text(renderer, font, (WINDOW_W - width_text)/2, 50, "HELP : CONTROLS");
   
    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
    render_text(renderer, font_small, offset_x, offset_y + 50,
                "Left arrow : move left");
    render_text(renderer, font_small, offset_x, offset_y + 100,
                "Right arrow : move right");
    render_text(renderer, font_small, offset_x, offset_y + 150,
                "Spacebar : fire");
    render_text(renderer, font_small, offset_x, offset_y + 200,
                "Z : superzapper");
    render_text(renderer, font_small, offset_x, offset_y + 250,
                "S : play/stop music");
    TTF_SizeText(font_small, "Press M - return to menu", 
        &width_text, NULL);
    render_text(renderer, font_small, (WINDOW_W - width_text)/2, offset_y + 500, "Press M - return to menu");
    TTF_SizeText(font_small, "Press Escape - quit", &width_text, NULL);
    render_text(renderer, font_small, (WINDOW_W - width_text)/2, offset_y + 550, "Press Escape - quit");
    TTF_SetFontStyle(font_small, TTF_STYLE_NORMAL);
    SDL_RenderPresent(renderer);
}

void Admin::play()
{
    Game *game = new Game(window,
                     renderer,
                     font,
                     font_small);
    status = game->play();
    delete game;

}