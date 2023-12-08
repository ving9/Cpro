#ifndef HEADER
    #define HEADER
 
typedef struct _point{
    double x;
    double y;
} point;
 
int sum(int a, int b);
void ressum(int* a, int* b, int* result);
double average(int a, int b);
void resaverage(int* a, int* b, double* result);
 
#endif