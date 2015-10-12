#pragma once
#define MATH_CUSTOM_MEMORY


#include <math.h>
#include "MathUtility.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "VectorT.h"
#include "Matrix4.h"
#include "Matrix3.h"
#include "Matrix2.h"
#include "Quaternion.h"

#include "DataTypedefs.h"
#include "MathError.h"
#include "MathMemoryManager.h"


#ifdef MATH_CUSTOM_MEMORY

namespace Math {
	
	inline void initMemory(U32 mat4, U32 Mat4Inc, U32 mat3, U32 mat3Inc) {
		MathMemoryManager::init(mat4, Mat4Inc, mat3, mat3Inc);
	}


}


#endif



//Linear interpolations:

namespace Math {

	//Linearly interpolates two numbers. t gets clamped, so it can be any F32 (well... contain your NaNs, still)
	inline F32 lerp(F32 v0, F32 v1, F32 t) {
		t = clamp(t, 0.f, 1.f);
		return (1 - t) * v0 + t * v1;
	}

	//Linearly interpolates components of Vector2
	inline Vector2 lerp(const Vector2& v1, const Vector2& v2, F32 t) {
		return Vector2(lerp(v1.x, v2.x, t), lerp(v1.y, v2.y, t));
	}

	//Linearly interpolates components of Vector3
	inline Vector3 lerp(const Vector3& v1, const Vector3& v2, F32 t) {
		return Vector3(lerp(v1.x, v2.x, t), lerp(v1.y, v2.y, t), lerp(v1.z, v2.z, t));
	}

	//Linearly interpolates components of Vector4
	inline Vector4 lerp(const Vector4& v1, const Vector4& v2, F32 t) {
		return Vector4(lerp(v1.x, v2.x, t), lerp(v1.y, v2.y, t), lerp(v1.z, v2.z, t), lerp(v1.w, v2.w, t));
	}

	//Linearly interpolates components of Vector
	template<U32 s>
	inline VectorT<s> lerp(const VectorT<s>& v1, const VectorT<s>& v2, F32 t) {
		VectorT<s> res;

		for (U32 i = 0; i < size; ++i)
			res.setElement(i, lerp(v1[i], v2[i], t));

		return res;
	}

	//Interpolates two Quaternions. There isn't a lot of speed variation, and lot cheaper than slerp. Finds the shortest path.
	inline Quaternion nlerp(const Quaternion& q1, const Quaternion& q2, F32 t) {
		F32 dot = q1.dot(q2);
		//Account for F32ing-point errors
		dot = clamp(dot, -1.f, 1.f);

		Quaternion q22 = q2;
		if (dot < 0.f) {
			q22 = -1 * q2;

		}

		return Quaternion(lerp(q1.x, q22.x, t), lerp(q1.y, q22.y, t), lerp(q1.z, q22.z, t), lerp(q1.w, q22.w, t)).normalized();


	}

	//Linearly interpolates components of Vector2 and normalizes the result
	inline Vector2 nlerp(const Vector2& v1, const Vector2& v2, F32 t) {
		return lerp(v1, v2, t).normalized();
	}

	//Linearly interpolates components of Vector3 and normalizes the result
	inline Vector3 nlerp(const Vector3& v1, const Vector3& v2, F32 t) {
		return lerp(v1, v2, t).normalized();
	}

	//Linearly interpolates components of Vector4 and normalizes the result
	inline Vector4 nlerp(const Vector4& v1, const Vector4& v2, F32 t) {
		return lerp(v1, v2, t).normalized();
	}

	//Linearly interpolates components of Vector and normalizes the result
	template<U32 size>
	inline VectorT<size> nlerp(const VectorT<size>& v1, const VectorT<size>& v2, F32 t) {
		return lerp(v1, v2, t).normalized();
	}


	//Spherical linear interpolation, q1 and q2 must be normalized. Finds the shortest path. Moves in constant speed. Heavier to compute than nlerp.
	inline Quaternion slerp(const Quaternion& q1, const Quaternion& q2, F32 t) {
		t = clamp(t, 0, 1);



		F32 dot = q1.dot(q2);

		Quaternion q22 = q2;

		//If dot is negative, invert q2 so interpolation will follow the shortest path
		if (dot < 0.f) {
			q22 = -1 * q2;

		}


		F32 angle = acosf(dot);

		F32 sina = sinf(angle);

		//Avoid dividing by 0, If they are pararell, just nlerp it
		if (sina == 0.f) {
			return nlerp(q1, q22, t);
		}


		F32 sinta = sinf(t * angle);
		F32 sinomta = sinf((1.f - t) * angle);

		Quaternion qq1 = (sinomta / sina) * q1;

		Quaternion qq2 = (sinta / sina) * q22;

		Quaternion res = qq1 + qq2;
		res.normalize();
		return res;

	}



	template<U32 size>
	inline F32 angle(const VectorT<size>& v1, const VectorT<size>& v2);
	
	inline F32 angle(const Vector2& v1, const Vector2& v2);
	inline F32 angle(const Vector3& v1, const Vector3& v2);
	inline F32 angle(const Vector4& v1, const Vector4& v2);

	//Spherical interpolation of two vectors
	inline Vector4 slerp(const Vector4& v1, const Vector4& v2, F32 t) {
		F32 angle = Math::angle(v1, v2);
		F32 sina = sinf(angle);

		if (sina == 0) {
			return lerp(v1, v2, t);
		}


		return (sinf((1 - t) * angle) / sina) * v1 + (sinf(t * angle) / sina) * v2;
	}

	//Spherical interpolation of two vectors
	inline Vector3 slerp(const Vector3& v1, const Vector3& v2, F32 t) {
		F32 angle = Math::angle(v1, v2);
		F32 sina = sinf(angle);

		if (sina == 0) {
			return lerp(v1, v2, t);
		}


		return (sinf((1 - t) * angle) / sina) * v1 + (sinf(t * angle) / sina) * v2;
	}

	//Spherical interpolation of two vectors
	inline Vector2 slerp(const Vector2& v1, const Vector2& v2, F32 t) {
		F32 angle = Math::angle(v1, v2);
		F32 sina = sinf(angle);

		if (sina == 0) {
			return lerp(v1, v2, t);
		}


		return (sinf((1 - t) * angle) / sina) * v1 + (sinf(t * angle) / sina) * v2;
	}


	//Spherical interpolation of two vectors
	template<U32 size>
	inline VectorT<size> slerp(const VectorT<size>& v1, const VectorT<size>& v2, F32 t) {
		F32 angle = Math::angle(v1, v2);
		F32 sina = sinf(angle);

		if (sina == 0) {
			return lerp(v1, v2, t);
		}


		return (sinf((1 - t) * angle) / sina) * v1 + (sinf(t * angle) / sina) * v2;
	}



}


//Vector stuff:

namespace Math {
	//Finds an angle(in radians), between two nonzero vectors
	template<U32 size>
	inline F32 angle(const VectorT<size>& v1, const VectorT<size>& v2) {
		if (v1.isZero() || v2.isZero()) {
			Math::mathError("ERROR: Tried to find an angle with zero vector");
			return 0.f;
		}
		F32 dot = v1.dot(v2);
		//Account for F32ing-point errors
		dot = clamp(dot, -1.f, 1.f);
		return acosf(dot / v1.lenght() / v2.lenght());

	}

	inline F32 angle(const Vector2& v1, const Vector2& v2) {
		if (v1.isZero() || v2.isZero()) {
			Math::mathError("ERROR: Tried to find an angle with zero vector");
			return 0.f;
		}
		F32 dot = v1.dot(v2);
		//Account for F32ing-point errors
		dot = clamp(dot, -1.f, 1.f);
		return acosf(dot / v1.lenght() / v2.lenght());
	}

	inline F32 angle(const Vector3& v1, const Vector3& v2) {
		if (v1.isZero() || v2.isZero()) {
			Math::mathError("ERROR: Tried to find an angle with zero vector");
			return 0.f;
		}
		F32 dot = v1.dot(v2);
		//Account for F32ing-point errors
		dot = clamp(dot, -1.f, 1.f);
		return acosf(dot / v1.lenght() / v2.lenght());
	}

	inline F32 angle(const Vector4& v1, const Vector4& v2) {
		if (v1.isZero() || v2.isZero()) {
			Math::mathError("ERROR: Tried to find an angle with zero vector");
			return 0.f;
		}
		F32 dot = v1.dot(v2);
		//Account for F32ing-point errors
		dot = clamp(dot, -1.f, 1.f);
		return acosf(dot / v1.lenght() / v2.lenght());
	}



	//Projects from to the line to. Both vectors need to be zero, but they do not need to be normalized
	inline Vector2 proj(const Vector2& from, const Vector2& to) {
		if (from.isZero() || to.isZero()) {
			Math::mathError("ERROR: Tried to calculate projection of Vector2 with zero vector(s)");
			return Vector2();
		}
		Vector2 u = to.normalized();
		return from.dot(u) * u;

	}

	//Projects from to the line to. Both vectors need to be zero, but they do not need to be normalized
	inline Vector3 proj(const Vector3& from, const Vector3& to) {
		if (from.isZero() || to.isZero()) {
			Math::mathError("ERROR: Tried to calculate projection of Vector3 with zero vector(s)");
			return Vector3();
		}
		Vector3 u = to.normalized();
		return from.dot(u) * u;

	}

	//Projects from to the line to. Both vectors need to be zero, but they do not need to be normalized
	inline Vector4 proj(const Vector4& from, const Vector4& to) {
		if (from.isZero() || to.isZero()) {
			Math::mathError("ERROR: Tried to calculate projection of Vector4 with zero vector(s)");
			return Vector4();
		}
		Vector4 u = to.normalized();
		return from.dot(u) * u;

	}

	//Projects from to the line to. Both vectors need to be zero, but they do not need to be normalized
	template<U32 size>
	inline VectorT<size> proj(const VectorT<size>& from, const VectorT<size>& to) {
		if (from.isZero() || to.isZero()) {
			Math::mathError("ERROR: Tried to calculate projection of generic Vector with zero vector(s)");
			return VectorT<size>();
		}

		VectorT<size> u = to.normalized();
		return from.dot(u) * u;
	}

	//Makes v2 orthogonal to v1. Returns v2 that is rotated to be orthogonal to v1.
	inline Vector2 orthogonalize(const Vector2& v1, const Vector2& v2) {
		return v2 - proj(v2, v1);
	}

	//Makes v2 orthogonal to v1. Returns v2 that is rotated to be orthogonal to v1.
	inline Vector3 orthogonalize(const Vector3& v1, const Vector3& v2) {
		return v2 - proj(v2, v1);
	}

	//Makes v2 orthogonal to v1. Returns v2 that is rotated to be orthogonal to v1.
	inline Vector4 orthogonalize(const Vector4& v1, const Vector4& v2) {
		return v2 - proj(v2, v1);
	}

	//Makes v2 orthogonal to v1. Returns v2 that is rotated to be orthogonal to v1.
	template<U32 size>
	inline VectorT<size> orthogonalize(const VectorT<size>& v1, const VectorT<size>& v2) {
		return v2 - proj(v2, v1);
	}


	//Makes v2 orthogonal to v1. Returns normalized v2 that is rotated to be orthogonal to v1.
	inline Vector2 orthonormalize(const Vector2& v1, const Vector2& v2) {
		return (v2 - proj(v2, v1)).normalized();
	}

	//Makes v2 orthogonal to v1. Returns normalized v2 that is rotated to be orthogonal to v1.
	inline Vector3 orthonormalize(const Vector3& v1, const Vector3& v2) {
		return (v2 - proj(v2, v1)).normalized();
	}

	//Makes v2 orthogonal to v1. Returns normalized v2 that is rotated to be orthogonal to v1.
	inline Vector4 orthonormalize(const Vector4& v1, const Vector4& v2) {
		return (v2 - proj(v2, v1)).normalized();
	}

	//Makes v2 orthogonal to v1. Returns normalized v2 that is rotated to be orthogonal to v1.
	template<U32 size>
	inline VectorT<size> orthonormalize(const VectorT<size>& v1, const VectorT<size>& v2) {
		return (v2 - proj(v2, v1)).normalized();
	}

}


//Matrices, rotations, that sort of stuff:

namespace Math {


	//Returns a Matrix4 representing rotation of angle around axis
	inline Matrix4 rotationMatrix(const Vector3& axis, F32 angle) {
		Matrix4 m;
		m.rotate(axis, angle);
		return m;
	}

	//Returns a Matrix4 representing translation
	inline Matrix4 translationMatrix(const Vector3& translation) {
		Matrix4 m;
		m.translate(translation);
		return m;
	}

	//Returns a Matrix4 representing scaling
	inline Matrix4 scaleMatrix(F32 f) {
		Matrix4 m;
		m.scale(f);
		return m;
	}

	//Returns a matrix representing perspective projection
	//Parameters: Field of view, aspect ratio(width / height), near clipping plane, far clipping plane
	inline Matrix4 perspectiveMatrix(F32 fov, F32 as, F32 zNear, F32 zFar) {
		Matrix4 m;



		m[0][0] = 1.f / (as * tan(fov / 2.f)); m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
		m[1][0] = 0; m[1][1] = 1.f / tan(fov / 2.f); m[1][2] = 0; m[1][3] = 0;
		m[2][0] = 0; m[2][1] = 0; m[2][2] = (-zNear - zFar) / (zNear - zFar); m[2][3] = (2.f * zFar * zNear) / (zNear - zFar);
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 1; m[3][3] = 0;

		return m;

	}


	//Returns a matrix representing orthographic projection
	inline Matrix4 orthographicMatrix(F32 left, F32 right, F32 top, F32 bottom, F32 n, F32 f) {
		F32 width = right - left;
		F32 height = top - bottom;
		F32 depth = f - n;

		Matrix4 m;



		m[0][0] = 2.f / width; m[0][1] = 0; m[0][2] = 0; m[0][3] = -(right + left) / width;
		m[1][0] = 0; m[1][1] = 2.f / height; m[1][2] = 0; m[1][3] = -(top + bottom) / height;
		m[2][0] = 0; m[2][1] = 0; m[2][2] = -2.f / depth; m[2][3] = -(f + n) / depth;
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;




		return m;


	}




	//Returns a Quaternion representing a rotation to look at some direction
	inline Quaternion
		lookAt(const Vector3& f, const Vector3& u) {

		F32 fDotU = f.dot(u);
		if ((!(fDotU < 0.001f && fDotU > -0.001f)) || f.isZero() || u.isZero()) {
			Math::mathError("ERROR: Called lookAt with f and u being not perpendicular non-zero vectors. Dot product: " + std::to_string(fDotU));
			return Quaternion();
		}

		Quaternion look, rot;

		Vector3 forw = f.normalized(), up = u.normalized();



		F32 dot = forw.dot(Vector3::WORLD_FORW);

		//If they are not aligned, rotate them to align.
		if (dot < 0.9999f) {

			look.axisAngle(Vector3::WORLD_FORW.cross(forw), acosf(dot));



		}

		dot = up.dot(Vector3::WORLD_UP);

		if (dot < 0.9999f) {

			rot.axisAngle(Vector3::WORLD_UP.cross(up), acosf(dot));



		}





		return rot * look;

	}



	//Namespace that has functions for working with homogeneous 2D coordinates
	namespace homogeneous2D {


		//Returns Matrix3 that rotates 2D homogeneous vectors by angle
		inline Matrix3 rotate(F32 angle) {
			Matrix3 res;

			res.setElement(0, 0, cosf(angle));
			res.setElement(0, 1, -sinf(angle));
			res.setElement(1, 0, sinf(angle));
			res.setElement(1, 1, cosf(angle));

			return res;
		}


		//Returns Matrix3 that translates 2D homogeneous vectors
		inline Matrix3 translate(Vector2 translation) {
			Matrix3 res;
			res.setElement(0, 2, translation.x);
			res.setElement(1, 2, translation.y);

			return res;

		}

		//Returns Matrix3 that scales 2D homogeneous vectors
		inline Matrix3 scale(F32 f) {
			Matrix3 res;
			res.setElement(0, 0, f);
			res.setElement(1, 1, f);

			return res;

		}








	}



}
