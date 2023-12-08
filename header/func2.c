double average(int a, int b)
{
    return (double)(a+b)/2;
}
 
void resaverage(int* a, int* b, double* result)
{
    *result=(double)(*a+*b)/2;
    return;
}