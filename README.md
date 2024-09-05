This library is for amateurs trying to add codec plugins and librsvg for ffmpeg in GCC 11.5.0. Overall, a waste of time without cmake, and it's best to buy something paid and working.
It's complicated, but possible to create. GCC 11.5.0 has pthread for win64 and C++11 thread/mutex posix compatible with windows.
The library removes gcc warning messages that don't appear in visual studio. One of the problems is whether unsigned integer can be negative. As some developers say don't use GCC shit on windows.So what do these programs do on websites?
Does everything work? These are examples of fixes for the current latest versions of the libraries. SVG files can be played. Fonts in SVG files don't rotate. The rotate="..." function doesn't work. SVG animation doesn't work.
Should all plugins be added? Not necessarily. I don't want to add, for example, lzma. You have to delete the ENABLE_LZMA definition in programs. And there will be no decoding of lzma compression.
Codecs xavs, xavs2, uavs3, xeve, uvg266 are prototypes, unfinished and will probably remain as is. Chinese avs4 equivalent based on vvc has not been released.
