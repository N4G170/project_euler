# Project Euler project

This is my oldest project (it suffered many facelifts), it has the implementation of algorithms used to solve some of the mathematical problems from the [Project Euler website](https://projecteuler.net/).

WARNING: If you want to solve them yourself do not read my solutions, study the maths and try it.

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

Another change was the reintroduction of the use of the keyboard to request problems. Number keys 1-0 can be used to insert, well, numbers and a problem can be requested using the RETURN or ENTER keys. BACKSPACE and DELETE act the same as the clear button.

## Running the program
You can download the latest release from the release tab ([link](https://github.com/N4G170/project_euler/releases)) or you can build it yourself.
The windows release has the needed dlls. On Linux make sure to install the dependencies SDL2, SDL2_image, SDL2_ttf and gmp.

## Building the program

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
If no errors appear, the build is complete inside the "bin" folder and you can run the program with the command ./euler in your terminal (you can only run it from the terminal).
NOTE: As cmake creates the executable as a shared object (I have yet to find why), you have to run the program through the terminal, rather than double click

### On windows

Note: On windows I only tested using Visual Studio 2017 (you can use whatever you want as long as it supports cpp14).

On windows you need to download [cmake](https://cmake.org/) and use it to create a "vs 15 2017 64bit" solution (needs to be 64bit).
To use cmake, create a "build" folder and set it as build folder. Set the root of the project as the source folder and run it. Inside the build folder will be a vs solution.
Open the solution, set it to release (64bit) and build it. The final build and all needed dlls and the data folder will be inside the "bin/release" folder.

## TODO

Solve the problems currently on standby and then solve more (I want to solve the first 100 before going for the next 100).

If you find any bug of error, let me know.
