#include "weight_init.h"

using namespace cv;
using namespace std;

//  weightRandomInit(tpntw, word_vec_len, hiddenConfig[0].NumHiddenNeurons);
void weightRandomInit(Hl &ntw, int inputsize, int hiddensize)//hiddensize是512，inputsize是1255,是不同的键值对个数
{
    double epsilon = 0.12;
    // weight between hidden layer with previous layer
    ntw.U_l = Mat::ones(hiddensize, inputsize, CV_64FC1);//hiddensize是row，inputsize是col
    randu(ntw.U_l, Scalar(-1.0), Scalar(1.0));//你可以通过用randu()函数产生的随机值来填充矩阵。另外两个参数应该是上下限
    ntw.U_l = ntw.U_l * epsilon;

    ntw.U_lgrad = Mat::zeros(hiddensize, inputsize, CV_64FC1);//hiddensize行数，inputsize列数，CV_64FC1：创建的矩阵的类型
    ntw.U_ld2 = Mat::zeros(ntw.U_l.size(), CV_64FC1);//ntw.U_l.size()：nat 有row，有col
    ntw.lr_U = lrate_w;//3e-3
    //// weight between current time t with previous time t-1
    ntw.W_l = Mat::ones(hiddensize, hiddensize, CV_64FC1);
    randu(ntw.W_l, Scalar(-1.0), Scalar(1.0));
    ntw.W_l = ntw.W_l * epsilon;
    ntw.W_lgrad = Mat::zeros(hiddensize, hiddensize, CV_64FC1);
    ntw.W_ld2 = Mat::zeros(ntw.W_l.size(), CV_64FC1);
    ntw.lr_W = lrate_w;//0.003

    ntw.U_r = Mat::ones(hiddensize, inputsize, CV_64FC1);
    randu(ntw.U_r, Scalar(-1.0), Scalar(1.0));
    ntw.U_r = ntw.U_r * epsilon;
    ntw.U_rgrad = Mat::zeros(hiddensize, inputsize, CV_64FC1);
    ntw.U_rd2 = Mat::zeros(ntw.U_r.size(), CV_64FC1);
    ntw.lr_U = lrate_w;//0.003

    ntw.W_r = Mat::ones(hiddensize, hiddensize, CV_64FC1);
    randu(ntw.W_r, Scalar(-1.0), Scalar(1.0));
    ntw.W_r = ntw.W_r * epsilon;
    ntw.W_rgrad = Mat::zeros(hiddensize, hiddensize, CV_64FC1);
    ntw.W_rd2 = Mat::zeros(ntw.W_r.size(), CV_64FC1);
    ntw.lr_W = lrate_w;
}

//有文件时，nclasses：11；nfeatures：1255
void weightRandomInit(Smr &smr, int nclasses, int nfeatures)
{
    double epsilon = 0.12;
    smr.W_l = Mat::ones(nclasses, nfeatures, CV_64FC1);
    randu(smr.W_l, Scalar(-1.0), Scalar(1.0));
    smr.W_l = smr.W_l * epsilon;
    smr.W_lgrad = Mat::zeros(nclasses, nfeatures, CV_64FC1);
    smr.W_ld2 = Mat::zeros(smr.W_l.size(), CV_64FC1);

    smr.W_r = Mat::ones(nclasses, nfeatures, CV_64FC1);
    randu(smr.W_r, Scalar(-1.0), Scalar(1.0));
    smr.W_r = smr.W_r * epsilon;
    smr.W_rgrad = Mat::zeros(nclasses, nfeatures, CV_64FC1);
    smr.W_rd2 = Mat::zeros(smr.W_r.size(), CV_64FC1);

    smr.cost = 0.0;
    smr.lr_W = lrate_w;//3e-3
}

void rnnInitPrarms(std::vector<Hl> &HiddenLayers, Smr &smr)
{
    // Init Hidden layers
	// hiddenConfig.size():1
	if(hiddenConfig.size() > 0)//隐藏层信息，读配置文件读出来的
	{
		Hl tpntw;//隐含层结构体
		//hiddenConfig[0].NumHiddenNeurons,512个神经元,word_vec_len是1255,是不同的键值对
        weightRandomInit(tpntw, word_vec_len, hiddenConfig[0].NumHiddenNeurons);
        HiddenLayers.push_back(tpntw);
        cout<<".... hiddenConfig.size() "<<hiddenConfig.size()<<endl;
        for(int i = 1; i < hiddenConfig.size(); i++)//1
        {
            Hl tpntw2;
            weightRandomInit(tpntw2, hiddenConfig[i - 1].NumHiddenNeurons, hiddenConfig[i].NumHiddenNeurons);
            HiddenLayers.push_back(tpntw2);
        }
    }
    // Init Softmax layer
    if(hiddenConfig.size() == 0)//没有配置文件
    {
    	//smr：softMax层，softmaxConfig.NumClasses：11，word_vec_len是1255
        weightRandomInit(smr, softmaxConfig.NumClasses, word_vec_len);
    }
    else
    {
    	//smr：softMax层，softmaxConfig.NumClasses：11，word_vec_len是1255；
    	//hiddenConfig[hiddenConfig.size() - 1].NumHiddenNeurons ：512个神经元
        weightRandomInit(smr, softmaxConfig.NumClasses, hiddenConfig[hiddenConfig.size() - 1].NumHiddenNeurons);
    }
}


