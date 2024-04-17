#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <iostream>
#include <math.h>
#define EPS 0.000001
using namespace std;
class Functie {
public:
	float a, b;
	virtual float f(int D, vector<float> v) = 0;
	float fitness(int D, float value, float min, float max, float selectionPressure){
		return pow((max-value)/(max-min+EPS)+1, selectionPressure)-1;
	}
};

class DeJong : public Functie {
public:
	DeJong() {
		this->a = -5.12;
		this->b = 5.12;
	}
	virtual float f(int D, vector<float> v) {
		float sum = 0;
		for (int i = 0; i < D; i++)
			sum += v[i] * v[i];
		return sum;
	}
};

class Rastrigin : public Functie {
public:
	Rastrigin() {
		this->a = -5.12;
		this->b = 5.12;
	}
	virtual float f(int D, vector<float> v) {
		float sum = 10 * D;
		for (int i = 0; i < D; i++)
			sum += v[i] * v[i] - 10 * cos(2 * M_PI * v[i]);
		return sum;
	}
};

class Schwefel : public Functie {
public:
	Schwefel() {
		this->a = -500;
		this->b = 500;
	}
	virtual float f(int D, vector<float> v) {
		float sum = 0;
		for (int i = 0; i < D; i++)
			sum += -v[i] * sin(sqrt(abs(v[i])));
		return sum;
	}
};

class Michalewicz : public Functie {
public:
	Michalewicz() {
		this->a = 0;
		this->b = M_PI;
	}
	virtual float f(int D, vector<float> v) {
		float sum = 0;
		for (int i = 0; i < D; i++)
			sum += -sin(v[i]) * pow((sin(pow(v[i], 2) * (i+1)  / M_PI)), 20);
		return sum;
	}
};