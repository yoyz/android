LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cursynth

#SDL_PATH := ../SDL

#LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include

# Add your application source files here...
#LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	#main.c opensl_io.c
#testgles.c
#LOCAL_SRC_FILES := coeff.cpp echo.cpp env.cpp envtab.cpp filter.cpp lfo.cpp lfotab.cpp osc.cpp osctab.cpp synthengine.cpp 
LOCAL_SRC_FILES := delay.cpp cursynth_strings.cpp cursynth_engine.cpp mono_panner.cpp midi_lookup.cpp linear_slope.cpp filter.cpp feedback.cpp envelope.cpp processor_router.cpp processor.cpp oscillator.cpp operators.cpp value.cpp trigger_operators.cpp step_generator.cpp smooth_value.cpp smooth_filter.cpp send_receive.cpp wave.cpp voice_handler.cpp

#LOCAL_SHARED_LIBRARIES := SDL2

#LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -lOpenSLES

include $(BUILD_SHARED_LIBRARY)
