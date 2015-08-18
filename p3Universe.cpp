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

void p3Universe::universeInit(DataIn in){
	//setup universe at defined time for required orbits (solar system structure)
	//generate bodies
}

//Analyzes initial and target orbits, and calculates burn objects
//with independent calculations for varied maneuver types.
void p3Universe::maneuverInit(DataIn in){

	//run appropriate calculation method
	if(in.maneuverType == 1){
		this->hohmannTransferManeuver(in);
	}
}

void p3Universe::hohmannTransferManeuver(DataIn in){
	//semi-major axis of transfer orbit
		double tSMA = (in.iRadius + in.fRadius) / 2;

		//orbital velocity on initial orbit at transfer intersection
		double initialOrbitV = sqrt((gravitation_ * celestialBodies[in.iOrbitPrimaryID].mass) / in.iRadius);
		//orbital velocity on final orbit at transfer intersection
		double finalOrbitV = sqrt((gravitation_ * celestialBodies[in.fOrbitPrimaryID].mass) / in.fRadius);

		//required velocity on transfer orbit at initial orbit intersection
		double initialTransferV = sqrt((gravitation_ * celestialBodies[in.iOrbitPrimaryID].mass) * ((2/in.iRadius) - (1/tSMA)));
		//required velocity on transfer orbit at initial orbit intersection
		double finalTransferV = sqrt((gravitation_ * celestialBodies[in.fOrbitPrimaryID].mass) * ((2/in.fRadius) - (1/tSMA)));

		//delta-V at initial transfer point
		double initialDV = initialTransferV - initialOrbitV;
		//delta-V at final transfer point
		double finalDV = finalTransferV - finalOrbitV;

		//rocket specifications
		//amount of propellant expelled during each burn
		float propellantExpelledInitial = exp(initialDV / (in.specificImpulse * ((gravitation_ * celestialBodies[in.iOrbitPrimaryID].mass)/(in.iRadius * in.iRadius))));
		float propellantExpelledFinal = exp(initialDV / (in.specificImpulse * ((gravitation_ * celestialBodies[in.fOrbitPrimaryID].mass)/(in.fRadius * in.fRadius))));
		//rocket exit velocity
		float iveq = in.specificImpulse * ((gravitation_ * celestialBodies[in.iOrbitPrimaryID].mass)/(in.iRadius * in.iRadius));
		float fveq = in.specificImpulse * ((gravitation_ * celestialBodies[in.fOrbitPrimaryID].mass)/(in.fRadius * in.fRadius));
		//thrust of rocket (N)
		double iThrust = in.massEjectRate * iveq + in.exitPressure * in.exitArea;
		double fThrust = in.massEjectRate * fveq + in.exitPressure * in.exitArea;

		///calculate burn mechanics

		//mass of rocket after initial burn
		double ifMass = in.massInitial - propellantExpelledInitial;
		//acceleration of rocket
		double iAcceleration = iThrust/ ifMass;
		//rocket equation DV from expelled mass
		double iRocketDV = iveq * log(in.massInitial / in.massFinal);
		//total required change in velocity after first burn
		double ifDV = initialDV - iRocketDV;
		//burn time - duration of thrusting to achieve required DV
		double iBurnTime = ifDV / iAcceleration;

		//mass of rocket after initial burn
		double ffMass = in.massFinal - propellantExpelledFinal;
		//acceleration of rocket
		double fAcceleration = fThrust/ ffMass;
		//rocket equation DV from expelled mass
		double fRocketDV = fveq * log(in.massInitial / in.massFinal);
		//total required change in velocity after first burn
		double ffDV = finalDV - fRocketDV;
		//burn time - duration of thrusting to achieve required DV
		double fBurnTime = ffDV / fAcceleration;

		//assign data to burn objects and body

		//we assume body position in array is 0
		nBurns = 2;
		p3Burn burnA = p3Burn();
		burnA.duration = iBurnTime;
		burnA.thrust = iThrust;
		burns[0] = burnA;

		p3Burn burnB = p3Burn();
		burnB.duration = fBurnTime;
		burnB.thrust = fThrust;
		burns[1] = burnB;

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

		//check for burn commands
		//run all burn execute methods in body
		for(int i = 0; i < nBurns; i++){
			burns[i].execute(step, b);
		}

		//resolve forces on body
		b->resolveLinearForces();
		b->resolveAngularForces();

		//resolve acceleration accumulative
		b->acceleration = (b->netForce / b->mass);

		//set linear velocity accumulative
		b->linearVelocity = b->linearVelocity + (b->acceleration * step.dt);

		cout << b->linearVelocity.x << endl;

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

