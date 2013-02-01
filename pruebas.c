/*
 * pruebas.c
 *
 *  Created on: 03-nov-2010
 *      Author: manuel
 */
#include <stdio.h>
//#include <stdlib.h>

int ** creaMatrizXYEnteros(unsigned int filas, unsigned int cols) {
	int ** matrix;
	unsigned int i = 0;
	matrix = (int **) calloc(cols, sizeof(int *));
	for( i = 0; i < cols; i++)
		matrix[i] = (int *) calloc(filas, sizeof(int));
	return matrix;
}

int main(void) {

	int min=0;
	int max=3;
	int paso=1;
	int dim= (max-min)/paso;
	int **modB=creaMatrizXYEnteros(dim, dim);
	FILE * pMedidasmodB = NULL;

	int i , x , y, z;
	i=x=y=z=0;
	char * pCab[] = { "Ax", "Ay", "Az", "Bx", "By", "Bz", "modB ", "A*B","modA" };
	char pvalor[]="x,y,z";
	char nombreFich[256];


	for (i = 0; i < 9; i++)
		printf("%s = %d\n", *(pCab + i), i);

	for (x = min; x < max; x+=paso) {
		sprintf (nombreFich, "./modB/MedidasmodB_%4f.txt", x);
		pMedidasmodB = fopen( nombreFich, "w");

		for (y = min; y < max; y+=paso) {
			for (z = min; z < max; z+=paso) {
				modB[x][y]=100*x+10*y+z;
				printf("%d,%d,%d : %03d\t", x,y,z,modB[x][y]);
				fprintf(pMedidasmodB, "%d,%d,%d : %03d\t", x,y,z,modB[x][y]);
			}
			printf("\t");
			fprintf(pMedidasmodB, "\t");
		}
		printf("\n");
		fprintf(pMedidasmodB, "\n");

		fclose(pMedidasmodB);
	}

}
