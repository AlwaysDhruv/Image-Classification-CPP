#ifndef PREPROCESśS_H
#define PREPROCESS_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

class Update
{
public:
	void updates(vector<vector<double>>& weights, float Learning_Rate, vector<vector<double>>& gradients)
	{
		for (int j = 0; j < weights.size(); ++j)
			for (int i = 0; i < weights[0].size(); ++i) weights[j][i] -= Learning_Rate * gradients[j][i];
	}
	void updates(vector<double>& biases, float Learning_Rate, vector<double>& gradients)
	{
		for (int j = 0; j < biases.size(); ++j) biases[j] -= Learning_Rate * gradients[j];
	}
};

#endif