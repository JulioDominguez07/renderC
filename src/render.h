/*
    render.h
    Help display graphics via 
    CPU (Main job to do all graphical) and GPU(Display them)
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

#ifndef RENDERER_H
#define RENDERER_H

#include "vector.h"

typedef struct {
    int width, height;
    unsigned char *colorBuffer;
    float *depthBuffer; // Depth buffer for z-values
} Framebuffer;

typedef struct {
    Vector3 vertices[3];
    Vector2 texcoords[3];
    Vector3 normals[3];
    unsigned char color[3]; // RGB color
    unsigned char *texture; // Texture image data
    int texture_width, texture_height; // Texture dimensions
} Triangle;

// The main functions of framebuffer to begin render
void framebuffer_init(Framebuffer *fb, int width, int height);
void framebuffer_clear(Framebuffer *fb);
void framebuffer_destroy(Framebuffer *fb);
// Functions that draw, translate or rotate any shapes
void framebuffer_draw_triangle(Framebuffer *fb, Triangle *triangle);
void translate_triangle(Triangle *triangle, float tx, float ty, float tz);
void rotate_triangle_z(Triangle *triangle, float angle);

#endif // RENDERER_H
