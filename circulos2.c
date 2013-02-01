//============================================================================
// Name        : circulos2.c
// Author      : manuel
// Version     :
// Copyright   : mi copyright notice
// Description : Bobinas polywell, Ansi-style
//============================================================================
/*
 * circulo2.c
 *
 *  Created on: 31-oct-2010
 *      Author: manuel
 */
#include <math.h>
#include <stdio.h>

#define TRUE 1
#define FALSE !TRUE

/** escribe en puntosBobinaXY_0soloxyz.txt las coordenadas de los puntos de la bobina en el plano XY
 *  con centro (rx, ry, z) y radio r
 *  SI ES LA PAREJA z=0.3 si no, z=0
 * @param rx
 * @param ry
 * @param pareja
 * @param r
 * @return void.
 */
void BobinaXY(double rx, double ry, int pareja, float r) {

	double x, y, z = pareja ? 0.6 : 0;
	double theta = 0;//angulo


	FILE * pFicherosoloxy0 = NULL;
	FILE * pFicherosoloxyz = NULL;
	if (!pareja){
		pFicherosoloxy0 = fopen("puntosBobinaXY_0soloxyz.txt", "w");
		for (theta; theta < (2 * M_PI)-M_PI/180 ; theta +=M_PI/180) {//you can play with the value to be added to theta
				x = rx +sin(theta) * r;
				y = ry -sin(theta + (M_PI / 2)) * r;
				fprintf(pFicherosoloxy0, "%-10.10E %-10.10E %-10.10E %4.2f\n", x, y, z,1.00);
		}
		x = rx + sin(theta) * r;
		y = ry - sin(theta + (M_PI / 2)) * r;
		fprintf(pFicherosoloxy0, "%-10.10E %-10.10E %-10.10E %4.2f\n", x, y, z,0.00);
		fclose(pFicherosoloxy0);

	}else{//ES LA PAREJA
		pFicherosoloxyz = fopen("puntosBobinaXY_Zsoloxyz.txt", "w");

	for (theta; theta < (2 * M_PI)-M_PI/180 ; theta +=M_PI/180) {//you can play with the value to be added to theta
			x = rx + sin(theta) * r;
			y = ry + sin(theta + (M_PI / 2)) * r;
			fprintf(pFicherosoloxyz, "%-10.10E %-10.10E %-10.10E %4.2f\n", x, y, z,1.00);
	}
		x = rx + sin(theta) * r;
		y = ry + sin(theta + (M_PI / 2)) * r;
		fprintf(pFicherosoloxyz, "%-10.10E %-10.10E %-10.10E %4.2f\n", x, y, z,0.00);
		fclose(pFicherosoloxyz);
	}

}
/** escribe en puntosBobinaXZ_0soloxyz.txt las coordenadas de los puntos de la bobina en el plano XZ
 *  con centro (rx, y, rz) y radio r
 *  SI ES LA PAREJA y=0.3 si no, y=0
 * @param rx
 * @param rz
 * @param pareja
 * @param r
 * @return void.
 */
void BobinaXZ(double rx, double ry, int pareja, float r) {

	double x, y, z = pareja ? 0.6 : 0;
	double theta = 0;//angulo


	FILE * pFicherosoloxy0 = NULL;
	FILE * pFicherosoloxyz = NULL;
	if (!pareja) {
		pFicherosoloxy0 = fopen("puntosBobinaXZ_0soloxyz.txt", "w");

		for (theta; theta < (2 * M_PI) - M_PI / 180; theta += M_PI / 180) {//you can play with the value to be added to theta
			x = rx + sin(theta) * r;
			y = ry + sin(theta + (M_PI / 2)) * r;
			fprintf(pFicherosoloxy0, "%-10.10E %-10.10E %-10.10E %4.2f\n", x, z, y,1.00);
		}
		x = rx + sin(theta) * r;
		y = ry + sin(theta + (M_PI / 2)) * r;
		fprintf(pFicherosoloxy0, "%-10.10E %-10.10E %-10.10E %4.2f\n", x, z, y,0.00);
		fclose(pFicherosoloxy0);

	} else {//ES LA PAREJA
		pFicherosoloxyz = fopen("puntosBobinaXZ_Ysoloxyz.txt", "w");

		for (theta; theta < (2 * M_PI) - M_PI / 180; theta += M_PI / 180) {//you can play with the value to be added to theta
			x = rx + sin(theta) * r;
			y = ry - sin(theta + (M_PI / 2)) * r;
			fprintf(pFicherosoloxyz, "%-10.10E %-10.10E %-10.10E %4.2f\n", x, z, y,1.00);
		}
		x = rx + sin(theta) * r;
		y = ry - sin(theta + (M_PI / 2)) * r;
		fprintf(pFicherosoloxyz, "%-10.10E %-10.10E %-10.10E %4.2f\n", x, z, y,0.00);
		fclose(pFicherosoloxyz);
	}

}
/** escribe en puntosBobinaYZ_0soloxyz.txt las coordenadas de los puntos de la bobina en el plano YZ
 *  con centro (x, ry, rz) y radio r
 *  SI ES LA PAREJA x=0.3 si no, x=0
 * @param rx
 * @param rz
 * @param pareja
 * @param r
 * @return void.
 */
void BobinaYZ(double rx, double ry, int pareja, float r) {

	double x, y, z = pareja ? 0.6 : 0;
	double theta = 0;//angulo


	FILE * pFicherosoloxy0 = NULL;
	FILE * pFicherosoloxyz = NULL;
	if (!pareja) {
		pFicherosoloxy0 = fopen("puntosBobinaYZ_0soloxyz.txt", "w");

		for (theta; theta < (2 * M_PI) - M_PI / 180; theta += M_PI / 180) {//you can play with the value to be added to theta
			x = rx + sin(theta) * r;
			y = ry - sin(theta + (M_PI / 2)) * r;
			fprintf(pFicherosoloxy0, "%-10.10E %-10.10E %-10.10E %4.2f\n", z, x, y,1.00);
		}
		x = rx + sin(theta) * r;
		y = ry - sin(theta + (M_PI / 2)) * r;
		fprintf(pFicherosoloxy0, "%-10.10E %-10.10E %-10.10E %4.2f\n", z, x, y,0.00);
		fclose(pFicherosoloxy0);
	} else {
		pFicherosoloxyz = fopen("puntosBobinaYZ_Xsoloxyz.txt", "w");

		for (theta; theta < (2 * M_PI) - M_PI / 180; theta += M_PI / 180) {//you can play with the value to be added to theta
			x = rx + sin(theta) * r;
			y = ry + sin(theta + (M_PI / 2)) * r;
			fprintf(pFicherosoloxyz, "%-10.10E %-10.10E %-10.10E %4.2f\n", z, x, y,1.00);
		}
		x = rx + sin(theta) * r;
		y = ry + sin(theta + (M_PI / 2)) * r;
		fprintf(pFicherosoloxyz, "%-10.10E %-10.10E %-10.10E %4.2f\n", z, x, y,0.00);
		fclose(pFicherosoloxyz);
	}

}
int main(int argc, char *argv[]) {

	//Bobina plano XY Z=0
	BobinaXY(0.3, 0.3, FALSE, 0.3 - 0.08 - 0.005);
	//y pareja
	BobinaXY(0.3, 0.3, TRUE, 0.3 - 0.08 - 0.005);
	//Bobina plano XZ Y=0
	BobinaXZ(0.3, 0.3, FALSE, 0.3 - 0.08 - 0.005);
	//y pareja
	BobinaXZ(0.3, 0.3, TRUE, 0.3 - 0.08 - 0.005);

	//Bobina plano YZ X=0
	BobinaYZ(0.3, 0.3, FALSE, 0.3 - 0.08 - 0.005);
	//y pareja
	BobinaYZ(0.3, 0.3, TRUE, 0.3 - 0.08 - 0.005);
}
