#include "utils.h"

void awaitInput()
{
	int a;
	std::cin >> a;
}

void handleError(HRESULT hr, int critical, char* msg, ...)
{
	va_list arg;

	if (FAILED(hr))
	{
		va_start(arg, msg);
		vfprintf(stderr, msg, arg);
		va_end(arg);
		if (critical)
		{
			awaitInput();
			exit(-critical);
		}
	}
}



void getFaceRotationInDegrees(const Vector4* pQuaternion, int* pYaw, int* pPitch, int* pRoll)
{
	double x = pQuaternion->x;
	double y = pQuaternion->y;
	double z = pQuaternion->z;
	double w = pQuaternion->w;

	// convert face rotation quaternion to Euler angles in degrees		
	double dPitch, dYaw, dRoll;
	dPitch = atan2(2 * (y * z + w * x), w * w - x * x - y * y + z * z) / M_PI * 180.0;
	dYaw = asin(2 * (w * y - x * z)) / M_PI * 180.0;
	dRoll = atan2(2 * (x * y + w * z), w * w + x * x - y * y - z * z) / M_PI * 180.0;

	// clamp rotation values in degrees to a specified range of values to control the refresh rate
	double increment = 1.0;
	*pPitch = static_cast<int>(floor((dPitch + increment / 2.0 * (dPitch > 0 ? 1.0 : -1.0)) / increment) * increment);
	*pYaw = static_cast<int>(floor((dYaw + increment / 2.0 * (dYaw > 0 ? 1.0 : -1.0)) / increment) * increment);
	*pRoll = static_cast<int>(floor((dRoll + increment / 2.0 * (dRoll > 0 ? 1.0 : -1.0)) / increment) * increment);
}