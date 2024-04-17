#include "Algoritm.h"
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
void runGeneticAlgorithm(int iteratii, int runs, int functie);
int main() {
	int D = 30, p = 5, runs = 5, functie = 3, iteratii = 2000, nrIndivizi = 200, nrElita = nrIndivizi/20;
	float crossProb = 0.8, mutProb = 2.0;
	int Dimensions[3] = { 5, 10, 30 };
	
	/*for(int i=0;i<3;i++)
		for (int fct = 1; fct <= 4; fct++) {
			SetDate(d, Dimensions[i], p, fct, nrIndivizi, nrElita,crossProb, mutProb);
			runGeneticAlgorithm(runs, iteratii, fct);
	}*/

	SetDate(d, D, p, functie, nrIndivizi, nrElita, crossProb, mutProb);
	runGeneticAlgorithm(runs, iteratii, functie);

}

void runGeneticAlgorithm(int runs, int iteratii, int functie) {
	vector<float> rezultate;
	chrono::steady_clock::time_point start_time(std::chrono::steady_clock::now());

	PrintDate(functie, runs);
	for (int i = 0; i < runs; i++)
		rezultate.push_back(GeneticAlgorithm(iteratii));
	chrono::steady_clock::time_point end_time(std::chrono::steady_clock::now());

	PrintResults(rezultate, runs);
	fstream fout;
	fout.open("Results.txt", fstream::app);
	fout << chrono::duration_cast<chrono::duration<double>>(
		end_time - start_time).count() / runs<<'\n\n';
}