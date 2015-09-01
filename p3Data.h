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
		double iInclination;
		//final orbit ID
		int fOrbitPrimaryID;
		//final orbit radius
		double fRadius;
		double fInclination;
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

		float thrust;

};

class DataOut{
public:
	double hm_initial_semimajoraxis;
	double hm_final_semimajoraxis;
	double hm_transfer_semimajoraxis;
	double hm_initial_orbit_v;
	double hm_final_orbit_v;
	double hm_initial_transfer_v;
	double hm_final_transfer_v;
	double hm_initial_dv;
	double hm_final_dv;
	double hm_initial_propellant_expelled;
	double hm_final_propellant_expelled;
	double hm_initial_rocket_exitv;
	double hm_final_rocket_exitv;
	double hm_initial_rocket_thrust;
	double hm_final_rocket_thrust;
	double hm_rocket_max_dv;
	double hm_initial_final_rocket_mass;
	double hm_final_final_rocket_mass;
	double hm_initial_rocket_acceleration;
	double hm_final_rocket_acceleration;
	double hm_initial_rocket_dv;
	double hm_final_rocket_dv;
	double hm_initial_burn_time;
	double hm_final_burn_time;
};

#endif
