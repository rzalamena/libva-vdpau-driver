/*
 *  vdpau_video_glx.h - VDPAU backend for VA API (GLX rendering)
 *
 *  vdpau-video (C) 2009 Splitted-Desktop Systems
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef VDPAU_VIDEO_GLX_H
#define VDPAU_VIDEO_GLX_H

#include "vdpau_driver.h"

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glext.h>

typedef struct opengl_data         opengl_data_t;
typedef struct object_glx_surface  object_glx_surface_t;
typedef struct object_glx_surface *object_glx_surface_p;

typedef enum {
    OPENGL_STATUS_NONE  = 0,
    OPENGL_STATUS_OK    = 1,
    OPENGL_STATUS_ERROR = -1
} OpenGLStatus;

struct opengl_data {
    OpenGLStatus                        gl_status;
    PFNGLXBINDTEXIMAGEEXTPROC           glx_bind_tex_image;
    PFNGLXRELEASETEXIMAGEEXTPROC        glx_release_tex_image;
    PFNGLGENFRAMEBUFFERSEXTPROC         gl_gen_framebuffers;
    PFNGLDELETEFRAMEBUFFERSEXTPROC      gl_delete_framebuffers;
    PFNGLBINDFRAMEBUFFEREXTPROC         gl_bind_framebuffer;
    PFNGLGENRENDERBUFFERSEXTPROC        gl_gen_renderbuffers;
    PFNGLDELETERENDERBUFFERSEXTPROC     gl_delete_renderbuffers;
    PFNGLBINDRENDERBUFFEREXTPROC        gl_bind_renderbuffer;
    PFNGLRENDERBUFFERSTORAGEEXTPROC     gl_renderbuffer_storage;
    PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC gl_framebuffer_renderbuffer;
    PFNGLFRAMEBUFFERTEXTURE2DEXTPROC    gl_framebuffer_texture_2d;
    PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC  gl_check_framebuffer_status;
};

struct object_glx_surface {
    struct object_base  base;
    GLenum              target;
    GLuint              texture;
    VASurfaceID         va_surface;
    unsigned int        width;
    unsigned int        height;
    int                 is_bound;
    Pixmap              pixmap;
    GLXPixmap           glx_pixmap;
    GLuint              fbo;
    GLuint              fbo_buffer;
    GLuint              fbo_texture;
};

// vaCreateSurfaceGLX
VAStatus
vdpau_CreateSurfaceGLX(
    VADriverContextP    ctx,
    unsigned int        target,
    unsigned int        texture,
    void              **gl_surface
) attribute_hidden;

// vaDestroySurfaceGLX
VAStatus
vdpau_DestroySurfaceGLX(
    VADriverContextP    ctx,
    void               *gl_surface
) attribute_hidden;

// vaAssociateSurfaceGLX
VAStatus
vdpau_AssociateSurfaceGLX(
    VADriverContextP    ctx,
    void               *gl_surface,
    VASurfaceID         surface,
    unsigned int        flags
) attribute_hidden;

// vaDeassociateSurfaceGLX
VAStatus
vdpau_DeassociateSurfaceGLX(
    VADriverContextP    ctx,
    void               *gl_surface
) attribute_hidden;

// vaSyncSurfaceGLX
VAStatus
vdpau_SyncSurfaceGLX(
    VADriverContextP    ctx,
    void               *gl_surface
) attribute_hidden;

// vaBeginRenderSurfaceGLX
VAStatus
vdpau_BeginRenderSurfaceGLX(
    VADriverContextP    ctx,
    void               *gl_surface
) attribute_hidden;

// vaEndRenderSurfaceGLX
VAStatus
vdpau_EndRenderSurfaceGLX(
    VADriverContextP    ctx,
    void               *gl_surface
) attribute_hidden;

// vaCopySurfaceGLX
VAStatus
vdpau_CopySurfaceGLX(
    VADriverContextP    ctx,
    void               *gl_surface,
    VASurfaceID         surface,
    unsigned int        flags
) attribute_hidden;

#endif /* VDPAU_VIDEO_GLX_H */