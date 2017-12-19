LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	main.cpp imgui_impl_sdl_gles2.cpp imgui_draw.cpp imgui_demo.cpp imgui.cpp
	#main.cpp imgui_impl_sdl.cpp imgui_draw.cpp imgui_demo.cpp imgui.cpp

#testgles.c

LOCAL_SHARED_LIBRARIES := SDL2

#LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -lOpenSLES
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -lOpenSLES

include $(BUILD_SHARED_LIBRARY)
