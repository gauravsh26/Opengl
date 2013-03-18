/*************************************************************************/
/*          (c) 2009 Fujitsu Microelectronics Europe GmbH                */
/*                                                                       */
/* ALL RIGHTS RESERVED. No part of this publication may be copied and    */
/* provided to any third party in any form or by any means without the   */
/* written permission of Fujitsu, unless expressly agreed to in written  */
/* form by Fujitsu.                                                      */
/* All trademarks used in this document are the property of their        */
/* respective owners.                                                    */
/*                                                                       */
/* For further provisions please refer to the respective License         */
/* Agreement.                                                            */
/*************************************************************************/



/** @file misc.c
    @brief Implementation of misc.
*/ 
/******************************************************************************/

/*******************************************************************************
 Includes
*******************************************************************************/

#include "misc.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*******************************************************************************
 Macro Definitions
*******************************************************************************/

#define PI_VAL 3.14159265358979323846f

/*******************************************************************************
 Data Types
*******************************************************************************/

typedef struct _Vector3D {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Vector3D;

/*******************************************************************************
 Variables
*******************************************************************************/

/* N/A */

/*******************************************************************************
 Function Prototypes
*******************************************************************************/

/* N/A */

/*******************************************************************************
 Function Definitions
*******************************************************************************/

GLfloat dotVector3D(Vector3D a, Vector3D b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

GLfloat lengthVector3D(Vector3D vec) {
    return (GLfloat)sqrt(dotVector3D(vec, vec));
}

Vector3D normalizedVector3D(Vector3D vec) {
    Vector3D norm;
    GLfloat len = lengthVector3D(vec);
    norm.x = vec.x / len;
    norm.y = vec.y / len;
    norm.z = vec.z / len;
    return norm;
}

Vector3D crossVector3D(Vector3D a, Vector3D b) {
    Vector3D cross;
    cross.x = (a.y * b.z) - (a.z * b.y);
    cross.y = (a.z * b.x) - (a.x * b.z);
    cross.z = (a.x * b.y) - (a.y * b.x);
    return cross;
}

void multMatrix(GLfloat *mat1, GLfloat *mat2, GLfloat *result) {
    GLuint i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            result[i*4+j] = mat1[j] * mat2[i*4] +
                            mat1[j+4] * mat2[i*4+1] +
                            mat1[j+8] * mat2[i*4+2] +
                            mat1[j+12] * mat2[i*4+3];
        }
    }
}

void buildIdentityMatrix(GLfloat *mat) {
    mat[0] = 1.0f;  mat[4] = 0.0f;  mat[8] = 0.0f;    mat[12] = 0.0f;
    mat[1] = 0.0f;  mat[5] = 1.0f;  mat[9] = 0.0f;    mat[13] = 0.0f;
    mat[2] = 0.0f;  mat[6] = 0.0f;  mat[10] = 1.0f;   mat[14] = 0.0f;
    mat[3] = 0.0f;  mat[7] = 0.0f;  mat[11] = 0.0f;   mat[15] = 1.0f;
}

void buildTranslationMatrix(GLfloat x, GLfloat y, GLfloat z, GLfloat *mat) {
	mat[0] = 1.0f;  mat[4] = 0.0f;  mat[8] = 0.0f;    mat[12] = x;
    mat[1] = 0.0f;  mat[5] = 1.0f;  mat[9] = 0.0f;    mat[13] = y;
    mat[2] = 0.0f;  mat[6] = 0.0f;  mat[10] = 1.0f;   mat[14] = z;
    mat[3] = 0.0f;  mat[7] = 0.0f;  mat[11] = 0.0f;   mat[15] = 1.0f;
}
void buildScaleMatrix(GLfloat x, GLfloat y, GLfloat z, GLfloat *mat) {
    mat[0] = x;     mat[4] = 0.0f;  mat[8] = 0.0f;    mat[12] = 0.0f;
    mat[1] = 0.0f;  mat[5] = y;     mat[9] = 0.0f;    mat[13] = 0.0f;
    mat[2] = 0.0f;  mat[6] = 0.0f;  mat[10] = z;      mat[14] = 0.0f;
    mat[3] = 0.0f;  mat[7] = 0.0f;  mat[11] = 0.0f;   mat[15] = 1.0f;
}
void buildRotationMatrix(GLfloat angle, GLfloat x, GLfloat y, GLfloat z, GLfloat *mat) {
    GLfloat c, s, d;

    Vector3D vec;
    vec.x = x; vec.y = y; vec.z = z;
    vec = normalizedVector3D(vec);
    x = vec.x; y = vec.y; z = vec.z;

    angle = angle * PI_VAL / 180.0f;
    c = (GLfloat)cos(angle);
    s = (GLfloat)sin(angle);
    d = 1.0f - c;

    mat[0] = x*x*d+c;   mat[4] = x*y*d-z*s; mat[8]  = x*z*d+y*s; mat[12] = 0.0f;
    mat[1] = y*x*d+z*s; mat[5] = y*y*d+c;   mat[9]  = y*z*d-x*s; mat[13] = 0.0f;
    mat[2] = x*z*d-y*s; mat[6] = y*z*d+x*s; mat[10] = z*z*d+c;   mat[14] = 0.0f;
    mat[3] = 0.0f;      mat[7] = 0.0f;      mat[11] = 0.0f;      mat[15] = 1.0f;
}

void buildPerspectiveMatrix(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar, GLfloat *mat) {
    GLfloat f, s, t;
    fovy = fovy * PI_VAL / 180.0f;
    f = 1.0f / (GLfloat)tan(fovy/2.0f);
    s = (zFar+zNear)/(zNear-zFar);
    t = (2.0f*zFar*zNear)/(zNear-zFar);
    mat[0] = f / aspect; mat[4] = 0.0f; mat[8]  = 0.0f;  mat[12] = 0.0f;
    mat[1] = 0.0f;       mat[5] = f;    mat[9]  = 0.0f;  mat[13] = 0.0f;
    mat[2] = 0.0f;       mat[6] = 0.0f; mat[10] = s;     mat[14] = t;
    mat[3] = 0.0f;       mat[7] = 0.0f; mat[11] = -1.0f; mat[15] = 0.0f;
}

void buildLookatMatrix(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ,
                       GLfloat viewX, GLfloat viewY, GLfloat viewZ,
                       GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat *mat) {
    Vector3D f, up, s, u;

    f.x = viewX - eyeX;
    f.y = viewY - eyeY;
    f.z = viewZ - eyeZ;
    f = normalizedVector3D(f);

    up.x = upX;
    up.y = upY;
    up.z = upZ;
    up = normalizedVector3D(up);

    s = crossVector3D(f, up);
    u = crossVector3D(s, f);

    mat[0] =  s.x; mat[4] =  s.y; mat[8]  =  s.z; mat[12] = -(eyeX*s.x + eyeY*s.y + eyeZ*s.z);
    mat[1] =  u.x; mat[5] =  u.y; mat[9]  =  u.z; mat[13] = -(eyeX*u.x + eyeY*u.y + eyeZ*u.z);
    mat[2] = -f.x; mat[6] = -f.y; mat[10] = -f.z; mat[14] =  (eyeX*f.x + eyeY*f.y + eyeZ*f.z);
    mat[3] = 0.0f; mat[7] = 0.0f; mat[11] = 0.0f; mat[15] = 1.0f;
}