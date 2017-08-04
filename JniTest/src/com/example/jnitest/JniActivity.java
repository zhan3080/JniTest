package com.example.jnitest;

import com.jni.test.JniNativeCallback;
import com.jni.test.JniTest;
import com.jni.test.JniTest1;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class JniActivity extends Activity {
	private final static String TAG = "JniActivity";
	private Button button1;
	private Button button2;
	private Button button3;
//	private JniTest1 mJtest1;
	private JniNativeCallback mJniNativeCallback;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_jni);
//		mJtest1 = new JniTest1();
		mJniNativeCallback = new JniNativeCallback();
		button1 = (Button) this.findViewById(R.id.button1);
		button2 = (Button) findViewById(R.id.button2);
		button3 = (Button) findViewById(R.id.button3);

		button1.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
//				mJtest1.test1();
				mJniNativeCallback.nativeInit();
			}
		});

		button2.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				mJniNativeCallback.nativeThreadStart();
			}
		});

		button3.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				mJniNativeCallback.nativeThreadStop();
			}
		});
	}
}
