#ifndef __MbUtils_h__
#define __MbUtils_h__

#include <cmath>

namespace math {

	const float pi = 3.14159;

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

	inline float radian2Angle(float radian) {
		return radian * 180.f / pi;
	}

    inline float angle2Radian (float angle) {
        return angle * pi / 180.0;
    }
    
    inline float normalizeAngle(float angle) {
        while (angle < 0) {
            angle += 360;
        }
        
        while (360 <= angle) {
            angle -= 360;
        }
        return angle;
    }
    
    inline float power(float x, int n) {
        return powf(x, n);
    }
    
    template <int n>
    inline int power(int x) {
        return x * power<n - 1>(x);
    }
    
    template <>
    inline int power<1>(int x) {
        return x;
    }
    
    template <int n>
    inline int power(float x) {
        return x * power<n - 1>(x);
    }
    
    template <>
    inline int power<1>(float x) {
        return x;
    }
    
    template <int n>
    inline int log(int x) {
        if (x >= n) {
            return 1 + log<n>(x / n);
        }
        return 0;
    }
}

#endif