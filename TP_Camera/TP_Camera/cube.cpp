#include "cube.h"




Cube::Cube()
{}


void Cube::affiche() {
	//face haute
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex3f(centre.getVx() + dimensions.getVx(), centre.getVy() + dimensions.getVy(), centre.getVz() + dimensions.getVz());
	glVertex3f(centre.getVx() - dimensions.getVx(), centre.getVy() + dimensions.getVy(), centre.getVz() + dimensions.getVz());
	glVertex3f(centre.getVx() - dimensions.getVx(), centre.getVy() + dimensions.getVy(), centre.getVz() - dimensions.getVz());
	glVertex3f(centre.getVx() + dimensions.getVx(), centre.getVy() + dimensions.getVy(), centre.getVz() - dimensions.getVz());
	glEnd();
	//face basse
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex3f(centre.getVx() + dimensions.getVx(), centre.getVy() - dimensions.getVy(), centre.getVz() + dimensions.getVz());
	glVertex3f(centre.getVx() - dimensions.getVx(), centre.getVy() - dimensions.getVy(), centre.getVz() + dimensions.getVz());
	glVertex3f(centre.getVx() - dimensions.getVx(), centre.getVy() - dimensions.getVy(), centre.getVz() - dimensions.getVz());
	glVertex3f(centre.getVx() + dimensions.getVx(), centre.getVy() - dimensions.getVy(), centre.getVz() - dimensions.getVz());
	glEnd();
	//face avant
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex3f(centre.getVx() + dimensions.getVx(), centre.getVy() - dimensions.getVy(), centre.getVz() + dimensions.getVz());
	glVertex3f(centre.getVx() - dimensions.getVx(), centre.getVy() - dimensions.getVy(), centre.getVz() + dimensions.getVz());
	glVertex3f(centre.getVx() - dimensions.getVx(), centre.getVy() + dimensions.getVy(), centre.getVz() + dimensions.getVz());
	glVertex3f(centre.getVx() + dimensions.getVx(), centre.getVy() + dimensions.getVy(), centre.getVz() + dimensions.getVz());
	glEnd();
	//face avant
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex3f(centre.getVx() + dimensions.getVx(), centre.getVy() - dimensions.getVy(), centre.getVz() - dimensions.getVz());
	glVertex3f(centre.getVx() - dimensions.getVx(), centre.getVy() - dimensions.getVy(), centre.getVz() - dimensions.getVz());
	glVertex3f(centre.getVx() - dimensions.getVx(), centre.getVy() + dimensions.getVy(), centre.getVz() - dimensions.getVz());
	glVertex3f(centre.getVx() + dimensions.getVx(), centre.getVy() + dimensions.getVy(), centre.getVz() - dimensions.getVz());
	glEnd();
	//face droite
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex3f(centre.getVx() + dimensions.getVx(), centre.getVy() + dimensions.getVy(), centre.getVz() + dimensions.getVz());
	glVertex3f(centre.getVx() + dimensions.getVx(), centre.getVy() - dimensions.getVy(), centre.getVz() + dimensions.getVz());
	glVertex3f(centre.getVx() + dimensions.getVx(), centre.getVy() - dimensions.getVy(), centre.getVz() - dimensions.getVz());
	glVertex3f(centre.getVx() + dimensions.getVx(), centre.getVy() + dimensions.getVy(), centre.getVz() - dimensions.getVz());
	glEnd();
	//face gauche
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glVertex3f(centre.getVx() - dimensions.getVx(), centre.getVy() + dimensions.getVy(), centre.getVz() + dimensions.getVz());
	glVertex3f(centre.getVx() - dimensions.getVx(), centre.getVy() - dimensions.getVy(), centre.getVz() + dimensions.getVz());
	glVertex3f(centre.getVx() - dimensions.getVx(), centre.getVy() - dimensions.getVy(), centre.getVz() - dimensions.getVz());
	glVertex3f(centre.getVx() - dimensions.getVx(), centre.getVy() + dimensions.getVy(), centre.getVz() - dimensions.getVz());
	glEnd();
}

Vector3D Cube::getDimensions() {
	return dimensions;
}
Vector3D Cube::getCentre() {
	return centre;
}
float Cube::getr() {
	return r;
}
float Cube::getg() {
	return g;
}
float Cube::getb() {
	return b;
}

void Cube::setDimensions(Vector3D dimensions) {
	this->dimensions = dimensions;
}

void Cube::setCentre(Vector3D centre) {
	this->centre = centre;
}

void Cube::setr(float r) {
	this->r = r;
}

void Cube::setg(float g) {
	this->g = g;
}
void Cube::setb(float b) {
	this->b = b;
}



Cube::~Cube()
{
}
