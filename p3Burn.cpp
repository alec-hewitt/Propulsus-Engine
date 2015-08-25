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

void p3Burn::execute(p3TimeStep step, Body* b, DataIn dataIn){

	//SWITCH THROUGH MANEUVER TYPES (to add dynamicism)
	//execute each maneuver type independantly with passed data

	switch(maneuverType){

		//hohmann transfer maneuver
		case 1:

			if(burnNumber == 1){
			//start burn immediately in circular orbit
				if(tRemaining > 0){
					tRemaining -= step.dt; //correct

				//calculate force in vector
				//magnitude of direction vector
				float magnitude = sqrt(pow(b->linearVelocity.x, 2) + pow(b->linearVelocity.y, 2) + pow(b->linearVelocity.z, 2));
				//convert velocity by unit vector
				Vector4 unit = b->linearVelocity / magnitude;
				//scale by given force magnitude
				Vector4 force = (unit * thrust);

				b->applyForce(force);

				}

			} else if(burnNumber == 2){
				//final burn
				//check if distance from primary < final orbit size (semi-major-axis)
				if(b->distFromPrimary < dataIn.fRadius){
					//begin burn, check for time expenditure
					if(tRemaining > 0){
						tRemaining -= step.dt; //correct

						//calculate force in vector
						//magnitude of direction vector
						float magnitude = sqrt(pow(b->linearVelocity.x, 2) + pow(b->linearVelocity.y, 2) + pow(b->linearVelocity.z, 2));
						//convert velocity by unit vector
						Vector4 unit = b->linearVelocity / magnitude;
						//scale by given force magnitude
						Vector4 force = (unit * thrust);
						//reverse burn direction
						force.x = force.x * -1;
						force.y = force.y * -1;
						force.z = force.z * -1;

						b->applyForce(force);

					}
				}
			}

		break;

	case 2:
		break;

	}




}
