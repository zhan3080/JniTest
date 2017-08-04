package com.jni.test;

public class JniTest {
	static{
		System.loadLibrary("JniTest");
	}
	public void testForHello(String s){
		System.out.println("hzz,"+s);
	}
	public native void testForVoid();
	
	public native String testForString(String s);
	
	public native void testForReflect();
}
