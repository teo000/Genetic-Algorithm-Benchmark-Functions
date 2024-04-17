#pragma once
#include "Date.h"
#include <vector>
#include <random>
#include <iomanip>
#include <fstream>
using namespace std;

bool RandomBit() {
	random_device rd;
	mt19937 gen(rd());
	bernoulli_distribution d(0.5);
	return d(gen);
}

float RandomProbability() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);
	return dis(gen);
}

int RandomInt(int n) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, n);

	return distrib(gen);
}


float DecodeParameter(vector<bool>& biti, int poz) {
	float x = 0, p2 = 1;
	for (int i = 0; i < d.l; i++) {
		x += p2 * biti[poz * d.l + i];
		p2 *= 2;
	}
	x = d.a + x * (d.b - d.a) / (p2 - 1);
	return x;
}

float DecodeGrayParameter(vector<bool>& gray, int poz) {
	vector<bool> binar;

	binar.push_back(gray[0]);
	for (int i = 1; i < gray.size(); i++) {
		binar.push_back((gray[i] == 0) ? binar[i - 1] : !binar[i - 1]);
	}

	float x = 0, p2 = 1;
	for (int i = 0; i < d.l; i++) {
		x += p2 * binar[poz * d.l + i];
		p2 *= 2;
	}
	x = d.a + x * (d.b - d.a) / (p2 - 1);
	return x;
}

int Find(float r, vector<float>& p, int nr) {
	for (int i = 1; i <= nr; i++)
		if (p[i] > r) return (i - 1);
	return nr - 1;
}

void PrintDate(int functie, int runs) {
	fstream fout;
	fout.open("Results.txt", fstream::app);
	fout << '\n';
	switch (functie) {
	case 1: fout << "DeJong's "; break;
	case 2: fout << "Rastrigin's "; break;
	case 3: fout << "Schwefel's "; break;
	case 4: fout << "Michalewicz's "; break;
	}
	fout << " D = " << d.D  << "  runs = "<< runs<<"  crossover = " << d.crossProb << "  mutation = "<<d.mutation << '\n';
}

void PrintResults(vector<float>& v, int n) {
	fstream fout;
	fout.open("Results.txt", fstream::app);


	float sum = 0.0, mean, stDev = 0.0, min = INFINITY, max = -INFINITY;

	for (int i = 0; i < n; i++) {
		sum += v[i];
		if (v[i] < min) min = v[i];
		if (v[i] > max) max = v[i];
	}
	mean = sum / n;
	for (int i = 0; i < n; i++) {
		stDev += pow(v[i] - mean, 2);
	}
	stDev = sqrt(stDev / n);

	fout << fixed << setprecision(5) << min << " & " << mean << " & " << max << " & " << stDev << '\n';
}
