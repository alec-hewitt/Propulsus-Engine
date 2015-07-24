//p3Structure.cpp

#include <iostream>
#include "p3Structure.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

p3Structure::p3Structure(){
	
	//zero all properties
	mass = 1;
	rotationalInertia = 1;
	centerOfMass.set(0, 0, 0);
	width = 1;
	height = 1;
	radius = 1;
	length = 1;

}

void p3Structure::setSphere(float radius){
	this->radius = radius;
	this->rotationalInertia = (0.4 * mass * radius);
}

void p3Structure::setCube(float length){
	this->width = length;
	this->height = length;
	this->length = length;
	this->radius = length * 1.5; //this is not exact by any means. 1:54 AM
	this->rotationalInertia = ((mass * (length * length)) / 6);
}

void p3Structure::setStructure(char resource){
	//compute all structural properties

	//SET A RADIUS
	this->radius = 1;
}