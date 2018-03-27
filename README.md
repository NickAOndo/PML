# PML
Library for a 3-D OpenGL renderer.  (Pixel Mash Library)

Currently this library is housed as an executable until more leading features are added.

In order to run the library, one needs to link against and include the requisite:

1.) SDL2 library

2.) SDL2_image library

3.) GLEW library

N.B. The graphics card must be compliant with Open GL 3.2.

N.B. When compiling on Windows based OS's, the #include <SDL2/SDL.h> (and all SDL2 headers),
must be renamed to "<SDL.h>" without the "SDL2/".
