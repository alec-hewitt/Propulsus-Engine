/*
 * p3Burn.cpp
 *
 *  Created on: Aug 4, 2015
 *      Author: alec
 */

#define _USE_MATH_DEFINES
#include <math.h>
#include "p3Burn.h"
#include <iostream>

using namespace std;

p3Burn::p3Burn() {
	// TODO Auto-generated constructor stub

}

p3Burn::~p3Burn() {
	// TODO Auto-generated destructor stub
}

void p3Burn::execute(p3TimeStep step, Body* b, DataIn dataIn){

	//SWITCH THROUGH MANEUVER TYPES (to add dynamicism)
	//execute each maneuver type independantly with passed data

	switch(maneuverType){

		//Hohmann transfer maneuver
		case 1:

			if(b->id == 1){ //check if this body is the spacecraft
			if(burnNumber == 1){
			//start burn immediately in circular orbit
				//CHECK IF APOAPSIS IS AT TARGET RADIUS
				if(rApoapsis < dataIn.fRadius){

				burnOneDuration += step.dt;
				//calculate force in vector
				//magnitude of direction vector
				float magnitude = sqrt(pow(b->linearVelocity.x, 2) + pow(b->linearVelocity.y, 2) + pow(b->linearVelocity.z, 2));
				//convert velocity by unit vector
				Vector4 unit = b->linearVelocity / magnitude;
				//scale by given force magnitude
				Vector4 force = (unit * dataIn.thrust);

				b->applyForce(force);

				//THROW FUEL AND SUBTRACT MASS

				} //burn terminate

			} //burn num check

			} else if(burnNumber == 2){
				//start final burn when distance from primary  == rApoapsis
				if(b->distFromPrimary >= rApoapsis){
				//check if distance from primary < final orbit size (semi-major-axis)
				if(rApoapsis + rPeriapsis < 2 * rApoapsis){
					//reached circular orbit
						burnTwoDuration -= step.dt; //correct
						//calculate force in vector
						//magnitude of direction vector
						float magnitude = sqrt(pow(b->linearVelocity.x, 2) + pow(b->linearVelocity.y, 2) + pow(b->linearVelocity.z, 2));
						//convert velocity by unit vector
						Vector4 unit = b->linearVelocity / magnitude;
						//scale by given force magnitude
						Vector4 force = (unit * dataIn.thrust);

						b->applyForce(force);

					} //burn terminate
				} //burn initiate
			} //second burn

			break;

		} //switch

	}
