#include "p3Universe.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
#include "p3Constants.h"

using namespace std;

p3Universe::p3Universe(p3TimeStep timeStep){
	
	//configure local
	this->step = timeStep;
	this->nBodies = 0;

}

//Iterate at specified delta-times until time duration is reached
//read code, step simulation, and solve collision
//non real-time so re-iterate immediately
void p3Universe::update(){

	//set iterations to be made
	int nItterations = (1 / this->step.dt) * this->step.duration;
	
	//begin update loop
	for (int i = 1; i < nItterations; i++){
		
		//mark all bodies as unchecked for TOI collision events
		for(int i = 0; i < nBodies; i++){
			universalBodies[i].checked = false;
		}

		stepSimulation();
	}
}

void p3Universe::maneuverInit(){
	//Analyzes initial and target orbits, and calculates burn objects
	//with independent calculations for varied maneuver types.

	//if hohmann transfer maneuver... pass packaged orbit data to hohmannTransfer function

}

void p3Universe::hohmannTransferManeuver(){
	/*accept orbit data
	create orbit objects and assign to body
	create transfer orbit object
	calculate transfer orbit points of intersection, semi-major-axis, and more
	calculate velocity at transfer orbit intersecting points (store in transfer orbit object)
	calculate required velocity at intersection points
	create two burn objects
	calculate required delta-V at each burn (intersection point) (store in each burn)
	initiate function in burn objects to calculate burn specifications
	pass all of this data somewhere accessible!!
	*/
}

void p3Universe::stepSimulation(){

	/*
	-Resolve velocity, acceleration, angle, and position of bodies
	-Check for and resolve collisions
	*/
	
	//solve physics and TOI events for each body
	for (int i = 0; i < nBodies; i++){

	Body* b = &universalBodies[i];

		for(int i = 0; i < nBodies; i++){
			if(&universalBodies[i] != b){
				double distx = b->absPos.x - universalBodies[i].absPos.x;
				double disty = b->absPos.y - universalBodies[i].absPos.y;
				double distz = b->absPos.z - universalBodies[i].absPos.z;
				double fgx = (gravitation_ * ((b->mass * universalBodies[i].mass) / (distx * distx)));
				if(universalBodies[i].absPos.x > b->absPos.x){fgx = (fgx * -1);}
				double fgy = (gravitation_ * ((b->mass * universalBodies[i].mass) / (disty * disty)));
				if(universalBodies[i].absPos.y > b->absPos.y){fgy = (fgy * -1);}
				double fgz = (gravitation_ * ((b->mass * universalBodies[i].mass) / (distz * distz)));
				if(universalBodies[i].absPos.z > b->absPos.z){fgz = (fgz * -1);}
				Vector4 gravitation;
				gravitation.set(fgx, fgy, fgz);
				universalBodies[i].applyForce(gravitation);
			}
		}

		//resolve forces on body
		b->resolveLinearForces();
		b->resolveAngularForces();

		//resolve acceleration accumulative
		b->acceleration = (b->netForce / b->mass);

		//set linear velocity accumulative
		b->linearVelocity = b->linearVelocity + (b->acceleration * step.dt);

		//retrieve greatest velocity
		if (b->linearVelocity.x > b->linearVelocity.y){
			if (b->linearVelocity.x > b->linearVelocity.z){
				b->greatestV = b->linearVelocity.x;
			} else {
				b->greatestV = b->linearVelocity.z;
			}
		}
		else if (b->linearVelocity.y > b->linearVelocity.z){
			b->greatestV = b->linearVelocity.y;
		}
		else {
			b->greatestV = b->linearVelocity.z;
		}
		
		//set absolute universe position (accumulative)
		b->absPos = b->absPos + (b->linearVelocity * step.dt);

		//calculate angular acceleration
		b->angularAcceleration = (b->netTorque / b->structure.rotationalInertia);

		//calculate angular velocity
		b->angularVelocity = b->angularVelocity + (b->angularAcceleration * step.dt);

		//calculate angular momentum
		b->angularMomentum + (b->angularVelocity * b->structure.rotationalInertia);

		broadPhase(b);

		cout << b->absPos.x << endl;

		//&universalBodies[i] = b;

	}
	return;
}

/*
 * It may be reasonable to use only a more brute-force and less intrusive broad-phase
 * collision detection method with no further detection phases, due to both the
 * expected small amount of generated bodies in the universe, and the expected scarcity
 * of collisions in the universe at any given time or even throughout entire execution.
 * The nature of most collisions in problems of orbital dynamics (excluding those such as docking procedures)
 * do not generally require intense collision checking in small spaces.
 * Basically is this ship going to hit mars or not.
 */

void p3Universe::broadPhase(Body* body){

	//nBodies -1 because i starts at 0 and nBodies starts at 1
	for (int i = 0; i <= (nBodies - 1); i++){

		//dont check collision with self or pre-checked bodies
		if (&universalBodies[i] != body && universalBodies[i].checked == false && nBodies > 1){

				//sum of both bodies' radius lengths
				float radii = body->boundingSphereRadius + universalBodies[i].boundingSphereRadius;

				//greatest distance bodies can travel in a single time step
				float velocityDistances = (body->greatestV * step.dt) - (universalBodies[i].greatestV * step.dt);

				//complete radial size of collision  hit zones
				float boundingDistances = radii + velocityDistances;

				//distance between bodies
				float dist = sqrt(((body->absPos.x - universalBodies[i].absPos.x) * (body->absPos.x - universalBodies[i].absPos.x)) + ((body->absPos.y - universalBodies[i].absPos.y) * (body->absPos.y - universalBodies[i].absPos.y)) + ((body->absPos.z - universalBodies[i].absPos.z) * (body->absPos.z - universalBodies[i].absPos.z)));

				if (dist < boundingDistances){
					//collision of bounding spheres detected
					body->collisionFlag = true;
					universalBodies[i].collisionFlag = true;
					//debug collision instances
					cout << "COLLISION" << endl;
				}
		
		}
	}

	//set body as checked
	body->checked = true;

	return;

}

Body* p3Universe::createBody(){

	//create new body
	Body body;

	//initialize body
	body.setupBody();

	//assign body id as its position in array
	body.id = nBodies;

	//assign next body in array to new body
	universalBodies[nBodies] = body;

	Body* b = &universalBodies[nBodies];

	//increment number of bodies
	nBodies++;

	//return address of body in array
	return b;

}

