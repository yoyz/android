Try to build the testgles.c hello world
=======================================

cd SDL/build-scripts/
./androidbuild.sh org.libsdl.testgles ../test/testgles.c
# it will create it in build in the SDL/build/org.libsdl.testgles directory 
# it "should" fail and need some hint
cd ../../
cd SDL/build/org.libsdl.testgles
# list the android target 
# update the project with the first target 
# rebuild in debug mode
android list targets
android update project -p $(pwd) -t 1
ant
ant debug
# find the created apk file
find .|grep apk
# install the debug apk on your device with ant 
ant debug install
# you can reinstall it with this command 
adb install bin/org.libsdl.testgles-debug.apk





rm -rf  SDL2-2.0.3/build/org.libsdl.testgles/jni/src/
cd      SDL2-2.0.3/build/org.libsdl.testgles/
ln -s ../../../../SDL2_image/external/libwebp-0.3.0/ jni/webp
ln -s ../../../../SDL2_mixer/ jni/
ln -s ../../../../SDL2_mixer/external/libmikmod- jni/
ln -s ../../../../SDL2_mixer/external/libmikmod-3.1.12/ jni/libmikmod
ln -s ../../../../SDL2_mixer/external/smpeg2-2.0.0/ jni/smpeg2
ln -s ../../../../SDL2_net/ jni/
ln -s ../../../../SDL2_ttf/ jni/

