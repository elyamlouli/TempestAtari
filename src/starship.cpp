#include "../include/starship.hpp"

Starship::Starship(SDL_Renderer *renderer, int position, Tube *tube) : renderer(renderer),
                                                position(position), tube(tube) {}

void Starship::display()
{
    SDL_SetRenderDrawColor(renderer, 247, 255, 0, 255);
    SDL_RenderDrawLine(renderer, tube->get_vertex(position).first, tube->get_vertex(position).second, tube->get_vertex(position+1).first, tube->get_vertex(position+1).second);

    int ABx = tube->get_vertex(position+1).first - tube->get_vertex(position).first;
    int ABy = tube->get_vertex(position+1).second - tube->get_vertex(position).second;
    double normAB = sqrt(ABx*ABx + ABy*ABy);

    double px1, py1;
    transfo2D(tube->get_vertex(position), tube->get_vertex(position+1), 0, 0, px1, py1, MIN_DEPTH_COEF, false);

    double px2, py2;
    transfo2D(tube->get_vertex(position), tube->get_vertex(position+1), normAB, 0, px2, py2, MIN_DEPTH_COEF, false);

    
    SDL_RenderDrawLine(renderer, px1, py1, px2, py2);
    SDL_RenderDrawLine(renderer, tube->get_vertex(position).first, tube->get_vertex(position).second, px1, py1);
    SDL_RenderDrawLine(renderer, tube->get_vertex(position+1).first, tube->get_vertex(position+1).second, px2, py2);
}

void Starship::move_left(void) {
    position = position - 1;
    if (position < 0) {
        position = tube->get_size() - 1;
    }
}

void Starship::move_right(void) {
    position = (position + 1)%(tube->get_size());
}

int Starship::get_position(void) {
    return position;
}