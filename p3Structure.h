//p3Structure.h

/* the structure object will accept a local link to a 3d design file 
from solidworks and calculate/analyze its properties for use
*/
#ifndef P3STRUCTURE_H
#define P3STRUCTURE_H

#include "p3Vector4.h"

class p3Structure{
public:

	float mass;
	float rotationalInertia;
	Vector4 centerOfMass;
	float width;
	float height;
	float length;
	float radius;

	//constructor
	p3Structure();
	
	//default non-external structures setup

	void setSphere(float radius);

	void setCube(float length);

	//external referenced structure setup
	void setStructure(char resource);
	
};

#endif //P3STRUCTURE_H