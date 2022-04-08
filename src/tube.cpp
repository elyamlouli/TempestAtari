#include "../include/tube.hpp"

Tube::Tube(SDL_Renderer *renderer, int level) : renderer(renderer),
                                                level(level)
{
    // SQUARE
    if (level == 1)
    {
        vertices.push_back(std::make_pair(200, 200));
        vertices.push_back(std::make_pair(600, 200));
        vertices.push_back(std::make_pair(600, 600));
        vertices.push_back(std::make_pair(200, 600));
    }

    // OCTOGONE
    if (level == 2)
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

    // FLOWER
    if (level == 3)
    {
        vertices.push_back(std::make_pair(150, 150));
        vertices.push_back(std::make_pair(400, 200));
        vertices.push_back(std::make_pair(650, 150));
        vertices.push_back(std::make_pair(600, 400));
        vertices.push_back(std::make_pair(650, 650));
        vertices.push_back(std::make_pair(400, 600));
        vertices.push_back(std::make_pair(150, 650));
        vertices.push_back(std::make_pair(200, 400));
    }

    // INFINITY
    if (level == 4)
    {
        vertices.push_back(std::make_pair(100, 400));
        vertices.push_back(std::make_pair(200, 300));
        vertices.push_back(std::make_pair(250, 250));
        vertices.push_back(std::make_pair(380, 300));
        vertices.push_back(std::make_pair(420, 300));
        vertices.push_back(std::make_pair(550, 250));
        vertices.push_back(std::make_pair(600, 300));
        vertices.push_back(std::make_pair(700, 400));
        vertices.push_back(std::make_pair(600, 500));
        vertices.push_back(std::make_pair(550, 550));
        vertices.push_back(std::make_pair(420, 500));
        vertices.push_back(std::make_pair(380, 500));
        vertices.push_back(std::make_pair(250, 550));
        vertices.push_back(std::make_pair(200, 500));
    }
}

Tube::~Tube() {}

void Tube::display()
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < vertices.size(); i++)
    {
        SDL_RenderDrawLine(renderer, vertices[i].first, vertices[i].second, vertices[(i + 1) % vertices.size()].first, vertices[(i + 1) % vertices.size()].second);

        int ABx = vertices[(i + 1) % vertices.size()].first - vertices[i].first;
        int ABy = vertices[(i + 1) % vertices.size()].second - vertices[i].second;
        double normAB = sqrt(ABx * ABx + ABy * ABy);

        double px1, py1;
        transfo2D(vertices[i], vertices[(i + 1) % vertices.size()], 0, 0, px1, py1, MIN_DEPTH_COEF, false);

        double px2, py2;
        transfo2D(vertices[i], vertices[(i + 1) % vertices.size()], normAB, 0, px2, py2, MIN_DEPTH_COEF, false);

        SDL_RenderDrawLine(renderer, px1, py1, px2, py2);
        SDL_RenderDrawLine(renderer, vertices[i].first, vertices[i].second, px1, py1);
    }
}

std::pair<int, int> Tube::get_vertex(int position)
{
    return vertices[position % vertices.size()];
}

int Tube::get_size()
{
    return vertices.size();
}
