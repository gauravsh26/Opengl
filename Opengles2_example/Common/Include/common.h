#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "ruby/ruby_directaccess.h"
#include "ruby/ruby_display.h"
#include "ruby/ruby_driver.h"
#include "ruby/ruby_external_types.h"
#include "os_helper/os_helper.h"

extern void* render_videoAlloc(ruby_uint32 size, ruby_uint32 alignment);
extern void render_videoFree( void* addr );


/* alpha blending */

#define LA0SEL                                 (0 << 11)
#define LA1SEL                                 (1 << 11)
#define LA2SEL                                 (2 << 11)
#define LA3SEL                                 (3 << 11)

#define LAFROMPIXEL                            (0 << 10)
#define LAFROMALPHA                            (1 << 10)

/* cursor 0 */
#define CU0ON                                   (1 << 31)
#define CU0OFF                                  (0 << 31)
#define SC0enC0ON                               (1 << 29)
#define SC0enC0OFF                              (0 << 29)
#define CU0SIZ128                               (0 << 1)
#define CU0SIZ64                                (1 << 1)
#define CU0SIZ32                                (2 << 1)
#define CU0SIZ16                                (3 << 1)
#define L0CU0                                   (0 << 0)
#define CU0L0                                   (1 << 0)
#define CUZTON                                  (1 << 8)
#define CUZTOFF                                 (0 << 8)


#define EXIT_FAIL                           \
{                                           \
    printf("CreateRenderTarget failed!\n"); \
    printf("\nPress <Enter> to exit >");    \
    getchar();                               \
    return( -1 );                           \
}


typedef struct {
    ruby_uint32 left;
    ruby_uint32 top;
    ruby_uint32 right;
    ruby_uint32 bottom;
} MYWindowPosition;

typedef struct _MYRenderContext {
    EGLNativeDisplayType display_id;
    EGLDisplay          dpy;
    EGLNativeWindowType win;
    EGLSurface          surf;
    EGLContext          context;
} MYRenderContext;


#define DISPLAY_WIDTH           1024
#define DISPLAY_HEIGHT           768

#define MY_NUM_RENDER_CONTEXTS   2*8


int OpenShaderBinary( char* fileName, unsigned char* storageBuffer, ruby_uint32 storageBufferSize );
int CreateRenderTarget( RubyWindowProperties *RubyWindow, EGLDisplay *dpy, EGLNativeDisplayType *display_id, EGLint *configAttribs, EGLContext *context, EGLSurface *surf, EGLNativeWindowType *win);
int DeleteRenderTarget( EGLDisplay dpy, EGLNativeDisplayType display_id, EGLContext context, EGLSurface surf, EGLNativeWindowType win );
void SelectDisplay( ruby_uint32 layer, ruby_uint32 screen );
void DrawTriangle( int n, int width, int height );
void DrawRectangle( int width, int height );
void EnableDualDisplay();
void DisableDualDisplay();
