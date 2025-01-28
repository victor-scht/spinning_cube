#include <stdio.h>
#include <string.h>

#include "quaternion.h"

#ifndef _WIN32

#include <unistd.h>

#else

#include <windows.h>
void usleep(__int64 usec) {
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10 * usec);  // Convert to 100 nanosecond interval, negative
                                 // value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}

#endif

int width = 300, height = 100;  // size of the buffer
float zBuffer[300 *
              100];  // the buffer that stores the depth to avoid overlapping
char buffer[300 * 100];  // the buffer used for display
int backgroundASCIICode =
    ' ';  // background character it initially fills the buffer
int distanceFromCam = 150;  // where is placed the cube from the screen
float K1 = 60.;             // zoom coefficient
float resolution_ratio = 2.;
float speed = 1;  // the speed of rotation
float horizontalOffset = 0.;
float cubeWidth = 20.;

float x, y, z;
float ooz;
int xp, yp;
int idx;
vec vs;
float thetas;
vec us;
vec rs;

void update_surface(vec u, float theta, vec v, int ch) {
    rotate(u, theta, v);
    z = v[2];
    z += distanceFromCam;
    ooz = 1 / z;

    x = v[0];
    y = v[1];

    yp = (int)(height / 2. + y * ooz * K1);
    xp = (int)(width / 2. + horizontalOffset + x * ooz * K1 * resolution_ratio);

    idx = xp + width * (height - 1 - yp);

    if (idx >= 0 && idx < width * height) {
        if (zBuffer[idx] < ooz) {
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

int main() {
    printf("\x1b[2J");
    us[0] = 1.;
    us[1] = 1.;
    us[2] = 0.;

    rs[0] = 0.;
    rs[1] = 0.;
    rs[2] = 1.;

    normalize(us);
    normalize(rs);

    while (1) {
        memset(buffer, backgroundASCIICode, width * height);
        memset(zBuffer, 0, width * height * 4);
        cubeWidth = 40;

        rotate(rs, 0.05, us);

        for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += 1.) {
            for (float cubeY = -cubeWidth; cubeY < cubeWidth; cubeY += 1.) {
                vs[0] = cubeX;
                vs[1] = cubeY;
                vs[2] = -cubeWidth;
                update_surface(us, thetas, vs, '@');

                vs[0] = cubeWidth;
                vs[1] = cubeY;
                vs[2] = cubeX;
                update_surface(us, thetas, vs, '$');

                vs[0] = -cubeWidth;
                vs[1] = cubeY;
                vs[2] = -cubeX;
                update_surface(us, thetas, vs, '~');

                vs[0] = -cubeX;
                vs[1] = cubeY;
                vs[2] = cubeWidth;
                update_surface(us, thetas, vs, '#');

                vs[0] = cubeX;
                vs[1] = -cubeWidth;
                vs[2] = -cubeY;
                update_surface(us, thetas, vs, ';');

                vs[0] = cubeX;
                vs[1] = cubeWidth;
                vs[2] = cubeY;
                update_surface(us, thetas, vs, '+');
            }
        }

        printf("\x1b[H");
        for (int k = 0; k < width * height; k++) {
            putchar(k % width ? buffer[k] : 10);
        }
        thetas += 0.05 * speed;
        int time_pause = (int)(8000 * 2);
        usleep(time_pause);
    }

    return 0;
}
