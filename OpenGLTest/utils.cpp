#include "utils.h"

point3 rand_point_in_triangle(point3 v1, point3 v2, point3 v3)
{
    double a1, a2, a3;
    a1 = rand() / (double) RAND_MAX;
    a2 = rand() / (double) RAND_MAX;
    if (a1 + a2 > 1) {
        a1 = 1.0 - a1;
        a2 = 1.0 - a2;
    }
    a3 = 1.0 - a1 - a2;
    point3 p = point3(a1*v1.x + a2*v2.x + a3*v3.x, a1*v1.y + a2*v2.y + a3*v3.y, a1*v1.z + a2*v2.z + a3*v3.z);
    return p;
}