#include <jni.h>
#include <android/log.h>
#include <pthread.h>
#include <unistd.h>

#define TAG "Hzz"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)


void *test_thread(void *param)
{
	LOGI("test_thread");
	while(1){
		sleep(2);
		LOGI("sleep 2s");
	}
}

JNIEXPORT void JNICALL test1(JNIEnv *env, jobject jthiz)
{
	LOGI("test1");
	pthread_t recvMirrorDataThreadID=-1;
	pthread_create(&recvMirrorDataThreadID, NULL, test_thread,NULL);
	return ;
}

static const char *classPath = "com/jni/test/JniTest1";
JNINativeMethod methods[] = {
		{"test1","()V",(void*)test1}
};

jint JNI_OnLoad(JavaVM *vm, void *reserv)
{
	JNIEnv *env;
	if(vm->GetEnv((void**)&env,JNI_VERSION_1_4)!=JNI_OK){
		return -1;
	}
	jclass jthiz = env->FindClass(classPath);
	if(env->RegisterNatives(jthiz,methods,sizeof(methods)/sizeof(methods[0]))<0){
		return -1;
	}
	return JNI_VERSION_1_4;

}
