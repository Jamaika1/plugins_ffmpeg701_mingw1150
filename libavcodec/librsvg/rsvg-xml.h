/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* vim: set sw=4 sts=4 expandtab: */
/*
 * Copyright © 2010 Christian Persch
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
  
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
*/

#ifndef RSVG_XML_H
#define RSVG_XML_H

#include "libxml2/xmlIO.h"
#include "gio/gio.h"

G_BEGIN_DECLS

G_GNUC_INTERNAL
xmlParserCtxtPtr rsvg_create_xml_parser_from_stream (xmlSAXHandlerPtr sax,
						     void            *sax_user_data,
						     GInputStream    *stream,
						     GCancellable    *cancellable,
						     GError         **error);

G_END_DECLS

#endif /* !RSVG_XML_H */
