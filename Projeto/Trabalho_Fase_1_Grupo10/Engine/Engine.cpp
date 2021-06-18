#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define GL_SILENCE_DEPRECATION

#include <GLUT/glut.h>
#include <list>


#include <iostream>
#include <fstream>
#include <string>
#include <string.h> 
#include <stdio.h>


#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>

using namespace tinyxml2;
using namespace std;

float camX = 1, camY = 1, camZ = 20;  //posicao x,y,z da camara
int alpha = 0, beta = 0, r = 20;      // angulos e raio da camara
int xInicial, yInicial, modoRato = 0;   //posicoes anteriores da camara e modo da mesma

bool eixos = true;   //eixos
int tipo = GL_LINE;   //tipo de desenho linhas, pontos ou fill
float v = 0.0f, g = 1.0f, b = 0.0f; //cores do desenho



//classe ponto que contem as coordenadas x,y,z de cada ponto junto com os getters e setters
class Ponto {
	float x;
	float y;
	float z;

public:


	Ponto() {
		x = 0;
		y = 0;
		z = 0;
	}

	Ponto(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	float getZ() {
		return z;
	}

	void setX(float a) {
		x = a;
	}

	void setY(float b) {
		y = b;
	}

	void setZ(float c) {
		z = c;
	}
};


//lista de pontos onde vao ser guardados em mem�ria todos os pontos do desenho
list<Ponto> pontosLista;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45, ratio, 1, 1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}




//funcao desenha
//pega na lista de pontos e vai percorrer a mesma usando um iterador, a cada 3 pontos desenha um triangulo
//desta forma, cada itera��o do ciclo for 3 pontos e um triangulo sao desenhados avan�ando assim o iterador em 3 posi�oes
void draw() {

	for (auto it = pontosLista.begin(); it != pontosLista.end(); ) {
		glBegin(GL_TRIANGLES);
		glVertex3f(it->getX(), it->getY(), it->getZ());  
		++it;
		glVertex3f(it->getX(), it->getY(), it->getZ());
		++it;
		glVertex3f(it->getX(), it->getY(), it->getZ());
		++it;
		glEnd();
	}

}


//funcao que desenha os eixos
void eixo() {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}



void renderScene(void) {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//modo de desenho, come�a com linhas por defeito
	glPolygonMode(GL_FRONT_AND_BACK, tipo);
	

	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);


	//desenhar eixos caso seja true
	if (eixos) {
		eixo();
	}

	//cor do desenho
	glColor3f(v, g, b);

	//desenhar a figura
	draw();

	glutSwapBuffers();

}


//funcao que processa as teclas do rato e muda as coordenadas, angulos ou raio da camara com base nisso
void processMouseButtons(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		xInicial = x;
		yInicial = y;
		if (button == GLUT_LEFT_BUTTON)		modoRato = 1; //modo rodar camara
		else if (button == GLUT_RIGHT_BUTTON)  modoRato = 2; //modo aproximar ou afastar camara
		else modoRato = 0;
	}
	else if (state == GLUT_UP) {
		if (modoRato == 1) { //muda alpha e beta pois este modo muda a posicao
			alpha += (x - xInicial); 
			beta += (y - yInicial);
		}
		else if (modoRato == 2) { //muda raio pois este modo muda o zoom
			r -= y - yInicial;
			if (r < 3) r = 3.0;
		}
		modoRato = 0;
	}
}


//funcao que faz a movimentacao das variaveis da camara
void processMouseMotion(int x, int y)
{
	int xAux, yAux;
	int alphaAux, betaAux;
	int rAux;

	if (!modoRato) return;

	xAux = x - xInicial;
	yAux = y - yInicial;

	if (modoRato == 1) { 

		alphaAux = alpha + xAux;
		betaAux = beta + yAux;
		if (betaAux > 85.0) betaAux = 85.0;
		else if (betaAux < -85.0) betaAux = -85.0;
		rAux = r;
	}
	else if (modoRato == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - yAux;
		if (rAux < 3) rAux = 3;
	}
	//nova posicao x,y,z da camara
	camX = rAux * sin(-alphaAux * M_PI / 180.0) * cos(betaAux * M_PI / 180.0);
	camZ = rAux * cos(-alphaAux * M_PI / 180.0) * cos(betaAux * M_PI / 180.0);
	camY = rAux * sin(betaAux * M_PI / 180.0);
}






//funcao que l� cada ficheiro .3d a partir do seu caminho
//preenchendo a lista de pontos com os pontos lidos do ficheiro

void readFile(string caminho3d) {
	string linha;
	vector<string> coordenadas;
	
	//abrir o ficheiro
	ifstream file(caminho3d);
	if (file.is_open()) {
		
		//pega na primeira linha que � o n�mero de v�rtices ou seja numero de linhas a ler (1 vertice por linha)
		getline(file, linha);                   
		int nLinhas = atoi(linha.c_str());        
		for (int i = 1; i <= nLinhas; i++) {
			getline(file, linha);     //pegar na linha atual
			stringstream ss(linha);		
			vector<string> result{
				istream_iterator<string>(ss), {}    //separar a linha nos espa�os e guardar como array de strings em result
			};
			pontosLista.push_back(Ponto(stof(result[0]), stof(result[1]), stof(result[2]))); //adiciona o Ponto lido � lista de pontos
		}
	}
	else { cout << "Erro ao ler o ficheiro .3d" << endl; }
}


//funcao que le o ficheiro.xml da pasta ../xml/ 
void readXML(string file) {
	XMLDocument xml;
	string s;
	if (!(xml.LoadFile(("../xml/" + file).c_str()))) {  //condicao que carrega o ficheiro e testa se � v�lido
		XMLElement* elemento = xml.FirstChildElement("scene")->FirstChildElement("model");    //pega no elemento scene do xml
		while (elemento != nullptr) {                  //avan�a at� ser null
			readFile(elemento->Attribute("file"));       //pega no atributo file e vai ler-lo
			elemento = elemento->NextSiblingElement();     //avan�a para o proximo
		}
	}
	else {
		cout << "Erro ao ler o xml" << endl;
	}
	return;
}


//funcao que d� fun��o �s teclas premidas
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'e') {
		eixos = !eixos;
	}
	if (key == 'f') {
		tipo = GL_FILL;
	}
	if (key == 'l') {
		tipo = GL_LINE;
	}
	if (key == 'p') {
		tipo = GL_POINT;
	}

	if (key == 'r') {
		v = 1.0f;
		g = 0.0f;
		b = 0.0f;

	}
	if (key == 'g') {
		v = 0.0f;
		g = 1.0f;
		b = 0.0f;
	}
	if (key == 'b') {
		v = 0.0f;
		g = 0.0f;
		b = 1.0f;
	}




	glutPostRedisplay();

}




int main(int argc, char* argv[]) {

	if (argc == 2) {
		readXML(argv[1]);
	}
	else {
		//l� sempre o "ficheiro.xml", este tem que estar em ../xml/
		readXML("ficheiro.xml");
	}



	

	// inicialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Phase 1");

	// callback registration 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	// mouse callbacks
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	glutKeyboardFunc(keyboard);

	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle 
	glutMainLoop();
}