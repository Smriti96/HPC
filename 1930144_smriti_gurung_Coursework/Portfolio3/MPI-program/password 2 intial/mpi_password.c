
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <crypt.h>
#include <mpi.h>




int n_passwords = 4;
pthread_t t1, t2;
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
  
void kernel_function1(char *salt_and_encrypted){
  int s, r, g;     
  char salt[7];    

  char plain[7];   
  char *enc;       
  int count = 0;   

  substr(salt, salt_and_encrypted, 0, 6);
  
  for(s='A'; s<='M'; s++){
    for(r='A'; r<='Z'; r++){
      for(g=0; g<=99; g++){
	
	sprintf(plain, "%c%c%02d",s, r, g);
	enc = (char *) crypt(plain, salt);
	count++;
	if(strcmp(salt_and_encrypted, enc) == 0){
	  printf("#%-8d%s %s\n", count, plain, enc);
	} else {
	  printf(" %-8d%s %s\n", count, plain, enc);
	}
      }
    }
  }
  printf("%d solutions explored\n", count);
}
void kernel_function2(char *salt_and_encrypted){
  int s, r, g;     
  char salt[7];    

  char plain[7];   
  char *enc;       
  int count = 0;  

  substr(salt, salt_and_encrypted, 0, 6);
  
  for(s='N'; s<='Z'; s++){
    for(r='A'; r<='Z'; r++){
      for(g=0; g<=99; g++){
	
	sprintf(plain, "%c%c%02d",s, r, g);
	enc = (char *) crypt(plain, salt);
	count++;
	if(strcmp(salt_and_encrypted, enc) == 0){
	  printf("#%-8d%s %s\n", count, plain, enc);
	} else {
	  printf(" %-8d%s %s\n", count, plain, enc);
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

int main(int argc, char** argv) {
 struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);

 
  int size, rank;
int i;

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(size != 3) {
    if(rank == 0) {
      printf("This program needs to run on exactly 3 processes\n");
    }
  } else {
    if(rank ==0){

      int s;
    
      MPI_Send(&s, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      MPI_Send(&s, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);


 
    } else if(rank==1){
      int number;
      MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, 
                         MPI_STATUS_IGNORE);
        for(i=0;i<n_passwords;i<i++) {
          kernel_function1(encrypted_passwords[i]);
        }
      }
      else{
      int number;
      MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, 
                         MPI_STATUS_IGNORE);
        for(i=0;i<n_passwords;i<i++) {
          kernel_function2(encrypted_passwords[i]);
        }
      }
    }
    MPI_Finalize(); 
 clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9)); 

  return 0;
}
