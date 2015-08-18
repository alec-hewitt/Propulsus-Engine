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
#include "p3Universe.h"
#include "p3Constants.h"

//tests

int main(){

	/* -- TEST -- */

	p3TimeStep step;
	step.dt = .5;
	step.duration = 15;

	p3Universe universe(step);

	Body* earth = universe.createBody();
	Vector4 pos1(0, 0, 0);
	earth->setAbsPosition(pos1);

	Body* moon = universe.createBody();
	Vector4 pos2(36, 0, 0);
	moon->setAbsPosition(pos2);

	p3Structure st;
	st.setSphere(5);
	st.mass = 6;

	p3Structure st2;
	st2.setSphere(5);
	st2.mass = 6;

	earth->setStructure(st);
	moon->setStructure(st2);

	/* -- END -- */

	//input data structure
	DataIn dIn;

	//prepare universe
	universe.universeInit(dIn);

	//begin maneuver calculations
	universe.maneuverInit(dIn);

	//run simulation
	universe.update();

	//output data structure
	//dataOut dOut;
	//collect data and send to front-end in dataOut structure

}
