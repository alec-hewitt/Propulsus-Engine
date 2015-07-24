#ifndef P3TIMESTEP_H
#define P3TIMESTEP_H

struct p3TimeStep{

	//change in time between physics and collision itterations (seconds)
	float dt;

	//duration of time to simulate (seconds)
	float duration;

	int velocityIterations; //times to solve for velocity

	int positionIterations; //times to solve for position

	float inverse_dt; //calculations per second, or (1/dt) (seconds)

};

#endif
