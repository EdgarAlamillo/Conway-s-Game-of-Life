# Conway-s-Game-of-Life using SFML

## Discription
This is John Conway's [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) implementaion using [SFML 2.6.2](https://www.sfml-dev.org/download/sfml/2.6.2/) and C++ 20. Game of life rules are that if an alive cell has atleast 2 neighbors it lives and if not it dies. With this algorithm it can create some interesting paterns. The program uses unordered sets which has mutiple copies for each state so it is all update smoothly. By defualt the simulation starts with a line going across the screen which can be changed if you want as it is in the constructer. This implementation has a finite grid (720 x 1280) and allows for drawing with the mouse.

## Screenshot

<img width="2564" height="1502" alt="image" src="https://github.com/user-attachments/assets/c0d2771b-fb62-4154-b8da-bbf74937be60" />

## Video

https://github.com/user-attachments/assets/613386ba-db6e-4703-b965-92fe01dcb775

## Requirements
 - C++ 20 compiler
 - SFML 2.6.2
 - CMake 3.16 or aboe 
## How to Run
Cmake is set up to download the dependencies and link. In terminal run
```
git clone https://github.com/EdgarAlamillo/Conway-s-Game-of-Life.git
cd Conway-s-Game-of-Life
mkdir build
cd build
cmake ..
make
./GameofLife
```
