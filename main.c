/*
    main.c
    Test program to display a triangle by .ppm
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

#include <stdio.h>
#include <math.h>
#include "src/render.h"

#define PI 3.14159265359

int main() {
    Framebuffer fb;
    framebuffer_init(&fb, 800, 600);

    // Example Triangle
    Triangle triangle = {
        .vertices = {
            {100, 100, 0},
            {700, 100, 0},
            {400, 500, 0}
        },
        .color = {255, 0, 0}
    };

    float angle = 0.0f;
    float rotation_speed = 0.01f;

    while (1) {
        framebuffer_clear(&fb);

        // Rotate the triangle around the z-axis
        rotate_triangle_z(&triangle, angle);

        // Draw the rotated triangle
        framebuffer_draw_triangle(&fb, &triangle);

        // Save framebuffer to a file (PPM format)
        char filename[20];
        sprintf(filename, "output_%04d.ppm", (int)(angle * 1000)); // Save multiple frames
        FILE *file = fopen(filename, "wb");
        fprintf(file, "P6\n%d %d\n255\n", fb.width, fb.height);
        fwrite(fb.colorBuffer, 1, 3 * fb.width * fb.height, file);
        fclose(file);

        // Increase angle for next frame
        angle += rotation_speed;

        // Break after one full rotation (just for demonstration)
        if (angle >= 2 * PI) {
            break;
        }
    }

    framebuffer_destroy(&fb);
    return 0;
}
