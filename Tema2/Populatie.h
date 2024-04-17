#pragma once
#include "Utile.h"
#include <vector>
using namespace std;
struct Chromosome {
	vector<bool> biti;
	vector<float> dec;
	float val;
};
struct Fitness {
	float total;
	vector<float> val;
	vector<int> order;
};
struct Population {
	vector<Chromosome> crom;
	Fitness fitness;
	vector<float> accumProb;
}P;

//P
void EvaluatePopulation(Population& P);
Chromosome GenerateRandomChromosome();
void CrossoverChromosomes(Chromosome& C1, Chromosome& C2, int locus);
void EvaluateChromosome(Chromosome& C);

//bool compareChromosomes(Chromosome& C1, Chromosome& C2);

void GenerateStartingPopulation(Population& P) {
	float min=INFINITY, max = -INFINITY;
	P.fitness.total = 0;
	for (int i = 0; i < d.nrCrom; i++) {
		P.crom.push_back(GenerateRandomChromosome());
		if (P.crom[i].val > max)
			max = P.crom[i].val;
		if (P.crom[i].val < min)
			min = P.crom[i].val;
	}

	P.accumProb.push_back(0);
	for (int i = 0; i < d.nrCrom; i++) {
		P.fitness.val.push_back(d.F->fitness(d.D, P.crom[i].val, min, max, selectionPressure));
		P.fitness.total += P.fitness.val[i];
		P.fitness.order.push_back(i);
	}
	for (int i = 0; i < d.nrCrom; i++) {
		float indProb = P.fitness.val[i] / P.fitness.total;
		P.accumProb.push_back(P.accumProb[i] + indProb);
	}
	selectionPressure = 1;

	
}

Chromosome GenerateRandomChromosome() {
	Chromosome C;
	for (int i = 0; i < d.L; i++)
		C.biti.push_back(RandomBit());
	for (int j = 0; j < d.D; j++)
		C.dec.push_back(DecodeParameter(C.biti, j));
	C.val = d.F->f(d.D, C.dec);


	return C;
}

void EvaluatePopulation(Population& P) {
	float min = INFINITY, max = -INFINITY;
	for (int i = 0; i < d.nrCrom; i++) {
		EvaluateChromosome(P.crom[i]);
		if (P.crom[i].val > max)
			max = P.crom[i].val;
		if (P.crom[i].val < min)
			min = P.crom[i].val;
	}

	P.fitness.total = 0;
	
	for (int i = 0; i < d.nrCrom; i++) {
		P.fitness.val.push_back(d.F->fitness(d.D, P.crom[i].val, min, max, selectionPressure));
		P.fitness.total += P.fitness.val[i];
		P.fitness.order.push_back(i);
	}

	P.accumProb.push_back(0);
	for (int i = 0; i < d.nrCrom; i++) {
		float indProb = P.fitness.val[i] / P.fitness.total;
		P.accumProb.push_back(P.accumProb[i] + indProb);
	}
	selectionPressure += 0.001;
}

void EvaluateChromosome(Chromosome& C) {
	for (int i = 0; i < d.D; i++)
		C.dec[i] = DecodeParameter(C.biti, i);
	C.val = d.F->f(d.D, C.dec);
}

void Selection(Population& P) {
	//find best popsize/10 chromosomes (cum??)
	
	sort(P.fitness.order.begin(), P.fitness.order.end(), [=](int index_left, int index_right) {
		return P.fitness.val[index_left] > P.fitness.val[index_right];
		});

	Population newP;
	for (int i = 0; i < d.nrElite; i++)
		newP.crom.push_back(P.crom[P.fitness.order[i]]);


	for (int i = d.nrElite ; i < d.nrCrom; i++) {
		float r = RandomProbability();
		int elem = Find(r, P.accumProb, d.nrCrom);
		newP.crom.push_back(P.crom[elem]);
	}
	P = newP;
}

void Mutation(Population& P) {
	random_device rd;
	mt19937 gen(rd());
	std::uniform_real_distribution<>  distr(0.0,1.0);
	

	for (int i = d.nrElite; i < d.nrCrom; i++) 
		for (int j = 0; j < d.L; j++)
			if (distr(gen) < d.mutProb)
				P.crom[i].biti[j] = !P.crom[i].biti[j];

}

void Crossover(Population& P) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(0, d.L - 1);

	for (int i = d.nrElite; i < d.nrCrom; i += 2) {
		int locus = RandomInt(d.L - 1);
		if (distrib(gen) > d.crossProb) 
			CrossoverChromosomes(P.crom[i], P.crom[i + 1], locus);
	}
}

void CrossoverChromosomes(Chromosome& C1, Chromosome& C2, int locus) {
	for (int i = locus; i < d.L; i++)
		swap(C1.biti[i], C2.biti[i]);
}
