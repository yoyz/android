#!/bin/bash
echo "Clone SDL"
hg clone http://hg.libsdl.org/SDL SDL
echo "Clone SDL mixer" 
hg clone http://hg.libsdl.org/SDL_mixer SDL2_mixer

echo "Clone SDL net" 
hg clone http://hg.libsdl.org/SDL_net   SDL2_net

echo "Clone SDL ttf" 
hg clone http://hg.libsdl.org/SDL_ttf   SDL2_ttf
