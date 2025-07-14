#ifndef _STRUCTURE_H_INCLUDED_
#define _STRUCTURE_H_INCLUDED_
typedef struct node {
    int vertexnum;
    int weight;
    struct node *next;
} NODE;

typedef struct list {
    NODE *head;
} LIST;

typedef struct {
    int index;
    char name[50];
    int population;
} PLACE;

typedef struct TrieNode {
    struct TrieNode* children[26];
    int isendofword;
} TRIENODE;

typedef struct segnode {
    int value;
} SEGNODE;

typedef struct {
    int source;
    int destination;
    int weight;
} EDGE;

typedef struct user {
    int userid;
    char username[20];
    char password[20];
} USER;

typedef struct 
{
    int metronumber;
    char metroname[20];
    char metrosource[20];
    char metrodestination[20];
    int availableseats;
    int bookedseats;
    int ticketprice;
    int journeytime;
}METRO;

typedef struct bstnode
{
    int metronumber;
    METRO* metroinfo; 
    struct bstnode *left;
    struct bstnode *right;
} BSTNODE;

typedef struct monthlypass {
    char name[20];
    char source[20];
    char destination[20];
    char startdate[20];
    char expirydate[20];
    int amount;
} MONTHLYPASS;

typedef struct MinHeap {
    MONTHLYPASS* heaparray;
    int capacity;
    int size;
} MINHEAP;


#endif