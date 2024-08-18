// ===========================================================================
// version.h
// - collection of version numbers
//
// Author:  Falei LUO <falei.luo@gmail.com>
//
// ===========================================================================

#ifndef XAVS2_VERSION_H
#define XAVS2_VERSION_H

// version number
#define VER_MAJOR         1     // major version number
#define VER_MINOR         7     // minor version number
#define VER_BUILD         0     // build number
#define VER_SHA_STR       "cc1ed78"  // commit id

// stringify
#define _TOSTR(x)       #x            // stringify x
#define TOSTR(x)        _TOSTR(x)     // stringify x, perform macro expansion

// define XVERSION string
#define XVERSION        1, 7, 0
#define XVERSION_STR    TOSTR(1) "." TOSTR(7) "." TOSTR(0) " " VER_SHA_STR
#define XBUILD_TIME     "2022-11-30 00:00:00"

#define XAVS2_VERSION      010700
#define XAVS2_POINTVER  "1.7.0"

#endif // __VERSION_H__
