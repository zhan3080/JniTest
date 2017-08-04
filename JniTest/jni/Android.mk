#LOCAL_PATH := $(call my-dir)
#include $(CLEAR_VARS)
#
#LOCAL_MODULE := JniTest1
#LOCAL_SRC_FILES := JniTest1.cpp
#
#LOCAL_LDLIBS := -llog
#
#include $(BUILD_SHARED_LIBRARY)

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := JniNativeCallback
LOCAL_SRC_FILES := JniNativeCallback.cpp

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)