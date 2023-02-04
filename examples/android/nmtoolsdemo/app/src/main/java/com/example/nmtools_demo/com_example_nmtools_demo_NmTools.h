/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_example_nmtools_demo_NmTools */

#ifndef _Included_com_example_nmtools_demo_NmTools
#define _Included_com_example_nmtools_demo_NmTools
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    to_string
 * Signature: ([I[I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_nmtools_1demo_NmTools_to_1string___3I_3I
  (JNIEnv *, jclass, jintArray, jintArray);

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    to_string
 * Signature: ([F[I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_nmtools_1demo_NmTools_to_1string___3F_3I
  (JNIEnv *, jclass, jfloatArray, jintArray);

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    arange
 * Signature: (III)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_arange
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    random
 * Signature: (FF[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_random
  (JNIEnv *, jclass, jfloat, jfloat, jintArray);

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    sin
 * Signature: ([F[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_sin
  (JNIEnv *, jclass, jfloatArray, jintArray);

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    relu
 * Signature: ([F[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_relu
  (JNIEnv *, jclass, jfloatArray, jintArray);

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    sigmoid
 * Signature: ([F[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_sigmoid
  (JNIEnv *, jclass, jfloatArray, jintArray);

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    add
 * Signature: ([F[I[F[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_add
  (JNIEnv *, jclass, jfloatArray, jintArray, jfloatArray, jintArray);

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    subtract
 * Signature: ([F[I[F[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_subtract
  (JNIEnv *, jclass, jfloatArray, jintArray, jfloatArray, jintArray);

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    multiply
 * Signature: ([F[I[F[I)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_multiply
  (JNIEnv *, jclass, jfloatArray, jintArray, jfloatArray, jintArray);

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    reduce_add
 * Signature: ([F[I[IZ)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_reduce_1add
  (JNIEnv *, jclass, jfloatArray, jintArray, jintArray, jboolean);

/*
 * Class:     com_example_nmtools_demo_NmTools
 * Method:    reduce_multiply
 * Signature: ([F[I[IZ)Lcom/example/nmtools_demo/NmTools/NDArrayFloat;
 */
JNIEXPORT jobject JNICALL Java_com_example_nmtools_1demo_NmTools_reduce_1multiply
  (JNIEnv *, jclass, jfloatArray, jintArray, jintArray, jboolean);

#ifdef __cplusplus
}
#endif
#endif