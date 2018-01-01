# Project Euler project

I uploaded the code to github for convenience, but if anyone finds it useful, even as a bad example, good.

NOTE:github is marking the project as C, but it is C++ only.

This project is one of my oldest ones, it has the implementation of algorithms used to solve some of the mathematical problems from the [Project Euler website](https://projecteuler.net/).

WARNING: If you want to solve them yourself do not read my solutions, study the maths and try.

It started as a simple console application with a simple text base ui, then I made a rudimentary gui with SDL2, and right now it uses my [sdl_gui](https://github.com/N4G170/sdl_gui), it looks bad, really bad, my ui design skills are not very good, but it works.

Truth be told, the interesting bit of this project is not the ui but the algorithms used to solve the problems.

Currently the problems solved and available to the user are:

[1](https://projecteuler.net/problem=1), [2](https://projecteuler.net/problem=2), [3](https://projecteuler.net/problem=3), [4](https://projecteuler.net/problem=4),     [5](https://projecteuler.net/problem=5), [6](https://projecteuler.net/problem=6), [7](https://projecteuler.net/problem=7), [8](https://projecteuler.net/problem=8),     [9](https://projecteuler.net/problem=9), [10](https://projecteuler.net/problem=10), [11](https://projecteuler.net/problem=11), [12](https://projecteuler.net/problem=12), [13](https://projecteuler.net/problem=13), [14](https://projecteuler.net/problem=14), [15](https://projecteuler.net/problem=15), [16](https://projecteuler.net/problem=16), [17](https://projecteuler.net/problem=17), [18](https://projecteuler.net/problem=18), [19](https://projecteuler.net/problem=19), [20](https://projecteuler.net/problem=20), [21](https://projecteuler.net/problem=21), [22](https://projecteuler.net/problem=22), [23](https://projecteuler.net/problem=23), [24](https://projecteuler.net/problem=24), [25](https://projecteuler.net/problem=25),

[27](https://projecteuler.net/problem=27), [29](https://projecteuler.net/problem=29), [30](https://projecteuler.net/problem=30), [34](https://projecteuler.net/problem=34),
[35](https://projecteuler.net/problem=35), [36](https://projecteuler.net/problem=36), [40](https://projecteuler.net/problem=40), [42](https://projecteuler.net/problem=42), [48](https://projecteuler.net/problem=48), [49](https://projecteuler.net/problem=49),
[52](https://projecteuler.net/problem=52), [67](https://projecteuler.net/problem=67), [71](https://projecteuler.net/problem=71), [72](https://projecteuler.net/problem=72),
[73](https://projecteuler.net/problem=73), [80](https://projecteuler.net/problem=80), [81](https://projecteuler.net/problem=81), [83](https://projecteuler.net/problem=83),
[92](https://projecteuler.net/problem=92), [94](https://projecteuler.net/problem=94)

As of the last update, windows and Linux builds have the same problems available. When checking problem 25 performance issues (it worked but was too slow on windows so I disabled it), I noticed that the boost big number header I was using was the culprit, so I tried to compile [MPIR](http://mpir.org/) lib again, as it is the best port of [GMP](https://gmplib.org/) for use with MSVC. In the past, I failed to use it, but, using the last release, I found success. So now the windows version uses MPIR for big numbers and the Linux version continues to use GMP.

The other non-working problems, 3, 36 and 94, all suffered from the same problem, lack of precision. For some reason, on windows, a long variable is only 32bit long on 64bit systems, so I had to adjust the code for that, and now all is well.

So it upsets me a little, that even simple code with no external dependencies give different result depending on the platform. I now have a lot more respect for porting companies.

Another change was made, as a test, on this project. The [sdl_gui](https://github.com/N4G170/sdl_gui) used for the UI, now comes as a static lib on both Linux and windows. And after checking the size of the lib file on windows, I decided not to use it in any other project(as a static lib).

Another change was the reintroduction of the use of the keyboard to request problems. Number keys 1-0 can be used to insert, well, numbers and a problem can be requested using the RETURN or ENTER keys. BACKSPACE and DELETE act the same as the clear button.

## Running the program
If you are using one of the release builds, double click the .exe on windows or run in a terminal on Linux.
The provided build represents a demo showcasing the elements present on the project. Use the button on the top to change panels and try the elements.

## Building the program

If you are building this project I recommend using a Linux distro, as it is so easier and all problems run. I removed previous boost dependency.

### If on Linux

First install all the dependencies:
- SDL2
- SDL2_image
- SDL2_ttf
- gmp
- cmake (needed for "fast" build)

After that, open terminal window at the base of the project (the folder with this file) and run the commands:

```
- mkdir build
- cd build
- cmake ..
- make -j
```
If no errors appear, the build is complete and you can run the program with the command ./euler
I did not configure any install instructions, so if you want to move the build, copy the folder 'data' and the file 'euler' from the build folder.
As stated before, the Linux build now uses a static version of the gui lib, so no more .so files to go around.

NOTE: As cmake creates the executable as a shared object (I have yet to find why), you have to run the program through the terminal, rather than double click

### On windows

As my SDL2 cmake modules are not working properly on windows, the 'vs' folder contains a Visual Studio solution with the project and all the needed dependencies linked, so it should be a matter of opening the solution on a VS 15+ and build it.

NOTE: the project only builds when targeting x64.

To run the program, you need the data folder next to the .exe as well as all of [SDL2](https://www.libsdl.org/), [SDL2_image](https://www.libsdl.org/projects/SDL_image/), [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/) dlls (you can find them in my release or download them from the linked SDL website).

As stated before, the current version uses sdl_gui as a static lib, and that is the reason the project is bigger.

## TODO

Solve the problems currently on standby and then solve more (I want to solve the first 100 before going for the next 100).

If you find any bug of error, let me know.
