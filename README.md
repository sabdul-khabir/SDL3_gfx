# SDL3_gfx
> Graphics primitives and surface functions for SDL3

![FilledCircle](https://github.com/user-attachments/assets/7c848ff5-cd66-4c56-b655-0684fffed826)

## Contact and License

Email aschiffler at ferzkopp dot net to contact the author 
or better check author's homepage at http://www.ferzkopp.net 
for the most up-to-date contact information.

This library is licenced under the zlib License, see the file LICENSE for details. 


## Introduction

The SDL3_gfx library provides the basic drawing functions such as lines,
circles or polygons provided by SDL_gfx on SDL3 against renderers of SDL3.

The current components of the SDL3_gfx library are:
- Graphic Primitives (SDL3_gfxPrimitives.h, SDL3_gfxPrimitives.c)
- Surface Rotozoomer (SDL3_rotozoom.h, SDL3_rotozoom.c)
- Framerate control (SDL3_framerate.h, SDL3_framerate.c)
- MMX image filters (SDL3_imageFilter.h, SDL3_imageFilter.c)
- Build-in 8x8 Font (SDL3_gfxPrimitives_font.h)

Note that SDL3_gfx is compatible with SDL version 3.0 (not SDL 1.2 or 2.0).

## Installation

### Unix/Linux

Use the standard cmake sequence to compile and install the library.
Update the cmake file to point to your specific configuration.
```
        cmake ..
        cmake --build .
        cmake --install
        ldconfig
```

### Windows (VS2022)

Open the SDL3_gfx.sln solution file, right click on the solution and choose 'Rebuild'.

The SDL3 folder must be placed in a directory alongside SDL3_gfx (or sdl3gfx-code) and build in the same configuration, i.e. Debug or Release, beforehand so the referenced SDL3.lib file can be found.

## Test Programs

The tests are currently built with the library.

## Documentation

Please refer to the Doxygen-generated API documentation found in the
Docs/html folder as well as the test programs in the test folder.

## Change Log

```ChangeLog
```

