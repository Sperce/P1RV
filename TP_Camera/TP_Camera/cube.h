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


class Cube
{
protected:
	Vector3D centre;
	Vector3D dimensions;
	float r;
	float g;
	float b;


public:
	Cube();
	~Cube();
	virtual Vector3D poke(Vector3D camPos ,Vector3D futur, bool* grounded)=0;
	Vector3D getDimensions();
	Vector3D getCentre();
	void setDimensions(Vector3D dimensions);
	void setCentre(Vector3D centre);
	void affiche();
	float getr();
	float getg();
	float getb();
	void setr(float r);
	void setg(float g);
	void setb(float b);
};



