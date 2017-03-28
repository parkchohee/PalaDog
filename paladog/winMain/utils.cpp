#include "stdafx.h"
#include "utils.h"

namespace MY_UTIL
{
	float getDistance( float startX, float startY, float endX, float endY )
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf( x*x + y*y );
	}

	float getAngle( float startX, float startY, float endX, float endY )
	{
		float x = endX - startX;
		float y = endY - startY;

		float dist = sqrtf( x*x + y*y );
		float angle = acosf( x / dist );

		if ( y > 0 ) angle = PI2 - angle;

		return angle;
	}
}

