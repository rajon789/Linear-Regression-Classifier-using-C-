#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <typeinfo>
#include <bits/stdc++.h>

void SelectOption();
using namespace std ;

int m;
vector<float>w, y_pred, slop, y, x[100];

void linearRegression(int feature, int m)
{
    float cal = 0.0 ;
    for(int i = 0 ; i < m ; i++)
    {
        cout << "data" << i <<"" <<endl;
        for(int j = 0 ; j <= feature ; j++)
        {
            cal += w[j]*x[j][i] ;
            cout << "cal: " << cal << "  w[j]: " << w[j] << "  x[j][i]:  " << x[j][i]  << endl;
        }
        y_pred.push_back(cal) ;
    }
    cout << "ypred\n";
    for(int j = 0; j < m; j++){
            cout <<y_pred[j] << endl;
        }

    for(int i = 0; i <= feature; i++){
        float temp = 0.0;
        cout << "feature" << endl;
        for(int j = 0; j < m; j++){
            temp += (y_pred[j]- y[j]) * x[i][j];
            cout << "temp: " << temp << "  x[i][j]  :" << x[i][j] << endl;
        }
        slop.push_back(temp);
    }

    for(int i = 0; i <= feature; i++){
        w[i] = w[i] - 0.01*slop[i];
    }
}
void clearfile()
{
    ofstream ofs;
    ofs.open("learnWi.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}
void TrainModel()
{
    int feature ;
    fstream newfile;
    m = 0 ;
    cout<< "Number of feature : " ;
    cin>> feature ;
    newfile.open("New Text Document.txt",ios::in);
    if(newfile.is_open())
    {
        string str ;
        while(getline(newfile, str))
        {
            m++ ;
            stringstream check1(str);
            string intermediate;
            int i = 1 ;
            for(int k = 0 ; k < m ; k++)
                x[0].push_back(1) ;

            while(getline(check1, intermediate, ','))
            {
                int val = atoi(intermediate.c_str()) ;
                if(i<=feature)
                {

                    x[i].push_back(val) ;
                    i++ ;
                }
                else
                {
                    y.push_back(val) ;
                }

            }
        }

        newfile.close() ;
    }

    for(int i = 0 ; i <= feature ; i++)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        w.push_back(r) ;
    }
    for(int i = 0 ; i <= feature ; i++)
    {
        cout << "initial:" << w[i] << endl;
        cout << "y:" << y[i] << endl;
    }
    clearfile();

    ofstream outfile;
    outfile.open("learnWi.txt", std::ios_base::app);

    linearRegression(feature, m) ;
    for(int i = 0 ; i <= feature ; i++)
    {
        outfile << w[i] << endl;
    }
    outfile.close();
    cout << "Regression Model is trained successfully with " << m << " data";
    cout << endl << "select Option: ";
    SelectOption();

}

void TestModel()
{
    int feature;
    cout << "number of features: ";
    cin >> feature;
    float userval[feature];
    for(int i = 1 ; i <= feature ; i++)
    {
        cout << "x" << i << ": ";
        cin >> userval[i];
    }
    cout << endl;

    float weight[10], var;
    short loop = 0;
    ifstream myfile ("learnWi.txt");
    if (myfile.is_open())
    {
        while (! myfile.eof() )
        {
            myfile >> var;
            weight[loop] = var;
            loop++;
        }
        myfile.close();
    }
    float pred = weight[0];
    for(int i = 1; i <= feature; i++){
        pred += weight[i] * userval[i];
    }

    cout << "Approximate price is : " << pred << " taka";
    SelectOption();

}

void SelectOption()
{
    cout << endl;
    cout << "1. Train Model" << endl;
    cout << "2. Test Model" << endl;
    cout << "3. Exit" << endl;
    int option;
    cin >> option;
    if(option==1)
        TrainModel();
    else if(option==2)
        TestModel();
    else if(option==3)
        exit(0);
    else
    {
        cout << "Wrong input";
        SelectOption();
    }
}
int main()
{
    cout << "\tHouse price prediction" << endl;
    SelectOption();
}
