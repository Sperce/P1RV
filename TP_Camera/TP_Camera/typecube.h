#pragma once
#include <Windows.h>

#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "vector3D.h"
#include "cube.h"

///////////////////////Sous-classes de CUBE///////////////////////////////

/* Plateforme classique*/

class Platform : public Cube {

	public: 
		Vector3D poke(Vector3D camPos, Vector3D futur, bool* grounded);

	Platform(Vector3D centre, Vector3D dimensions);
	~Platform();
};


/* Plateforme permettant un rebond */ 

class Trumpoline : public Cube {
	public:
		Vector3D poke(Vector3D camPos, Vector3D futur, bool* grounded);

	Trumpoline(Vector3D centre, Vector3D dimensions);
	~Trumpoline();
};

/* Plateforme permettant un  rebond */

class Jumpoline : public Cube {
protected:
	float jump;
public:
	Vector3D poke(Vector3D camPos, Vector3D futur, bool* grounded);
	float getjump();
	void setjump(float jump);


	Jumpoline(Vector3D centre, Vector3D dimensions, float jump);
	~Jumpoline();
};


class Shadowcube : public Cube {
public:
	Vector3D poke(Vector3D camPos, Vector3D futur, bool* grounded);

	Shadowcube(Vector3D centre, Vector3D dimensions, float r, float g, float b);
	~Shadowcube();
};

class Elevator : public Cube {
protected:
	float elevation;
public:
	Vector3D poke(Vector3D camPos, Vector3D futur, bool* grounded);
	float getelevation();
	void setelevation(float elevation);


	Elevator(Vector3D centre, Vector3D dimensions, float jump);
	~Elevator();
};
/*
class doublejumper : public Cube {
public:
	Vector3D poke(Vector3D camPos, Vector3D futur, bool* grounded);
	bool jumpgiv
	doublejumper(Vector3D centre, Vector3D dimensions);
	~doublejumper();
};
*/