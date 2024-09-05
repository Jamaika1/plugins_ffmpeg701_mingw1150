/*** BEGIN file-header ***/
#if defined(GDK_PIXBUF_DISABLE_SINGLE_INCLUDES) && !defined (GDK_PIXBUF_H_INSIDE) && !defined (GDK_PIXBUF_COMPILATION)
#error "Only <gdk-pixbuf/gdk-pixbuf.h> can be included directly."
#endif

#ifndef __GDK_PIXBUF_ENUM_TYPES_H__
#define __GDK_PIXBUF_ENUM_TYPES_H__

#include "../glib/glib-object.h"

#include "gdk-pixbuf-macros.h"

G_BEGIN_DECLS
GDK_PIXBUF_AVAILABLE_IN_ALL GType gdk_colorspace_get_type (void) G_GNUC_CONST;
#define GDK_TYPE_COLORSPACE (gdk_colorspace_get_type ())
G_END_DECLS

#endif /* __GDK_PIXBUF_ENUM_TYPES_H__ */
/*** END file-tail ***/
