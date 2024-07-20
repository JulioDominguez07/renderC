/*
    render.c
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

#include "src/render.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// The main functions of framebuffer to begin render
void framebuffer_init(Framebuffer *fb, int width, int height) {
    fb->width = width;
    fb->height = height;
    fb->colorBuffer = (unsigned char *)malloc(3 * width * height);
    fb->depthBuffer = (float *)malloc(width * height * sizeof(float));
    framebuffer_clear(fb);
}

void framebuffer_clear(Framebuffer *fb) {
    memset(fb->colorBuffer, 0, 3 * fb->width * fb->height);
    memset(fb->depthBuffer, 0, fb->width * fb->height * sizeof(float));
}

void framebuffer_destroy(Framebuffer *fb) {
    free(fb->colorBuffer);
    free(fb->depthBuffer);
}

void draw_pixel(Framebuffer *fb, int x, int y, unsigned char color[3]) {
    if (x < 0 || x >= fb->width || y < 0 || y >= fb->height) return;
    int index = (y * fb->width + x) * 3;
    fb->colorBuffer[index] = color[0];
    fb->colorBuffer[index + 1] = color[1];
    fb->colorBuffer[index + 2] = color[2];
}

void framebuffer_draw_triangle(Framebuffer *fb, Triangle *triangle) {
    // TODO: Implement 3D triangle rasterization with depth buffering
    // Perspective projection, texture mapping, lighting, etc. would be implemented here
    
    // Actual 3D rendering would involve much more complex calculations. For future I would implement 3D.

    // Wireframe rendering
    for (int i = 0; i < 3; ++i) {
        Vector3 v0 = triangle->vertices[i];
        Vector3 v1 = triangle->vertices[(i + 1) % 3];
        int x0 = (int)v0.x, y0 = (int)v0.y;
        int x1 = (int)v1.x, y1 = (int)v1.y;

        // Bresenham's line drawing algorithm for wireframe
        int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2, e2;

        while (1) {
            draw_pixel(fb, x0, y0, triangle->color);
            if (x0 == x1 && y0 == y1) break;
            e2 = err;
            if (e2 > -dx) { err -= dy; x0 += sx; }
            if (e2 < dy) { err += dx; y0 += sy; }
        }
    }
}

// Translate a triangle
void translate_triangle(Triangle *triangle, float tx, float ty, float tz) {
    for (int i = 0; i < 3; ++i) {
        triangle->vertices[i].x += tx;
        triangle->vertices[i].y += ty;
        triangle->vertices[i].z += tz;
    }
}

// Rotate a triangle around the z-axis
void rotate_triangle_z(Triangle *triangle, float angle) {
    float cos_theta = cos(angle);
    float sin_theta = sin(angle);

    for (int i = 0; i < 3; ++i) {
        float x = triangle->vertices[i].x;
        float y = triangle->vertices[i].y;
        triangle->vertices[i].x = x * cos_theta - y * sin_theta;
        triangle->vertices[i].y = x * sin_theta + y * cos_theta;
        // Z-coordinate remains unchanged for rotation around z-axis in 2D
    }
}
