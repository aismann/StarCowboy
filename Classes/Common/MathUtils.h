#ifndef __MbUtils_h__
#define __MbUtils_h__

#include <cmath>

namespace math {

	const double pi = 3.14159;

	template<typename T>
	inline bool is_equal(T a, T b) {
		return !(a != b);
	}

	template<>
	inline bool is_equal<float>(float a, float b) {
		if (fabs(a-b) < 1E-12) {
			return true;
		}
		return false;
	}

	template<>
	inline bool is_equal<double>(double a, double b) {
		if (fabs(a-b) < 1E-12) {
			return true;
		}
		return false;
	}

	inline double radian2Angle(double radian) {
		return radian * 180.0 / pi;
	}

    inline double angle2Radian (double angle) {
        return angle * pi / 180.0;
    }
    
    inline double normalizeAngle(double angle) {
        while (angle < 0) {
            angle += 360;
        }
        
        while (360 <= angle) {
            angle -= 360;
        }
        return angle;
    }
}

#endif