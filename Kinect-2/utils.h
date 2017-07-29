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

void handleError(HRESULT hr, int critical, char* msg, ...);

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