/*
 * p3Burn.h
 *
 *  Created on: Aug 4, 2015
 *      Author: alec
 */

#ifndef P3BURN_H_
#define P3BURN_H_

class p3Burn {
public:
	p3Burn();
	virtual ~p3Burn();

	float duration;
	float thrust;
	float tRemaining;

	void execute();
};

#endif /* P3BURN_H_ */
