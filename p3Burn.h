#ifndef P3BURN_H_
#define P3BURN_H_

#include "p3TimeStep.h"
#include "p3Body.h"

class p3Burn {
public:
	p3Burn();
	virtual ~p3Burn();

	float duration;
	float thrust;
	float tRemaining;

	p3TimeStep p;

	void execute(p3TimeStep step, Body* b);


};

#endif /* P3BURN_H_ */
