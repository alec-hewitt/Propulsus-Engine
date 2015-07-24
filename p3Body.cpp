//p3Body.cpp

#include <iostream>
#include "p3Body.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;



//class constructor
Body::Body(){

}

void Body::setupBody(){

	//setupBody needs to be run before any calculations

	//initate dynamic body proprties
	relPos.set(0, 0, 0);
	absPos.set(0, 0, 0);
	rotation.set(0, 0, 0);
	linearVelocity.set(0, 0, 0);
	angularVelocity.set(0, 0, 0);
	angularAcceleration.set(0, 0, 0);
	acceleration.set(0, 0, 0);
	mass = this->structure.mass;

	//zero all dynamic properties
	appliedLinearForces.set(0, 0, 0);
	appliedTorque.set(0, 0, 0);
	netForce.set(0, 0, 0);
	netTorque.set(0, 0, 0);

	//resolve forces applied on object before next physics step occours
	resolveLinearForces();
	resolveAngularForces();

}

void Body::setStructure(p3Structure _structure){
	//set local structure object to passed
	this->structure = _structure;
	//mass
	this->mass = _structure.mass;
	//bounding sphere
	this->boundingSphereRadius = _structure.radius;
}

//setters

void Body::setRelPosition(Vector4 newRelPos){
	relPos = newRelPos;
}

void Body::setAbsPosition(Vector4 newAbsPos){
	absPos = newAbsPos;
}

void Body::setRotation(Vector4 newRotation){
	rotation = newRotation;
}

void Body::setLinearVelocity(Vector4 newLinearVelocity){
	linearVelocity = newLinearVelocity;
}

void Body::setAngularVelocity(Vector4 newAngularVelocity){
	angularVelocity = newAngularVelocity;
}

void Body::setAcceleration(Vector4 newAcceleration){
	acceleration = newAcceleration;
}

void Body::setNetTorque(Vector4 newNetTorque){
	netTorque = newNetTorque;
}

void Body::setMass(float newMass){
	mass = newMass;
}

//getters

Vector4 Body::getRelPosition(){
	return relPos;
}

Vector4 Body::getAbsPosition(){
	return absPos;
}

Vector4 Body::getRotation(){
	return rotation;
}

Vector4 Body::getLinearVelocity(){
	return linearVelocity;
}

Vector4 Body::getAngularVelocity(){
	return angularVelocity;
}

Vector4 Body::getAcceleration(){
	return acceleration;
}

Vector4 Body::getNetTorque(){
	return netTorque;
}

float Body::getMass(){
	return mass;
}

Vector4 Body::getNetForce(){
	return netForce;
}

//body modifiers

void Body::applyLinearImpulse(Vector4 impulse){
	linearVelocity = (impulse / mass);
}

void Body::applyForce(Vector4 force){
	appliedLinearForces.x += force.x;
	appliedLinearForces.y += force.y;
	appliedLinearForces.z += force.z;
}

void Body::applyTorque(Vector4 pivot, Vector4 force){
	//calculate torque and add
	appliedTorque = appliedTorque + (pivot * force);
}

void Body::resolveLinearForces() {
	//set net force to all applied forces
	netForce.set((appliedLinearForces.x), (appliedLinearForces.y), (appliedLinearForces.z));
	appliedLinearForces.reset(); //reset instance of applied forces for impulse calculation
}

void Body::resolveAngularForces(){
	netTorque.set(appliedTorque.x, appliedTorque.y, appliedTorque.z);
	appliedTorque.reset(); //reset instance of applied torque for impulse calculation
}