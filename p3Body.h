//p3Body.h

#ifndef P3BODY_H
#define P3BODY_H

#include "p3Vector4.h"
#include "p3Structure.h"

class Body{
public:

	//constructor
	Body();

	//sets up the body before any calculations are done
	//sets some properties to zero, sets others to defined info in bodyDef from connstructor
	void setupBody();

	//setup strucure component if applicable

	//rigidbody properties
	//position/rotation
	Vector4 relPos;
	Vector4 absPos;
	float mass;
	float rotationalInertia;
	Vector4 rotation;
	Vector4 angularMomentum;
	Vector4 appliedTorque;
	Vector4 netTorque;
	Vector4 angularAcceleration;
	Vector4 angularVelocity;
	Vector4 linearVelocity;
	Vector4 acceleration;
	Vector4 appliedLinearForces;
	Vector4 netForce;
	
	//setters

	void setRelPosition(Vector4 newRelPos);
	void setAbsPosition(Vector4 newAbsPos);
	void setRotation(Vector4 newRotation);
	void setLinearVelocity(Vector4 newLinearVelocity);
	void setAngularVelocity(Vector4 newAngularVelocity);
	void setAcceleration(Vector4 newAcceleration);
	void setNetTorque(Vector4 newNetTorque);
	void setMass(float newMass);

	//getters

	Vector4 getRelPosition();
	Vector4 getAbsPosition();
	Vector4 getRotation();
	Vector4 getLinearVelocity();
	Vector4 getAngularVelocity();
	Vector4 getAcceleration();
	Vector4 getNetTorque();
	Vector4 getNetForce();
	float getMass();
	Vector4 getGravitation();
	float greatestV;

	//smallest possible sphere around the object
	//broadphase collision
	float boundingSphereRadius;

	//checked alll possible collisions
	bool checked;

	//collision
	//flagged when body is checked against all other bodies
	bool collisionFlag;

	//strucure object (potentially an array)
	p3Structure structure;

	//passes structure object to body
	void setStructure(p3Structure _structure);

	//body modifiers

	//adds a linear gravitational acceleration
	void addGravtitation(Vector4 pull);

	//applies a constant force to Vector3 applied forces
	void applyForce(Vector4 force);

	//applies a single impulse. only affects current velocity, not the net force
	void applyLinearImpulse(Vector4 impulse);

	//combines all forces acting upon the body to get and set the net force
	//does not return the net force whilst getNetForce() calls this method and returns netForce
	void resolveLinearForces();

	void resolveAngularForces();

	//applies an angular force of given magnitude at given pivot point from body
	//point 0,0,0 is the center of mass of the modified body
	void applyTorque(Vector4 force, Vector4 pivot);

};

#endif // P3_BODY_H