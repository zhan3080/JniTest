#include <jni.h>
#include <android/log.h>
#include <pthread.h>
#include <unistd.h>

#define TAG "JniNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
//gJavaVM���Դ�JNI_OnLoad�︳ֵ��Ҳ����ͨ��native_init���env��ȡ
//gJavaObj������JNI_OnLoad�︳ֵ����java��������
JavaVM *gJavaVM;
jobject gJavaObj;
int volatile gIsThreadStop = 0;
static const char *classPath = "com/jni/test/JniNativeCallback";

static void* native_thread_exec(void *arg)
{
	LOGI("nativeThreadExec");
	JNIEnv *env;
	//get env From gJavaVm
	gJavaVM->AttachCurrentThread(&env,NULL);
	//get Java class by classPath
	//���������ȡ����thiz�󣬲�������ʹ�á�һ��Ҫ�ӳ�ʼ����ȡ����object����ΪFineClass��ȡ�����࣬GetObjectClass��ȡ���ǵ�ǰ����
	//jclass thiz = env->FindClass(classPath);
	jclass thiz = env->GetObjectClass(gJavaObj);


	unsigned char buffer[100];
	int i=0;
	for(i=0;i<100;i++)
	{
		buffer[i] = i;
	}

//	jbyte ba[100];
//	for(i=0;i<100;i++)
//	{
//		ba[i] = buffer[i];
//	}
//	jcharArray array = env->NewCharArray(len);
//	jchar *pArray ;
	jbyteArray array = env->NewByteArray(100);
	jbyte ba[100];
		for(i=0;i<100;i++)
		{
			ba[i] = buffer[i];
		}
	env->SetByteArrayRegion(array,0,100,ba);
	//get Java method from thiz
	jmethodID nativeCallback = env->GetMethodID(thiz,"nativeCallback","([BI)V");
	int count = 0;
	env->CallVoidMethod(gJavaObj,nativeCallback,array,100);
	while(!gIsThreadStop)
	{
		sleep(2);
		//env->CallVoidMethod(thiz,nativeCallback,count++);
	}
	gJavaVM->DetachCurrentThread();
	LOGI("thread stoped");
}


JNIEXPORT void JNICALL native_init(JNIEnv *env,jobject thiz)
{
	LOGI("native_init");
	gIsThreadStop = 0;
//	env->GetJavaVM(&gJavaVM);
	gJavaObj = env->NewGlobalRef(thiz);
}

JNIEXPORT void JNICALL native_thread_start(JNIEnv *env,jobject jthiz)
{
	LOGI("native_thread_start");
	gIsThreadStop = 0;

	pthread_t id;
	if(pthread_create(&id,NULL,native_thread_exec,NULL)!=0)
	{
		LOGI("native thread create fail");
		return;
	}

	LOGI("native thread creat success");
}

JNIEXPORT void JNICALL native_thread_stop(JNIEnv *env,jobject jthiz)
{
	gIsThreadStop = 1;
	LOGI("native_thread_stop");
}


static JNINativeMethod methods[] = {
		{"nativeInit","()V",(void*)native_init},
		{"nativeThreadStart","()V",(void*)native_thread_start},
		{"nativeThreadStop","()V",(void*)native_thread_stop}
};

jint JNI_OnLoad(JavaVM *vm, void *reserve)
{
	LOGI("JNI_OnLoad");
	JNIEnv *env;
	if(vm->GetEnv((void**)&env,JNI_VERSION_1_4)!=JNI_OK)
	{
		return -1;
	}
	//������ֵҲ���ԣ����vm���ǵ�ǰ�������������
	//gJavaVM = vm;

	jclass jthiz = env->FindClass(classPath);
	//error��������ȡ����gJavaObj����ʹ��
	//gJavaObj = env->NewGlobalRef(jthiz);
	if(env->RegisterNatives(jthiz,methods,sizeof(methods)/sizeof(methods[0]))<0)
	{
		return -1;
	}

	return JNI_VERSION_1_4;

}
