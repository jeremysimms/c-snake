# C-Snake

##Introduction
It's a fairly straightforward Snake clone I've been writing in my spare time in order to better understand how C works, and how to design a reasonably complex program in it. Some would say to learn the language first, and then jump into doing more complicated things like game development, but the learning experiment has been fruitful so far. I am sure there are numerous problems with this so it is an ongoing project, but the rewards of learning how to manage memory and deal with pointers have been tremendous. I attempted to make the codebase about as extensible as I could given my level of expertise and I think most of the base structs can be reused to a certain degree. I guess I'll know for sure on my next game. Overall I think C is my new favorite language, and although debugging can be a hastle at times (learning the unix tool chain has helped a lot with this though), I believe it has made me a better programmer.

Thanks to Carleton Burke for the music.

##Dependencies

In order to run this game you must install the SDL, and SDL_image libraries.

On Debian based systems:
```
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-2.0-0 libsdl2-dbg libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-image-dbg
```

##Compiling

Once you have the required libraries installed, compiling is just a simple matter of running make in the top level directory of the project.

```
cd c-snake
make
```

The compiled executable will be located in the `bin` directory and will be named `game`. If you'd like to build the executable with debug flags, simply run `make debug` instead of `make`.


##Running

To run the game, your current working directory must be the top level directory of the project, otherwise the game will not be able to locate its required resources correctly and the sprites will not render. Once I have a cross platform resource loading solution figured out this will no longer be necessary but until then, you must execute the game a level up from the `bin` directory.

```
cd c-snake
./bin/game
```

##Notes

Although this game works fine on both OSX and Windows, I have not yet nailed down a solution for resource loading, so I will be holding off on creating prebuilt binaries for these operating systems. For now, if you follow the same compilation steps with minGW32 on windows or Clang on Mac OS, the game should work fine in much the same way. At some point I hope to at least have some sort of cross compiling solution for windows set up on a Jenkins box that will build automatically whenever commits are pushed to this repo. Stay tuned for more.
