# media_programming_3D_shading
A very simple 3D shading engine written in C++. This is a extenstion of the assignment in media programming course in Hokkiado University in 2023. 

# How to compile
Since I used the windows-bmp IO library provided by the professor to output rendered image, 
it is necessary to compile the program in windows environment. 

But I cannot deal with the slash direction problem properly in makefile, so please execute the makefile in WSL with C++ compiler in windows.
The current makefile specify CPP compiler as g++.exe from mingw32.

- `make cube`
This compile the cube rotation example.

-`make solar`
This compile the orbit rotation example.

# How export the rendered photo / video
While executing the compiled file, the program will export rendered result frame by frame.
The rendered images will be in `.\output` directory.

The demo videos are made with Blender by concatenating all rendered frame into a video.

# How to create new  animation

Please refer to `cube.cpp` and `solar.cpp` example programs.

# Background

When I was an exchange student in Hokkaido University back in 2023,
in the media programming course, the professor tought us about the basic of 3D shading.

The assignment of implementation of 3D shading engine was not mandatory, but I was interested in it.
So I made use of the 2d array to bmp image library provided by the professor, and tried to implemented the shading engine.

