#include <stdio.h>
#include <iostream>

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <math.h>

#include <stdarg.h>

#include <Kinect.h>


#include "yal.h"

#ifndef __KINECT_TRACK_IR_UTILS__
#define __KINECT_TRACK_IR_UTILS__
void handleError(HRESULT hr, int critical, char* msg, ...);

void getFaceRotationInDegrees(const Vector4* pQuaternion, int* pYaw, int* pPitch, int* pRoll);

// Safe release for interfaces
template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}

#endif