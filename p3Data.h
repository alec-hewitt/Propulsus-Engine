#ifndef P3_DATA_H_
#define P3_DATA_H_

class DataIn{
public:
		//maneuver info
		int maneuverType;
		char time; //given in char value yyyymmddhhmmss
		//initial orbit ID
		int iOrbitPrimaryID;
		//initial orbit radius
		double iRadius;
		//final orbit ID
		int fOrbitPrimaryID;
		//final orbit radius
		double fRadius;
		//vehicle info
		float massInitial;
		float massFinal;
		float specificImpulse;
		Vector4 impulseLocation;
		float exitPressure; //n/m2
		float exitArea;
		float massEjectRate;
		//center of mass coordinates
		Vector4 centerOfMass;
		float width;
		float height;

};

#endif
