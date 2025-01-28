#ifndef QUATERNION_H
#define QUATERNION_H

// Define a new type 'vec' as an array of 3 floats
typedef float vec[3];

// Define the 'struct quaternion'
struct quaternion {
    float real;
    vec img;
};

// Define a typedef for 'struct quaternion' to alias it as 'quat'
typedef struct quaternion quat;

int conjugate(quat q, quat *qs);
int mul(quat q1, quat q2, quat *qs);
int get_quat(vec u, quat *q);
int get_vec(quat q, vec u);
int get_rotation_quat(vec u, float theta, quat *q);
int rotate(vec u, float theta, vec v);
int normalize(vec u);

#endif
