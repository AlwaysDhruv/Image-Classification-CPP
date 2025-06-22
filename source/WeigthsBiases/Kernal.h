#ifndef PREPROCESśS_H
#define PREPROCESS_H

#include <string>
#include <vector>
#include <random>

using namespace std;

class Kernal
{
	public:
	void values(vector<vector<double>>& convo_weigth, vector<double>& convo_bias, int height, int width, int channel, int filters)
	{
	    float limit = sqrt(6.0f / ((height * width * channel) + (height * width * filters)));
		for (int i = 0; i < filters; ++i)
		{
			vector<double> temp;
			for (int j = 0; j < height * width; ++j)
			{
				random_device rd;
	    		mt19937 gen(rd());
	    		uniform_real_distribution<> dist(-limit, limit);
				temp.push_back(round(dist(gen) * 100.0) / 100.0);
			}
			convo_weigth.push_back(temp);
			random_device rd;
    		mt19937 gen(rd());
    		uniform_real_distribution<> dist(-limit, limit);
    		convo_bias.push_back(round(dist(gen) * 100.0) / 100.0);
		}
	}
	void values(vector<vector<double>>& weight, vector<double>& bias, int input, int output)
	{
		float limit = sqrt(6.0f / (input + output));
		for (int i = 0; i < output; ++i)
		{
			vector<double> temp;
			random_device rd;
	   		mt19937 gen(rd());
	  		uniform_real_distribution<> dist(-limit, limit);
			for (int j = 0; j < input; ++j) temp.push_back(round(dist(gen) * 100.0) / 100.0);
			weight.push_back(temp);
			bias.push_back(round(dist(gen) * 100.0) / 100.0);
		}
	}
};
#endif