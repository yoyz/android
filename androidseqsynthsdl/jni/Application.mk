
# Uncomment this if you're using STL in your project
# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
# APP_STL := stlport_static 
#APP_STL := stlport_static 
#NDK_TOOLCHAIN_VERSION := clang
NDK_TOOLCHAIN_VERSION := 4.9
#NDK_TOOLCHAIN_VERSION := g++

#APP_ABI := armeabi armeabi-v7a x86
APP_ABI := x86
APP_CPPFLAGS += -std=c++11
#APP_STL := gnustl_static
LOCAL_C_INCLUDES += ${ANDROID_NDK}/sources/cxx-stl/gnu-libstdc++/4.9/include
#APP_STL := c++_shared 
APP_STL := c++_shared 
#APP_STL:=c++_static 
# Min SDK level
APP_PLATFORM=android-10

