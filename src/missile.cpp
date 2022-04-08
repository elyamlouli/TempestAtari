#include "../include/missile.hpp"

Missile::Missile(SDL_Renderer *renderer, Tube *tube, int position) : renderer(renderer), tube(tube), position(position) 
{
    depth = 1;
    z = 0;
}

void Missile::display()
{
    SDL_SetRenderDrawColor(renderer, 247, 255, 0, 255);

    double px1, py1;
    transfo2D(tube->get_vertex(position), tube->get_vertex(position+1), 0, 0, px1, py1, depth, true);

    double px2, py2;
    transfo2D(tube->get_vertex(position), tube->get_vertex(position+1), 0, 45, px2, py2, depth, true);

    SDL_RenderDrawLine(renderer, px1, py1, px2, py2);
}

void Missile::move()
{
    z += MISSILE_VELOCITY_COEF;
    depth = 1/(1 + (1 - DEPTH_TUBE_COEF)*z*z);
}

double Missile::get_depth()
{
    return depth;
}

int Missile::get_position()
{
    return position;
}