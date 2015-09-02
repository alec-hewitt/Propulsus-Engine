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
void p3Universe::update(DataOut* data, DataIn dataIn){

	//set iterations to be made
	int nItterations = (1 / this->step.dt) * this->step.duration;
	
	//begin update loop
	for (int i = 1; i < nItterations; i++){
		
		//mark all bodies as unchecked for TOI collision events
		for(int i = 0; i < nBodies; i++){
			universalBodies[i].checked = false;
		}

		stepSimulation(data, dataIn);

		//function to aggregate collected data in universe methods throughout iterations
		//send data to main file for cpp-json parsing

	}
}

void p3Universe::universeInit(DataIn in, DataOut* data){
	//setup universe at defined time for required orbits (solar system structure)
	//generate bodies

	//bodies will be created in order (for purpose of ID assignment and comparison) by method:
	// 1) celestial planets beginning with sun, going outwards by distance from sun
	// 2) space vehicles in order of parsed array position

	if(in.maneuverType == 1){
		//create primary body
		Body* primary = createBody();
		Vector4 primaryPos(0, 0, 0);
		primary->setAbsPosition(primaryPos);
		p3Structure primaryStr;

		switch(in.iOrbitPrimaryID){
		case 0: //Sun
			primaryStr.setSphere(sunRadius_);
			primaryStr.mass = sunMass_;
			break;
		case 1: //Mercury
			primaryStr.setSphere(mercuryRadius_);
			primaryStr.mass = mercuryMass_;
			break;
		case 2: //Venus
			primaryStr.setSphere(venusRadius_);
			primaryStr.mass = venusMass_;
			break;
		case 3: //Earth
			primaryStr.setSphere(earthRadius_);
			primaryStr.mass = earthMass_;
			break;
		case 4: //Mars
			primaryStr.setSphere(marsRadius_);
			primaryStr.mass = marsMass_;
			break;
		case 5: //Jupiter
			primaryStr.setSphere(jupiterRadius_);
			primaryStr.mass = jupiterMass_;
			break;
		case 6: //Saturn
			primaryStr.setSphere(saturnRadius_);
			primaryStr.mass = saturnMass_;
			break;
		case 7: //Uranus
			primaryStr.setSphere(uranusRadius_);
			primaryStr.mass = uranusMass_;
			break;
		case 8: //Neptune
			primaryStr.setSphere(neptuneRadius_);
			primaryStr.mass = neptuneMass_;
			break;
		case 9: //Pluto
			primaryStr.setSphere(plutoRadius_);
			primaryStr.mass = plutoMass_;
			break;
		}
		primary->setStructure(primaryStr);

		//create spacecraft
		Body* craft = createBody();
		Vector4 craftPos(in.iRadius + primaryStr.radius, 0, 0);
		craft->setAbsPosition(craftPos);
		p3Structure craftStr;
			//set craft dimensions
		craftStr.mass = in.massInitial;
		//set velocity vector
		//orbital velocity scalar
		float v = sqrt((gravitation_ * primary->mass) / (in.iRadius + primaryStr.radius));

		//convert velocity to vector form
		Vector4 craftV(0,(v * sin(in.iInclination)), (v * cos(in.iInclination)));

		craft->setLinearVelocity(craftV);
		craft->setStructure(craftStr);

	}

}

//Analyzes initial and target orbits, and calculates burn objects
//with independent calculations for varied maneuver types.
void p3Universe::maneuverInit(DataIn in, DataOut* data){

	//run appropriate calculation method
	if(in.maneuverType == 1){
		this->hohmannTransferManeuver(in, data);
	}
}

void p3Universe::hohmannTransferManeuver(DataIn in, DataOut* data){
	//semi-major axis of transfer orbit
		double tSMA = (in.iRadius + in.fRadius) / 2;

		//orbital velocity on initial orbit at transfer intersection
		double initialOrbitV = sqrt((gravitation_ * universalBodies[0].mass) / in.iRadius);
		//orbital velocity on final orbit at transfer intersection
		double finalOrbitV = sqrt((gravitation_ * universalBodies[0].mass) / in.fRadius);

		//required velocity on transfer orbit at initial orbit intersection
		double initialTransferV = sqrt((gravitation_ * universalBodies[0].mass) * ((2/in.iRadius) - (1/tSMA)));
		//required velocity on transfer orbit at final orbit intersection
		double finalTransferV = sqrt((gravitation_ * universalBodies[0].mass) * ((2/in.fRadius) - (1/tSMA)));

		//delta-V at initial transfer point
		double initialDV = initialTransferV - initialOrbitV;
		//delta-V at final transfer point
		double finalDV = finalTransferV - finalOrbitV;

		//rocket specifications
		//amount of propellant expelled during each burn
		float propellantExpelledInitial = exp(initialDV / (in.specificImpulse * ((gravitation_ * universalBodies[0].mass)/(in.iRadius * in.iRadius))));
		float propellantExpelledFinal = exp(initialDV / (in.specificImpulse * ((gravitation_ * universalBodies[0].mass)/(in.fRadius * in.fRadius))));
		//rocket exit velocity
		float iveq = in.specificImpulse * ((gravitation_ * universalBodies[0].mass)/(in.iRadius * in.iRadius));
		float fveq = in.specificImpulse * ((gravitation_ * universalBodies[0].mass)/(in.fRadius * in.fRadius));
		//thrust of rocket (N)
		double iThrust = in.massEjectRate * iveq + in.exitPressure * in.exitArea;
		double fThrust = in.massEjectRate * fveq + in.exitPressure * in.exitArea;

		//double rocketMaxDV;

		///calculate burn mechanics
		//mass of rocket after initial burn
		double ifMass = in.massInitial - propellantExpelledInitial;
		//acceleration of rocket
		double iAcceleration = iThrust/ ifMass;
		//rocket equation DV from expelled mass
		double iRocketDV = iveq * log(in.massInitial / ifMass);
		//total required change in velocity after first burn
		double ifDV = initialDV - iRocketDV;

		//mass of rocket after fianl burn
		double ffMass = ifMass - propellantExpelledFinal;
		//acceleration of rocket
		double fAcceleration = fThrust/ ffMass;
		//rocket equation DV from expelled mass
		double fRocketDV = fveq * log(ifMass / ffMass);
		//total required change in velocity after first burn
		double ffDV = finalDV - fRocketDV;

		//assign data to burn objects and body
		nBurns = 2;
		p3Burn burnA = p3Burn();
		burnA.targetORadius = in.iRadius;
		burnA.targetPrimary = 0;
		burnA.maneuverType = 1;
		burnA.burnNumber = 1;
		burns[0] = burnA;

		p3Burn burnB = p3Burn();
		burnB.targetORadius = in.fRadius;
		burnB.targetPrimary = 0;
		burnB.maneuverType = 1;
		burnB.burnNumber = 2;
		burns[1] = burnB;

}

void p3Universe::stepSimulation(DataOut* data, DataIn dataIn){

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

				double dist = sqrt((distx * distx) + (disty * disty) + (distz * distz));

				Vector4 distUnit;
				distUnit.set(distx/dist, disty/dist, distz/dist);

				double gravity;
				if(dist == 0){gravity = 0;} else {
				gravity = (gravitation_ * ((b->mass * universalBodies[i].mass) / dist));
				}
				Vector4 gravitation;
				gravitation.set(gravity * distUnit.x, gravity * distUnit.y, gravity * distUnit.z);

				universalBodies[i].applyForce(gravitation);
			}
		}

		//resolve forces on body
		b->resolveLinearForces();
		b->resolveAngularForces();

		//resolve acceleration accumulative
		b->acceleration = (b->netForce / b->mass);

		//set linear velocity accumulative
		b->linearVelocity.x += b->acceleration.x * step.dt;
		b->linearVelocity.y += b->acceleration.y * step.dt;
		b->linearVelocity.z += b->acceleration.z * step.dt;

		b->velocity = sqrt( (b->linearVelocity.x * b->linearVelocity.x) + (b->linearVelocity.y * b->linearVelocity.y) + (b->linearVelocity.z * b->linearVelocity.z));

		//cout << b->velocity << endl;

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

		broadPhase(b, data, dataIn);

		switch(dataIn.maneuverType){
			case 1:
				if(b->id == 1){
				float v = sqrt((b->linearVelocity.x * b->linearVelocity.x) + (b->linearVelocity.y * b->linearVelocity.y) + (b->linearVelocity.z * b->linearVelocity.z)); //CALCULATE
				float sma = (gravitation_ * universalBodies[0].mass) / (2 * ((v * v) / 2));
				float rApoapsis = (2 * sma) - dataIn.iRadius;

				float rPeriapsis = (2 * sma) - rApoapsis;
				burns[0].semiMajorAxis = sma;
				burns[0].rApoapsis = rApoapsis;
				burns[0].rPeriapsis = rPeriapsis;

				//cout << "AP" << v << endl;

				//DEBUG
				if(rApoapsis < dataIn.fRadius){

					//burnOneDuration += step.dt;
					//magnitude of direction vector
					float magnitude = sqrt(pow(b->linearVelocity.x, 2) + pow(b->linearVelocity.y, 2) + pow(b->linearVelocity.z, 2));
					//convert velocity by unit vector
					Vector4 unit = b->linearVelocity / magnitude;
					//scale by given force magnitude
					Vector4 force = (unit * dataIn.thrust);
					force.x = force.x * -1;
					force.y = force.y * -1;
					force.z = force.z * -1;
					b->applyForce(force);
					//THROW FUEL AND SUBTRACT MASS
					float forcemag = sqrt((force.x * force.x) + (force.y * force.y) + (force.z * force.z));
					float dvi = (forcemag / b->mass) * step.dt;
					float propellantExpelledInitial = exp(dvi / (dataIn.specificImpulse * ((gravitation_ * universalBodies[0].mass)/(dataIn.iRadius * dataIn.iRadius))));
					b->mass -= propellantExpelledInitial;
					float iveq = dataIn.specificImpulse * ((gravitation_ * universalBodies[0].mass)/(dataIn.iRadius * dataIn.iRadius));
					double iRocketDV = iveq * log((b->mass + propellantExpelledInitial) / b->mass);
					//convert rocket dv to vector


				} //burn terminate

				//burn 2



				}
				break;
			}

		//check for burn commands
		//run all burn execute methods in body
		for(int i = 0; i < nBurns; i++){
			//burns[i].execute(step, b, dataIn);
		}


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

void p3Universe::broadPhase(Body* body, DataOut* data, DataIn dataIn){

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

				//assign distance from primary in data object
				//if checked body is the orbited primary
				switch(dataIn.maneuverType){
				case 1:
					if(i == 1){
						//set distance variable in body
						body->distFromPrimary = dist;
					}
				break;
				}

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
