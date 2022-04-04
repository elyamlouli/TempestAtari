#include "../include/utils.hpp"

void render_text(SDL_Renderer *renderer, TTF_Font *font,
                 int x, int y, const char *text)
{
    SDL_Surface *message =
        TTF_RenderText_Shaded(font, text, {0, 255, 240}, {0, 0, 0});
    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(renderer, message);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect rect = {x, y, texW, texH};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(message);
    SDL_DestroyTexture(texture);
}