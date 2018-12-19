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

#include "typecube.h"



Platform::Platform(Vector3D centre, Vector3D dimensions)
{
	setCentre(centre);
	setDimensions(dimensions);
	setr(0.7);
	setg(0.7);
	setb(0.7);
}

Vector3D Platform::poke(Vector3D footPos, Vector3D futur, bool* grounded)
{
	if ((footPos.getVx() + futur.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() + futur.getVx() <= getCentre().getVx() + getDimensions().getVx())
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz()))
		&& ((footPos.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1))) {
		futur.setVx(0);//si on rentre dans le cube grace au mouvement selon X, alors on y va pas
	}
	if ((footPos.getVz() + futur.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() + futur.getVz() <= getCentre().getVz() + getDimensions().getVz())
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))
		&& ((footPos.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1))) {
		futur.setVz(0);//mmême chose selon z
	}

	if ((footPos.getVy() + futur.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() + futur.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1)
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz()))) {
		futur.setVy(0);//même chose selon y, et, de plus, ça veut dire qu'on est sur le sol (/!\ se cogner la tête sur une plaque en sautant en étant en dessous met donc grounded true pour une milliseconde)
		*grounded = true;
	}
	if ((footPos.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1.1)
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz())) && futur.getVy() == 0) {
		*grounded = true;//pour éviter les problèmes avec grounded, on agrandit un peu sa zone d'action

	}

	return futur;
}
Platform::~Platform()
{
}
//****************************************************************************************************************************************************************************************************

Trumpoline::Trumpoline(Vector3D centre, Vector3D dimensions)
{
	setCentre(centre);
	setDimensions(dimensions);
	setr(0.2);
	setg(0.2);
	setb(0.2);
}

Vector3D Trumpoline::poke(Vector3D footPos, Vector3D futur, bool* grounded) {
	if ((footPos.getVx() + futur.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() + futur.getVx() <= getCentre().getVx() + getDimensions().getVx())
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz()))
		&& ((footPos.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1))) {
		futur.setVx(0);
	}
	if ((footPos.getVz() + futur.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() + futur.getVz() <= getCentre().getVz() + getDimensions().getVz())
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))
		&& ((footPos.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1))) {
		futur.setVz(0);
	}

	if ((footPos.getVy() + futur.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() + futur.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1)
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz()))) {
		futur.setVy(-futur.getVy());//un trampoline, au lieu de nous arrêter nous renvoie dans l'autre sens
	}

	return futur;
}
Trumpoline::~Trumpoline()
{
}


//*****************************************************************************
void Jumpoline::setjump(float jump) {
	this->jump = jump;
}

float Jumpoline::getjump() {
	return jump;
}

Jumpoline::Jumpoline(Vector3D centre, Vector3D dimensions, float jump)
{
	setCentre(centre);
	setDimensions(dimensions);
	setr(0.2);
	setg(0.5);
	setb(0.2);
	setjump(jump);

}

Vector3D Jumpoline::poke(Vector3D footPos, Vector3D futur, bool* grounded) {
	if ((footPos.getVx() + futur.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() + futur.getVx() <= getCentre().getVx() + getDimensions().getVx())
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz()))
		&& ((footPos.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1))) {
		futur.setVx(0);
	}
	if ((footPos.getVz() + futur.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() + futur.getVz() <= getCentre().getVz() + getDimensions().getVz())
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))
		&& ((footPos.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1))) {
		futur.setVz(0);
	}

	if ((footPos.getVy() + futur.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() + futur.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1)
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz()))) {
		futur.setVy(getjump());//  /!\ venir par le dessous du jumpoline nous fait passer au travers et nous envoie
	}

	return futur;
}
Jumpoline::~Jumpoline()
{
}

//*****************************************************************************

Shadowcube::Shadowcube(Vector3D centre, Vector3D dimensions, float r, float g, float b)
{
	setCentre(centre);
	setDimensions(dimensions);
	setr(r);
	setg(g);
	setb(b);
}

Vector3D Shadowcube::poke(Vector3D footPos, Vector3D futur, bool* grounded) {
	return futur;
}
Shadowcube::~Shadowcube()
{
}
//*****************************************************************************
void Elevator::setelevation(float elevation) {
	this->elevation = elevation;
}

float Elevator::getelevation() {
	return elevation;
}

Elevator::Elevator(Vector3D centre, Vector3D dimensions, float elevation)
{
	setCentre(centre);
	setDimensions(dimensions);
	setr(0.2);
	setg(0.2);
	setb(0.5);
	setelevation(elevation);

}

Vector3D Elevator::poke(Vector3D footPos, Vector3D futur, bool* grounded) {

	if ((footPos.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1)
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz())))
	{
		futur.setVy(getelevation());//si on est dans l'ascenseur on monte
	}
	else if (((footPos.getVy() + futur.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() + futur.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1)
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz()))
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))))
	{
		futur.setVy(0);//on ne peut rentre ni par en dessous, ni par au dessus
		*grounded = true;
	}

	if ((footPos.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1.1)
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz())) && futur.getVy() == 0)
	{
		*grounded = true;
	}
	return futur;
}
Elevator::~Elevator()
{
}


//****************************************************************************************

Goal::Goal(Vector3D centre, Vector3D dimensions)//juste un cube de couleur différente, on pensait lui donner un autre poke mais il a finalement été laissé tel quel
{
	setCentre(centre);
	setDimensions(dimensions);
	setr(0.7);
	setg(0.7);
	setb(0.2);
}

Vector3D Goal::poke(Vector3D footPos, Vector3D futur, bool* grounded)
{
	if ((footPos.getVx() + futur.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() + futur.getVx() <= getCentre().getVx() + getDimensions().getVx())
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz()))
		&& ((footPos.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1))) {
		futur.setVx(0);
	}
	if ((footPos.getVz() + futur.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() + futur.getVz() <= getCentre().getVz() + getDimensions().getVz())
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))
		&& ((footPos.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1))) {
		futur.setVz(0);
	}

	if ((footPos.getVy() + futur.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() + futur.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1)
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz()))) {
		futur.setVy(0);
		*grounded = true;
	}
	if ((footPos.getVy() >= getCentre().getVy() - getDimensions().getVy()) && (footPos.getVy() <= getCentre().getVy() + getDimensions().getVy() + 1.1)
		&& ((footPos.getVx() >= getCentre().getVx() - getDimensions().getVx()) && (footPos.getVx() <= getCentre().getVx() + getDimensions().getVx()))
		&& ((footPos.getVz() >= getCentre().getVz() - getDimensions().getVz()) && (footPos.getVz() <= getCentre().getVz() + getDimensions().getVz())) && futur.getVy() == 0) {
		*grounded = true;

	}

	return futur;
}
Goal::~Goal()
{
}

/***********************************************************************************************************************************************/
