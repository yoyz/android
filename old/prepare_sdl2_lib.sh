rm -rf  SDL2-2.0.3/build/org.libsdl.testgles/jni/src/
cd      SDL2-2.0.3/build/org.libsdl.testgles/
ln -s ../../../../SDL2_image/external/libwebp-0.3.0/ jni/webp
ln -s ../../../../SDL2_mixer/ jni/
ln -s ../../../../SDL2_mixer/external/libmikmod- jni/
ln -s ../../../../SDL2_mixer/external/libmikmod-3.1.12/ jni/libmikmod
ln -s ../../../../SDL2_mixer/external/smpeg2-2.0.0/ jni/smpeg2
ln -s ../../../../SDL2_net/ jni/
ln -s ../../../../SDL2_ttf/ jni/

