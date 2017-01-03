LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/../SDL2_ttf

LOCAL_CFLAGS += -D__SDL20__
# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	Block.cpp  DrawSdl.cpp  GameBoard.cpp  GameSdl.cpp  main.cpp  Shape.cpp opensl_io.c
#testgles.c

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -lOpenSLES

include $(BUILD_SHARED_LIBRARY)
