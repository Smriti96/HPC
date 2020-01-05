#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>


int count=0;    


void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void crack(char *salt_and_encrypted){
  int x, y, z;     
  char salt[7];    
  char plain[7];   
  char *enc;      

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z); 
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

int main(int argc, char *argv[]){
  crack("$6$KB$O1fCjJpf3J5VAD.EaKzlSKn7O7ezwCNy7Fo0AoaG.rczR.t5xsHa8h7be9Qly8M/dxmaRwhGJMQvn4AUtD0ZE.");
  printf("%d solutions explored\n", count);

  return 0;
}

