package com.jni.test;

public class JniTest1 {
	static {
		System.loadLibrary("JniTest1");
	}
	public native void test1();
}
