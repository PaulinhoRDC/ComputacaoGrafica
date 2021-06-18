#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h> 
#include <stdio.h>
using namespace std;
#define _USE_MATH_DEFINES
#include <math.h>

string fileName;


//converte para string as coordenadas x,y,z é uma linha no ficheiro .3d
string converte(float x, float y, float z) {

	return to_string(x) + " " + to_string(y) + " " + to_string(z);

}

//escreve os pontos do plano no ficheiro 
void drawPlano(float dimensao) {

	fstream(file);
	file.open("../Engine/3dFiles/" + fileName, fstream::out); //abre ficheiro para escrita
	if (file.is_open()) {

		float aux = dimensao / 2;

		int vertices = 6;
		file << to_string(vertices) << endl;


		file << converte(aux, 0.0, aux) << endl;
		file << converte(aux,0.0,-aux) << endl;
		file << converte(-aux,0.0,-aux) << endl;

		file << converte(-aux, 0.0, -aux) << endl;
		file << converte(-aux, 0.0, aux) << endl;
		file << converte(aux, 0.0, aux) << endl;


		file.close();
	}
	else { cout << "Nao se conseguiu abrir o ficheiro." << endl; }

	
}


//escreve os pontos da box  no ficheiro 
void drawBox(float x, float y, float z, int div) {

	float pX = (float)x / div;
	float pY = (float)y / div;
	float pZ = (float)z / div;

	x = x / 2;
	z = z / 2;

	fstream(file);
	file.open("../Engine/3dFiles/" + fileName, fstream::out); //abre ficheiro para escrita

	if (file.is_open()) {
		int vertices = 6 * 2 * div * div * 3;
		file << to_string(vertices) << endl;
		for (int i = 0; i < div; i++) {
			for (int j = 0; j < div; j++) {

				


				//base
				file << converte(-x + (i * pX), 0.0f, z - (j * pZ)) << endl;
				file << converte(-x + (i * pX), 0.0f, z - (j * pZ) - pZ) << endl;
				file << converte(-x + (i * pX) + pX, 0.0f, z - (j * pZ) - pZ) << endl;

				file << converte(-x + (i * pX), 0.0f, z - (j * pZ)) << endl;
				file << converte(-x + (i * pX) + pX, 0.0f, z - (j * pZ) - pZ) << endl;
				file << converte(-x + (i * pX) + pX, 0.0f, z - (j * pZ)) << endl;

				//face cima
				file << converte(-x + (i * pX), y, -z + (j * pZ)) << endl;
				file << converte(-x + (i * pX), y, -z + (j * pZ) + pZ) << endl;
				file << converte(-x + (i * pX) + pX, y, -z + (j * pZ) + pZ) << endl;

				file << converte(-x + (i * pX), y, -z + (j * pZ)) << endl;
				file << converte(-x + (i * pX) + pX, y, -z + (j * pZ) + pZ) << endl;
				file << converte(-x + (i * pX) + pX, y, -z + (j * pZ)) << endl;

				//face trás
				file << converte(-x + (i * pX) + pX, j * pY, -z) << endl;
				file << converte(-x + (i * pX), j * pY, -z) << endl;
				file << converte(-x + (i * pX) + pX, (j * pY) + pY, -z) << endl;

				file << converte(-x + (i * pX), j * pY, -z) << endl;
				file << converte(-x + (i * pX), (j * pY) + pY, -z) << endl;
				file << converte(-x + (i * pX) + pX, j * pY + pY, -z) << endl;

				//face frontal
				file << converte(-x + (i * pX), y - (j * pY), z) << endl;
				file << converte(-x + (i * pX), y - (j * pY) - pY, z) << endl;
				file << converte(-x + (i * pX) + pX, y - (j * pY) - pY, z) << endl;

				file << converte(-x + (i * pX), y - (j * pY), z) << endl;
				file << converte(-x + (i * pX) + pX, y - (j * pY) - pY, z) << endl;
				file << converte(-x + (i * pX) + pX, y - (j * pY), z) << endl;

				//face esquerda
				file << converte(-x, y - (i * pY), -z + (j * pZ)) << endl;
				file << converte(-x, y - (i * pY) - pY, -z + (j * pZ)) << endl;
				file << converte(-x, y - (i * pY) - pY, -z + (j * pZ) + pZ) << endl;

				file << converte(-x, y - (i * pY), -z + (j * pZ)) << endl;
				file << converte(-x, y - (i * pY) - pY, -z + (j * pZ) + pZ) << endl;
				file << converte(-x, y - (i * pY), -z + (j * pZ) + pZ) << endl;

				//face direita

				file << converte(x, y - (i * pY), z - (j * pZ)) << endl;
				file << converte(x, y - (i * pY) - pY, z - (j * pZ)) << endl;
				file << converte(x, y - (i * pY) - pY, z - (j * pZ) - pZ) << endl;

				file << converte(x, y - (i * pY), z - (j * pZ)) << endl;
				file << converte(x, y - (i * pY) - pY, z - (j * pZ) - pZ) << endl;
				file << converte(x, y - (i * pY), z - (j * pZ) - pZ) << endl;

			}
		}

		file.close();
	}
	else { cout << "Nao se conseguiu abrir o ficheiro." << endl; }
}



//escreve os pontos do cone no ficheiro 
void drawCone(float radius, float height, float slices, float stacks) {

	float angulo = (float)2 * M_PI / slices;
	float alturaStack = height / stacks;
	float alpha2;
	float alpha1;
	float alturaCima;
	float alturaBaixo;
	float raio2 = radius;
	float raio2ant;
	float angulo2;

	fstream(file);
	file.open("../Engine/3dFiles/" + fileName, fstream::out); //abre ficheiro para escrita
	if (file.is_open()) {
		int vertices = (slices * 3) + slices * (3 + 6 * (stacks - 1));
		file << to_string(vertices) << endl;

	for (int j = 1; j <= stacks; j++) {

			alturaCima = alturaStack * j;
			raio2 = raio2 - (radius / stacks);

			for (int i = 1; i <= slices; i++) {

				alpha1 = angulo * i;
				alpha2 = alpha1 + angulo;

				// stack 1
				if (j == 1) {


					//base
				
					file << converte(0.0f, 0.0f, 0.0f) << endl;
					file << converte(radius * sin(alpha2), 0, radius * cos(alpha2)) << endl;
					file << converte(radius * sin(alpha1), 0, radius * cos(alpha1)) << endl;
				

					// lados

					file << converte(radius * sin(alpha2), 0, radius * cos(alpha2)) << endl;
					file << converte(raio2 * sin(alpha2), alturaCima, raio2 * cos(alpha2)) << endl;
					file << converte(radius * sin(alpha1), 0, radius * cos(alpha1)) << endl;


					file << converte(radius * sin(alpha1), 0, radius * cos(alpha1)) << endl;
					file << converte(raio2 * sin(alpha2), alturaCima, raio2 * cos(alpha2)) << endl;
					file << converte(raio2 * sin(alpha1), alturaCima, raio2 * cos(alpha1)) << endl;



				}

				else if (j != stacks) {


					file << converte(raio2ant * sin(alpha2), alturaBaixo, raio2ant * cos(alpha2)) << endl;
					file << converte(raio2 * sin(alpha2), alturaCima, raio2 * cos(alpha2)) << endl;
					file << converte(raio2ant * sin(alpha1), alturaBaixo, raio2ant * cos(alpha1)) << endl;


					file << converte(raio2ant * sin(alpha1), alturaBaixo, raio2ant * cos(alpha1)) << endl;
					file << converte(raio2 * sin(alpha2), alturaCima, raio2 * cos(alpha2)) << endl;
					file << converte(raio2 * sin(alpha1), alturaCima, raio2 * cos(alpha1)) << endl;

				}


				else {

					file << converte(raio2ant * sin(alpha2), alturaBaixo, raio2ant * cos(alpha2)) << endl;
					file << converte(0, alturaCima, 0) << endl;
					file << converte(raio2ant * sin(alpha1), alturaBaixo, raio2ant * cos(alpha1)) << endl;

				}

			}

			alturaBaixo = alturaCima;
			raio2ant = raio2;
		}

		file.close();
	}
	else { cout << "Nao se conseguiu abrir o ficheiro." << endl; }

}


//escreve os pontos da esfera no ficheiro 
void drawSphere(float radius, int slices, int stacks) {


	float alfa = (2 * M_PI) / slices;//fatias
	float beta = M_PI / stacks;//camadas

	fstream(file);
	file.open("../Engine/3dFiles/" + fileName, fstream::out);  //abre ficheiro para escrita
	if (file.is_open()) {

		int vertices = slices * (2 + 2 * (stacks-2)) * 3;
		file << to_string(vertices) << endl;

		for (int i = 0; i < slices; i++) {
			float alfa1 = alfa * i;
			//cima


			file << converte(radius * cos(M_PI / 2) * sin(alfa1), radius * sin(M_PI / 2), radius * cos(M_PI / 2) * cos(alfa1)) << endl;
			file << converte(radius * cos(M_PI / 2 - beta) * sin(alfa1), radius * sin(M_PI / 2 - beta), radius * cos(M_PI / 2 - beta) * cos(alfa1)) << endl;
			file << converte(radius * cos(M_PI / 2 - beta) * sin(alfa1 + alfa), radius * sin(M_PI / 2 - beta), radius * cos(M_PI / 2 - beta) * cos(alfa1 + alfa)) << endl;

			//baixo


			file << converte(radius * cos(-M_PI / 2) * sin(alfa1), sin(-M_PI / 2) * radius, radius * cos(-M_PI / 2) * cos(alfa1)) << endl;
			file << converte(radius * cos((-M_PI / 2) + beta) * sin(alfa1 + alfa), radius * sin((-M_PI / 2) + beta), radius * cos((-M_PI / 2) + beta) * cos(alfa1 + alfa)) << endl;
			file << converte(radius * cos((-M_PI / 2) + beta) * sin(alfa1), radius * sin((-M_PI / 2) + beta), radius * cos((-M_PI / 2) + beta) * cos(alfa1)) << endl;


			for (int j = 1; j < stacks - 1; j++) {
				float beta1 = M_PI / 2 - (j * beta);

				file << converte(radius * cos(beta1) * sin(alfa1), radius * sin(beta1), radius * cos(beta1) * cos(alfa1)) << endl;
				file << converte(radius * cos(beta1 - beta) * sin(alfa1), radius * sin(beta1 - beta), radius * cos(beta1 - beta) * cos(alfa1)) << endl;
				file << converte(radius * cos(beta1) * sin(alfa1 + alfa), radius * sin(beta1), radius * cos(beta1) * cos(alfa1 + alfa)) << endl;


			
				file << converte(radius * cos(beta1 - beta) * sin(alfa1), radius * sin(beta1 - beta), radius * cos(beta1 - beta) * cos(alfa1)) << endl;
				file << converte(radius * cos(beta1 - beta) * sin(alfa1 + alfa), radius * sin(beta1 - beta), radius * cos(beta1 - beta) * cos(alfa1 + alfa)) << endl;
				file << converte(radius * cos(beta1) * sin(alfa1 + alfa), radius * sin(beta1), radius * cos(beta1) * cos(alfa1 + alfa)) << endl;

			}
		}

	file.close();
	}
	else { cout << "Nao se conseguiu abrir o ficheiro." << endl; }


}


//na main comparamos sempre o primeiro argumento com as várias formas possiveis de gerar
int  main(int argc, char* argv[]) {


	
	if (strcmp(argv[1], "plane") == 0 && argc == 4) {
		float dimensao = stof(argv[2]);
		fileName = argv[3];
		drawPlano(dimensao);
		return 0;
	}


	if (strcmp(argv[1], "box") == 0 && argc > 5) {
		float x = stof(argv[2]);
		float y = stof(argv[3]);
		float z = stof(argv[4]);
		

		//caso nao tenha mandado os edges desenha com 1
		if (argc == 6) { fileName = argv[5]; drawBox(x, y, z, 1);}

		//caso contrario
		if (argc == 7) { float edges = stof(argv[5]); fileName = argv[6]; drawBox(x, y, z, edges);}
		
		return 0;
	}



	if (strcmp(argv[1], "cone") == 0 && argc == 7) {
		float radius = stof(argv[2]);
		float height = stof(argv[3]);
		int slices = atoi(argv[4]);
		int stack = atoi(argv[5]);
		fileName = argv[6];

		drawCone(radius, height, slices, stack);
		return 0;
	}


	if (strcmp(argv[1], "sphere") == 0 && argc == 6) {
		float radius = stof(argv[2]);
		int slices = atoi(argv[3]);
		int stack = atoi(argv[4]);
		fileName = argv[5];

		drawSphere(radius, slices, stack);
		return 0;
	}



	else{
		cout << "Argumentos insuficientes!" << endl;
		return 0;
	}

	

}