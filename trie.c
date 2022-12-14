#include <stdio.h>
#include <stdlib.h>
 
// Define the character size
#define CHAR_SIZE 26
 
// Data structure to store a Trie node
struct Trie
{
    int isLeaf;             // 1 when the node is a leaf node
    int count;
    struct Trie* character[CHAR_SIZE];
};
 




void printTrieContents(/* TODO: any parameters you need */struct Trie* root);

int freeTrieMemory(struct Trie **curr, char* str);

struct Trie* getNewTrieNode();

void insert(struct Trie *head, char* str);

int hasChildren(struct Trie* curr);

const int bufferSize = 300000;

char* test = "test";



int main(){


struct Trie* head = getNewTrieNode();
insert(head, test);
printTrieContents(head);



}

void printTrieContents(/* TODO: any parameters you need */struct Trie* root)
{
    // Prints the nodes of the trie
    if (!root)
        return;
    struct Trie* temp = root;
    printf("%c -> ", temp->character);
    for (int i=0; i<CHAR_SIZE; i++) {
        printTrieContents(temp->character[i]); 
    }
}

// Function that returns a new Trie node
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
 
// Iterative function to search a string in a Trie. It returns 1
// if the string is found in the Trie; otherwise, it returns 0.
int search(struct Trie* head, char* str)
{
    // return 0 if Trie is empty
    if (head == NULL) {
        return 0;
    }
 
    struct Trie* curr = head;
    while (*str)
    {
        // go to the next node
        curr = curr->character[*str - 'a'];
 
        // if the string is invalid (reached end of a path in the Trie)
        if (curr == NULL) {
            return 0;
        }
 
        // move to the next character
        str++;
    }
 
    // return 1 if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
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
 
// Recursive function to delete a string from a Trie
int deletion(struct Trie **curr, char* str)
{
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
            deletion(&((*curr)->character[*str - 'a']), str + 1) &&
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