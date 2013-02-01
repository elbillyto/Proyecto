/*
 * test.c
 *
 *  Created on: 03-nov-2010
 *      Author: manuel
 */
/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * test.c
 * Copyright (C) MVGS 2010 <elbillyto@gmail.com>
 *
 * polywell is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * polywell is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h> //para calloc bajo linux

int scanfdemo(){
	  /* We will use a floating-point and an integer variable. */

  double x;
  int n;


  /* Read in an integer. */

  printf("Please enter an integer: ");
  scanf("%d", &n);
  printf("The integer was %d\n\n", n);


  /* Read in a double. */

  printf("Please enter a double: ");
  scanf("%lf", &x);
  printf("The double was %g\n\n", x);


  /* Read in an integer and a double. */

  printf("Please enter an integer and a floating-point number: ");
  scanf("%d%lf", &n, &x);
  printf("The numbers were %d %g\n", n, x);
}


int ** creaMatrizXYEnteros(unsigned int filas, unsigned int cols) {
    int ** matrix;
    unsigned int i = 0;
    matrix = (int **) calloc(cols, sizeof(int *));
    for ( i = 0; i < cols; i++)
        matrix[i] = (int *) calloc(filas, sizeof(int));
    return matrix;
}

int generarFichero(void) {

    int min=0;
    int max=3;
    int paso=1;
    int dim= (max-min)/paso;
    int **modB=creaMatrizXYEnteros(dim, dim);
    FILE * pMedidasmodB = NULL;


    int i , x , y, z;
    i=x=y=z=0;
    char * pCab[] = { "Ax", "Ay", "Az", "Bx", "By", "Bz", "modB ", "A*B","modA" };
    //char pvalor[]="x,y,z";
    char nombreFich[256];


    for (i = 0; i < 9; i++)
        printf("%s = %d\n", *(pCab + i), i);
		

    for (x = min; x < max; x+=paso) {
        sprintf(nombreFich, "./modB/MedidasmodB_%d.txt", x);
        pMedidasmodB = fopen( nombreFich, "w");
        if(!pMedidasmodB){
            printf("Error al abrir el fichero %s",nombreFich);
            exit(EXIT_FAILURE);
        }


        for (y = min; y < max; y+=paso) {
            for (z = min; z < max; z+=paso) {
                modB[x][y]=100*x+10*y+z;
                printf("%d,%d,%d : %03d\t", x,y,z,modB[x][y]);
                fprintf(pMedidasmodB, "%d,%d,%d : %03d\t", x,y,z,modB[x][y]);
            }
            printf("\n");
            fprintf(pMedidasmodB, "\n");
        }
        printf("\n");
        fprintf(pMedidasmodB, "\n");

        fclose(pMedidasmodB);
    }

    return 0;
}


/**
 * @brief crea una matriz de x filas e y columnas
 * @param filas
 * @param cols
 * @return double **matriz  ---> matriz [X][Y] 
 */

double ** creaMatrizXYmodB(unsigned int filas, unsigned int cols) {
    double ** matrix;
    unsigned int i = 0;
    matrix = (double **) calloc(cols, sizeof(double *));
    for ( i=0; i < cols; i++)
        matrix[i] = (double *) calloc(filas, sizeof(double));
    return matrix;
}


/**
 * @class structure_puntoCampo
 * @author MVGS
 * @date 26/11/10
 * @file test.c
 * @brief represents the Field components at a given point
 */
typedef struct _puntoCampo{
	double componenteX;
	double componenteY;
	double componenteZ;
}puntoCampo;


/**
 * @brief Generates a 3D-GRID from structures puntosCampo
 * @param filas
 * @param cols
 * @param widthZ
 * @return (puntosCampo ***) GRID 
 */
puntoCampo *** creaGridXYZ(unsigned int filas, unsigned int cols, unsigned int widthZ ) {
    puntoCampo *** matrix;
    unsigned int i,j = 0;
    matrix = (puntoCampo ***) calloc(filas, sizeof(puntoCampo **));
	
    for ( i=0; i < filas; i++){
        matrix[i] = (puntoCampo **) calloc(cols, sizeof(puntoCampo*));		
		for ( j=0; j < cols; j++){
			matrix[i][j] = (puntoCampo*) calloc(widthZ, sizeof(puntoCampo));
		}
	}
    return matrix;
}


/**
 * @brief reads the file "medidasPolywell_test.txt" and fills in the GRID
 * @return
 */
int leerFichero_medidasPolywell(void) {

    float min=-0.1;
    float max=0.7;
    //float paso=0.01; Esto quisiera yo!
	float paso=0.02;
    int dim= (max-min)/paso;
    FILE * pMedidasA = NULL;
	double field3,field4,field5,field6,field7,field8;
	field3=field4=field5=field6=field7=field8=0;
    int i , x , y, z;
	double X , Y, Z;
    i=x=y=z=X=Y=Z=0;
    char nombreFich[256];
    puntoCampo ***GridA=creaGridXYZ(dim, dim, dim);
	puntoCampo ***GridB=creaGridXYZ(dim, dim, dim);

		
	//abrimos el fichero
	sprintf(nombreFich, "medidasPolywell_test.txt", x);
	pMedidasA = fopen( nombreFich, "r");
	if(!pMedidasA){
		printf("Error al abrir el fichero %s\n",nombreFich);
		exit(EXIT_FAILURE);
	}
	
	//read the file and fill in GridA and GridB
    for (x = 0; x < dim; x+=1) {
        for (y = 0; y < dim; y+=1) {
            for (z = 0; z < dim; z+=1) {
				//walk the line
				fscanf(pMedidasA, "%lf\t %lf\t %lf\t %lf\t %lf\t %lf\t %lf\t %lf\t %lf\t %lf\t %lf\t %lf\n", 
				&X, &Y, &Z, 
				&(*(*(*(GridA+x)+y)+z)).componenteX, &(*(*(*(GridA+x)+y)+z)).componenteY, &(*(*(*(GridA+x)+y)+z)).componenteZ, 
				&(*(*(*(GridB+x)+y)+z)).componenteX, &(*(*(*(GridB+x)+y)+z)).componenteY, &(*(*(*(GridB+x)+y)+z)).componenteZ , 
				&field6, &field7, &field8);
				//double check just to see
//				printf("%-10.10E\t%-10.10E\t%-10.10E\t-A-%-10.10E\t%-10.10E\t%-10.10E\t-B-%-10.10E\t%-10.10E\t%-10.10E\n",
//				X,Y,Z,
//				(*(*(*(GridA+x)+y)+z)).componenteX,(*(*(*(GridA+x)+y)+z)).componenteY,(*(*(*(GridA+x)+y)+z)).componenteZ,
//				(*(*(*(GridB+x)+y)+z)).componenteX,(*(*(*(GridB+x)+y)+z)).componenteY,(*(*(*(GridB+x)+y)+z)).componenteZ);
            }
        }
    }
    fclose(pMedidasA);
	
	//print some value (for example for x=-1.0000000000E-001	 Y=-1.0000000000E-001	 Z=6.8000000000E-001)
	printf("%-10.10E\t%-10.10E\t%-10.10E\n",(GridA[0][0][39]).componenteX,(GridA[0][0][39]).componenteY, (GridA[0][0][39]).componenteZ);
    return 0;
}

int main(void) {
	
	//generarFichero();
	leerFichero_medidasPolywell();
	//scanfdemo();

	return 0;
	}
