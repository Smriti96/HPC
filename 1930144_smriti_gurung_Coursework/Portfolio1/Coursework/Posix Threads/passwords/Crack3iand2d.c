#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>



int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$V0qTutgzmPspRKsTleW8lpVxQDI4fu.9UWabK1RVpKOo0YCyu1ALZicL83ampe5WvFVL.je0NFWHvq5SVUeSC1",
  "$6$KB$F/vq6r6A4/M48j2mzVz93K1YVnBvEx4neXxICwfUAPT.cSNlqH5LNVNFTCxAH.wHfmVnP4XsmIfvjicgiWgFf.",
  "$6$KB$XIt7PXVcgoQg9dthQcv.k4j3U9EwPy5G8QR9ELGoZ5NhsBQJQdYa4q.TFxD5b3tiB.sMFqUd5pOAjf8HatYMQ/",
  "$6$KB$bnLnm7PXQzjSL98uX/lFpMtgO0lUV98WrA.5O.aJrylXi6fcCSkFBnFoe/7gusdDHMIN6kWG.NiDxlOBbpX9C1"
};



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void crack(char *salt_and_encrypted){
  int w, x, y, z;    
  char salt[7];    
  char plain[7];   
  char *enc;       
  int count = 0;  

  substr(salt, salt_and_encrypted, 0, 6);

  for(w='A'; w<='Z'; w++){
    for(x='A'; x<='Z'; x++){
	for(y='A';y<='Z';y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%c%02d", w,x, y, z); 
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

int main(){
  int i;
   struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  
  for(i=0;i<n_passwords;i<i++) {
    crack(encrypted_passwords[i]);
  }
  
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 

  return 0;
}
