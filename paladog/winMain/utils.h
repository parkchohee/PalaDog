#pragma once

#include <cmath>

#define PI 3.141592654f // PI == 180도
#define PI2 (PI * 2)	// PI2 == 360도

#define PI8		float(PI / 8.f)
#define PI16	float(PI / 16.f)
#define PI32	float(PI / 32.f)
#define PI64	float(PI / 64.f)
#define PI128	float(PI / 128.f)

#define RAD_TO_DEG			(180.f / PI)
#define DEG_TO_RAD			(PI / 180.f)
#define FLOAT_EPSILON		0.0001f //이 정도 차이가 나면 같다고 봐도 무방하겠다 라는, 허용 오차범위
#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILON)
#define FLOAT_EQUAL(f1, f2) (fabs(f1 - f2) <= FLOAT_EPSILON)

namespace MY_UTIL
{
	//거리 가져오는 함수
	float getDistance( float startX, float startY, float endX, float endY );

	//앵글 가져오는 함수
	float getAngle( float startX, float startY, float endX, float endY );
}