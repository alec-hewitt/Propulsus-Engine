#ifndef P3UNIVERSE_H
#define P3UNIVERSE_H

#include "p3Body.h"
#include "p3Vector4.h"
#include "p3TimeStep.h"
#include "p3Timer.h"

class p3Universe{
	
public:

	const float gravitation = 0.00000000000667384;

	//constructor
	p3Universe(p3TimeStep timeStep);

	//timestep object
	//houses time stepping information passed into unviverse
	p3TimeStep step;

	//time passed in simulation
	float elapsedTime;

	//array of all rigidbodies in universe
	//eventually these will only be proccesed through galaxy or celestial body..
	//to account for relativity and other changes in space-time
	Body *universalBodies[2];
	int nBodies;

	//Main Loop
	//Has access and control over time and DT
	//Itterates until program ends at 60i/s
	//Calls appropriate functions (mainly stepSimulation)
	void update();

	//manages timestepping
	//moves with time at the fixed time step to account for object values at given time
	//processes all physics in a fixed timestep
	void stepSimulation();

	//collision solver
	//solves for all TOI events and collisions
	void solve(Body* body);

	//detections collisions of body's bounding spheres
	void broadPhase(Body* body);

	//detects collisions using raycast methods in short distances
	void narrowPhase(Body* body, Body* other);

	//adds a new rigidbody to the universe
	//body will be one outside of any scope
	Body createBody();
};

#endif
