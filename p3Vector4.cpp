#include "p3Vector4.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

//default constructor
Vector4::Vector4(){
	
}

//constructor
Vector4::Vector4(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

//destructor
Vector4::~Vector4(){

}

//Vector4 + Vector4
Vector4 Vector4::operator + (const Vector4 &v3Other){
	//add Vector3 param to existing Vector3 attributes (x,y,z)
	Vector4 sum(0, 0, 0);
	sum.x = this->x + v3Other.x;
	sum.y = this->y + v3Other.y;
	sum.z = this->z + v3Other.z;
	return sum;
}

Vector4 Vector4::operator - (const Vector4 &v3Other){
	//subtract Vector3 param from existing Vector3 attributes (x,y,z)
	Vector4 difference(0, 0, 0);
	difference.x = this->x - v3Other.x;
	difference.y = this->y - v3Other.y;
	difference.z = this->z - v3Other.z;
	return difference;
}

Vector4 Vector4::operator = (const Vector4 &v3Other){
	//set Vector3 existing Vector3 attributes to those of param Vector3 (x,y,z)
	Vector4 equal(0, 0, 0);
	x = v3Other.x;
	y = v3Other.y;
	z = v3Other.z;
	return equal;
}

Vector4 Vector4::operator * (const float v3Scalar){
	//multiply Vector3 quantities by respective param values
	Vector4 scalarProduct(0, 0, 0);
	scalarProduct.x = this->x * v3Scalar;
	scalarProduct.y = this->y * v3Scalar;
	scalarProduct.z = this->z * v3Scalar;
	return scalarProduct;
}

Vector4 Vector4::operator * (const Vector4 &v3Other){
	//caluculate cross product
	Vector4 crossProduct(0, 0, 0);
	crossProduct.x = (this->y * v3Other.z) - (this->z * v3Other.y);
	crossProduct.y = (this->z * v3Other.x) - (this->x * v3Other.z);
	crossProduct.z = (this->x * v3Other.y) - (this->y * v3Other.x);
	return crossProduct;
}

Vector4 Vector4::operator / (const float v4Scalar){
	//divide Vector3 quantities by respective param values
	Vector4 scalarQuotient(0, 0, 0);
	scalarQuotient.x = this->x / v4Scalar;
	scalarQuotient.y = this->y / v4Scalar;
	scalarQuotient.z = this->z / v4Scalar;
	return scalarQuotient;
}

float getMagnitude(Vector4 vector){
	float magnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	return magnitude;
}

Vector4 scaledVector(float magnitude, Vector4 direction){
	//retrieve unit vector
	Vector4 unit = direction / getMagnitude(direction);
	return (unit * magnitude);
}

/*
Vector4 Vector4::polarToCartesian(float magnitude, float direction){
	float newX = magnitude * (direction.x / (sqrt((direction.x * direction.x) + (direction.y * direction.y))));
	float newY = magnitude * (direction.y / (sqrt((direction.x * direction.x) + (direction.y * direction.y))));
	float newZ = magnitude * (direction.z / (sqrt((direction.z * direction.z) + (direction.y * direction.y))));

	Vector4 newVector;
	newVector.set(newX, newY, newZ);
	return newVector;
}
*/

void Vector4::set(float newX, float newY, float newZ){
	//set Vector3 quantities to respective param values
	this->x = newX;
	this->y = newY;
	this->z = newZ;
}

void Vector4::reset(){
	//set all Vector3 quantities to 0
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
