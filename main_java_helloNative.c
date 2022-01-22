#include "main_java_helloNative.h"
//#include <iostream>
#include <stdio.h>
#include "opencvtest.h"

#define _CRT_SECURE_NO_WARNINGS

//extern "C"
JNIEXPORT void JNICALL Java_main_java_helloNative_hello (JNIEnv *env, jclass cl){
	//cout << "hello from c language program!" << endl;
	printf("hello from c language program!\n");
}

JNIEXPORT jint JNICALL Java_main_java_helloNative_printfnum(JNIEnv* env, jclass cl, jint width, jint precision, jdouble x) {
	char fmt[30];
	jint ret;
	sprintf(fmt, "%%%d.%df", width, precision);
	ret = printf(fmt, x);
	fflush(stdout);
	return ret;
}

JNIEXPORT jstring JNICALL Java_main_java_helloNative_arraytest(JNIEnv* env, jclass cl, jstring filename, jint filenamelength) {
	const char* realpath = (char*)(*env)->GetStringUTFChars(env, filename, NULL);
	char* resulename = function(realpath, filenamelength);
	jstring ret;
	ret = (*env)->NewStringUTF(env,resulename);
	(*env)->ReleaseStringUTFChars(env, filename, realpath);
	return ret;
	
	/*jsize length = (*env)->GetArrayLength(env, inputArray);
	jbyteArray jbyte_arr = (*env)->NewIntArray(env, length);                  //创建一个指定大小的数组
	jbyte* elems = (*env)->GetByteArrayElements(env, inputArray, NULL);
	jint i = 0;
	for (; i < length; i++)
	{
		elems[i] = i * 2;
	}
	elems = function(inputArray, length);
	(*env)->ReleaseByteArrayElements(env, jbyte_arr, elems, 0);                  //同步

	return jbyte_arr;*/
}