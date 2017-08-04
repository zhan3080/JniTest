LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm
LOCAL_MODULE := JniTest
LOCAL_SRC_FILES := JniTest.cpp
LOCAL_LDLIBS := -llog


include $(BUILD_SHARED_LIBRARY)