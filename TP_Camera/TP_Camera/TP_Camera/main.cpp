//
//  main.cpp
//  testCamera
//
//  Created by Jean-Marie Normand on 29/09/2014.
//  Copyright (c) 2014 Jean-Marie Normand. All rights reserved.
//

#include <Windows.h>

#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include "vector3D.h"
#include "cube.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "typecube.h"
using namespace std;

vector <Cube*> listcubes;
Vector3D goal;


float forward_clavier = 0.0;

// angles de rotation (coordonnees spheriques) pour calculer le vecteur vision de la camera
float angleTheta = 0.0f;
float anglePhi = 0.0f;

// Camera viewing vectors
Vector3D forwardView;
Vector3D rightView;
// On garde le vecteur "up" du monde : 0 1 0
Vector3D upWorld;

// Difference "Fly" vs. "FPS" modes
Vector3D forwardMove;
Vector3D rightMove;

// Camera position
Vector3D camPos;
Vector3D footPos;
Vector3D targetPos;

// Sensibilite de deplacement
float moveSensitivity;
float mouseRotSensitivity;

// Déplacement "Fly" ou "FPS" ?
bool flyMode = false;

// les increments des angles theta et phi
// egales a 0 quand on n'appuie sur aucune touche
float deltaTheta = 0.0f;
float deltaPhi = 0.0f;
float PI = 3.1415;

// increments de deplacement
// remis a 0 quand on appuis sur rien
float deltaMove = 0;
float deltaStrafe = 0.0f;
float runspeed = 0.5f;
Vector3D futur = Vector3D(0, 0, 0);
bool grounded;
bool doublejump = true;
int t = 0;
int lvl = 0;


// coordonnes de la souris au moment du clic gauche
int xOrigin = -1;
int yOrigin = -1;

// Fonction de redimensionnement de la fenetre
void redimensionner(int w, int h) {

	// On evite une division par 0
	// la fenetre ne peut avoir une largeur de 0
	if (h == 0)
		h = 1;

	// Calcul du ratio
	float ratio = (w * 1.0) / h;

	// On passe en mode "matrice de projection"
	glMatrixMode(GL_PROJECTION);

	// on charge la matrice identite
	glLoadIdentity();

	// on definit le viewport pour prendre toute la fenetre
	glViewport(0, 0, w, h);

	// on definit la projection perspective
	gluPerspective(65.0f, ratio, 0.1f, 100.0f);

	// on repasse en mode "matrice modelview"
	glMatrixMode(GL_MODELVIEW);
}

// Fonction de dessin d'un poussin
void drawChick(Vector3D translate, float angle, Vector3D rotaxe) {
	glTranslatef(translate.getVx(), translate.getVy(), translate.getVz());
	glRotatef(angle, rotaxe.getVx(), rotaxe.getVy(), rotaxe.getVz());
	// On va dessiner en jaune
	glColor3f(0.8f, 0.7f, 0.1f);

	// Corps du poussin : une sphere
	glTranslatef(0.0f, 0.5f, 0.0f);
	glutSolidSphere(0.5f, 20, 20);

	// Tete du poussin : une sphere
	glTranslatef(0.0f, 0.5f, 0.5f);
	glutSolidSphere(0.25f, 20, 20);

	// Yeux du poussin : deux spheres noires
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Nez du poussin : un cone orange
	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}



vector <Cube*> creatlist(vector <Cube*> listcubes, int  lvl) {//on rentre un entier et la liste de plate forme, ressort la liste de plateformes correspondant à l'entier entré
	if (lvl == 1) {
		Platform* cube1 = new Platform(Vector3D(0, -1, -15), Vector3D(2.5f, 1, 20));
		listcubes.push_back(cube1);
		goal = Vector3D(0, 0, -40);
		Goal* cgoal = new Goal(goal - Vector3D(0, 1, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cgoal);

	}
	
	else if (lvl == 2) {
		Platform* cube1 = new Platform(Vector3D(0, -1, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cube1);
		Platform* cube2 = new Platform(Vector3D(0, -1, -15), Vector3D(5, 1, 5));
		listcubes.push_back(cube2);
		Platform* cube3 = new Platform(Vector3D(0, 4, -30), Vector3D(5, 1, 5));
		listcubes.push_back(cube3);
		goal = Vector3D(0, 0, -50);
		Goal* cgoal = new Goal(goal - Vector3D(0, 1, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cgoal);
	}
	else if (lvl == 3) {
		Platform* cube1 = new Platform(Vector3D(0, -1, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cube1);
		Jumpoline* cube2 = new Jumpoline(Vector3D(-15 , -1, -15), Vector3D(5, 1, 5), 1.1f);
		listcubes.push_back(cube2);		
		Platform* cube4 = new Platform(Vector3D(0, -1, -15), Vector3D(5, 1, 5));
		listcubes.push_back(cube4);
		goal = Vector3D(0, 15, -30);
		Goal* cgoal = new Goal(goal - Vector3D(0, 1, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cgoal);

	}
	else if (lvl == 4) {
		Platform* cube1 = new Platform(Vector3D(0, -1, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cube1);
		Trumpoline* cube2 = new Trumpoline(Vector3D(0, -1 , -15), Vector3D(5, 1, 5));
		listcubes.push_back(cube2);
		Platform* cube3 = new Platform(Vector3D(-15, 5, -15), Vector3D(5, 1, 5));
		listcubes.push_back(cube3);
		Platform* cube4 = new Platform(Vector3D(15, 10, -15), Vector3D(5, 1, 5));
		listcubes.push_back(cube4);
		Platform* cube5 = new Platform(Vector3D(-15, 15, -15), Vector3D(5, 1, 5));
		listcubes.push_back(cube5);
		Platform* cube6 = new Platform(Vector3D(15, 20, -15), Vector3D(5, 1, 5));
		listcubes.push_back(cube6);
		goal = Vector3D(-15, 26, -15);
		Goal* cgoal = new Goal(goal - Vector3D(0, 1, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cgoal);

	}
	else if (lvl == 5) {
		Platform* cube1 = new Platform(Vector3D(0, -1, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cube1);
		Elevator* cube2 = new Elevator(Vector3D(0, 8, -15), Vector3D(5, 8, 5), 0.1f);
		listcubes.push_back(cube2);
		Elevator* cube3 = new Elevator(Vector3D(0, 24, 0), Vector3D(5, 8, 5), 0.1f);
		listcubes.push_back(cube3);
		goal = Vector3D(0, 32, -15);
		Goal* cgoal = new Goal(goal - Vector3D(0, 1, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cgoal);
	}
	else if (lvl == 6) {
		Platform* cube1 = new Platform(Vector3D(0, -1, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cube1);
		Trumpoline* cube2 = new Trumpoline(Vector3D(15, 19, 5), Vector3D(5, 1, 5));
		listcubes.push_back(cube2);
		Platform* cube4 = new Platform(Vector3D(0, 30, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cube4);
		Platform* cube5 = new Platform(Vector3D(15, 35, -15), Vector3D(5, 1, 5));
		listcubes.push_back(cube5);
		Jumpoline* cube6 = new Jumpoline(Vector3D(30, 19, 0), Vector3D(5, 1, 5), 0.7f);
		listcubes.push_back(cube6);
		Elevator* cube7 = new Elevator(Vector3D(0, 8, 15), Vector3D(5, 8, 5), 0.1f);
		listcubes.push_back(cube7);
		goal = Vector3D(15, 41, 20);
		Goal* cgoal = new Goal(goal - Vector3D(0, 1, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cgoal);
	}
	else if (lvl == 7) {
		Platform* cube0 = new Platform(Vector3D(0, -1, 0), Vector3D(15, 1, 5));
		listcubes.push_back(cube0);
		Platform* cube1 = new Platform(Vector3D(0, -1, 0), Vector3D(5, 1, 15));
		listcubes.push_back(cube1);
		Trumpoline* cube2 = new Trumpoline(Vector3D(0, -5, 0), Vector3D(15, 1, 15));
		listcubes.push_back(cube2);
		Platform* cube3 = new Platform(Vector3D(20, 5, 20), Vector3D(5, 1, 5));
		listcubes.push_back(cube3);
		Platform* cube4 = new Platform(Vector3D(20, 10, -20), Vector3D(5, 1, 5));
		listcubes.push_back(cube4);
		Platform* cube5 = new Platform(Vector3D(-20, 15, -20), Vector3D(5, 1, 5));
		listcubes.push_back(cube5);
		goal = Vector3D(-20, 20, 20);
		Goal* cgoal = new Goal(goal - Vector3D(0, 1, 0), Vector3D(5, 1, 5));
		listcubes.push_back(cgoal);
	}
	else {
		Goal* cube1 = new Goal(Vector3D(0, -1, 0), Vector3D(24, 1, 24));
		listcubes.push_back(cube1);
		Platform* cube2 = new Platform(Vector3D(25, 5, 0), Vector3D(1, 5, 25));
		listcubes.push_back(cube2);
		Platform* cube3 = new Platform(Vector3D(-25, 5, 0), Vector3D(1, 5, 25));
		listcubes.push_back(cube3);
		Platform* cube4 = new Platform(Vector3D(0, 5, 25), Vector3D(25, 5, 1));
		listcubes.push_back(cube4);
		Platform* cube5 = new Platform(Vector3D(0, 5, -25), Vector3D(25, 5, 1));
		listcubes.push_back(cube5);
goal = Vector3D(0, -200, 0);//on ne pourra jamais l'atteindre, c'est le niveau de fin

	}
	return listcubes;

}


// Fonction de gestion du deplacement de la camera
void cameraMovement(float dM, float dS) {
	// est-on en "fly" mode ou non ?
	if (flyMode) {
		camPos += Vector3D(forwardView.getVx()*deltaMove*0.5, forwardView.getVy()*deltaMove*0.5, forwardView.getVz()*deltaMove*0.5);
		camPos += Vector3D(forwardView.getVz()*deltaStrafe*0.5, 0, -forwardView.getVx()*deltaStrafe*0.5);
		targetPos += Vector3D(forwardView.getVx()*deltaMove*0.5, forwardView.getVy()*deltaMove*0.5, forwardView.getVz()*deltaMove*0.5);
		targetPos += Vector3D(forwardView.getVz()*deltaStrafe*0.5, 0, -forwardView.getVx()*deltaStrafe*0.5);


	}
	else { // FPS mode

		futur.setVx(forwardView.getVx()*deltaMove*0.5 + forwardView.getVz()*deltaStrafe*0.5);
		futur.setVz(forwardView.getVz()*deltaMove*0.5 - forwardView.getVx()*deltaStrafe*0.5);
		if (!grounded) {// si on est pas sur un sol, on tombe de plus en plus vite avec une vitesse maximale de 20
			if (futur.getVy() >= -20) {
				futur -= Vector3D(0, 0.02f, 0);

			}
		}



		//footPos = camPos - Vector3D(0, 1, 0);
		grounded = false;//on n'est pas sur un sol par défaut 


		for (int i = 0; i < listcubes.size(); i++) {//on vérifie les intéractions avec tous les cubes présents
			futur = listcubes[i]->poke(camPos, futur, &grounded);
		}
		//cout << camPos.getVy() << endl;
		//cout << grounded << endl;
		if ((camPos - goal).length() < 1.4f) {//si on attein l'objectif, on nous renvoie à la case départ, on supprime le niveau puis on passe au niveau suivant.
			camPos = Vector3D(0, 1.1, 0);
			futur = Vector3D(0, 0, 0);
			listcubes.clear();
			lvl += 1;
			listcubes = creatlist(listcubes, lvl);

		}
		//cout << (camPos - goal).length() << endl;
		//cout << goal << endl;
		if (camPos.getVy() < -100) {//si on tombe trop bas, retour à la case départ
			camPos = Vector3D(0, 1.1, 0);
			futur = Vector3D(0, 0, 0);
		}
		camPos += futur;
		targetPos += futur;
	}
}

// Mettre a jour la cible



// fonction d'affichage de notre scene 3D

void affichageScene() {

	// On gere le deplacement de la camera
	cameraMovement(deltaMove, deltaStrafe);

	// On efface les tampons de couleur et de profondeur
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// On passe en matice modelview
	glMatrixMode(GL_MODELVIEW);

	// on charge la matrice identite
	glLoadIdentity();

	// on definit la position de la camera et ou elle regarde
	gluLookAt(camPos.getVx(), camPos.getVy(), camPos.getVz(),
		targetPos.getVx(), targetPos.getVy(), targetPos.getVz(),
		upWorld.getVx(), upWorld.getVy(), upWorld.getVz());


	for (int i = 0; i < listcubes.size(); i++) {//on affiche tous les cubes du niveau
		listcubes[i]->affiche();
	}

	drawChick(goal, 0, Vector3D(0, 1, 0));//on affiche le poussin



	// on echange les tampons d'affichage
	glutSwapBuffers();
}

// Fonction de gestion du clavier (touche enfoncee)

void clavier(unsigned char key, int xx, int yy) {

	// Quelle touchea ete appuyee ?
	switch (key) {
		// Q et S on strafe
	case 'q':
	case 'Q':
		deltaStrafe = 1.0*runspeed;
		break;
	case 'd':
	case 'D':
		deltaStrafe = -1.0*runspeed;
		break;

		// Z et S avance/recule
	case 'z':
	case 'Z':
		deltaMove = 1.0*runspeed;
		break;
	case 's':
	case 'S':
		deltaMove = -1.0*runspeed;
		break;
	case 32:// barre d'espace
		if (grounded) {
			futur = Vector3D(0, 0.5f, 0);
		}
		if (doublejump && !grounded) {
			futur = Vector3D(0, 0.5f, 0);
			doublejump = false;
		}
		break;
		// F pour activer/desactiver le mode "fly"
	case 'f':
	case 'F':
		flyMode = !flyMode;
		futur = Vector3D(0, 0, 0);//ainsi on ne conserve pas sa vitesse pré flymode

		break;

		// ESCAPE on termine l'application
	case 27:
		exit(0);
		break;
	}

}

// Fonction de gestion du clavier (touche relachee)
void clavierUp(unsigned char key, int x, int y) {

	// Que faire uand une touche est relachee
	switch (key) {

		// On arrete de strafer
	case 'q':
	case 'd':
	case 'Q':
	case 'D':
		deltaStrafe = 0;
		break;

		// On arrete d'avance/reculer
	case 'z':
	case 's':
	case 'Z':
	case 'S':
		deltaMove = 0;
		break;

	}
}




// Fonction de gestion du deplacement de la souris
void deplacementSouris(int x, int y) {

	// On ne fait quelque chose que si l'utilisateur
	// a deja clique quelque part avec le bouton gauche
	if (xOrigin >= 0 || yOrigin >= 0) {

		deltaTheta = mouseRotSensitivity * (x - xOrigin);
		deltaPhi = mouseRotSensitivity * (y - yOrigin);
		if (!flyMode) {// il y a des limites à jusqu'où on lève la tête
			if (deltaPhi >= 1) {
				deltaPhi = 1;
			}
			if (deltaPhi <= -1) {
				deltaPhi = -1;
			}
		}
		else {// on est en flymode, mince aux limites!!!
			if (deltaPhi >= PI / 2) {
				deltaPhi = PI / 2;
			}
			if (deltaPhi <= -PI / 2) {
				deltaPhi = -PI / 2;
			}
		}
		// Calcul du nouveau vecteur vision :
		// En se basant sur les coordonnes spheriques
		forwardView.setVx(cos(deltaPhi + anglePhi) * sin(deltaTheta + angleTheta));
		forwardView.setVy(-sin(deltaPhi + anglePhi));
		forwardView.setVz(-cos(deltaPhi + anglePhi) * cos(deltaTheta + angleTheta));
		// normalisation du vecteur forward
		forwardView.normalize();

		// Up ne change pas
		// et right est le cross product entre up et forward
		rightView = forwardView.crossProduct(upWorld);


		// Mettre a jour la cible = point "vise" par la camera
		targetPos = camPos + forwardView;

	}
}

// Fonction de gestion des clics souris
void clicSouris(int button, int state, int x, int y) {

	// On ne fait quelque chose que sur le bouton gauche de la souris
	if (button == GLUT_LEFT_BUTTON) {

		// si on relache le bouton on met a jour les angles theta et phi
		// et on dit que l'on a pas clique
		if (state == GLUT_UP) {
			angleTheta += deltaTheta;
			anglePhi += deltaPhi;
			xOrigin = 0;
			yOrigin = 0;
		}
		else {// state = GLUT_DOWN
			  // si l'on a clique sur le bouton gauche
			  // on garde les positions de la souris au moment du clic gauche
			xOrigin = x;
			yOrigin = y;
		}
	}
}




/// Le main
int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1500, 900);
	glutCreateWindow("FPS Camera");

	// enregistrement des callbacks d'affichage
	// de redimensionnement et d'idle
	glutDisplayFunc(affichageScene);
	glutReshapeFunc(redimensionner);
	glutIdleFunc(affichageScene);

	// pour que l'on puisse rester appuye sur les touches
	glutIgnoreKeyRepeat(1);

	// Declaration des callbacks clavier
	glutKeyboardFunc(clavier);
	glutKeyboardUpFunc(clavierUp);
	// declarationdes callbacks souris
	glutMouseFunc(clicSouris);
	glutMotionFunc(deplacementSouris);

	// on active le tampon de profondeur
	glEnable(GL_DEPTH_TEST);

	// on initialise la position de la camera
	camPos = Vector3D(0, 2, 0);

	// on initialise les vecteurs 'view'
	forwardView = Vector3D(0, 0, -1);
	upWorld = Vector3D(0, 1, 0);
	rightView = Vector3D(1, 0, 0);

	// Pour le FPS mode
	forwardMove = Vector3D(0, 0, -1);
	rightMove = Vector3D(1, 0, 0);

	// on initialise la cible a partir de la camera et du vecteur vision
	targetPos = camPos + forwardView;

	// Initialisation des "constantes"
	moveSensitivity = 0.1f;
	mouseRotSensitivity = 0.01f;

	
	//cin >> lvl;
	listcubes = creatlist(listcubes, 1);   

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}