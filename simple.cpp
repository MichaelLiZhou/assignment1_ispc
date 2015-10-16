#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#pragma warning (disable: 4244)
#pragma warning (disable: 4305)
#endif

#include <stdio.h>
#include <algorithm>
#include <string.h>
#include "timing.h"
#include <iostream>
#include "simple_ispc.h"
using namespace ispc;
void squareRootSerial(float random_array[], float output_array[]){
  for(int index = 0; index < 10000; index++){
    float A = random_array[index];
    float x;
    if(A <=(float)1){
      x = 1;
    }
    if(A > 1 && A <= (float)2){
      x = 2;
    }
    if(A > 2 && A <= (float)3){
      x = 3;
    }

    float diff;
    float x_next;
    diff = 1;
    
    while (diff > 0.0001){
      x_next = 0.5*(x + (A/x));
      diff = x_next - x;
      if ( diff < 0){
        diff *= -1;
      }
      x = x_next;
    }
  output_array[index] = x;
  }
}

int main(int argc, char const *argv[]){

  float random_array[10000];
  float output_array[10000];
  float random;
	double minISPC = 1e30;
	for(int k = 0; k < 2000; k++){ 	
    for(int i = 0; i < 10000; i++){
      random = (float) (rand()) / ((float) (RAND_MAX/3));
      random_array[i] = random;
 		 }
    reset_and_start_timer();
    Jsqrt(random_array, output_array);
    double dt = get_elapsed_mcycles();
    minISPC = std::min(minISPC, dt);
	}
  printf("[square root ispc]:\t[%.3f] million cycles\n", minISPC); 

  double minSerial = 1e30;
  for(int k = 0; k < 2000; k++){
    for(int i = 0; i < 10000; i++){
      random = (float) (rand()) / ((float) (RAND_MAX/3));
      random_array[i] = random;
    }
    reset_and_start_timer();
    squareRootSerial(random_array,output_array);
    double dt = get_elapsed_mcycles();
    minSerial = std::min(minSerial, dt);
  }
    for (int i = 0 ; i < 10 ; i++) {
      std::cout<<random_array[i]<<" "<<output_array[i]<<'\n';
    }
    printf("[square root serial]:\t\t[%.3f] millon cycles\n", minSerial);
    printf("\t\t\t\t(%.2fx speedup from ISPC)\n", minSerial/minISPC);
  return 0;
}

