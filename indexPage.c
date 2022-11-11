/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* TODO: structure definitions */
#define CHAR_SIZE 26

// Data structure to store a Trie node
struct Trie
{
    int count;
    int isLeaf;             // 1 when the node is a leaf node
    struct Trie* character[CHAR_SIZE];
};


/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

/* TODO: change this return type */
void indexPage(const char* url, char* buffer);//Benny Bergle

int addWordOccurrence(const char* word, const int wordLength,struct Trie* root);//Max Claypool

void printTrieContents(struct Trie* root, char* str);//Max Claypool

int freeTrieMemory(struct Trie **curr, char* str);//Benny Bergle

int getText(const char* srcAddr, char* buffer, const int bufSize);

struct Trie* getNewTrieNode();//Benny Bergle

void insert(struct Trie *head, char* str);//Benny Bergle

int hasChildren(struct Trie* curr);//Benny Bergle

const int bufferSize = 300000;

char* test = "test";

/* TODO: define the functions corresponding to the above prototypes */

/* TODO: change this return type */
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


}

int addWordOccurrence(const char* word, const int wordLength, struct Trie* root
		       /* TODO: other parameters you need */)
{
        //index of the constant word.
    int idx;
     // start from the root node
    struct Trie* curr = root;
    //Move from each letter in the word
    for (int i=0;i<wordLength;i++)
    {
        //Set the index equal to the word.
        idx = (word[i]);
        //set the index to a number value by subtracting character a.
        //idx-'a';
        //check if the value is inside the range of the alphabet.
        if(idx >= 0 && idx <= 25){
            //if the next is null, then make space for it.
            if(curr->character[idx]==NULL){
                //allocate memory .
                curr->character[idx] = malloc(sizeof(curr));
                
            }
            //Make a new node.
            curr->character[idx]=getNewTrieNode();
            //make a new node at the index.
            curr = curr->character[idx];
            //increase the count of the new character.
            curr->count = curr->count++;

        }
    }
 
    // mark the current node as a leaf
    curr->isLeaf = 1;
    //return 1 for a successful run of the function.
    return 1;
}

void printTrieContents(/* TODO: any parameters you need */
struct Trie* root, char* str)
{
        // Prints the nodes of the trie
    //string to hold all of the letters of each trie.
        str = malloc(sizeof(char)*(CHAR_SIZE)+sizeof(str));
        
        //if the root is nonexistant, continue on from where the function was called.
        //and print new line.

        if (!root){
        printf("\n");
            return;
        }
        //make a temporary trie to crawl through nodes.
        struct Trie* temp = root;
        for(char i=0;i<CHAR_SIZE;i++){
            //if there is something in the location, then add the letter to the string,
            //then run a different instance of the function with the character and part of the string.
            if(temp->character[i]!=NULL){
                str += (i+'a');
                printTrieContents(temp->character[i],str);
            }
        }
        //check if the letter is a leaf, then print if so.
        if(temp->isLeaf==1){
            temp->count=temp->count++;

   //         printf("%s:%s",str,temp->count);
        }
}

// Returns 1 if a given Trie node has any children
int hasChildren(struct Trie* curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i]) {
            return 1;       // child found
        }
    }
 
    return 0;
}

int freeTrieMemory(struct Trie **curr, char* str){

    // return 0 if Trie is empty
    if (*curr == NULL) {
        return 0;
    }
 
    // if the end of the string is not reached
    if (*str)
    {
        // recur for the node corresponding to the next character in
        // the string and if it returns 1, delete the current node
        // (if it is non-leaf)
        if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
            freeTrieMemory(&((*curr)->character[*str - 'a']), str + 1) &&
            (*curr)->isLeaf == 0)
        {
            if (!hasChildren(*curr))
            {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
            else {
                return 0;
            }
        }
    }
 
    // if the end of the string is reached
    if (*str == '\0' && (*curr)->isLeaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!hasChildren(*curr))
        {
            free(*curr);    // delete the current node
            (*curr) = NULL;
            return 1;       // delete the non-leaf parent nodes
        }
 
        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            (*curr)->isLeaf = 0;
            return 0;       // don't delete its parent nodes
        }
    }
 
    return 0;
}


//Returns a new trie node
struct Trie* getNewTrieNode()
{
    struct Trie* node = (struct Trie*)malloc(sizeof(struct Trie));
    node->isLeaf = 0;
 
    for (int i = 0; i < CHAR_SIZE; i++) {
        node->character[i] = NULL;
    }
 
    return node;
}


// Iterative function to insert a string into a Trie
void insert(struct Trie *head, char* str)
{
    // start from the root node
    struct Trie* curr = head;
    while (*str)
    {
        // create a new node if the path doesn't exist
        if (curr->character[*str - 'a'] == NULL) {
            curr->character[*str - 'a'] = getNewTrieNode();
        }
 
        // go to the next node
        curr = curr->character[*str - 'a'];
        curr->count=curr->count++;
        // move to the next character
        str++;
    }
 
    // mark the current node as a leaf
    curr->isLeaf = 1;
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


int main(int argc, char** argv){

    if(argc < 2){
        fprintf(stderr, "Please enter the correct ammount of args");
        return -1;
    }

    char *url = argv[1];
    printf("%s", url);
    char* buffer = malloc(sizeof(char) * bufferSize);
    struct Trie *head = getNewTrieNode();
    indexPage(url, buffer);
    insert(head, buffer);
   // printTrieContents(head,"");
    freeTrieMemory(&head, buffer);
    free(buffer);
    //Not finished and will not work with runTestCases
    //Prints buffer contents if executed like ./indexPage "https://users.pfw.edu/chenz/testWeb/page_000001.html"
    
  
  
}
