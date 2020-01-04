#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>

__device__ int is_a_match(char *attempt) {
  char plain_password1[] = "SM4565";
  char plain_password2[] = "RI7412";
  char plain_password3[] = "TI3211";
  char plain_password4[] = "GU4747";

  char *s = attempt;
  char *m = attempt;
  char *r = attempt;
  char *i = attempt;
  char *s1 = plain_password1;
  char *s2 = plain_password2;
  char *s3 = plain_password3;
  char *s4 = plain_password4;

  while(*s == *s1) {
   if(*s == '\0')
    {
    printf("Password: %s\n",plain_password1);
      break;
    }

    s++;
    s1++;
  }
    
  while(*m == *s2) {
   if(*m == '\0')
    {
    printf("Password: %s\n",plain_password2);
      break;
}

    m++;
    s2++;
  }

  while(*r == *s3) {
   if(*r == '\0')
    {
    printf("Password: %s\n",plain_password3);
      break;
    }

    r++;
    s3++;
  }

  while(*i == *s4) {
   if(*i == '\0')
    {
    printf("Password: %s\n",plain_password4);
      return 1;
    }

    i++;
    s4++;
  }
  return 0;

}
__global__ void  kernel() {
char h,a,r,t;
 
  char password[7];
  password[6] = '\0';

int i = blockIdx.x+65;
int j = threadIdx.x+65;
char firstValue = i;
char secondValue = j;
    
password[0] = firstValue;
password[1] = secondValue;
    for(h='0'; h<='9'; h++){
      for(a='0'; a<='9'; a++){
        for(r='0';r<='9';r++){
          for(t='0';t<='9';t++){
            password[2]=h;
            password[3]=a;
            password[4]=r;
            password[5]=t;
          if(is_a_match(password)) {
        
          }
             else {
                
            }
          }
        } 
      }
   }
}
int time_difference(struct timespec *start,
                    struct timespec *finish,
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec;
  long long int dn =  finish->tv_nsec - start->tv_nsec;

  if(dn < 0 ) {
    ds--;
    dn += 1000000000;
  }
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}


int main() {

  struct  timespec start, finish;
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

kernel <<<26,26>>>();
  cudaThreadSynchronize();

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9));
  return 0;
}



