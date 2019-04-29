/*
 * gaussianeq.cpp
 *
 * Authors:
 *   Lucas Gutierrez lucas@codesociety.com.ar
 *
 * Copyright (C) 2012 Lucas Gutierrez
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
using namespace std;
   
int i, j, z=4;
void gauss_2x2(double m1[1][2], double m2[2][3]);
void gauss_3x3(double m1[1][2], double m2[2][3], double m3[3][4]);
void gauss_4x4(double m1[1][2], double m2[2][3], double m3[3][4], double m4[4][5]);
void gauss_5x5(double m1[1][2], double m2[2][3], double m3[3][4], double m4[4][5], double m5[5][6]);
void mostrar(int dimension, double m1[1][2], double m2[2][3], double m3[3][4], double m4[4][5], double m5[5][6]);
void incognitas(int dimension, double *p_m5, double *p_m4, double *p_m3, double *p_m2, double *p_m1);
void ecuaciones(int dimension, double *p_m5, double *p_m4, double *p_m3, double *p_m2, double *p_m1);

int main(int argc, char *argv[]) {
    double m5[5][6], *p_m5;
    double m4[4][5], *p_m4;
    double m3[3][4], *p_m3;
    double m2[2][3], *p_m2;
    double m1[1][2], *p_m1;
    int dimension;
    
    if (argc==1) {
        cout<<"\nThis small program solves systems of linear equations using Gauss-Jordan elimination algorithm."
        <<"\nSupported dimensions are: 2x2, 3x3, "
        <<"4x4 and 5x5."<<"\n\nUsage:\n"<<"\tgaussianeq -d "
        <<"<dimension> -v <values>"<<"\n\nExamples:\n"
        <<"\tgaussianeq -d 2x2 -v 10 4 62 3 5 30\n";
        return 0;
    } 
    else {
        if(strcmp(argv[1], "-d")==0) {
            if(strcmp(argv[2], "2x2")==0) {
                dimension=2;
            }
            else if(strcmp(argv[2], "3x3")==0) {
                dimension=3;
            }
            else if(strcmp(argv[2], "4x4")==0) {
                dimension=4;
            }
            else if(strcmp(argv[2], "5x5")==0) {
                dimension=5;
            }
        }
    }
    
    if(strcmp(argv[3], "-v")==0) {
        switch(dimension) {
            case 2:
                for(i=0;i<2;i++) {
                    for(j=0;j<3;j++) {
                        m2[i][j]=atoi(argv[z]);
                        z++;
                    }
                }
                break;
            case 3:
                for(i=0;i<3;i++) {
                    for(j=0;j<4;j++) {
                        m3[i][j]=atoi(argv[z]);
                        z++;
                    }
                }
                break;
            case 4:
                for(i=0;i<4;i++) {
                    for(j=0;j<5;j++) {
                        m4[i][j]=atoi(argv[z]);
                        z++;
                    }
                }
                break;
            case 5:
                for(i=0;i<5;i++) {
                    for(j=0;j<6;j++) {
                        m5[i][j]=atoi(argv[z]);
                        z++;
                    }
                }
                break;
        }
    }

    switch(dimension) {
        case 2:
            gauss_2x2(m1, m2);
            p_m2=&m2[0][0], p_m1=&m1[0][0];
            break;
        case 3:
            gauss_3x3(m1, m2, m3);
            p_m3=&m3[0][0], p_m2=&m2[0][0], p_m1=&m1[0][0];
            break;
        case 4:
            gauss_4x4(m1, m2, m3, m4);
            p_m4=&m4[0][0], p_m3=&m3[0][0], p_m2=&m2[0][0], p_m1=&m1[0][0];
            break;
        case 5:
            gauss_5x5(m1, m2, m3, m4, m5);
            p_m5=&m5[0][0], p_m4=&m4[0][0], p_m3=&m3[0][0], p_m2=&m2[0][0], p_m1=&m1[0][0];
            break;
    }    
    
    mostrar(dimension, m1, m2, m3, m4, m5);
    ecuaciones(dimension, p_m5, p_m4, p_m3, p_m2, p_m1);
    incognitas(dimension, p_m5, p_m4, p_m3, p_m2, p_m1);
    cout<<endl;
}

void ecuaciones(int dimension, double *p_m5, double *p_m4, double *p_m3, double *p_m2, double *p_m1) {
    switch(dimension) {
        case 2:
            for(i=0;i<3;i++) cout<<";"<<p_m2[i];
            for(i=0;i<2;i++) cout<<";"<<p_m1[i];
            break;
        case 3:
            for(i=0;i<4;i++) cout<<";"<<p_m3[i];
            for(i=0;i<3;i++) cout<<";"<<p_m2[i];
            for(i=0;i<2;i++) cout<<";"<<p_m1[i];
            break;
        case 4:
            for(i=0;i<5;i++) cout<<";"<<p_m4[i];
            for(i=0;i<4;i++) cout<<";"<<p_m3[i];
            for(i=0;i<3;i++) cout<<";"<<p_m2[i];
            for(i=0;i<2;i++) cout<<";"<<p_m1[i];
            break;
        case 5:
            for(i=0;i<6;i++) cout<<";"<<p_m5[i];
            for(i=0;i<5;i++) cout<<";"<<p_m4[i];
            for(i=0;i<4;i++) cout<<";"<<p_m3[i];
            for(i=0;i<3;i++) cout<<";"<<p_m2[i];
            for(i=0;i<2;i++) cout<<";"<<p_m1[i];
            break;
    }
}

void incognitas(int dimension, double *p_m5, double *p_m4, double *p_m3, double *p_m2, double *p_m1) {
    double incog_2[2], incog_3[3], incog_4[4], incog_5[5];
    
    switch(dimension) {
        case 2:
            incog_2[1]=p_m1[1]/p_m1[0];
            incog_2[0]=(p_m2[2]-p_m2[1]*incog_2[1])/p_m2[0];
            cout<<";"<<incog_2[0]<<";"<<incog_2[1];
            break;
        case 3:
            incog_3[2]=p_m1[1]/p_m1[0];
            incog_3[1]=(p_m2[2]-p_m2[1]*incog_3[2])/p_m2[0];
            incog_3[0]=(p_m3[3]-p_m3[1]*incog_3[1]-p_m3[2]*incog_3[2])/p_m3[0];
            cout<<";"<<incog_3[0]<<";"<<incog_3[1]<<";"<<incog_3[2];
            break;
        case 4:
            incog_4[3]=p_m1[1]/p_m1[0];
            incog_4[2]=(p_m2[2]-p_m2[1]*incog_4[3])/p_m2[0];
            incog_4[1]=(p_m3[3]-p_m3[1]*incog_4[2]-p_m3[2]*incog_4[3])/p_m3[0];
            incog_4[0]=(p_m4[4]-p_m4[1]*incog_4[1]-p_m4[2]*incog_4[2]-p_m4[3]*incog_4[3])/p_m4[0];
            cout<<";"<<incog_4[0]<<";"<<incog_4[1]<<";"<<incog_4[2]<<";"<<incog_4[3];
            break;
        case 5:
            incog_5[4]=p_m1[1]/p_m1[0];
            incog_5[3]=(p_m2[2]-p_m2[1]*incog_5[4])/p_m2[0];
            incog_5[2]=(p_m3[3]-p_m3[1]*incog_5[3]-p_m3[2]*incog_5[4])/p_m3[0];
            incog_5[1]=(p_m4[4]-p_m4[1]*incog_5[2]-p_m4[2]*incog_5[3]-p_m4[3]*incog_5[4])/p_m4[0];
            incog_5[0]=(p_m5[5]-p_m5[1]*incog_5[1]-p_m5[2]*incog_5[2]-p_m5[3]*incog_5[3]-p_m5[4]*incog_5[4])/p_m5[0];
            cout<<";"<<incog_5[0]<<";"<<incog_5[1]<<";"<<incog_5[2]<<";"<<incog_5[3]<<";"<<incog_5[4];
            break;
    }
}

void mostrar(int dimension, double m1[1][2], double m2[2][3], double m3[3][4], double m4[4][5], double m5[5][6]) {
    switch(dimension) {
        case 2:
            cout<<"2x2";
            for(i=0;i<1;i++) for(j=0;j<2;j++) cout<<";"<<m1[i][j];
            break;
        case 3:
            cout<<"3x3";
            for(i=0;i<2;i++) for(j=0;j<3;j++) cout<<";"<<m2[i][j];
            for(i=0;i<1;i++) for(j=0;j<2;j++) cout<<";"<<m1[i][j];
            break;
        case 4:
            cout<<"4x4";
            for(i=0;i<3;i++) for(j=0;j<4;j++) cout<<";"<<m3[i][j];
            for(i=0;i<2;i++) for(j=0;j<3;j++) cout<<";"<<m2[i][j];
            for(i=0;i<1;i++) for(j=0;j<2;j++) cout<<";"<<m1[i][j];
            break;
        case 5:
            cout<<"5x5";
            for(i=0;i<4;i++) for(j=0;j<5;j++) cout<<";"<<m4[i][j];
            for(i=0;i<3;i++) for(j=0;j<4;j++) cout<<";"<<m3[i][j];
            for(i=0;i<2;i++) for(j=0;j<3;j++) cout<<";"<<m2[i][j];
            for(i=0;i<1;i++) for(j=0;j<2;j++) cout<<";"<<m1[i][j];
            break;
    }
}
    
void gauss_2x2(double m1[1][2], double m2[2][3]) {
    for(i=0;i<1;i++) {
        for(j=0;j<2;j++) {
            m1[i][j]=double(m2[i+1][j+1])-(double(m2[i+1][0])/double(m2[0][0]))*double(m2[0][j+1]);
        }
    }
}

void gauss_3x3(double m1[1][2], double m2[2][3], double m3[3][4]) {
    for(i=0;i<2;i++) {
        for(j=0;j<3;j++) {
            m2[i][j]=double(m3[i+1][j+1])-(double(m3[i+1][0])/double(m3[0][0]))*double(m3[0][j+1]);
        }
    }
    
    for(i=0;i<1;i++) {
        for(j=0;j<2;j++) {
            m1[i][j]=double(m2[i+1][j+1])-(double(m2[i+1][0])/double(m2[0][0]))*double(m2[0][j+1]);
        }
    }
}

void gauss_4x4(double m1[1][2], double m2[2][3], double m3[3][4], double m4[4][5]) {
    for(i=0;i<3;i++) {
        for(j=0;j<4;j++) {
            m3[i][j]=double(m4[i+1][j+1])-(double(m4[i+1][0])/double(m4[0][0]))*double(m4[0][j+1]);
        }
    }
    
    for(i=0;i<2;i++) {
        for(j=0;j<3;j++) {
            m2[i][j]=double(m3[i+1][j+1])-(double(m3[i+1][0])/double(m3[0][0]))*double(m3[0][j+1]);
        }
    }
    
    for(i=0;i<1;i++) {
        for(j=0;j<2;j++) {
            m1[i][j]=double(m2[i+1][j+1])-(double(m2[i+1][0])/double(m2[0][0]))*double(m2[0][j+1]);
        }
    }
}

void gauss_5x5(double m1[1][2], double m2[2][3], double m3[3][4], double m4[4][5], double m5[5][6]) {
    for(i=0;i<4;i++) {
        for(j=0;j<5;j++) {
            m4[i][j]=double(m5[i+1][j+1])-(double(m5[i+1][0])/double(m5[0][0]))*double(m5[0][j+1]);
        }
    }
    
    for(i=0;i<3;i++) {
        for(j=0;j<4;j++) {
            m3[i][j]=double(m4[i+1][j+1])-(double(m4[i+1][0])/double(m4[0][0]))*double(m4[0][j+1]);
        }
    }
    
    for(i=0;i<2;i++) {
        for(j=0;j<3;j++) {
            m2[i][j]=double(m3[i+1][j+1])-(double(m3[i+1][0])/double(m3[0][0]))*double(m3[0][j+1]);
        }
    }
    
    for(i=0;i<1;i++) {
        for(j=0;j<2;j++) {
            m1[i][j]=double(m2[i+1][j+1])-(double(m2[i+1][0])/double(m2[0][0]))*double(m2[0][j+1]);
        }
    }
}
