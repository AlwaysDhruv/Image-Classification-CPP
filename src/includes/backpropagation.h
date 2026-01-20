#ifndef PREPROCESśS_H
#define PREPROCESS_H

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

class Backward
{
public:
	void pass(vector<double>& data, vector<double>& labels, vector<vector<double>>& pixel, vector<vector<vector<int>>>& mask, vector<double>& temp, vector<vector<double>>& fc_g_w, vector<vector<double>>& convo_g_w, vector<double>& convo_g_b, vector<double>& fc_g_b, vector<double>& fc_g_a, int rows, int cols)
	{

		//Gradient w.r.t. logits 𝑆 (softmax + cross‐entropy)
		//Gradients in the fully‐connected layer
		//Bias Gradients
	    vector<double> loss;
	    for (int k = 0; k < temp.size(); ++k)
	    {
	        loss.push_back(temp[k] - labels[k]);
	        fc_g_b.push_back(loss.back());
	    }

	    //Gradients in the fully‐connected layer
	    //Weigths Gradients
		vector<double> temp1;
	    for (int l = 0; l < loss.size(); ++l)
	    {
	        for (int k = 0; k < data.size(); ++k) temp1.push_back(data[k] * loss[l]);
	        fc_g_w.push_back(temp1);
	        temp1.clear();
	    }

	    //Gradient w.r.t. the dense‐layer input 𝑎
		double sum = 0.0;
	    for (int l = 0; l < fc_g_w[0].size(); ++l)
	    {
	        for (int k = 0; k < fc_g_w.size(); ++k) sum += fc_g_w[k][l] * loss[l];
	        fc_g_a.push_back(sum);
	        temp1.push_back(relu_derivative(sum));
	        sum = 0.0;
	    }

	    //Gradients in the Convolutional layer
	    //Bias Gradients
	    for (int l = 0; l < fc_g_a.size(); ++l) convo_g_b.push_back(fc_g_a[l] * temp1[l]);

	    //Gradients in the Convolutional layer
	    //Weigths Gradients
	    temp1.clear();
	    convo_g_w.resize(rows);
    	for (int i = 0; i < rows; ++i) convo_g_w[i].resize(cols, 0);
    	int ct = 0;
	    for (int m = 0; m < mask.size(); ++m)
	    {
		    for (int i = 0; i <= pixel.size() - cols; ++i)
		        for (int j = 0; j <= pixel[0].size() - rows; ++j)
		        {
		            for (int k = 0; k < cols; ++k)
		                for (int l = 0; l < rows; ++l) temp1.push_back(pixel[i + k][j + l] * mask[m][i][j]);
	                for (int l = 0; l < convo_g_w[ct].size(); ++l) convo_g_w[ct][l] += temp1[l];
	                temp1.clear();
		        }
            ++ct;
	    }
	}
    double relu_derivative(double x)
    {
        return x > 0 ? 1 : 0;
    }
};
#endif