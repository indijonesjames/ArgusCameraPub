
#ifndef MATHUTILS_H
#define MATHUTILS_H

namespace MathUtils
{

void createFrustumMatrix(float left, float right, float bottom, float top, float znear, float zfar,
    float mat[16]);

void createPerspectiveMatrix(float fovyInDegrees, float aspectRatio, float znear, float zfar,
    float mat[16]);

void createRotationMatrix(float angle, float x, float y, float z, float mat[16]);

} // namespace MathUtils

#endif // MATHUTILS_H
