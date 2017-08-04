LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_MODULE := jni_test
LOCAL_SRC_FILES := jni_test.cpp
LOCAL_C_INCLUDES := \
			 $(LOCALE_PATH)
			 
#链接log库文件
LOCAL_LDLIBS += -llog 
#压缩库（Z） 实时库（real time）数学库（math） 标准C库（C lib）  dl库(libdl.so)
#LOCAL_LDLIBS += -lz -lrt -lm -lc -ldl
#编译时，是否提示warn警告信息
LOCAL_CFLAGS += -W -Wall
#LOCAL_CFLAGS+=-llog

#LOCAL_ALLOW_UNDEFINED_SYMBOLS := true
#LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true

include $(BUILD_SHARED_LIBRARY)