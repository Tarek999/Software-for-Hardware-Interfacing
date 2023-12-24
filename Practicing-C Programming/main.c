#include <stdio.h>
/*Homework*/
int main()
{
    int n,i ;
    float exp = 1 , newterm =1 ,x ;

    printf("Please enter the exponent:") ;
    scanf("%f",&x) ;
    printf("Please enter the number of iteration:") ;
    scanf("%d",&n) ;

    for(i= 1; i<n; i++)
    {
        newterm *= x/i ;
        exp += newterm ;
    }

    printf("result = %f",exp);
    return 0;
}
