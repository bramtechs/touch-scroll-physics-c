#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include "touch_scroll_physics.h"
#include "com_doomhowl_touchscrollphysics_TouchScroller.h"

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeCreate
 * Signature: (IFFFFZFFLjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeCreate
  (JNIEnv *env, jobject obj, jint totalCells, jfloat viewSize, jfloat cellSize, 
   jfloat gutterSize, jboolean dipToClosestCell, jfloat dipMaxSpeed, jfloat dipSnappiness)
{
    TouchScroller* scroller = (TouchScroller*)malloc(sizeof(TouchScroller));
    if (scroller == NULL) {
        return 0; // Memory allocation failed
    }
    
    // Initialize with zeros
    memset(scroller, 0, sizeof(TouchScroller));
    
    // Set configuration parameters
    scroller->totalCells = totalCells;
    scroller->viewSize = viewSize;
    scroller->cellSize = cellSize;
    scroller->gutterSize = gutterSize;
    scroller->dipToClosestCell = dipToClosestCell;
    scroller->dipMaxSpeed = dipMaxSpeed;
    scroller->dipSnappiness = dipSnappiness;
    
    return (jlong)scroller;
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeUpdate
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeUpdate
  (JNIEnv *env, jobject obj, jlong handle, jfloat dtInMillis)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        TouchScroller_Update(scroller, dtInMillis);
    }
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeStart
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeStart
  (JNIEnv *env, jobject obj, jlong handle, jfloat offset)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        TouchScroller_Start(scroller, offset);
    }
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeMove
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeMove
  (JNIEnv *env, jobject obj, jlong handle, jfloat offset)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        TouchScroller_Move(scroller, offset);
    }
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeEnd
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeEnd
  (JNIEnv *env, jobject obj, jlong handle, jfloat offset)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        TouchScroller_End(scroller, offset);
    }
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeIsVisible
 * Signature: (JFF)Z
 */
JNIEXPORT jboolean JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeIsVisible
  (JNIEnv *env, jobject obj, jlong handle, jfloat startOffset, jfloat endOffset)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        return TouchScroller_IsVisible(scroller, startOffset, endOffset);
    }
    return JNI_FALSE;
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeGetOffset
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeGetOffset
  (JNIEnv *env, jobject obj, jlong handle)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        return TouchScroller_GetOffset(scroller);
    }
    return 0.0f;
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeDispose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeDispose
  (JNIEnv *env, jobject obj, jlong handle)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        free(scroller);
    }
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeSetTotalCells
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeSetTotalCells
  (JNIEnv *env, jobject obj, jlong handle, jint totalCells)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        scroller->totalCells = totalCells;
    }
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeSetViewSize
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeSetViewSize
  (JNIEnv *env, jobject obj, jlong handle, jfloat viewSize)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        scroller->viewSize = viewSize;
    }
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeSetCellSize
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeSetCellSize
  (JNIEnv *env, jobject obj, jlong handle, jfloat cellSize)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        scroller->cellSize = cellSize;
    }
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeSetGutterSize
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeSetGutterSize
  (JNIEnv *env, jobject obj, jlong handle, jfloat gutterSize)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        scroller->gutterSize = gutterSize;
    }
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeSetDipToClosestCell
 * Signature: (JZ)V
 */
JNIEXPORT void JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeSetDipToClosestCell
  (JNIEnv *env, jobject obj, jlong handle, jboolean dipToClosestCell)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        scroller->dipToClosestCell = dipToClosestCell;
    }
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeSetDipMaxSpeed
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeSetDipMaxSpeed
  (JNIEnv *env, jobject obj, jlong handle, jfloat dipMaxSpeed)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        scroller->dipMaxSpeed = dipMaxSpeed;
    }
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeSetDipSnappiness
 * Signature: (JF)V
 */
JNIEXPORT void JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeSetDipSnappiness
  (JNIEnv *env, jobject obj, jlong handle, jfloat dipSnappiness)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        scroller->dipSnappiness = dipSnappiness;
    }
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeGetTotalCells
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeGetTotalCells
  (JNIEnv *env, jobject obj, jlong handle)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        return scroller->totalCells;
    }
    return 0;
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeGetViewSize
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeGetViewSize
  (JNIEnv *env, jobject obj, jlong handle)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        return scroller->viewSize;
    }
    return 0.0f;
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeGetCellSize
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeGetCellSize
  (JNIEnv *env, jobject obj, jlong handle)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        return scroller->cellSize;
    }
    return 0.0f;
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeGetGutterSize
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeGetGutterSize
  (JNIEnv *env, jobject obj, jlong handle)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        return scroller->gutterSize;
    }
    return 0.0f;
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeGetDipToClosestCell
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeGetDipToClosestCell
  (JNIEnv *env, jobject obj, jlong handle)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        return scroller->dipToClosestCell;
    }
    return JNI_FALSE;
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeGetDipMaxSpeed
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeGetDipMaxSpeed
  (JNIEnv *env, jobject obj, jlong handle)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        return scroller->dipMaxSpeed;
    }
    return 0.0f;
}

/*
 * Class:     com_doomhowl_touchscrollphysics_TouchScroller
 * Method:    nativeGetDipSnappiness
 * Signature: (J)F
 */
JNIEXPORT jfloat JNICALL Java_com_doomhowl_touchscrollphysics_TouchScroller_nativeGetDipSnappiness
  (JNIEnv *env, jobject obj, jlong handle)
{
    TouchScroller* scroller = (TouchScroller*)handle;
    if (scroller != NULL) {
        return scroller->dipSnappiness;
    }
    return 0.0f;
} 