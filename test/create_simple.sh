#!/bin/bash
# export JAVA_HOME=/home/peyrardj/local/jdk1.8.0_111/
# export ANDROID_HOME=/home/peyrardj/local/android-sdk-linux/
# export NDK_STANDALONE=/home/peyrardj/local/android-ndk-r13b/
# export PATH=$JAVA_HOME/bin/:$PATH:$NDK_STANDALONE:$ANDROID_HOME/tools

android create project --name AndroidHelloJNI --activity JNIActivity --package "com.mytest"   --path . --target 1
ant
ant debug
find .|grep apk

