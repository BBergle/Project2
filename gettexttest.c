#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* buffer = NULL;
const int bufferSize = 300000;

int getText(const char* srcAddr, char* buffer, const int bufSize);

int main(){

getText("https://users.pfw.edu/chenz/testWeb/page_000001.html",buffer, bufferSize);

printf("%s", buffer);



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