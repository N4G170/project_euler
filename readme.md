# Project Euler project

I uploaded the code to github for convenience, but if anyone finds it useful, even as a bad example, good.

NOTE:github is marking the project as C, but it is C++ only.

This project is one of my oldest ones, it has the implementation of algorithms used to solve some of the mathematical problems from the [Project Euler website](https://projecteuler.net/).

WARNING: If you want to solve them yourself do not read my solutions, study the maths and try.

It started as a simple console application with a simple text base ui, then I made a rudimentary gui with SDL2, and right now it uses my [sdl_gui](https://github.com/N4G170/sdl_gui), it looks bad, really bad, my ui design skills are not very good, but it works.

Truth be told, the interesting bit of this project is not the ui but the algorithms used to solve the problems.

Currently the problems solved and available(some are solved but are too slow so they need to be changed) to the program are:

[1](https://projecteuler.net/problem=1), [2](https://projecteuler.net/problem=2), [3](https://projecteuler.net/problem=3)(\*), [4](https://projecteuler.net/problem=4),     [5](https://projecteuler.net/problem=5), [6](https://projecteuler.net/problem=6), [7](https://projecteuler.net/problem=7), [8](https://projecteuler.net/problem=8),     [9](https://projecteuler.net/problem=9), [10](https://projecteuler.net/problem=10), [11](https://projecteuler.net/problem=11), [12](https://projecteuler.net/problem=12), [13](https://projecteuler.net/problem=13), [14](https://projecteuler.net/problem=14), [15](https://projecteuler.net/problem=15), [16](https://projecteuler.net/problem=16), [17](https://projecteuler.net/problem=17), [18](https://projecteuler.net/problem=18), [19](https://projecteuler.net/problem=19), [20](https://projecteuler.net/problem=20), [21](https://projecteuler.net/problem=21), [22](https://projecteuler.net/problem=22), [23](https://projecteuler.net/problem=23), [24](https://projecteuler.net/problem=24), [25](https://projecteuler.net/problem=25)(\*),

[27](https://projecteuler.net/problem=27), [29](https://projecteuler.net/problem=29), [30](https://projecteuler.net/problem=30), [34](https://projecteuler.net/problem=34),
[35](https://projecteuler.net/problem=35), [36](https://projecteuler.net/problem=36)(\*), [40](https://projecteuler.net/problem=40), [42](https://projecteuler.net/problem=42), [48](https://projecteuler.net/problem=48), [49](https://projecteuler.net/problem=49),
[52](https://projecteuler.net/problem=52), [67](https://projecteuler.net/problem=67), [71](https://projecteuler.net/problem=71), [72](https://projecteuler.net/problem=72),
[73](https://projecteuler.net/problem=73), [80](https://projecteuler.net/problem=80), [81](https://projecteuler.net/problem=81), [83](https://projecteuler.net/problem=83),
[92](https://projecteuler.net/problem=92), [94](https://projecteuler.net/problem=94)(\*)

\* - Disabled on windows as it either crashes or returns wrong answer

The marked problems are disabled on the windows build and the code is protected with a preprocessor guard to avoid mistakes.
I already know what the problems are with them, for example, I use GMP on the linux version for big numbers calculations and I could not find a binary version of it for windows, only compile it yourself, a I did, and it failed (haven't tried since). To remediate I chose to use boost multiprecision libs, they work, but are slow and it can cause problems.
For example, problem 25 uses boost big numbers and after a log while the program crashes. Problems 3 and 94 have problems with precision, I gave the biggest variable available and they still give a wrong answer.

So it upsets me a little, that even simple code with no external dependencies give different result depending on the platform. I now have a lot more respect for porting companies.


## Running the program
If you are using one of the release builds, double click the .exe on windows or run in a terminal on linux.
The provided build represents a demo showcasing the elements present on the project. Use the button on the top to change panels and try the elements.

## Building the program

If you are building this project I recommend using a linux distro, as it is so easier and all problems run.

### If on Linux

First install all the dependencies:
- SDL2
- SDL2_image
- SDL2_ttf
- boost
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
The linux build uses a separate .so lib with only the gui files.
Sadly on windows I was unable to do so, as sdl_gui code is not ready for it, when implementing the ECS I'll take extra care to make the code ready for it.

NOTE: As cmake creates the executable as a shared object (I have yet to find why), you have to run the program through the terminal, rather than double click

### On windows

On windows, building the program is not that easier. As the cmake module used to find SDL2 does not work on windows, the build has to be made manually.

Inside the vs folder there is a Visual studio solution configured to build the program using the current folder structure.
You also need to add the boost headers folder to the include folder inside dependencies (I did not include it because it is too big, you can download it from http://www.boost.org/)
If all goes well, all you have to do is open the solution, and build (only works for x64 builds).

If the solution does not work, or you use another build system, you have to add the files by hand to you project and take care of the dependencies.
For ease of building, you can find the needed dependencies inside the vs folder.
NOTE: I do not own any of the code from the dependencies(other than sdl_gui). Their license allows them to be freely used and shared.

To run the program, you need the data folder next to the .exe as well as all of SDL2, SDL2_image, SDL2_ttf dlls (you can find them in my release or download them from the SDL website).

NOTE: the windows builds does not use sdl_gui as a separate lib, as I was unable to do so, because sdl_gui code is not ready for it, when implementing the ECS I'll take extra care to make the code ready for it. One of the problems of multiplatform development, if you do not expect it.

## TODO

Correct the problems with the windows build and solve more problems (my first objective is to solve the first 100).

If you find any bug of error, let me know.
