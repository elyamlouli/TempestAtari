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

void transfo2D(std::pair<int, int> A, std::pair<int, int> B, int px, int py, double &new_px, double &new_py, double depth_coef, bool middle)
{
    int center_shift = 400;

    int ABx = B.first - A.first;
    int ABy = B.second - A.second;
    double normAB = sqrt(ABx * ABx + ABy * ABy);
    double ux = ABx / normAB;
    double uy = ABy / normAB;

    if (middle) {
        new_px =  (ux * px - uy * py + (A.first + B.first)/2 - center_shift) * depth_coef + center_shift;
        new_py = (uy * px + ux * py + (A.second + B.second)/2 - center_shift) * depth_coef + center_shift;
    }

    else {
        new_px =  (ux * px - uy * py + A.first - center_shift) * depth_coef + center_shift;
        new_py = (uy * px + ux * py + A.second - center_shift) * depth_coef + center_shift;
    }

}

[[noreturn]] void handle_perror(const char *msg, ...)
{
    va_list ap;

    va_start(ap, msg);
    vfprintf(stderr, "perror : ", ap);
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    perror("");

    exit(EXIT_FAILURE);
}
