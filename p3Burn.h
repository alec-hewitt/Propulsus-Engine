#ifndef P3BURN_H_
#define P3BURN_H_

#include "p3TimeStep.h"
#include "p3Body.h"

class p3Burn {
public:
	p3Burn();
	virtual ~p3Burn();

	int maneuverType;
	int burnNumber;
	bool executed;

	float semiMajorAxis;
	float rApoapsis;
	float rPeriapsis;
	float burnOneDuration = 0;
	float burnTwoDuration = 0;
	float targetPrimary;
	float targetORadius;

	p3TimeStep p;

	void execute(p3TimeStep step, Body* b, DataIn dataIn);


};

#endif /* P3BURN_H_ */
