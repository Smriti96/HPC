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
  char plain[4];   
  plain[3] = '\0'; 
  char *enc;       

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='a'; x<='z'; x++){
    plain[0] = x;
    for(y='a'; y<='z'; y++){
      plain[1] = y;
      for(z='a'; z<='z'; z++){
        plain[2] = z; 
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
  if(argc!=2){
    printf("This program requires you to provide an encrypted password\n");
    return 1;
  }

  if(strlen(argv[1])!=92){
    printf("Encrypted passwords should be 92 characters long including salt\n");
    return 1; 
  }

  crack(argv[1]);
  printf("%d solutions explored\n", count);

  return 0;
}

