/*

The MIT License(MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <iostream>

#include <array>

#include "p3Structure.h"
#include "p3Body.h"
#include "p3Universe.h"
#include "p3TimeStep.h"

//tests

int main(){

	p3TimeStep step;
	step.dt = .2;
	step.duration = 5;

	p3Universe universe(step);

	Body* b1 = universe.createBody();
	b1->setMass(1.5);
	Vector4 pos1(0, 0, 0);
	b1->setAbsPosition(pos1);

	Body* b2 = universe.createBody();
	b2->setMass(2);
	Vector4 pos2(150, 0, 0);
	b2->setAbsPosition(pos2);

	p3Structure st;
	st.setSphere(2);

	b1->setStructure(st);

	b2->setStructure(st);

	Vector4 force(0, 0, 0);
	
	Vector4 force2(0, 0, 0);

	b1->applyForce(force);
	b2->applyForce(force2);

	universe.update();

	//universe.stepSimulation();

}

