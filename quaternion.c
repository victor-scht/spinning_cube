#include <complex.h>
#include <math.h>
// #include <stdio.h>

#include "quaternion.h"

// ===================== Methods =====================

int conjugate(quat q, quat *qs) {
    // qs is the quaternion where to store the output
    (*qs).real = q.real;
    (*qs).img[0] = -q.img[0];
    (*qs).img[1] = -q.img[1];
    (*qs).img[2] = -q.img[2];

    return 0;
}
// q1*q2 is stored in qs
int mul(quat q1, quat q2, quat *qs) {
    float a1 = q1.real;
    float b1 = q1.img[0];
    float c1 = q1.img[1];
    float d1 = q1.img[2];

    float a2 = q2.real;
    float b2 = q2.img[0];
    float c2 = q2.img[1];
    float d2 = q2.img[2];

    (*qs).real = a1 * a2 - b1 * b2 - c1 * c2 - d1 * d2;
    (*qs).img[0] = a1 * b2 + b1 * a2 + c1 * d2 - c2 * d1;
    (*qs).img[1] = a1 * c2 + c1 * a2 + b2 * d1 - b1 * d2;
    (*qs).img[2] = a1 * d2 + d1 * a2 + b1 * c2 - c1 * b2;

    return 0;
}

int get_quat(vec u, quat *q) {
    (*q).real = 0.0;
    (*q).img[0] = u[0];
    (*q).img[1] = u[1];
    (*q).img[2] = u[2];

    return 0;
}

int get_vec(quat q, vec u) {
    u[0] = (q.img)[0];
    u[1] = (q.img)[1];
    u[2] = (q.img)[2];

    return 0;
}

// store the quaternion that defines rotation
int get_rotation_quat(vec u, float theta, quat *q) {
    theta /= 2;

    (*q).real = cos(theta);
    (*q).img[0] = sin(theta) * u[0];
    (*q).img[1] = sin(theta) * u[1];
    (*q).img[2] = sin(theta) * u[2];

    return 0;
}

// compute the rotation of vector v based on some rotation angle theta
// and invariant vector u (u norm needs to be one)
int rotate(vec u, float theta, vec v) {
    quat q1;
    quat q2;
    quat q;

    get_quat(v, &q);

    get_rotation_quat(u, theta, &q1);
    conjugate(q1, &q2);

    mul(q1, q, &q);
    mul(q, q2, &q);

    get_vec(q, v);

    return 0;
}

// normalize a vector
int normalize(vec u) {
    float a = u[0];
    float b = u[1];
    float c = u[2];

    float norm = sqrt(a * a + b * b + c * c);

    a /= norm;
    b /= norm;
    c /= norm;

    u[0] = a;
    u[1] = b;
    u[2] = c;

    return 0;
}

// ===================== Test  =====================
// // rotate a vector several times based on some invariant vector and rotation
// angle
// // display the result
// int main() {
//     quat q;
//     vec u = {1.0, 0.0, 0.0};
//     float theta = M_PI / 4;
//     vec v = {0.0, 1.0, 0.0};
//
//     for (int i = 0; i < 10; i++) {
//         rotate(u, theta, v);
//         printf("%f,%f,%f\n", v[0], v[1], v[2]);
//     }
//     return 0;
// }
