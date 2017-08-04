#include <android/log.h>
#include <stdio.h>
#include <jni.h>

#define TAG "hzz"
#define LOG_INFO(tag,...) __android_log_print(ANDROID_LOG_INFO,tag,__VA_ARGS__)

JNIEXPORT void JNICALL testForVoid(JNIEnv *env, jobject jthiz)
{
	LOG_INFO(TAG,"testForVoid");
}

JNIEXPORT jstring JNICALL testForString(JNIEnv *env, jobject jthiz, jstring s)
{
	 LOG_INFO(TAG,"testForString");
	 const char *str;
	 str = env->GetStringUTFChars(s, JNI_FALSE);
	 LOG_INFO(TAG,"str=%s",str);
	 char *tmpstr = "return string succeeded";
	 return env->NewStringUTF(tmpstr);

}


static const char* className = "com/jni/test/JniTest";

JNIEXPORT void JNICALL testForReflect(JNIEnv *env, jobject jthiz)
{
	LOG_INFO(TAG,"testForReflect");
	char *tmpstr = "Reflect succeeded";
	jstring s = env->NewStringUTF(tmpstr);
	//��ȡ�ص������Ķ��������ַ�ʽ��һ��ͨ����������object��һ����ͨ����������
//	jclass cn = env->FindClass(className);
	jclass cn = env->GetObjectClass(jthiz);
	//��ͨ����ȡ���Ķ��󣬵���GetMethodID����ȡ��Ӧ�ķ����������Ե���etFieldID����ȡ�ö��������
	jmethodID mId = env->GetMethodID(cn,"testForHello","(Ljava/lang/String;)V");
	env->CallVoidMethod(jthiz,mId,s);
}

static JNINativeMethod methods[] = {
		{"testForVoid", "()V", (void*)testForVoid},
		{"testForString", "(Ljava/lang/String;)Ljava/lang/String;", (void*)testForString},
		{"testForReflect", "()V", (void*)testForReflect}
};

jint JNI_OnLoad(JavaVM *VM, void *reserv)
{
	LOG_INFO(TAG,"JNI_OnLoad");
	JNIEnv *env;
	jclass jthiz;
	if(VM->GetEnv((void**)&env,JNI_VERSION_1_4)!=JNI_OK)
	{
		LOG_INFO(TAG,"get env fail");
		return -1;
	}
	jthiz = env->FindClass(className);
	if(env->RegisterNatives(jthiz,methods,sizeof(methods)/sizeof(methods[0]))<0){
		LOG_INFO(TAG,"RegistNatives fail");
		return -1;
	}
	LOG_INFO(TAG,"JNI_VERSION_1_4");
	return JNI_VERSION_1_4;
}
