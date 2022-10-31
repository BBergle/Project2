#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


const int bufferSize = 300000;
const char* url = "https://sjmulder.nl/en/textonly.html";


int getText(const char* srcAddr, char* buffer, const int bufSize);

void indexPage(const char* url, char* buffer);

int main(){


char* buffer = malloc(sizeof(char) * bufferSize);

indexPage(url, buffer);

printf("%s", buffer);

}


void indexPage(const char* url, char* buffer){

   int returnValue = getText(url, buffer, bufferSize);

int i,j;
//Clean up the buffer by removing numbers and the leading b 
for (i = 0; buffer[i] != '\0'; ++i) {
     while ((buffer[i] == 'b' && buffer[i+1] == '\'') || buffer[i] == '!' || buffer[i] == '.' || buffer[i] == ',' || buffer[i] == '?' 
     || buffer[i] == '\'' || (buffer[i] >= '0' && buffer[i] <= '9')) {
         for (j = i; buffer[j] != '\0'; ++j) {
            buffer[j] = buffer[j + 1];
         }
         buffer[j] = '\0';
      }
   }

//make everything lowercase
for(i = 0; buffer[i] != '\0'; i++){
   if(isupper(buffer[i])){
      buffer[i] = tolower(buffer[i]);
   }
}



//Seperate all words at white spaces and all punctuation
 char* newBuffer;
    newBuffer= strtok(buffer, " \n,.-()");
    while (newBuffer!= NULL)
    {
        printf("%s\n", newBuffer);
        newBuffer= strtok(NULL, " \n,.-()");
    }




}// End of indexPage

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