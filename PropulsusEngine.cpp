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

	p3TimeStep step;
	step.dt = .5;
	step.duration = 50;

	p3Universe universe(step);

	//input data structure
	DataIn dataIn;
	dataIn.maneuverType = 1;
	dataIn.iInclination = 0; //degrees
	dataIn.iOrbitPrimaryID = 3; //integer
	dataIn.iRadius = 435000; //M
	dataIn.fRadius = 535000; //M
	dataIn.massInitial = 10000; //KG
	dataIn.massFinal = 9000; //KG
	dataIn.thrust = 1800000; //N

	dataIn.exitArea = 3.3528;
	dataIn.exitPressure = 6653440.7752;
	dataIn.massEjectRate = 788.344;
	dataIn.specificImpulse = 2580;
	//retrive inputted data and place into dataIn object

	//data output object
	DataOut dataOut;
	DataOut* data;

	//prepare universe
	universe.universeInit(dataIn, &dataOut);

	//begin maneuver calculations
	universe.maneuverInit(dataIn, data);

	//run simulation
	universe.update(data, dataIn);


	//output data structure
	//dataOut dOut;

}
