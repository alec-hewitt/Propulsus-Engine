/*
 * p3Burn.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: alec
 */

#define _USE_MATH_DEFINES
#include <math.h>
#include "p3Burn.h"

p3Burn::p3Burn() {
	// TODO Auto-generated constructor stub

}

p3Burn::~p3Burn() {
	// TODO Auto-generated destructor stub
}

void p3Burn::execute(p3TimeStep step, Body* b){

	//check timer and body data
	//perform thrust at burn location
	//subtract dt from time remaining

	if(tRemaining > 0){
		tRemaining -= step.dt; //correct
	}

	//calculate force in vector
	//magnitude of direction vector
	float magnitude = sqrt(pow(b->linearVelocity.x, 2) + pow(b->linearVelocity.y, 2) + pow(b->linearVelocity.z, 2));
	//convert velocity by unit vector
	Vector4 unit = b->linearVelocity / magnitude;
	//scale by given force magnitude
	Vector4 force = (unit * thrust);

	b->applyForce(force);

}
