#include <stdio.h>
#include <gsl/gsl_ieee_utils.h>

int
main (void)
{   
    gsl_ieee_env_setup();

    float f = 1000.0/(19.3*1e30);

    printf("Example 1:\n Initail number = %f, divided by 2.0\n", f);
    while (f > 0){
        f /= 2.0;
        gsl_ieee_printf_float(&f);
        printf("\n");
    }

    f = 1000.0/(11.7*1e31);
    printf("\n\nExample 2:\n Initail number = %f, divided by 3.7\n", f);
    while (f > 0){
        f /= 3.7;
        gsl_ieee_printf_float(&f);
        printf("\n");
    }
    return 0;
}

