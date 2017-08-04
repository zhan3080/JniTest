#include <jni.h>
#include <stdio.h>
#include <android/log.h>

#define TAG "JniTest"
#define LOG_DEBUG(tag, ...)  __android_log_print(ANDROID_LOG_DEBUG,tag,__VA_ARGS__)
#define LOG_INFO(tag, ...)  __android_log_print(ANDROID_LOG_INFO,tag,__VA_ARGS__)

void jniTestVoid(){
	LOG_INFO(TAG,"test jni void");
}


//JNIEXPORT void JNICALL Java_com_jni_test_jniTestVoid(JNIEnv *env, jobject jthiz)
JNIEXPORT void JNICALL nJniTestVoid(JNIEnv *env, jobject jthiz){
	jniTestVoid();
	return;
}


static const char* classPathName = "com/jni/test/JniTest";
static JNINativeMethod methods[] = {
		{"jniTestVoid",  "()V",  (void*)nJniTestVoid}
};

static int registerNativeMethods(JNIEnv *env, const char* className, JNINativeMethod* gMethods, int numMethods){
	jclass clazz;
	clazz = env->FindClass(className);
	if(clazz == NULL)
	{
		LOG_DEBUG(TAG, "Native registration unable to find class '%s'", className);
		return JNI_FALSE;
	}
	if(env->RegisterNatives(clazz,gMethods,numMethods)<0)
	{
		LOG_DEBUG(TAG, "RegisterNatives failed for '%s'", className);
		return JNI_FALSE;
	}
	return JNI_TRUE;
}

static int registerNatives(JNIEnv *env)
{
	if (!registerNativeMethods(env, classPathName,methods, sizeof(methods) / sizeof(methods[0])))
		{
			return JNI_FALSE;
		}
		return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv *env;
//	gJavaVM = vm;
	int result;

	LOG_DEBUG(TAG,"JNI OnLoad call");
	if(vm->GetEnv((void**)&env,JNI_VERSION_1_4) != JNI_OK)
	{
		LOG_DEBUG(TAG, "(JNI_OnLoad()) .... Failed to get the environment using GetEnv()");
				return -1;
	}
	if (registerNatives(env) != JNI_TRUE)
	{
		LOG_DEBUG(TAG, "ERROR: registerNatives failed .... (JNI_OnLoad())");
		goto bail;
	}

	result = JNI_VERSION_1_4;
	LOG_DEBUG(TAG, "JNI_OnLoad success");

	bail:
	return result;
}
