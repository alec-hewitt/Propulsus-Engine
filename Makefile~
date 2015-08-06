CC=g++ -std=c++11

CFLAGS=-MMD -c -Wall

DEPS := $(SOURCES:.o=.d)

SOURCES=PropulsusEngine.o p3Universe.o p3Orbit.o p3Burn.o p3Body.o p3Vector4.o p3Matrix4.o p3Structure.o p3Timer.o

all: propulsus

propulsus: $(SOURCES)
	$(CC) $(SOURCES) -o propulsus

PropulsusEngine.o: PropulsusEngine.cpp p3Structure.h p3Body.h p3Universe.h p3TimeStep.h p3Constants.h
	$(CC) $(CFLAGS) PropulsusEngine.cpp

p3Universe.o: p3Universe.cpp p3Universe.h p3Body.h p3Vector4.h p3TimeStep.h p3Timer.h p3Constants.h
	$(CC) $(CFLAGS) p3Universe.cpp

p3Orbit.o: p3Orbit.cpp p3Orbit.h p3Body.h p3Vector4.h p3Timer.h p3TimeStep.h
	$(CC) $(CFLAGS) p3Orbit.cpp

p3Burn.o: p3Burn.cpp p3Burn.h p3Body.h p3Vector4.h p3Timer.h p3TimeStep.h
	$(CC) $(CFLAGS) p3Burn.cpp

p3Body.o: p3Body.cpp p3Body.h p3Vector4.h p3Structure.h
	$(CC) $(CFLAGS) p3Body.cpp

p3Vector4.o: p3Vector4.cpp p3Vector4.h
	$(CC) $(CFLAGS) p3Vector4.cpp

p3Matrix4.o: p3Matrix4.cpp p3Matrix4.h p3Vector4.h
	$(CC) $(CFLAGS) p3Matrix4.cpp

p3Structure.o: p3Structure.cpp p3Structure.h p3Vector4.h
	$(CC) $(CFLAGS) p3Structure.cpp

p3Timer.o: p3Timer.cpp p3Timer.h
	$(CC) $(CFLAGS) p3Timer.cpp

p3Draw.o: p3Draw.cpp p3Draw.h p3Vector4.h
	$(CC) $(CFLAGS) p3Draw.cpp

clean:
	rm *o *d propulsus
