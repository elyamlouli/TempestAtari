#include "../include/tube.hpp"

Tube::Tube(SDL_Renderer *renderer, int level) : renderer(renderer),
                                                level(level)
{
    vertices.push_back(std::make_pair(200, 200));
    vertices.push_back(std::make_pair(400, 100));
    vertices.push_back(std::make_pair(600, 200));
    vertices.push_back(std::make_pair(700, 400));
    vertices.push_back(std::make_pair(600, 600));
    vertices.push_back(std::make_pair(400, 700));
    vertices.push_back(std::make_pair(200, 600));
    vertices.push_back(std::make_pair(100, 400));
}

Tube::~Tube() {}

void Tube::display()
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < vertices.size(); i++)
    {
        SDL_RenderDrawLine(renderer, vertices[i].first, vertices[i].second, vertices[(i+1)%vertices.size()].first, vertices[(i+1)%vertices.size()].second);
        
        int ABx = vertices[(i+1)%vertices.size()].first - vertices[i].first;
        int ABy = vertices[(i+1)%vertices.size()].second - vertices[i].second;
        double normAB = sqrt(ABx*ABx + ABy*ABy);

        double px1, py1;
        transfo2D(vertices[i], vertices[(i+1)%vertices.size()], 0, 0, px1, py1);

        double px2, py2;
        transfo2D(vertices[i], vertices[(i+1)%vertices.size()], normAB, 0, px2, py2);

        double p = 0.7;
        int center_shift = 400;
        
        SDL_RenderDrawLine(renderer, px1, py1, px2, py2);
        SDL_RenderDrawLine(renderer, vertices[i].first, vertices[i].second, px1, py1);

    }
}

std::pair<int, int> Tube::get_vertex(int position) {
    return vertices[position%vertices.size()];
}

int Tube::get_size() {
    return vertices.size();
}
