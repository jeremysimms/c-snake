# C-Snake

##Introduction
It's a fairly straightforward Snake clone I've been writing in my spare time in order to better understand how C works, and how to design a reasonably complex program in it. Some would say to learn the language first, and then jump into doing more complicated things like game development, but the learning experiment has been fruitful so far. I am sure there are numerous problems with this so it is an ongoing project, but the rewards of learning how to manage memory and deal with pointers have been tremendous. I attempted to make the codebase about as extensible as I could given my level of expertise and I think most of the base structs can be reused to a certain degree. I guess I'll know for sure on my next game. Overall I think C is my new favorite language, and although debugging can be a hastle at times (learning the unix tool chain has helped a lot with this though), I believe it has made me a better programmer.

Thanks to Carleton Burke for the music.

##Dependencies

In order to compile and run this game you must install the SDL, and SDL_image libraries.

On Debian based systems:
```
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-2.0-0 libsdl2-dbg libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-image-dbg libsdl2-ttf-2.0-0 libsdl2-ttf-dev libsdl2-ttf-dbg
```

##Compiling

Once you have the required libraries installed, compiling is just a simple matter of running make in the top level directory of the project.

```
cd c-snake
make
```

The compiled executable will be located in the `bin` directory and will be named `game`. If you'd like to build the executable with debug flags, simply run `make debug` instead of `make`.


##Running

The game can be run from anywhere now that the resource locator is finished, but now the `res/` exist in the same directory as the executable otherwise the game will not be able to locate its required resources. If the game cannot find its resources, then the all that will appear is a blue screen. After folowing the compilation instructions above, run the following commands to run:

```
mv bin/game .
./bin/game
```

##Controls

* Start/Pause: spacebar
* Move: arrow keys

##Notes

As of now I have a cross compiler and build server set up to handle packaging prebuilt binaries for Windows. I will eventually add a linux install task to the make file for easier compilation and will come up with some methodology for compiling and packaging OSX binaries. OSX is proving to be more troublesome since a GCC cross compiler for it doesn't seem to exist. I might have to just set up a Jenkins slave to run on my laptop, not optimal. Stay tuned.
