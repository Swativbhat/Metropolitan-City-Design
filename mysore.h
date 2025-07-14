#ifndef _MYSORE_H_INCLUDED_
#define _MYSORE_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include "structure.h"

//Global declaration
#define maxnode 50
#define metronum 42
#define HISTORY_FILE "history.txt"
#define USER_FILE "users.txt"
#define MAX_METROS 42
LIST *adjlist = NULL;
LIST graph[maxnode];
int distances[maxnode][maxnode];

//Static Variables
PLACE data[50]; 
int population, count;
char name[50], pattern[50];
PLACE ARR[50];
int size;
int choice;
BSTNODE *bstroot = NULL;
METRO metros[metronum];
USER currentuser;
BSTNODE* searchresult = NULL;
int metronumber, numtickets;
int n;
int s, d;
char buffer[50];
int source, destination;
int useredgecount;
// int validedgescount = 0;
// int num=50; 
int weight;
int src;
int query; 
int searchnumber;
int searchname;
int preferance;
int numpasses;
int passindex = -1;
int linenumber = 1;
char line[100];
int cancelchoice;
int sizek = 42;
MONTHLYPASS newpass;
int maxjourneytime;
//*********Function Prototypes*********

//:::::::intialiazation function::::::
void initializing_linkedlist();
void initializesegmenttree(int node, int start, int end, SEGNODE segmenttree[], int parent);
void Initializedistancesarray();
//:::::::Inserting/adding functions:::::::
void addnode(int s, int d, int w);
void addedgetofile(int s, int d, int w);
void adding_edges(int n);
void insertname(TRIENODE* root, const char* name);
void addlocationnamestotrie(TRIENODE* root, const char* filename);
void addedge(int u, int v, int w);
MINHEAP* createminheap(int capacity);
void insertminheap(MINHEAP* minheap, MONTHLYPASS* monthlypass);
void add30days(char* startdate, char* expirydate);
void bookticket(METRO* metros, int userid, BSTNODE* bstroot);
void deleteedge(int s, int d);
void writeusertofile(USER user);
BSTNODE *insertbstnode(BSTNODE *root, METRO* metro);

//:::::::::Display/Printing functions:::::::::
void printlist_();
void printlist();
void print_data(const PLACE data[], int size);
void printtrie(TRIENODE* root, char* buffer, int depth);
void printmst(int parent[], int n, int graph[maxnode][maxnode]);
void displaymetro(const METRO metros[], int size);
void displaymetroinfo(BSTNODE *node);
void showloadingspinner();
void updatemetroinfo(const METRO* metros);
void writehistory(const USER* user, const METRO* metro, int numtickets);
void displayminheap(MINHEAP* minheap);
void displaymetroswithinjourneytime(METRO metros[], int size, int maxjourneytime);
void searchanddisplaymetro(const char *searchname, METRO metros[], int size);

//:::::::::Sorting Functions:::::::::
void bubble_sort(PLACE arr[], int size);
void selection_sort_desc(PLACE arr[], int size);
void quicksort(EDGE edges[], int low, int high);
void insertionsort(PLACE arr[], int size);
void mergesort(METRO metros[], int left, int right);
void heapifyup(MINHEAP* minheap, int index);
int partition(EDGE edges[], int low, int high);
void swapedges(EDGE* a, EDGE* b);
void merge(METRO metros[], int left, int mid, int right);
void swap(MONTHLYPASS* a, MONTHLYPASS* b);
void insertionsortbyticketprice(METRO metros[], int size);

//:::::::::Build||Create||Read||Query functions::::::::
void read_from_palcestxt(PLACE data[], int *count);
void buildgraph();
TRIENODE* createnode();
void buildsegmenttree(int node, int start, int end, SEGNODE segmenttree[], int parent);
int querysegmenttree(int node, int start, int end, SEGNODE segmenttree[], int left, int right);
int edgepresentinfile(EDGE edge, const char* filename);
void buildgraphfromdistances(int graph[maxnode][maxnode]);
void getnthmostpopulouscity(PLACE arr[], int n, int size);
BSTNODE *searchbstnode(BSTNODE *root, int metronumber);
bool checkuserexists(const char* username);
int createuser(USER *newuser);
int loginuser();
MINHEAP* createminheap(int capacity);

//::::::::Traversal::::::::
void bfstraversal(int graph[maxnode][maxnode], int n, int src);
void dfstraversal(int graph[maxnode][maxnode], int n, int src, int visited[]);
void preordertraversal(BSTNODE *root);
void postordertraversal(BSTNODE *root);
void inordertraversal(BSTNODE *root);

//:::::::Hashing:::::::::
int generateuserid();
unsigned int hashfunction(const char* str);

//:::::::::Substring search functions:::::::::
int bruteforcesearchinname(const char *pattern, const char *name);
void searchpatterninnames(const PLACE data[], int count, const char *pattern);
int kmpsearch(const char *text, const char *pattern);
void buildkmptable(const char *pattern, int *kmptable);

//:::::::::Minimum Spanning Tree:::::::::
void unionsets(int parent[], int x, int y);
int findparent(int parent[], int node);
void kruskalmst(EDGE* userenterededges, int validedgescount);
void executeprimalgorithm();
int minkey(int key[], int mstset[], int n);
void primmst(int graph[maxnode][maxnode], int n, int src);
//::::::::Shortestpath:::::::::::
int* dijkstra(int src, int n);

//::::::Free() functions:::::
void freetrie(TRIENODE* node);
void freeminheap(MINHEAP* minheap);

//:::::Others:::::
void clearinputbuffer();

#endif