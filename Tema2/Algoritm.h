#pragma once
#include "Populatie.h"
float Best(Population& P);
float Worst(Population& P);
void PrintDataAnalysis(vector<Chromosome>& v, int n, int it);

float GeneticAlgorithm(int iteratii) {
	float best, worst;
	Population P;
	GenerateStartingPopulation(P);
	for (int it = 0; it < iteratii; it++) {
		Selection(P);
		Mutation(P);
		Crossover(P);
		EvaluatePopulation(P);
		best = Best(P); worst = Worst(P);
		PrintDataAnalysis(P.crom, d.nrCrom, it);
	}
	return Best(P);
}

float Best(Population& P) {
	float best = P.crom[0].val;
	for (int i = 1; i < d.nrCrom; i++)
		if (P.crom[i].val < best)
			best = P.crom[i].val;
	return best;
}
float Worst(Population& P) {
	float worst = P.crom[0].val;
	for (int i = 1; i < d.nrCrom; i++)
		if (P.crom[i].val > worst)
			worst = P.crom[i].val;
	return worst;
}

void PrintDataAnalysis(vector<Chromosome>& v, int n, int it) {
	float sum = 0.0, mean, stDev = 0.0, min = INFINITY, max = -INFINITY;

	for (int i = 0; i < n; i++) {
		sum += v[i].val;
		if (v[i].val < min) min = v[i].val;
		if (v[i].val > max) max = v[i].val;
	}
	mean = sum / n;
	for (int i = 0; i < n; i++) {
		stDev += pow(v[i].val - mean, 2);
	}
	stDev = sqrt(stDev / n);
	printf("iteratie: %d;   variatia: %6f;   medie: %6f;   stDev: %6f;   best: %6f\n", it, max - min, mean, stDev, min);

}