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
bool doublejump = false;
int t = 0;



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

// Fonction de dessin d'un bonhomme de neige
void drawChick(Vector3D translate, float angle, Vector3D rotaxe) {
	glTranslatef(translate.getVx(), translate.getVy(), translate.getVz());
	glRotatef(angle, rotaxe.getVx(), rotaxe.getVy(), rotaxe.getVz());
	// On va dessiner en blanc
	glColor3f(0.8f, 0.7f, 0.1f);

	// Corps du bonhomme de neige : une sphere
	glTranslatef(0.0f, 0.5f, 0.0f);
	glutSolidSphere(0.5f, 20, 20);

	// Tete de bonhomme : une sphere
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
		   // AJOUTER LE POKE
		futur.setVx(forwardView.getVx()*deltaMove*0.5 + forwardView.getVz()*deltaStrafe*0.5);
		futur.setVz(forwardView.getVz()*deltaMove*0.5 - forwardView.getVx()*deltaStrafe*0.5);
		if (!grounded) {
			if (futur.getVy() >= -20) {
				futur -= Vector3D(0, 0.02f, 0);

			}
		}
		else {
			if (futur.getVy() < 0) {
				futur.setVy(0);
			}
		}


		//footPos = camPos - Vector3D(0, 1, 0);
		grounded = false;


		for (int i = 0; i < listcubes.size(); i++) {
			futur = listcubes[i]->poke(camPos, futur, &grounded);
		}
		//cout<<footPos.getVy()<<endl;
		//cout << grounded << endl;

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

	/*
	cube1.affiche();
	cube2.affiche();
	cube3.affiche();
	cube4.affiche();
	cube5.affiche();
	cube6.affiche();
	cube7.affiche();*/

	for (int i = 0; i < listcubes.size(); i++) {
		listcubes[i]->affiche();
	}

	t += 1;
	// On dessine un canard =)
	drawChick(Vector3D(35, 41, 15), 0, Vector3D(0, 1, 0));

	// On dessine 36 bonhommes de neige
	/*   for(int i = -3; i < 3; i++) {
	for(int j=-3; j < 3; j++) {
	glPushMatrix();
	glTranslatef(i*10.0,0,j * 10.0);
	drawSnowMan();
	glPopMatrix();
	}
	}
	*/
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
			futur += Vector3D(0, 0.5f, 0);
		}
		if (doublejump) {
			futur += Vector3D(0, 0.5f, 0);
			doublejump = false;
		}
		break;
	case 'a'://Meh:courir/marcher bof-bof
	case 'A':
		runspeed = 1.5 - runspeed;
		break;
		// F pour activer/desactiver le mode "fly"
	case 'f':
	case 'F':
		flyMode = !flyMode;
		// On force la camera a revenir sur le sol :)

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
	case 'a':
	case 'A'://Meh: courir/marcher bof-bof
		break;

	}
}


// Fonction de gestion du clavier (touche speciale appuyee)
void specialKeyDown(int key, int xx, int yy) {

	switch (key) {
		// Deplacement avance/recul
	case GLUT_KEY_UP:

		break;
	case GLUT_KEY_DOWN:

		break;

		// Strafe a gauche/droite
	case GLUT_KEY_RIGHT:

		break;
	case GLUT_KEY_LEFT:

		break;
	default:
		break;
	}

}

// Fonction de gestion du clavier (touche speciale relachee)
void releaseSpecialKey(int key, int x, int y) {

	switch (key) {
		// On remet le delate deplacement a 0
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:

		break;

		// On remet le delta strafe a 0
	case GLUT_KEY_RIGHT:
	case GLUT_KEY_LEFT:

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
		forwardView.setVx(cos(deltaPhi + anglePhi) * sin(deltaTheta + angleTheta)); //rho = 1
		forwardView.setVy(-sin(deltaPhi + anglePhi));
		forwardView.setVz(-cos(deltaPhi + anglePhi) * cos(deltaTheta + angleTheta));
		// normalisation du vecteur forward
		forwardView.normalize();

		// Up ne change pas
		// et right est le cross product entre up et forward
		rightView = forwardView.crossProduct(upWorld);


		// Mettre a jour la cible = point "vise" par la camera
		targetPos = camPos + forwardView;





		// Pour le mode "FPS" on force les deplacements a avoir lieu sur le plan de la camera !
		// ise a jour des vecteurs forwardMove et rightMove

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

// tentative de creation de liste
vector <Cube*> creatlist(vector <Cube*> listcubes) {

	Platform cube1 = Platform::Platform(Vector3D(0, -1, 0), Vector3D(5, 1, 5));

	listcubes.push_back(&cube1);

	//cout << cube1.getCentre() << listcubes[listcubes.size() - 1]->getCentre() << endl;
	return listcubes;

}


/*// Le main*/
int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
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
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(releaseSpecialKey);

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

	// ne fonctionne pas avec le if true
	//if (true) {
		// LEVEL 1
		Platform cube1 = Platform::Platform(Vector3D(0, -1, 0), Vector3D(5, 1, 5));
		Trumpoline cube2 = Trumpoline::Trumpoline(Vector3D(15, 19, 0), Vector3D(5, 1, 5));
		Platform cube3 = Platform::Platform(Vector3D(35, 40, 15), Vector3D(5, 1, 5));
		Platform cube4 = Platform::Platform(Vector3D(0, 30, 0), Vector3D(5, 1, 5));
		Platform cube5 = Platform::Platform(Vector3D(15, 35, -15), Vector3D(5, 1, 5));
		Jumpoline cube6 = Jumpoline::Jumpoline(Vector3D(30, 19, 0), Vector3D(5, 1, 5), 0.7f);
		Elevator cube7 = Elevator::Elevator(Vector3D(0, 8, 15), Vector3D(5, 8, 5), 0.1f);
		listcubes.push_back(&cube1);
		listcubes.push_back(&cube2);
		listcubes.push_back(&cube3);
		listcubes.push_back(&cube4);
		listcubes.push_back(&cube5);
		listcubes.push_back(&cube6);
		listcubes.push_back(&cube7);
	//}



	// listcubes = creatlist(listcubes);    //marche pas encore


	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
//*/

/*//Le test
int main(int argc, char **argv) {
Platform cube1 = Platform::Platform(Vector3D(0, -1, 0), Vector3D(5, 1, 5));
listcubes.push_back(&cube1);
listcubes = creatlist(listcubes);
int potato = 0;
while (potato <= listcubes.size()) {
cout << listcubes[potato]->getCentre() << endl;
cin >> potato;
}



return 1;
}
//*/