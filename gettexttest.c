#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


const int bufferSize = 300000;
const char* url = "https://users.pfw.edu/chenz/testWeb/page_000001.html";


int getText(const char* srcAddr, char* buffer, const int bufSize);

void indexPage(const char* url, char* buffer);

int main(){


char* buffer = malloc(sizeof(char) * bufferSize);

indexPage(url, buffer);

printf("%s", buffer);

}


void indexPage(const char* url, char* buffer){

   int returnValue = getText(url, buffer, bufferSize);

    //Clean up the buffer so we can add all words in the trie

    //Remove all numbers
    int i,j;
     for (i = 0; buffer[i] != '\0'; ++i) {
     while (buffer[i] >= '0' && buffer[i] <= '9') {
         for (j = i; buffer[j] != '\0'; ++j) {
            buffer[j] = buffer[j + 1];
         }
         buffer[j] = '\0';
      }
   }

    //Remove all single quotes
    for (int i = 0; buffer[i] != '\0'; i++){

            


    }




/*
//Seperate all words at white spaces
 char* newBuffer;
    newBuffer= strtok(buffer, " ,.-");
    while (newBuffer!= NULL)
    {
        printf("%s\n", newBuffer);
        newBuffer= strtok(NULL, " ,.-");
    }

*/
   

}



/* You should not need to modify this function */
int getText(const char* srcAddr, char* buffer, const int bufSize){
  FILE *pipe;
  int bytesRead;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getText.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
	    buffer);
    return 0;
  }

  bytesRead = fread(buffer, sizeof(char), bufSize-1, pipe);
  buffer[bytesRead] = '\0';

  pclose(pipe);

  return bytesRead;
}