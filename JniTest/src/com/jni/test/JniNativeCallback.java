package com.jni.test;

import android.util.Log;

public class JniNativeCallback {
	private static final String TAG = "JniNativeCallback";
	static {
		System.loadLibrary("JniNativeCallback");
	}
	
	public native void nativeInit();
	public native void nativeThreadStart();
	public native void nativeThreadStop();
	
	public void nativeCallback(byte[] buf,int lenth){
		Log.i(TAG, "lenth="+lenth);
		Log.i(TAG, "buf lenth="+buf.length);
		for(int i=0; i<lenth; i++)
		{
			Log.i(TAG, i+" : "+buf[i]);
		}
	}
}
