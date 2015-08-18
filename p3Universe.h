
#ifndef P3UNIVERSE_H
#define P3UNIVERSE_H

#include "p3Body.h"
#include "p3Burn.h"
#include "p3TimeStep.h"

class p3Universe{
	
public:

	//constructor
	p3Universe(p3TimeStep timeStep);

	//time-step object
	//houses time stepping information passed into universe
	p3TimeStep step;

	//time passed in simulation
	float elapsedTime;

	//array of all rigid-bodies in universe
	//eventually these will only be processed through galaxy or celestial body..
	//to account for relativity and other changes in space-time
	Body universalBodies[2];
	int nBodies;

	int nBurns;
	p3Burn burns[9];

	//celestial bodies
	Body celestialBodies[9];

	//data

	//Analyzes initial and target orbits, and calculates burn objects
	//with independent calculations for varied maneuver types.
	//F.e.: A Hohmann Transfer orbit will be called to calculate 2 burn objects
	//if two elliptical orbits are around the same primary and do not intersect.
	//Calls appropriate maneuver calculation function for UI-selected maneuver
	void maneuverInit(DataIn in);

	void hohmannTransferManeuver(DataIn in);

	//Main Loop
	//Has access and control over time and DT
	//Iterates until program ends at 60i/s
	//Calls appropriate functions (mainly stepSimulation)
	void update();

	//generate celestial bodies and user bodies
	void universeInit(DataIn dw);

	//manages time-stepping
	//moves with time at the fixed time step to account for object values at given time
	//processes all physics in a fixed time-step
	void stepSimulation();

	//detections collisions of body's bounding spheres
	void broadPhase(Body* body);

	//function to return data structure

	//adds a new rigid-body to the universe
	//body will be one outside of any scope
	Body* createBody();
};

#endif
