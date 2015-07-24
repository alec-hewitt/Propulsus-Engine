#ifndef P3TIMER_H
#define P3TIMER_H

//p3Timer: keep track of passed time for simulation

class Timer{
public:
	//current elapsed time
	//default in seconds
	float startTime;
	float elapsedTime;
	float time;

	//constructor
	Timer();

	//functions
	void start();
	void stop();
	float getTime();
};

#endif