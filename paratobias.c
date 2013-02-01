/*
 * paratobias.c
 *
 *  Created on: 10-nov-2010
 *      Author: manuel
 */
#include <stdio.h>
#include <math.h>
// GIVEN A POINT C= R , Z  IN METERS, THIS ROUTINE CALCULATES THE
// B-FIELD IN TESLA DUE TO A CURRENT LOOP OF GIVEN
// RADIUS=radio_espira CENTERED AT THE ORIGIN FOR A CURRENT OF I=corriente
// AMPERES FLOWING COUNTER-CLOCKWISE AROUND THE Z-AXIS,
// AND RETURNS THE R,Z COMPONENTS OF magnetic field and the PHI component of the
// potential vector in loop coordinates.
//returns field[0]=Br field[1]=Aphi field[2]=Bz


#define eps 1e-8
#define eps_single eps

void ellipticIntegral(double m, double tol, double *k, double *e) {

	double a0, b0, a1, b1, c1, s0, i1, mm, w1;

	a0 = 1.;
	b0 = sqrt(1 - m);
	s0 = m;
	i1 = 0;
	mm = 1;
	while (mm > tol) {
		a1 = (a0 + b0) / 2.;
		b1 = sqrt(a0 * b0);
		c1 = (a0 - b0) / 2.;
		i1 = i1 + 1.;
		w1 = pow(2, i1) * c1 * c1;
		// max(w1(:))  (c version not vectorized)
		mm = w1;
		s0 = s0 + w1;
		a0 = a1;
		b0 = b1;
	}

	k[0] = M_PI / (2. * a1);
	e[0] = k[0] * (1. - s0 / 2.);

	//  im = find(m ==1);
	//if ~isempty(im)
	//    e(im) = ones(length(im),1);
	//    k(im) = inf;
	//end
}

void Relative2CoilABField(double R, double Z, int N_turns, double current,
		double radio_espira, double *field) {
	double tol, mu, corriente, radio, zeta;
	double alfa, beta, gamma, Q, M;
	double A0, B0, K_first, E_second;

	if (current == 0.) {
		//Br
		field[0] = 0.;
		//Aphi
		field[1] = 0.;
		//Bz
		field[2] = 0.;

		return;
	}

	tol = eps_single;

	mu = 4. * M_PI * 1e-7;

	corriente = N_turns * current;

	radio = R;

	if (radio < 0.)
		printf("%e radius relative to coil axis is negative\n", radio);

	zeta = Z;

	//Calculate separatly along coil axis
	if (radio < tol) {
		//Br
		field[0] = 0.;
		//Bz
		field[2] = 0.5 * mu * corriente * (radio_espira * radio_espira) * pow(
				radio_espira * radio_espira + zeta * zeta, -3. / 2.);
		//Aphi
		field[1] = 0.;

		return;
	} else if (fabs(radio - radio_espira) < tol && fabs(zeta) < tol) {
		//calculate separately when R=radio_espira and Z=0
		//Br
		field[0] = 0.;
		//Aphi
		field[1] = 0.;
		//Bz
		field[2] = 0.;

		printf("Relative2CoilABField: Attempt to calculate fields on the coil. Corrective action taken \n");

		return;
	} else {
		alfa = radio / radio_espira;
		beta = zeta / radio_espira;
		gamma = zeta / radio;

		Q = ((1. + alfa) * (1. + alfa) + beta * beta);

		M = 4. * alfa / Q;

		ellipticIntegral(M, tol, &K_first, &E_second);

		B0 = mu * corriente / 2. / radio_espira;

		//Bz
		field[2] = B0 / M_PI / sqrt(Q) * (E_second * (1. - alfa * alfa - beta
				* beta) / (Q - 4. * alfa) + K_first);

		//Br
		field[0] = B0 * gamma / M_PI / sqrt(Q) * (E_second * (1. + alfa * alfa
				+ beta * beta) / (Q - 4. * alfa) - K_first);

		M = 4. * radio_espira * radio / ((radio_espira + radio) * (radio_espira
				+ radio) + zeta * zeta);

		//calcula integrales elipticas otra vez (potencial vector y campo no usan
		//la misma M en el calculo de las integrales elipticas

		ellipticIntegral(M, tol, &K_first, &E_second);

		A0 = mu * corriente / M_PI / sqrt(M) * sqrt(radio_espira / radio);
		//Aphi
		field[1] = A0 * ((1. - M / 2.) * K_first - E_second);
	}

}

int main(void) {

	double field[3];
	double R=0;
	double Z=0;
	double radio_espira=0.3 - 0.08 - 0.005;
	double min=-0.1;
	double max=0.7;
	double paso=0.01;

	for (Z = min; Z <= max; Z+= paso) {
		Relative2CoilABField(R, Z, 1, 10000, radio_espira, field);
		printf("%-10.10E %-10.10E %-10.10E %4.2f\n", field[0], field[1], field[2],0.00);
	}

}
