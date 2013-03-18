
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<Winbase.h>
#include<EGL/egl.h>
#include<GLES2/gl2.h>
#include<GLES2/gl2ext.h>
#include"graphicslib.h"
#include"esUtil.h"
#include"misc.h"
#include"bg.h"
#include"needle.h"


#define WIN_WIDTH	512
#define WIN_HEIGHT	512
#define BUFFER_SIZE (64*1024)
#define MIN_SPEEDO		138
#define MAX_SPEEDO		-100
#define MIN_TACH		137
#define MAX_TACH		-20

static void InitGL(void);
void ShutDown (void);
static int InitShader2(void);
static int InitShader1(void);
GLuint LoadTexture1(void);
GLuint LoadTexture2(void);
static void Draw(void);
static void SetupShader1(void);
static void SetupShader2(void);
static void DrawBackground(void);
static void DrawNeedle( float angle, float x, float y ) ;

static GLfloat texCoords[8];

typedef  struct
{
	GLuint programObject1; //handle to program
	GLuint programObject2;

	GLuint positionLoc1;   //Attribute location
	GLuint texCoordLoc1;
	GLuint primaryColor;

	GLint uniformProjection1;	//Sampler Location
	GLint uniformView1;			//Sampler Location
	

	GLuint positionLoc2;   //Attribute location
	GLuint texCoordLoc2;
	GLuint primaryColor2;

	GLint uniformProjection2;	//Sampler Location
	GLint uniformView2;			//Sampler Location
	

	GLint  baseMapLoc;	  //Sampler Location
	GLuint baseMapTexId;  //Texture Handle

	GLint  needleLoc;	  //Sampler Location
	GLuint needleTexId;  //Texture Handle
	
}UserData;

static ESContext esContext;
static UserData	userData;

void ShutDown (void)
{
   UserData *userData = esContext.userData;
   // Delete texture object
    glDeleteTextures ( 1, &userData->needleTexId );
   // Delete program object
    glDeleteProgram ( userData->programObject2 );
    glDeleteTextures ( 1, &userData->baseMapTexId );
   // Delete program object
    glDeleteProgram ( userData->programObject1 );
}

int main(int argc, char *argv[])
{
	esInitContext (&esContext);
	esContext.userData = &userData;

	esCreateWindow (&esContext, "Texture",WIN_WIDTH, WIN_HEIGHT, ES_WINDOW_RGB);
	
	InitGL();

	InitShader1();
	InitShader2();
	
	
	// Load the textures
    userData.baseMapTexId = LoadTexture1();
	userData.needleTexId = LoadTexture2();



	/* Setup the use texture unit 0 */
    glUseProgram( userData.programObject1 );
    userData.baseMapLoc = glGetUniformLocation( userData.programObject1, "uTexUnit");
    glUniform1i( userData.baseMapLoc, 0);

	glUseProgram( userData.programObject2 );
    userData.needleLoc = glGetUniformLocation( userData.programObject2, "uTexUnit");
    glUniform1i( userData.needleLoc, 0);

	esRegisterDrawFunc ( &esContext, Draw );
	
	esMainLoop ( &esContext );
	ShutDown ( &esContext );
}

static void InitGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

static int InitShader2(void)
{
	UserData *userData = esContext.userData;
   GLbyte vShaderStr[] =  
      "precision highp float;					\n"
	  "uniform mat4 uProjectionMatrix;			\n"
	  "uniform mat4 uViewMatrix;				\n"
	  "attribute vec3 aPosition;				\n"
	  "attribute vec4 a_PrimaryColor;			\n"
	  "varying vec4 v_PrimaryColor;				\n"
	  "attribute vec2 aTexCoord;				\n"
	  "varying vec2 vTexCoord;					\n"
	  "void main()								\n"
	  "{										\n"	
	  "    v_PrimaryColor = a_PrimaryColor;		\n"
	  "    vTexCoord = aTexCoord;				\n"
	  "	gl_Position = uProjectionMatrix *  uViewMatrix * vec4(aPosition, 1.0);  \n"  //   
	  "}                          \n";
   
   GLbyte fShaderStr[] =  
      "precision highp float;							\n"
	  "uniform sampler2D uTexUnit;						\n"
	  "varying vec2 vTexCoord;							\n"
	  "varying vec4 v_PrimaryColor;						\n"
	  "void main()										\n"
	  "{												\n"
	  "gl_FragColor = texture2D(uTexUnit, vTexCoord)* v_PrimaryColor;	\n"
	  "}												\n";
		
   // Load the shaders and get a linked program object
   userData->programObject2 = esLoadProgram ( vShaderStr, fShaderStr );
}


static int InitShader1(void)
{
	UserData *userData = esContext.userData;
   GLbyte vShaderStr[] =  
      "precision highp float;					\n"
	  "uniform mat4 uProjectionMatrix;			\n"
	  "uniform mat4 uViewMatrix;				\n"
	  "attribute vec3 aPosition;				\n"
	  "attribute vec2 aTexCoord;				\n"
	  "attribute vec4 a_PrimaryColor;			\n"
	  "varying vec4 v_PrimaryColor;				\n"
	  "varying vec2 vTexCoord;					\n"
	  "void main()								\n"
	  "{										\n"	
	  "    v_PrimaryColor = a_PrimaryColor;		\n"
	  "    vTexCoord = aTexCoord;				\n"
	  "	gl_Position = vec4((aPosition.xy - 0.5)*2.0, 0.0, 1.0);   \n"   
	  "}                          \n";
   
   GLbyte fShaderStr[] =  
      "precision highp float;							\n"
	  "uniform sampler2D uTexUnit;						\n"
	  "varying vec4 v_PrimaryColor;						\n"
	  "varying vec2 vTexCoord;							\n"
	  "void main()										\n"
	  "{												\n"
	  "gl_FragColor = texture2D(uTexUnit, vTexCoord)* v_PrimaryColor;	\n"
	  "}												\n";
		
   // Load the shaders and get a linked program object
   userData->programObject1 = esLoadProgram ( vShaderStr, fShaderStr );
  }

GLuint LoadTexture1(void) 
{
   	GLint bgTexName;
	// Setup the background texture.
	glGenTextures( 1, &bgTexName );
	glBindTexture(GL_TEXTURE_2D, bgTexName);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE,alt_gauge_bg);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	return bgTexName; 
	}


GLuint LoadTexture2(void) 
{
   	GLint needleTexName;
	// Setup the background texture.
	glGenTextures( 1, &needleTexName );
	glBindTexture(GL_TEXTURE_2D, needleTexName);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, alt_gauge_needle);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, alt_gauge_bg);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	return needleTexName; 
	}

static void Draw(void) 
{
	UserData *userData = esContext.userData;

	static float speedoAngle = MIN_SPEEDO, speedoVelocityUp = -0.7f, speedoVelocityDown = 3.4f;
	static float tachAngle = MIN_TACH, tachVelocityUp = -1.7f, tachVelocityDown = 5.0f;
	static float speedoVelocity = -0.7f, tachVelocity = -1.7f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Enable blending.
    
	
    glUseProgram( userData->programObject1 );
	SetupShader1( userData->programObject1);	
	DrawBackground();
		
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Activate needle shader.
    glUseProgram( userData->programObject2 );
	SetupShader2( userData->programObject2);

	glDisable(GL_DEPTH_TEST);
	// Draw speedo
	DrawNeedle( speedoAngle, 0.0f, 0.0f );
	// Draw tach
	//DrawNeedle( tachAngle, 0.495f, -0.0314f );
	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	eglSwapBuffers ( esContext.eglDisplay, esContext.eglSurface );

	Sleep(40);
	// Update angles
	speedoAngle += speedoVelocity;
	tachAngle += tachVelocity;

	if ( (speedoAngle + speedoVelocity) <= MAX_SPEEDO ) {
		speedoVelocity = speedoVelocityDown;
	} else if ( (speedoAngle + speedoVelocity) >= MIN_SPEEDO ) {
		speedoVelocity = speedoVelocityUp;
	}

	if ( (tachAngle + tachVelocity) <= MAX_TACH ) {
		tachVelocity = tachVelocityDown;
	} else if ( (tachAngle + tachVelocity) >= MIN_TACH ) {
		tachVelocity = tachVelocityUp;
	}

}


static void SetupShader1(void) 
{
	UserData *userData = esContext.userData;

	// Get the attribute locations
   userData->positionLoc1 = glGetAttribLocation ( userData->programObject1, "aPosition" );
   userData->texCoordLoc1 = glGetAttribLocation ( userData->programObject1, "aTexCoord" );
   userData->primaryColor = glGetAttribLocation ( userData->programObject1, "a_PrimaryColor" );
   glEnableVertexAttribArray( userData->positionLoc1);
   glEnableVertexAttribArray( userData->texCoordLoc1);
   glEnableVertexAttribArray( userData->primaryColor);
   glBindAttribLocation( userData->programObject1, userData->positionLoc1, "aPosition");
   glBindAttribLocation( userData->programObject1, userData->texCoordLoc1, "aTexCoord");
   glBindAttribLocation( userData->programObject1, userData->primaryColor, "a_PrimaryColor");
   // Get the sampler location
   userData->uniformProjection1  = glGetUniformLocation (userData->programObject1, "uProjectionMatrix" );
   userData->uniformView1  = glGetUniformLocation (userData->programObject1, "uViewMatrix" );
	  
}
static void SetupShader2(void) 
{
	UserData *userData = esContext.userData;

	// Get the attribute locations
   userData->positionLoc2 = glGetAttribLocation ( userData->programObject2, "aPosition" );
   userData->texCoordLoc2 = glGetAttribLocation ( userData->programObject2, "aTexCoord" );
   userData->primaryColor2 = glGetAttribLocation ( userData->programObject2, "a_PrimaryColor" );
   glEnableVertexAttribArray( userData->positionLoc2);
   glEnableVertexAttribArray( userData->texCoordLoc2);
   glEnableVertexAttribArray( userData->primaryColor2);
   glBindAttribLocation( userData->programObject2, userData->positionLoc2, "aPosition");
   glBindAttribLocation( userData->programObject2, userData->texCoordLoc2, "aTexCoord");
   glBindAttribLocation( userData->programObject2, userData->primaryColor2, "a_PrimaryColor");
   // Get the sampler location
   userData->uniformProjection2  = glGetUniformLocation (userData->programObject2, "uProjectionMatrix" );
   userData->uniformView2  = glGetUniformLocation (userData->programObject2, "uViewMatrix" );
	  
}


static void DrawBackground(void) 
{
	UserData *userData = esContext.userData;
	GLfloat verts[12]= {0.0f, 0.0f, 0.0f, 
                       1.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f,
                       1.0f, 1.0f, 0.0f};


	float x=(140/WIN_WIDTH),y=(140/WIN_HEIGHT);
	 
	//GLfloat verts[16]= {-x,  y, 0.0f, 
 //                       -x, -y, 0.0f,
 //                     0.0f,  y, 0.0f,
 //                        x, -y, 0.0f,
	//				     x,  y, 0.0f
	//                   };
	GLfloat texCoords[8]= {
			0.0f, 0.0f,
			1.0f, 0.0f, 
			0.0f, 1.0f,
			1.0f, 1.0f
			};
    GLfloat primaryColor[] = { 0.0f,1.0f,1.0f,1.0f,
							   1.0f,0.0f,1.0f,1.0f,
							   1.0f,1.0f,0.0f,1.0f,
							   1.0f,1.0f,1.0f,0.0f};
	//GLfloat* TexCoordinate;
	//temp = 0;
	//TexCoordinate = Draw_Character('9');
	

	glBindTexture(GL_TEXTURE_2D,userData->baseMapTexId);
    glEnableVertexAttribArray(userData->positionLoc1);
    glEnableVertexAttribArray(userData->texCoordLoc1);
	glEnableVertexAttribArray(userData->primaryColor);
    glVertexAttribPointer(userData->positionLoc1, 3, GL_FLOAT, GL_FALSE, 0, verts);
	glVertexAttribPointer(userData->texCoordLoc1, 2, GL_FLOAT, GL_FALSE, 0, texCoords);
	//glVertexAttribPointer(userData->texCoordLoc1, 2, GL_FLOAT, GL_FALSE, 0, TexCoordinate);
	glVertexAttribPointer(userData->primaryColor, 4, GL_FLOAT, GL_FALSE, 0, primaryColor);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}


static void DrawNeedle( float angle, float x, float y ) {

	UserData *userData = esContext.userData;	

    GLfloat projectionMatrix[16], viewMatrix[16];
	GLfloat translationMatrix[16];
    GLfloat rotationMatrix[ 16 ], originalViewMatrix[ 16 ];
	GLfloat verts[] = {0.0f, 0.0f, 0.0f, 
                       0.045f, 0.0f, 0.0f,
                       0.0f, 0.700f, 0.0f,
                       0.045f, 0.700f, 0.0f};
    GLfloat texCoords[] = {
			0.0f, 0.0f,
			1.0f, 0.0f, 
			0.0f, 1.0f,
			1.0f, 1.0f
			};
	GLfloat primaryColor[] = { 0.0f,1.0f,1.0f,1.0f,
							   0.0f,1.0f,1.0f,1.0f,
							   0.0f,1.0f,1.0f,1.0f,
							   0.0f,1.0f,1.0f,1.0f};
    // Generate matrices
    buildPerspectiveMatrix(60.0f, (GLfloat)WIN_WIDTH/(GLfloat)WIN_HEIGHT, 0.0f, 1000.0f, projectionMatrix);
    buildLookatMatrix(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, originalViewMatrix);

    buildRotationMatrix( angle, 0.0f, 0.0f, 1.0f, rotationMatrix);
	buildTranslationMatrix( -0.01875f, -0.024f, 0.0f, translationMatrix );
	multMatrix( rotationMatrix, translationMatrix, rotationMatrix);
	buildTranslationMatrix( x, y, 0.f, translationMatrix );
	multMatrix( translationMatrix, rotationMatrix, rotationMatrix);
    multMatrix( originalViewMatrix, rotationMatrix, viewMatrix);
 
    glUniformMatrix4fv(userData->uniformProjection2 , 1, 0, projectionMatrix);
    glUniformMatrix4fv(userData->uniformView2, 1, 0, viewMatrix);

	glBindTexture(GL_TEXTURE_2D, userData->needleTexId);
    glEnableVertexAttribArray(userData->positionLoc2);
    glEnableVertexAttribArray(userData->texCoordLoc2);
	glEnableVertexAttribArray(userData->primaryColor2);
    glVertexAttribPointer(userData->positionLoc2, 3, GL_FLOAT, GL_FALSE, 0, verts);
	glVertexAttribPointer(userData->texCoordLoc2, 2, GL_FLOAT, GL_FALSE, 0, texCoords);
	glVertexAttribPointer(userData->primaryColor2, 4, GL_FLOAT, GL_FALSE, 0, primaryColor);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

