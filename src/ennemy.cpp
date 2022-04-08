#include "../include/ennemy.hpp"

Ennemy::Ennemy(SDL_Renderer *renderer, Tube *tube, int position, double time) : renderer(renderer), tube(tube), position(position), time(time)
{
    depth = MIN_DEPTH_COEF;
    z = 1;
}

void Ennemy::display()
{
    SDL_SetRenderDrawColor(renderer, 255, 139, 0, 255);

    int ABx = tube->get_vertex(position + 1).first - tube->get_vertex(position).first;
    int ABy = tube->get_vertex(position + 1).second - tube->get_vertex(position).second;
    double normAB = sqrt(ABx * ABx + ABy * ABy);

    double px1, py1;
    transfo2D(tube->get_vertex(position), tube->get_vertex(position + 1), 0, 0, px1, py1, depth, true);

    double px2, py2;
    transfo2D(tube->get_vertex(position), tube->get_vertex(position + 1), normAB / 16, normAB / 8, px2, py2, depth, true);

    double px3, py3;
    transfo2D(tube->get_vertex(position), tube->get_vertex(position + 1), normAB / 8, 0, px3, py3, depth, true);

    SDL_RenderDrawLine(renderer, px1, py1, px2, py2);
    SDL_RenderDrawLine(renderer, px2, py2, px3, py3);
    SDL_RenderDrawLine(renderer, px3, py3, px1, py1);
}

void Ennemy::move()
{
    z -= 0.0004; // increase this number to increase ennemy speed
    if (z >= 0)
    {
        depth = 1 - (1 - MIN_DEPTH_COEF) * sqrt(z);
    }
    else 
    {
        depth = 1;
    }
}

double Ennemy::get_depth()
{
    return depth;
}

double Ennemy::get_time()
{
    return time;
}

int Ennemy::get_position()
{
    return position;
}