#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>


int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$6SsUGf4Cq7/Oooym9WWQN3VKeo2lynKV9gXVyEG4HvYy1UFRx.XAye89TLp/OTcW7cGpf9UlU0F.cK/S9CfZn1",
  "$6$KB$Lsc5GJc6UWLEyVocbQBpezWOUtiLMkAO6MZ9vJY15o7P5jBXl4w7zxwolBkw5Z4jftUo.6aLeQ6gMUBrADh2q0",
  "$6$KB$Uz4xNPXyfRlE5p5Q9Lc5OYV8gx0aEC0y2ANJwH7YtOLRcww/Bwyu4fRegp5qiVdx.oiUZEreiOqMeYkVp1.P.0",
  "$6$KB$lbJjW9gPftksxWfNDz2.ekZdGfZV1747n1ERgTAcU8m7eTS9xtAruTZIDDuXy43qZJJvtuYtZeKsRMsGJUSR7."
};



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}


void *function()
{
   int i;
   pthread_t t1, t2;
    void *kernel_function_1();
   void *kernel_function_2();

   for(i=0;i<n_passwords;i<i++) {
     pthread_create(&t1, NULL, kernel_function_1, encrypted_passwords[i]);
     pthread_create(&t2, NULL, kernel_function_2, encrypted_passwords[i]);

     pthread_join(t1, NULL);
     pthread_join(t2, NULL);

  }
}

void *kernel_function_1(char *salt_and_encrypted){
  int d, e, f;     
  char salt[7];   
  char plain[7];  
  char *enc;       
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);

  for(d='A'; d<='M'; d++){
    for(e='A'; e<='Z'; e++){
      for(f=0; f<=99; f++){
        sprintf(plain, "%c%c%02d", d, e, f); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }

      }
    }
  }
  printf("%d solutions explored\n", count);
}
void *kernel_function_2(char *salt_and_encrypted){
  int x, y, z;     
  char salt[7];   
  char plain[7];  
  char *enc;      
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='N'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } 
      }
    }
  }
  printf("%d solutions explored\n", count);
}
int time_difference(struct timespec *start, struct timespec *finish, 
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

int main(int argc, char *argv[]){
  
struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
 
  
  
    function();
  

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 

  return 0;
}
