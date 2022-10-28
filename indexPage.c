/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
int indexPage(const char* url, char* buffer);

int addWordOccurrence(const char* word, const int wordLength
		       /* TODO: other parameters you need */);

void printTrieContents(/* TODO: any parameters you need */);

int freeTrieMemory(struct Trie **curr, char* str);

int getText(const char* srcAddr, char* buffer, const int bufSize);

struct Trie* getNewTrieNode();

void insert(struct Trie *head, char* str);

int hasChildren(struct Trie* curr);

const int bufferSize = 300000;

int main(int argc, char** argv){
  /* TODO: write the (simple) main function

  /* argv[1] will be the URL to index, if argc > 1 */
  char* buffer = malloc(sizeof(char) * bufferSize);
  //Testing indexPage with a hardcoded link
  indexPage("https://users.pfw.edu/chenz/testWeb/page_000001.html", buffer);
  printf("%s", buffer);

  return 0;
}

/* TODO: define the functions corresponding to the above prototypes */

/* TODO: change this return type */
int indexPage(const char* url, char* buffer){
    
    getText(url, buffer, 300000);

}

int addWordOccurrence(const char* word, const int wordLength
		       /* TODO: other parameters you need */)
{}

void printTrieContents(/* TODO: any parameters you need */)
{}

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
