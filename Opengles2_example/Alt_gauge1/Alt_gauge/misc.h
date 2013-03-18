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

#include <EGL/egl.h>
#include <GLES2/gl2.h>

void buildPerspectiveMatrix(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar, GLfloat *mat);
void buildLookatMatrix(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ,
                       GLfloat viewX, GLfloat viewY, GLfloat viewZ,
                       GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat *mat);
void buildRotationMatrix(GLfloat angle, GLfloat x, GLfloat y, GLfloat z, GLfloat *mat);
void buildTranslationMatrix(GLfloat x, GLfloat y, GLfloat z, GLfloat *mat);
void multMatrix(GLfloat *mat1, GLfloat *mat2, GLfloat *result);
