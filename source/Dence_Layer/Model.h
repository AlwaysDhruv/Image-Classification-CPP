#ifndef PREPROCESśS_H
#define PREPROCESS_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include "update.h"
#include "convolutional.h"
#include "backpropagation.h"

using namespace std;

class Model
{
public:
	void train(vector<vector<vector<double>>>& data, vector<vector<double>>& labels, vector<vector<vector<vector<double>>>>& pixel, vector<vector<vector<vector<vector<int>>>>>& mask, vector<vector<double>>& fc_weigths, vector<vector<double>>& convo_weigths, vector<double>& convo_bias,vector<double>& fc_bias, int train)
	{
        Backward backward;
        Update update;
        Convolution convo;
        for (int epochs = 0; epochs < train; ++epochs)
        {
            double losses = 0.0;
            for (int i = 0; i < data.size(); ++i)
            {
                for (int j = 0; j < data[0].size(); ++j)
                {
                    double sum = 0.0;
                    vector<double> temp;
                    vector<double> temp1;
                    for (int k = 0; k < fc_weigths.size(); ++k)
                    {
                        for (int l = 0; l < fc_weigths[0].size(); ++l) sum += fc_weigths[k][l] * data[i][j][l];
                        temp.push_back(sum + fc_bias[k]);
                        sum = 0.0;
                    }
                    softmax(temp);
                    cout << endl;                    
                    for (int k = 0; k < labels[0].size(); ++k)
                    {
                        if (labels[i][k]==1)
                        {
                            losses += -log(temp[k]);
                            break;
                        }
                    }
                    vector<vector<double>> fc_g_w;
                    vector<vector<double>> convo_g_w;
                    vector<double> convo_g_b;
                    vector<double> fc_g_b;
                    vector<double> fc_g_a;
                    backward.pass(data[i][j],labels[i],pixel[i][j],mask[i][j],temp,fc_g_w,convo_g_w,fc_g_b,convo_g_b,fc_g_a,convo_weigths.size(),convo_weigths[0].size());
                    update.updates(convo_weigths,0.01,convo_g_w);
                    update.updates(fc_weigths,0.01,fc_g_w);
                    update.updates(convo_bias,0.01,convo_g_b);
                    update.updates(fc_bias,0.01,fc_g_b);
                    temp.clear();
                    temp1.clear();
                    data.clear();
                    mask.clear();
                    pixel.clear();
                    convo.operation(data,pixel,mask,convo_weigths,convo_bias,sqrt(convo_weigths[0].size()),2);
                }
            }
            cout << "Training Complete : " << epochs + 1 << " Loss : " << losses << endl;
        }
	}

    int predict(vector<vector<double>>& data, vector<vector<double>>& fc_weigths, vector<double>& fc_bias)
    {
        vector<double> temp;
        for (int i = 0; i < data.size(); ++i)
        {
            double sum = 0.0;
            for (int k = 0; k < fc_weigths.size(); ++k)
            {
                for (int l = 0; l < fc_weigths[0].size(); ++l) sum += fc_weigths[k][l] * data[i][l];
                temp.push_back(sum + fc_bias[k]);
                sum = 0.0;
            }
        }
        int index;
        vector<double> temp1;
        softmax(temp);
        for (int i = 0; i < temp.size(); ++i)
            if (temp[i]==*max_element(temp.begin(), temp.end()))
                index = i;
        return index;
    }
    
    void softmax(vector<double>& input) 
    {
        double maxVal = *max_element(input.begin(), input.end());
        double sum = 0.0;
        for (double val : input) sum += exp(val - maxVal);
        for (size_t i = 0; i < input.size(); ++i) input[i] = (exp(input[i] - maxVal) / sum);
    }
};
#endif
