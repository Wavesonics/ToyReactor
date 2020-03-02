//
// Created by Adam on 2/27/2020.
//

#include "HeatMap.h"
#include "../util/Utils.h"
#include <Engine.hpp>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace nuclearPhysics;
using namespace godot;


HeatMap::HeatMap() : Node2D()
{
    
}

HeatMap::~HeatMap() = default;

void HeatMap::calculateCellSizes(const godot::Rect2 &rect)
{
    cellWidth = rect.size.width / (float)mapSize;
    cellHeight = rect.size.height / (float)mapSize;
}

void HeatMap::addHeat(float heat, const int x, const int y)
{
    if (x < mapSize && y < mapSize && x >= 0 && y >= 0)
    {
        map[y][x] = clamp(map[y][x] + heat, 0.0f, 1.0f);
        // update(); // Happens to often to do this every time
    }
    else
    {
        Godot::print("HeatMap:: index out of range");
    }
}

void HeatMap::_init()
{
    mapSize = DEFAULT_MAP_SIZE;
}

void HeatMap::_ready()
{
    map = new float*[mapSize];
    for (int yy = 0; yy < mapSize; ++yy)
    {
        map[yy] = new float[mapSize];
        for (int xx = 0; xx < mapSize; ++xx)
        {
            map[yy][xx] = 0.0f;
        }
    }
    
    update();
}

void HeatMap::_draw()
{
    constexpr float rectSize = 2.0f;
    auto drawRect = Rect2(Vector2(), Vector2(rectSize, rectSize));
    auto color = Color();

    for (int yy = 0; yy < mapSize; ++yy)
    {
        drawRect.position.y = yy * rectSize;
        
        for (int xx = 0; xx < mapSize; ++xx)
        {
            const float heat = map[yy][xx];

            drawRect.position.x = xx * rectSize;
            color.r = heat;
            
            draw_rect(drawRect, color);
        }
    }
}

void HeatMap::_register_methods()
{
    register_property<HeatMap, int>("mapSize", &HeatMap::mapSize, DEFAULT_MAP_SIZE);

    register_method("addHeat", &HeatMap::addHeat);
    register_method("_init", &HeatMap::_init);
    register_method("_ready", &HeatMap::_ready);
    register_method("_draw", &HeatMap::_draw);
}
