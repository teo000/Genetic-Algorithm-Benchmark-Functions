#include "Functii.h"

int lungimeBitstring(float a, float b, float p) {
	return ceil(log2((b - a) * pow(10, p)));
}

struct Date {
	float a, b, constant, crossProb, mutProb, mutation;
	int D, p, l, L, nrCrom, nrElite;
	Functie* F;
};
Date d;
float selectionPressure = 1;
void SetDate(Date& date, int D, int p, int functie, int nrCrom, int nrElita, float crossProb, float mutProb) {
	Functie* f;
	switch (functie) {
	case 1: f = new DeJong(); break;
	case 2: f = new Rastrigin(); break;
	case 3: f = new Schwefel(); break;
	default: f = new Michalewicz();
	}
	date.F = f;
	date.a = f->a; date.b = f->b; date.D = D; date.p = p;
	date.l = lungimeBitstring(date.a, date.b, p);
	date.L = date.l * D;
	date.nrCrom = nrCrom;
	date.nrElite = nrElita;
	date.crossProb = crossProb;
	date.mutation = mutProb;
	date.mutProb = mutProb / d.L;
}


