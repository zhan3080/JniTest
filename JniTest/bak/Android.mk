LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_MODULE := jni_test
LOCAL_SRC_FILES := jni_test.cpp
LOCAL_C_INCLUDES := \
			 $(LOCALE_PATH)
			 
#����log���ļ�
LOCAL_LDLIBS += -llog 
#ѹ���⣨Z�� ʵʱ�⣨real time����ѧ�⣨math�� ��׼C�⣨C lib��  dl��(libdl.so)
#LOCAL_LDLIBS += -lz -lrt -lm -lc -ldl
#����ʱ���Ƿ���ʾwarn������Ϣ
LOCAL_CFLAGS += -W -Wall
#LOCAL_CFLAGS+=-llog

#LOCAL_ALLOW_UNDEFINED_SYMBOLS := true
#LOCAL_DISABLE_FATAL_LINKER_WARNINGS := true

include $(BUILD_SHARED_LIBRARY)