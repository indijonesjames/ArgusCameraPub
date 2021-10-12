
#include "MathUtils.h"
#include <math.h>

void MathUtils::createFrustumMatrix(float left, float right, float bottom, float top,
                                    float znear, float zfar, float mat[16])
{
    float temp, temp2, temp3, temp4;
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    mat[0] = temp / temp2;
    mat[1] = 0.0;
    mat[2] = 0.0;
    mat[3] = 0.0;
    mat[4] = 0.0;
    mat[5] = temp / temp3;
    mat[6] = 0.0;
    mat[7] = 0.0;
    mat[8] = (right + left) / temp2;
    mat[9] = (top + bottom) / temp3;
    mat[10] = (-zfar - znear) / temp4;
    mat[11] = -1.0;
    mat[12] = 0.0;
    mat[13] = 0.0;
    mat[14] = (-temp * zfar) / temp4;
    mat[15] = 0.0;
}

void MathUtils::createPerspectiveMatrix(float fovyInDegrees, float aspectRatio,
                                        float znear, float zfar, float mat[16])
{
    float ymax, xmax;
    ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
    xmax = ymax * aspectRatio;
    createFrustumMatrix(-xmax, xmax, -ymax, ymax, znear, zfar, mat);
}

void MathUtils::createRotationMatrix(float angle, float x, float y, float z, float mat[16])
{
    float mag, cosA, sinA, sqX, sqY, sqZ, xY, xZ, yZ;
    cosA = cosf(angle * M_PI / 180.0f);
    sinA = sinf(angle * M_PI / 180.0f);
    mag = sqrtf(x*x+y*y+z*z);
    x /= mag;
    y /= mag;
    z /= mag;
    sqX = x*x;
    sqY = y*y;
    sqZ = z*z;

    xY = x * y;
    xZ = x * z;
    yZ = y * z;

    mat[0] = sqX + (cosA * (1.0f - sqX));
    mat[1] = xY - (cosA * xY) + (sinA * z);
    mat[2] = xZ - (cosA * xZ) - (sinA * y);
    mat[3] = 0.0f;
    mat[4] = xY - (cosA * xY) - (sinA *z);
    mat[5] = sqY + (cosA * (1.0f - sqY));
    mat[6] = yZ - (cosA * yZ) + (sinA * x);
    mat[7] = 0.0f;
    mat[8] = xZ - (cosA * xZ) + (sinA * y);
    mat[9] = yZ - (cosA * yZ) - (sinA * x);
    mat[10] = sqZ + (cosA * (1.0f - sqZ));
    mat[11] = 0.0f;
    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}
