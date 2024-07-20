/*
    vector.c
    Help create geometric shapes defined on a framebuffer, 
    such as points, lines, curves and polygons.
    Copyright (C) 2024  Julio Dominguez

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    float x, y;
} Vector2;

Vector3 vector_add(Vector3 a, Vector3 b);
Vector3 vector_sub(Vector3 a, Vector3 b);
Vector3 vector_cross(Vector3 a, Vector3 b);
float vector_dot(Vector3 a, Vector3 b);
Vector3 vector_normalize(Vector3 v);

#endif // VECTOR_H
