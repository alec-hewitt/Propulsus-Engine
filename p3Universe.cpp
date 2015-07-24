#include "p3Universe.h"
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

p3Universe::p3Universe(p3TimeStep timeStep){
	
	//configure local
	this->step = timeStep;
	this->nBodies = 0;

}

//runs
void p3Universe::update(){
	
	//itterate at specified deltatimes until time duration is reached
	//read code, step simulation, and solve collision
	//non real-time so re-itterate immediately

	//set itterationns to be made
	int nItterations = (1 / this->step.dt) * this->step.duration;
	
	//begin update loop
	for (int i = 0; i < nItterations; i++){
		
		//STAGE
		//step physics
		stepSimulation();

		//STAGE
		//save data

	}
	
}

void p3Universe::stepSimulation(){

	/*
	-Resolve velocity, acceleration, angle, and position of bodies
	-Check for and resolve collisions
	*/
	
	//solve physics and TOI events for each body
	for (int i = 1; i <= nBodies; i++){
		
		Body b = universalBodies[i];

		//resolve forces on body
		b.resolveLinearForces();
		b.resolveAngularForces();

		//resolve acceleration accumulative
		b.acceleration = (b.netForce / b.mass);
		
		//set linear velocity accumulative
		b.linearVelocity = b.linearVelocity + (b.acceleration * step.dt);

		//enforce the speed limit
		if (b.linearVelocity.x > 299792458){
			b.linearVelocity.x = 2997924578;
		}
		if (b.linearVelocity.y > 299792458){
			b.linearVelocity.y = 299792458;
		}
		if (b.linearVelocity.z > 299792458){
			b.linearVelocity.z = 299792458;
		}

		//retrieve greatest velocity
		if (b.linearVelocity.x > b.linearVelocity.y){
			if (b.linearVelocity.x > b.linearVelocity.z){
				b.greatestV = b.linearVelocity.x;
			} else {
				b.greatestV = b.linearVelocity.z;
			}
		}
		else if (b.linearVelocity.y > b.linearVelocity.z){
			b.greatestV = b.linearVelocity.y;
		}
		else {
			b.greatestV = b.linearVelocity.z;
		}
		

		//set absolute universe position (accumulative)
		b.absPos = b.absPos + (b.linearVelocity * step.dt);
		
		//calculate angular acceleration
		b.angularAcceleration = (b.netTorque / b.structure.rotationalInertia);

		//calculate angular velocity
		b.angularVelocity = b.angularVelocity + (b.angularAcceleration * step.dt);

		//calculate angular momentum
		b.angularMomentum + (b.angularVelocity * b.structure.rotationalInertia);

		//detect collisions and solve body restitutions
		solve(&b);

		//last! return body to modified temp
		universalBodies[i] = b;

	}

}

void p3Universe::solve(Body* body){
	//solve collisions
	body->checked = false;
	body->collisionFlag = false;

	//run collision detection methods
	broadPhase(body);

	//body is clear of collisions if failed to detect any
	if (body->collisionFlag == false){
		body->checked = true;
	}
	
}

void p3Universe::broadPhase(Body* body){

	for (int i = 0; i <= nBodies; i++){

		//dont check collision with self or pre-checked bodies
		if (&universalBodies[i] != body && universalBodies[i].checked == false){

				//sum of both bodies' radius lengths
				float radii = body->boundingSphereRadius + universalBodies[i].boundingSphereRadius;

				//term for greatest distance bodies can travel in a single time step
				//each term is RVD for each body
				float velocityDistances = (body->greatestV * step.dt) + (universalBodies[i].greatestV * step.dt);

				//complete radial size of collision  hit zones
				float boundingDistances = radii;

				//distance between bodies
				float dist = sqrt(((body->absPos.x - universalBodies[i].absPos.x) * (body->absPos.x - universalBodies[i].absPos.x)) + ((body->absPos.y - universalBodies[i].absPos.y) * (body->absPos.y - universalBodies[i].absPos.y)) + ((body->absPos.z - universalBodies[i].absPos.z) * (body->absPos.z - universalBodies[i].absPos.z)));

				cout << "dist" << dist << endl;

				if (dist < boundingDistances){
					//collision of bounding spheres detected
					narrowPhase(body, &universalBodies[i]);

					cout << "collision" << endl;

				}

				//set body as checked
				body->checked = true;
		
		}
	}

}

void p3Universe::narrowPhase(Body* body, Body* other){
	//cout << "narrrow" << endl;

	/*
	if collision, flag bodies :

	body->collisionFlag = true;
	universalBodies[i].collisionFlag = true;

	*/
}

Body* p3Universe::createBody(){

	//create new body
	Body body;
	//setup with bodydef
	body.setupBody();
	
	//increment number of bodies
	nBodies++;
	//assign next bady in array to new body
	universalBodies[nBodies] = body;

	//create body pointer to array location
	Body* b = &universalBodies[nBodies];

	//return address of body in array
	return b;

}

void p3Universe::destroyBody(Body body){
	//remove specific body in param from body array
	
}
