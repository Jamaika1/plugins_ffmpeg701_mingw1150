

#include "config.h"
#include "rsvg.h"

/* enumerations from "rsvg.h" */
GType
rsvg_error_get_type (void)
{
  static GType g_define_type_id__volatile = 0;

  if (g_once_init_enter_pointer (&g_define_type_id__volatile))
    {
      static const GEnumValue values[] = {
        { RSVG_ERROR_FAILED, "RSVG_ERROR_FAILED", "failed" },
        { 0, NULL, NULL }
      };
      GType g_define_type_id =
        g_enum_register_static (g_intern_static_string ("RsvgError"), values);
      g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
    }

  return g_define_type_id__volatile;
}
GType
rsvg_handle_flags_get_type (void)
{
  static GType g_define_type_id__volatile = 0;

  if (g_once_init_enter_pointer (&g_define_type_id__volatile))
    {
      static const GFlagsValue values[] = {
        { RSVG_HANDLE_FLAGS_NONE, "RSVG_HANDLE_FLAGS_NONE", "flags-none" },
        { RSVG_HANDLE_FLAG_UNLIMITED, "RSVG_HANDLE_FLAG_UNLIMITED", "flag-unlimited" },
        { RSVG_HANDLE_FLAG_KEEP_IMAGE_DATA, "RSVG_HANDLE_FLAG_KEEP_IMAGE_DATA", "flag-keep-image-data" },
        { 0, NULL, NULL }
      };
      GType g_define_type_id =
        g_flags_register_static (g_intern_static_string ("RsvgHandleFlags"), values);
      g_once_init_leave (&g_define_type_id__volatile, g_define_type_id);
    }

  return g_define_type_id__volatile;
}



