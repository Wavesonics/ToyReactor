//
// Created by Adam on 2/28/2020.
//

#ifndef REACTORCPPTEST_UTILS_H
#define REACTORCPPTEST_UTILS_H

#include <iostream>
#include <Vector2.hpp>

float randf(const float min, const float max);

float randPercent();

godot::Vector2 rand_vec2(const float start, const float range);

godot::Vector2 rand_vec2(const float startX, const float rangeX, const float startY, const float rangeY);

bool about_equal(float a, float b, float epsilon);

std::ostream& operator<<(std::ostream& os, const godot::Vector2& v);
std::ostream& operator<<(std::ostream& os, godot::Vector2& v);

#endif //REACTORCPPTEST_UTILS_H