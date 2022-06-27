/*
 *  vdpau_driver_template.h - VDPAU driver initialization template
 *
 *  libva-vdpau-driver (C) 2009-2011 Splitted-Desktop Systems
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

#undef  CONCAT_
#define CONCAT_(x, y)   x##y
#undef  CONCAT
#define CONCAT(x, y)    CONCAT_(x, y)
#undef  FUNC
#define FUNC(name)      CONCAT(CONCAT(CONCAT(vdpau_,name),_),VA_INIT_SUFFIX)

#ifndef VA_INIT_SUFFIX
#define VA_INIT_SUFFIX  Current
#define VA_INIT_CURRENT 1
#else
#define VA_INIT_CURRENT 0
#endif

#if VA_INIT_CURRENT
#define VA_DRIVER_VTABLE        VADriverVTable
#define VA_DRIVER_CONTEXT       VADriverContext
#define VA_DRIVER_CONTEXT_P     VADriverContextP
#else
#define VA_DRIVER_VTABLE        CONCAT(VADriverVTable_,VA_INIT_SUFFIX)
#define VA_DRIVER_VTABLE_GLX_P  CONCAT(VADriverVTableGLX_,VA_INIT_SUFFIX)
#define VA_DRIVER_CONTEXT       CONCAT(VADriverContext_,VA_INIT_SUFFIX)
#define VA_DRIVER_CONTEXT_P     CONCAT(VADriverContextP_,VA_INIT_SUFFIX)

typedef struct VA_DRIVER_CONTEXT *VA_DRIVER_CONTEXT_P;

/* Driver VTable */
struct VA_DRIVER_VTABLE {
	VAStatus (*vaTerminate) ( VA_DRIVER_CONTEXT_P ctx );

	VAStatus (*vaQueryConfigProfiles) (
		VADriverContextP ctx,
		VAProfile *profile_list,	/* out */
		int *num_profiles			/* out */
	);

	VAStatus (*vaQueryConfigEntrypoints) (
		VADriverContextP ctx,
		VAProfile profile,
		VAEntrypoint  *entrypoint_list,	/* out */
		int *num_entrypoints			/* out */
	);

	VAStatus (*vaGetConfigAttributes) (
		VADriverContextP ctx,
		VAProfile profile,
		VAEntrypoint entrypoint,
		VAConfigAttrib *attrib_list,	/* in/out */
		int num_attribs
	);

	VAStatus (*vaCreateConfig) (
		VADriverContextP ctx,
		VAProfile profile, 
		VAEntrypoint entrypoint, 
		VAConfigAttrib *attrib_list,
		int num_attribs,
		VAConfigID *config_id		/* out */
	);

	VAStatus (*vaDestroyConfig) (
		VADriverContextP ctx,
		VAConfigID config_id
	);

	VAStatus (*vaQueryConfigAttributes) (
		VADriverContextP ctx,
		VAConfigID config_id, 
		VAProfile *profile,		/* out */
		VAEntrypoint *entrypoint, 	/* out */
		VAConfigAttrib *attrib_list,	/* out */
		int *num_attribs		/* out */
	);

	VAStatus (*vaCreateSurfaces) (
		VADriverContextP ctx,
		int width,
		int height,
		int format,
		int num_surfaces,
		VASurfaceID *surfaces		/* out */
	);

	VAStatus (*vaCreateSurfaces2) (
		VADriverContextP ctx,
		unsigned int format,
		unsigned int width,
		unsigned int height,
		VASurfaceID *surfaces,		/* out */
		unsigned int num_surfaces,
		VASurfaceAttrib *attrib_list,
		unsigned int num_attribs
	);

	VAStatus (*vaDestroySurfaces) (
		VADriverContextP ctx,
		VASurfaceID *surface_list,
		int num_surfaces
	);

	VAStatus (*vaCreateContext) (
		VADriverContextP ctx,
		VAConfigID config_id,
		int picture_width,
		int picture_height,
		int flag,
		VASurfaceID *render_targets,
		int num_render_targets,
		VAContextID *context		/* out */
	);

	VAStatus (*vaDestroyContext) (
		VADriverContextP ctx,
		VAContextID context
	);

	VAStatus (*vaCreateBuffer) (
		VADriverContextP ctx,
		VAContextID context,		/* in */
		VABufferType type,		/* in */
		unsigned int size,		/* in */
		unsigned int num_elements,	/* in */
		void *data,			/* in */
		VABufferID *buf_id		/* out */
	);

	VAStatus (*vaBufferSetNumElements) (
		VADriverContextP ctx,
		VABufferID buf_id,	/* in */
		unsigned int num_elements	/* in */
	);

	VAStatus (*vaMapBuffer) (
		VADriverContextP ctx,
		VABufferID buf_id,	/* in */
		void **pbuf         /* out */
	);

	VAStatus (*vaUnmapBuffer) (
		VADriverContextP ctx,
		VABufferID buf_id	/* in */
	);

	VAStatus (*vaDestroyBuffer) (
		VADriverContextP ctx,
		VABufferID buffer_id
	);

	VAStatus (*vaBeginPicture) (
		VADriverContextP ctx,
		VAContextID context,
		VASurfaceID render_target
	);

	VAStatus (*vaRenderPicture) (
		VADriverContextP ctx,
		VAContextID context,
		VABufferID *buffers,
		int num_buffers
	);

	VAStatus (*vaEndPicture) (
		VADriverContextP ctx,
		VAContextID context
	);

	VAStatus (*vaSyncSurface) (
		VADriverContextP ctx,
		VASurfaceID render_target
	);

	VAStatus (*vaQuerySurfaceStatus) (
		VADriverContextP ctx,
		VASurfaceID render_target,
		VASurfaceStatus *status	/* out */
	);

        VAStatus (*vaQuerySurfaceError) (
                VADriverContextP ctx,
                VASurfaceID render_target,
                VAStatus error_status,
                void **error_info /*out*/
        );

	VAStatus (*vaPutSurface) (
    		VADriverContextP ctx,
		VASurfaceID surface,
		VADrawable draw, /* X Drawable */
		short srcx,
		short srcy,
		unsigned short srcw,
		unsigned short srch,
		short destx,
		short desty,
		unsigned short destw,
		unsigned short desth,
		VARectangle *cliprects, /* client supplied clip list */
		unsigned int number_cliprects, /* number of clip rects in the clip list */
		unsigned int flags /* de-interlacing flags */
	);

	VAStatus (*vaQueryImageFormats) (
		VADriverContextP ctx,
		VAImageFormat *format_list,        /* out */
		int *num_formats           /* out */
	);

	VAStatus (*vaCreateImage) (
		VADriverContextP ctx,
		VAImageFormat *format,
		int width,
		int height,
		VAImage *image     /* out */
	);

	VAStatus (*vaDeriveImage) (
		VADriverContextP ctx,
		VASurfaceID surface,
		VAImage *image     /* out */
	);

	VAStatus (*vaDestroyImage) (
		VADriverContextP ctx,
		VAImageID image
	);
	
	VAStatus (*vaSetImagePalette) (
	        VADriverContextP ctx,
	        VAImageID image,
	        /*
                 * pointer to an array holding the palette data.  The size of the array is
                 * num_palette_entries * entry_bytes in size.  The order of the components
                 * in the palette is described by the component_order in VAImage struct
                 */
                unsigned char *palette
	);
	
	VAStatus (*vaGetImage) (
		VADriverContextP ctx,
		VASurfaceID surface,
		int x,     /* coordinates of the upper left source pixel */
		int y,
		unsigned int width, /* width and height of the region */
		unsigned int height,
		VAImageID image
	);

	VAStatus (*vaPutImage) (
		VADriverContextP ctx,
		VASurfaceID surface,
		VAImageID image,
		int src_x,
		int src_y,
		unsigned int src_width,
		unsigned int src_height,
		int dest_x,
		int dest_y,
		unsigned int dest_width,
		unsigned int dest_height
	);

	VAStatus (*vaQuerySubpictureFormats) (
		VADriverContextP ctx,
		VAImageFormat *format_list,        /* out */
		unsigned int *flags,       /* out */
		unsigned int *num_formats  /* out */
	);

	VAStatus (*vaCreateSubpicture) (
		VADriverContextP ctx,
		VAImageID image,
		VASubpictureID *subpicture   /* out */
	);

	VAStatus (*vaDestroySubpicture) (
		VADriverContextP ctx,
		VASubpictureID subpicture
	);

        VAStatus (*vaSetSubpictureImage) (
                VADriverContextP ctx,
                VASubpictureID subpicture,
                VAImageID image
        );

	VAStatus (*vaSetSubpictureChromakey) (
		VADriverContextP ctx,
		VASubpictureID subpicture,
		unsigned int chromakey_min,
		unsigned int chromakey_max,
		unsigned int chromakey_mask
	);

	VAStatus (*vaSetSubpictureGlobalAlpha) (
		VADriverContextP ctx,
		VASubpictureID subpicture,
		float global_alpha 
	);

	VAStatus (*vaAssociateSubpicture) (
		VADriverContextP ctx,
		VASubpictureID subpicture,
		VASurfaceID *target_surfaces,
		int num_surfaces,
		short src_x, /* upper left offset in subpicture */
		short src_y,
		unsigned short src_width,
		unsigned short src_height,
		short dest_x, /* upper left offset in surface */
		short dest_y,
		unsigned short dest_width,
		unsigned short dest_height,
		/*
		 * whether to enable chroma-keying or global-alpha
		 * see VA_SUBPICTURE_XXX values
		 */
		unsigned int flags
	);

	VAStatus (*vaDeassociateSubpicture) (
		VADriverContextP ctx,
		VASubpictureID subpicture,
		VASurfaceID *target_surfaces,
		int num_surfaces
	);

	VAStatus (*vaQueryDisplayAttributes) (
		VADriverContextP ctx,
		VADisplayAttribute *attr_list,	/* out */
		int *num_attributes		/* out */
        );

	VAStatus (*vaGetDisplayAttributes) (
		VADriverContextP ctx,
		VADisplayAttribute *attr_list,	/* in/out */
		int num_attributes
        );
        
        VAStatus (*vaSetDisplayAttributes) (
		VADriverContextP ctx,
                VADisplayAttribute *attr_list,
                int num_attributes
        );

        /* used by va trace */        
        VAStatus (*vaBufferInfo) (
                VADriverContextP ctx,
                VAContextID context, /* in */
                VABufferID buf_id, /* in */
                VABufferType *type,    /* out */
                unsigned int *size,    /* out */
                unsigned int *num_elements /* out */
        );

        /* lock/unlock surface for external access */    
        VAStatus (*vaLockSurface) (
		VADriverContextP ctx,
                VASurfaceID surface,
                unsigned int *fourcc, /* out  for follow argument */
                unsigned int *luma_stride,
                unsigned int *chroma_u_stride,
                unsigned int *chroma_v_stride,
                unsigned int *luma_offset,
                unsigned int *chroma_u_offset,
                unsigned int *chroma_v_offset,
                unsigned int *buffer_name, /* if it is not NULL, assign the low lever
                                            * surface buffer name
                                            */
                void **buffer /* if it is not NULL, map the surface buffer for
                                * CPU access
                                */
        );
    
        VAStatus (*vaUnlockSurface) (
		VADriverContextP ctx,
                VASurfaceID surface
        );
};

/* Driver context */
struct VA_DRIVER_CONTEXT {
    void *pDriverData;
    struct VA_DRIVER_VTABLE *vtable;
    struct VADriverVTableGLX *vtable_glx;
    struct VADriverVTableEGL *vtable_egl;
    void *vtable_tpi; /* the structure is malloc-ed */

    Display *native_dpy;
    int x11_screen;
    int version_major;
    int version_minor;
    int max_profiles;
    int max_entrypoints;
    int max_attributes;
    int max_image_formats;
    int max_subpic_formats;
    int max_display_attributes;
    const char *str_vendor;

    void *handle;			/* dlopen handle */
    
    void *dri_state;
    void *glx;                         /* opaque for GLX code */
};
#endif

static VAStatus FUNC(Terminate)(VA_DRIVER_CONTEXT_P ctx)
{
    VDPAU_DRIVER_DATA_INIT;

    vdpau_common_Terminate(driver_data);

    free(ctx->pDriverData);
    ctx->pDriverData = NULL;

    return VA_STATUS_SUCCESS;
}

static VAStatus FUNC(Initialize)(VA_DRIVER_CONTEXT_P ctx)
{
    struct vdpau_driver_data *driver_data;

    driver_data = calloc(1, sizeof(*driver_data));
    if (!driver_data)
        return VA_STATUS_ERROR_ALLOCATION_FAILED;

    ctx->pDriverData            = driver_data;
    driver_data->x11_dpy        = ctx->native_dpy;
    driver_data->x11_screen     = ctx->x11_screen;

    VAStatus va_status = vdpau_common_Initialize(driver_data);
    if (va_status != VA_STATUS_SUCCESS) {
        FUNC(Terminate)(ctx);
        return va_status;
    }

    ctx->version_major          = VA_INIT_VERSION_MAJOR;
    ctx->version_minor          = VA_INIT_VERSION_MINOR;
    ctx->max_profiles           = VDPAU_MAX_PROFILES;
    ctx->max_entrypoints        = VDPAU_MAX_ENTRYPOINTS;
    ctx->max_attributes         = VDPAU_MAX_CONFIG_ATTRIBUTES;
    ctx->max_image_formats      = VDPAU_MAX_IMAGE_FORMATS;
    ctx->max_subpic_formats     = VDPAU_MAX_SUBPICTURE_FORMATS;
    ctx->max_display_attributes = VDPAU_MAX_DISPLAY_ATTRIBUTES;
    ctx->str_vendor             = driver_data->va_vendor;

    struct VA_DRIVER_VTABLE *vtable;
    vtable = ctx->vtable;
    memset(vtable, 0, sizeof(*vtable));
    vtable->vaTerminate                     = FUNC(Terminate);
    vtable->vaQueryConfigEntrypoints        = vdpau_QueryConfigEntrypoints;
    vtable->vaQueryConfigProfiles           = vdpau_QueryConfigProfiles;
    vtable->vaQueryConfigEntrypoints        = vdpau_QueryConfigEntrypoints;
    vtable->vaQueryConfigAttributes         = vdpau_QueryConfigAttributes;
    vtable->vaCreateConfig                  = vdpau_CreateConfig;
    vtable->vaDestroyConfig                 = vdpau_DestroyConfig;
    vtable->vaGetConfigAttributes           = vdpau_GetConfigAttributes;
    vtable->vaCreateSurfaces                = vdpau_CreateSurfaces;
    vtable->vaCreateSurfaces2               = vdpau_CreateSurfaces2;
    vtable->vaDestroySurfaces               = vdpau_DestroySurfaces;
    vtable->vaCreateContext                 = vdpau_CreateContext;
    vtable->vaDestroyContext                = vdpau_DestroyContext;
    vtable->vaCreateBuffer                  = vdpau_CreateBuffer;
    vtable->vaBufferSetNumElements          = vdpau_BufferSetNumElements;
    vtable->vaMapBuffer                     = vdpau_MapBuffer;
    vtable->vaUnmapBuffer                   = vdpau_UnmapBuffer;
    vtable->vaDestroyBuffer                 = vdpau_DestroyBuffer;
    vtable->vaBeginPicture                  = vdpau_BeginPicture;
    vtable->vaRenderPicture                 = vdpau_RenderPicture;
    vtable->vaEndPicture                    = vdpau_EndPicture;
    vtable->vaSyncSurface                   = vdpau_SyncSurface2;
    vtable->vaQuerySurfaceStatus            = vdpau_QuerySurfaceStatus;
    vtable->vaPutSurface                    = vdpau_PutSurface;
    vtable->vaQueryImageFormats             = vdpau_QueryImageFormats;
    vtable->vaCreateImage                   = vdpau_CreateImage;
    vtable->vaDeriveImage                   = vdpau_DeriveImage;
    vtable->vaDestroyImage                  = vdpau_DestroyImage;
    vtable->vaSetImagePalette               = vdpau_SetImagePalette;
    vtable->vaGetImage                      = vdpau_GetImage;
    vtable->vaPutImage                      = vdpau_PutImage_full;
    vtable->vaQuerySubpictureFormats        = vdpau_QuerySubpictureFormats;
    vtable->vaCreateSubpicture              = vdpau_CreateSubpicture;
    vtable->vaDestroySubpicture             = vdpau_DestroySubpicture;
    vtable->vaSetSubpictureImage            = vdpau_SetSubpictureImage;
    vtable->vaSetSubpictureChromakey        = vdpau_SetSubpictureChromakey;
    vtable->vaSetSubpictureGlobalAlpha      = vdpau_SetSubpictureGlobalAlpha;
    vtable->vaAssociateSubpicture           = vdpau_AssociateSubpicture_full;
    vtable->vaDeassociateSubpicture         = vdpau_DeassociateSubpicture;
    vtable->vaQueryDisplayAttributes        = vdpau_QueryDisplayAttributes;
    vtable->vaGetDisplayAttributes          = vdpau_GetDisplayAttributes;
    vtable->vaSetDisplayAttributes          = vdpau_SetDisplayAttributes;
    vtable->vaBufferInfo                    = vdpau_BufferInfo;
    vtable->vaLockSurface                   = vdpau_LockSurface;
    vtable->vaUnlockSurface                 = vdpau_UnlockSurface;

    return VA_STATUS_SUCCESS;
}

#undef VA_INIT_CURRENT
#undef VA_INIT_VERSION_MAJOR
#undef VA_INIT_VERSION_MINOR
#undef VA_INIT_SUFFIX

#undef VA_DRIVER_VTABLE
#undef VA_DRIVER_VTABLE_GLX_P
#undef VA_DRIVER_CONTEXT
#undef VA_DRIVER_CONTEXT_P
