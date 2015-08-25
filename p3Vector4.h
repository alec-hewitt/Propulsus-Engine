#ifndef P3VECTOR4_H
#define P3VECTOR4_H

class Vector4{
	public:
	
		//x, y, z components
		float x, y, z;

		//default constructor
		Vector4();

		//constructor
		Vector4(float x, float y, float z);

		//destructor
		~Vector4();
		
		//operators
		//adds the x, y, z, and w components of another Vector3 to this
		Vector4 operator + (const Vector4 &v4Other);
		//subtracts the x, y, z, and w components of another Vector3 from this
		Vector4 operator - (const Vector4 &v4Other);
		//sets the x, y, z, and w components of this to those of another Vector3
		Vector4 operator = (const Vector4 &v4other);
		//multiplies the x, y, z, and w components of this Vector3 by a scalar
		Vector4 operator * (int v4Scalar);
		//multiplies the x, y, z, and w components of this Vector3 by a scalar
		Vector4 operator * (const float v4Scalar);
		//multiplies the x, y, z, and w components of this Vector3 by a scalar
		Vector4 operator * (const double v4Scalar);
		//Vector4 cross product
		Vector4 operator * (const Vector4 &v4Other);
		///divide by scalar
		Vector4 operator / (const float v4Scalar);

		//returns magnitude of 3D vector
		float getMagnitude(Vector4 vector);

		//given reference vector direction and scalar magnitude, returns scaled vector
		Vector4 scaledVector(float magnitude, Vector4 direction);

		//converts from polar co-ordinate system to Cartesian
		//Vector4 polarToCartesian(float magnitude, float direction);

		//set the vector4's  x, y, z, and w components
		void set(float x, float y, float z);

		//resets all Vector4 quantities to 0
		void reset();
};

#endif
