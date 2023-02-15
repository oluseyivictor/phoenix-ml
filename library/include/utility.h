#ifndef UTILITY_H
#define UTILITY_H

struct{
    float ** in;  //2D array for input
    float **tg;  //2D array for targets
    int nips;  //number of inputs
    int nops;   //Number of outputs
    int rows; //number of rows
}ReadData;


char *readIn(FILE * const file);

#endif