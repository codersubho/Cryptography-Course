
#include <stdint.h>
#include <stdio.h>
#include <math.h>



int no_of_1_bits(int n){

    int ans = 0;
    int tmp = n;


    while(tmp != 0){
        ans += tmp & 1;
        tmp >>= 1;
    }


    return ans;

}



int lfsr_period(int num, int arr[], int bitLen)
{
    int start_state = 1;
    int lfsr = start_state;
    int bit;
    int period = 0;

    do
    {   bit = 0;
        for(int i = 0;i< num ; i ++){
            bit ^= lfsr >> (bitLen - arr[i]);
        }
        bit = bit & 1;

        lfsr = (lfsr >> 1) | (bit << (bitLen-1));
        ++period;
    }
    while ((lfsr != start_state));


    return period;
}

void generate_primitive_poly(int deg){
    int l = pow(2,deg-1);
    for(int j=1;j < l;j++){
        int tap = (1 << (deg-1)) | j;

        int numtaps = no_of_1_bits(tap);


        int tapArray[numtaps];

        int tmp = tap;
        int position_in_taps = 1;
        int arrIndex = numtaps-1;


        while(tmp != 0){
            if (tmp & 1 == 1){
                tapArray[arrIndex] = position_in_taps;
                arrIndex-=1;
            }
            position_in_taps+=1;
            tmp >>=1 ;
        }


        int period = lfsr_period(numtaps, tapArray, deg);
        if(period == pow(2,deg) - 1){
            for(int j = 0; j < numtaps ; j++){
                int coeff = tapArray[j];
                printf("x^ %d + ",coeff);
                //fflush( stdout );
            }
            printf("1\n");
        }
   }
    return;
}
void main(){
    int maxDeg = 16;
    for(int deg = 4; deg < maxDeg + 1 ; deg ++){
        printf("The primitive polynomials of deg %d are\n", deg);
        generate_primitive_poly(deg);

    }

}

