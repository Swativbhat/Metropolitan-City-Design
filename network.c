#include "mysore.h"
// #ifndef MYSORE_H
// #define MYSORE_H
/**
Funtion Name:initializing_linkedlist
Input Para:NIL
Return Type:void
Description:the function allocates memory for an array of linked lists**/
void initializing_linkedlist() 
{
    LIST *adjlist = (LIST *)malloc(maxnode * sizeof(LIST));
    for (int i = 0; i < maxnode; i++) 
    {
      adjlist[i].head = NULL;
    }
}
/*
Funtion Name:addnode
Input Para:int s,intd,int d
Return Type:void
Description:This function adds the edges to the adjacency list
*/
void addnode(int s, int d, int w) 
{
    // LIST *adjlist = NULL;
    NODE *dest, *temp, *src;

    if (adjlist[s].head == NULL)
    {
         src = (NODE *)malloc(sizeof(NODE));
         src->vertexnum = s;
         src->weight = 0;
         src->next = NULL;
         adjlist[s].head = src;
    }

    dest = (NODE *)malloc(sizeof(NODE));
    dest->vertexnum = d;
    dest->weight = w;
    dest->next = NULL;
    temp = adjlist[s].head;
    while (temp->next != NULL) 
      {
        temp = temp->next;
      }
    temp->next = dest;
}
/*
Funtion Name:printlist_
Input Para:NIL
Return Type:void
Description:This function prints the adjacency list
*/
void printlist_()
{
    int i;
    LIST *adjlist = NULL;
    for (i = 0; i < maxnode; i++) 
    {
        NODE *p = adjlist[i].head;
        printf("adjacency list for vertex %d\n", i);
        while (p) 
        {
            printf("%d(%d) ", p->vertexnum, p->weight);
            p = p->next;
        }
        printf("\n");
    }
}
/*
Funtion Name:printlist
Input Para:NIL
Return Type:void
Description:This function read text file distances.txt and create a
            temporary adjacency list and print the adjacency list
*/
void printlist() 
{
    FILE *file = fopen("distances.txt", "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    LIST *tempadjlist = (LIST *)malloc(maxnode * sizeof(LIST));
    if (tempadjlist == NULL)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < maxnode; i++)
    {
        tempadjlist[i].head = NULL;
    }
    int source, destination, weight;
    while (fscanf(file, "%d %d %d", &source, &destination, &weight) == 3)
    {
        NODE *newnode = (NODE *)malloc(sizeof(NODE));
        newnode->vertexnum = destination;
        newnode->weight = weight;
        newnode->next = tempadjlist[source].head;
        tempadjlist[source].head = newnode;
    }
    for (int i = 0; i < maxnode; i++) 
    {
        NODE *p = tempadjlist[i].head;
        printf("%d --> ", i);
        while (p) 
        {
            printf("%d(%d) ", p->vertexnum, p->weight);
            p = p->next;
        }
        printf("\n");
    }
    for (int i = 0; i < maxnode; i++) 
    {
        NODE *p = tempadjlist[i].head;
        while (p) 
        {
            NODE *temp = p;
            p = p->next;
            free(temp);
        }
    }
    free(tempadjlist);
    fclose(file);
}
/*
Funtion Name:print_data
Input Para:const PLACE data[], int size
Return Type:void
Description:This function prints the data
*/
void print_data(const PLACE data[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d %s %d\n", data[i].index, data[i].name, data[i].population);
    }
}
/*
Funtion Name:addedgetofile
Input Para:int s, int d, int w
Return Type:void
Description:This function adds the edges with weights to
            the adjacency list
*/
void addedgetofile(int s, int d, int w)
{
    FILE *file = fopen("distances.txt", "a");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%d %d %d\n", s, d, w);
    fclose(file);
}
/*
Funtion Name:adding_edges
Input Para:int n
Return Type:void
Description:This function takes input for source destination
            weights from the user
*/
void adding_edges(int n)
{
    int s, d, w;
    printf("Enter additional edges (source destination weight):\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &s, &d, &w);
        addedgetofile(s, d, w);
    }
    FILE *file = fopen("distances.txt", "r");
    if (file != NULL) 
    {
        while (fscanf(file, "%d %d %d", &s, &d, &w) == 3)
        {
            addnode(s, d, w);
            addnode(d,s,w);
        }
        fclose(file);
    }
}
/*
Funtion Name:read_from_palcestxt
Input Para:PLACE data[], int *count
Return Type:void
Description:This function reads the mysore city information
            from places.txt file
*/
void read_from_palcestxt(PLACE data[], int *count) 
{
    FILE *file = fopen("places.txt", "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        return;
    }
    int index, population;
    char name[50];
    *count = 0; 
    while (*count < 50 && fscanf(file, "%d %s %d", &index, name, &population) == 3)
    {
        data[*count].index = index;
        strcpy(data[*count].name, name);
        data[*count].population = population;
        (*count)++;
    }
    fclose(file);
}
/*
Funtion Name:bubble_sort
Input Para:PLACE arr[], int size
Return Type:void
Description:This function Sorts city data in ascending order 
            based on population
*/
void bubble_sort(PLACE arr[], int size) 
{
    for (int i = 0; i < size - 1; i++) 
    {
        for (int j = 0; j < size - i - 1; j++) 
        {
            if (arr[j].population > arr[j + 1].population) 
            {
                PLACE temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
/*
Funtion Name:selection_sort_desc
Input Para:PLACE arr[], int size
Return Type:void
Description:This function Sorts city data in descending order 
            based on population
*/
void selection_sort_desc(PLACE arr[], int size) 
{
    int i, j, max_index;
    PLACE temp;
    for (i = 0; i < size - 1; i++) 
    {
        max_index = i;
        for (j = i + 1; j < size; j++) 
        {
            if (arr[j].population > arr[max_index].population) 
            {
                max_index = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[max_index];
        arr[max_index] = temp;
    }
}
/*
Funtion Name:bruteforcesearchinname
Input Para:const char *pattern, const char *name
Return Type:int
Description:This function does the brute force string search
            by taking a pattern from a user and search it 
            in the cityname
*/
int bruteforcesearchinname(const char *pattern, const char *name) 
{
    int patternlength = strlen(pattern);
    int namelength = strlen(name);
    for (int i = 0; i <= namelength - patternlength; i++) 
    {
        int j;
        for (j = 0; j < patternlength; j++) 
        {
            if (name[i + j] != pattern[j])
            {
                break; 
            }
        }
        if (j == patternlength) 
        {
            return i; 
        }
    }
    return -1; 
}
/*
Funtion Name:searchpatterninnames
Input Para:const PLACE data[], int count, const char *pattern
Return Type:void
Description:This function prints whether pattern found in 
            cityname or not
*/
void searchpatterninnames(const PLACE data[], int count, const char *pattern) 
{
    printf("Search results for pattern \"%s\" in names:\n", pattern);
    for (int i = 0; i < count; i++) 
    {
        int result = bruteforcesearchinname(pattern, data[i].name);
        if (result != -1)
         {
            printf("Pattern found in %s at index %d.\n", data[i].name, result);
             
        }
    }
}
/*
Funtion Name:createnode
Input Para:NIL
Return Type:TRIENODE*
Description:This function creates the nodes for 
            trie data structure
*/
TRIENODE* createnode() 
{
    TRIENODE* newnode = (TRIENODE*)malloc(sizeof(TRIENODE));
    if (newnode) 
    {
        for (int i = 0; i < 26; i++) 
        {
            newnode->children[i] = NULL;
        }
        newnode->isendofword = 0;
    }
    return newnode;
}
/*
Funtion Name:addlocationnamestotrie
Input Para:TRIENODE* root, const char* filename
Return Type:void
Description:This function reads the cityname from places.txt and 
            pass the cityname to the insertname() function
*/
void addlocationnamestotrie(TRIENODE* root, const char* filename) 
{
    FILE* file = fopen("places.txt", "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char name[50];
    while (fscanf(file, "%*d %s %*d", name) == 1) 
    {
        for (int i = 0; name[i]; i++)
        {
            name[i] = tolower(name[i]);
        }
        insertname(root, name);
    }
    fclose(file);
}
/*
Funtion Name:insertname
Input Para:TRIENODE* root, const char* name
Return Type:void
Description:This function inserts the city name in lexicographic 
            order to the trie 
*/
void insertname(TRIENODE* root, const char* name) 
{
    TRIENODE* current = root;
    for (int i = 0; i < strlen(name); i++) 
    {
        int index = name[i] - 'a';
        if (current->children[index] == NULL) 
        {
            current->children[index] = createnode();
        }
        current = current->children[index];
    }
    current->isendofword = 1;
}
/*
Funtion Name:printtrie
Input Para:TRIENODE* root, char* buffer, int depth
Return Type:void
Description:It prints the cityname in lexicographic order
*/
void printtrie(TRIENODE* root, char* buffer, int depth) 
{
    if (root != NULL) 
    {
        if (root->isendofword) 
        {
            buffer[depth] = '\0';
            printf("%s\n", buffer);
        }
        for (int i = 0; i < 26; i++) 
        {
            if (root->children[i] != NULL)
             {
                buffer[depth] = 'a' + i;
                printtrie(root->children[i], buffer, depth + 1);
            }
        }
    }
}
/*
Funtion Name:freetrie
Input Para:TRIENODE* node
Return Type:void
Description:This function free the allocated memory for 
            the trie data structure
*/
void freetrie(TRIENODE* node) 
{
    if (node != NULL) 
    {
        for (int i = 0; i < 26; i++) 
        {
            freetrie(node->children[i]);
        }
        free(node);
    }
}

/*
Funtion Name:initializesegmenttree
Input Para:int node, int start, int end, SEGNODE segmenttree[], int parent
Return Type:void
Description:It intializes the segment tree nodes
*/
void initializesegmenttree(int node, int start, int end, SEGNODE segmenttree[], int parent)
{
    if (start == end) 
    {
        segmenttree[node].value = distances[parent][start];
        return;
    }
    int mid = (start + end) / 2;
    int leftchild = 2 * node + 1;
    int rightchild = 2 * node + 2;
    initializesegmenttree(leftchild, start, mid, segmenttree, parent);
    initializesegmenttree(rightchild, mid + 1, end, segmenttree, parent);
    segmenttree[node].value = INT_MAX;  
}
/*
Funtion Name:buildsegmenttree
Input Para:int node, int start, int end, SEGNODE segmenttree[], int parent
Return Type:void
Description:It builds the segment tree for the given nodes 
*/
void buildsegmenttree(int node, int start, int end, SEGNODE segmenttree[], int parent) 
{
    if (start == end) 
    {
        segmenttree[node].value = distances[parent][start];
        return;
    }
    int mid = (start + end) / 2;
    int leftchild = 2 * node + 1;
    int rightchild = 2 * node + 2;
    buildsegmenttree(leftchild, start, mid, segmenttree, parent);
    buildsegmenttree(rightchild, mid + 1, end, segmenttree, parent);
    if (segmenttree[leftchild].value < segmenttree[rightchild].value) 
    {
      segmenttree[node].value = segmenttree[leftchild].value;
    } 
    else
    {
      segmenttree[node].value = segmenttree[rightchild].value;
    } 

}
/*
Funtion Name:querysegmenttree
Input Para:int node, int start, int end, SEGNODE segmenttree[], int left, int right
Return Type:int
Description:This function returns minimum distance between the
            user entered edges in a segment tree
*/
int querysegmenttree(int node, int start, int end, SEGNODE segmenttree[], int left, int right)
{
    if (right < start || left > end)
    {
        return INT_MAX;
    }
    if (left <= start && right >= end) 
    {
        return segmenttree[node].value;
    }
    int mid = (start + end) / 2;
    int leftchild = 2 * node + 1;
    int rightchild = 2 * node + 2;
    int leftmin = querysegmenttree(leftchild, start, mid, segmenttree, left, right);
    int rightmin = querysegmenttree(rightchild, mid + 1, end, segmenttree, left, right);
    if (leftmin < rightmin) 
    {
       return leftmin;
    } 
    else
    {
     return rightmin;
    }
}
/*
Funtion Name:findparent
Input Para:int parent[], int node
Return Type:int
Description:This function finds the parent of the node
*/
int findparent(int parent[], int node) 
{
    if (parent[node] == -1) 
    {
        return node;
    }
    return findparent(parent, parent[node]);
}
/*
Funtion Name:unionsets
Input Para:int parent[], int x, int y
Return Type:void
Description:It performs the union of two sets
*/
void unionsets(int parent[], int x, int y) 
{
    int xset = findparent(parent, x);
    int yset = findparent(parent, y);
    parent[xset] = yset;
}
/*
Funtion Name:swapedges
Input Para:EDGE* a, EDGE* b
Return Type:void
Description:It swaps the edges
*/
void swapedges(EDGE* a, EDGE* b)
{
    EDGE temp = *a;
    *a = *b;
    *b = temp;
}
/*
Funtion Name:partition
Input Para:EDGE edges[], int low, int high
Return Type:int
Description:This function partition the array for quicksort
*/
int partition(EDGE edges[], int low, int high)
{
    int pivot = edges[high].weight;
    int i = low - 1;
    for (int j = low; j < high; j++) 
    {
        if (edges[j].weight < pivot)
        {
            i++;
            swapedges(&edges[i], &edges[j]);
        }
    }
    swapedges(&edges[i + 1], &edges[high]);
    return i + 1;
}
/*
Funtion Name:quicksort
Input Para:EDGE edges[], int low, int high
Return Type:void
Description:This function performs the quick sort based on 
            weights in ascending order
*/
void quicksort(EDGE edges[], int low, int high) 
{
    if (low < high) 
    {
        int pivotindex = partition(edges, low, high);
        quicksort(edges, low, pivotindex - 1);
        quicksort(edges, pivotindex + 1, high);
    }
}
/*
Funtion Name:edgepresentinfile
Input Para:EDGE edge, const char* filename
Return Type:int
Description:This function checks whether the user entered edges
            are there in distances.txt or not
*/
int edgepresentinfile(EDGE edge, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0; 
    }
    int found = 0;
    EDGE currentedge;
    while (fscanf(file, "%d %d %d", &currentedge.source, &currentedge.destination, &currentedge.weight) == 3)
     {
        if (edge.source == currentedge.source && edge.destination == currentedge.destination && edge.weight == currentedge.weight)
        {
            found = 1;
            break;
        }
    }
    fclose(file);
    return found;
}

/*
Funtion Name:kruskalmst
Input Para:EDGE* userenterededges, int validedgescount
Return Type:void
Description:It applies kruskal algorithm to the valid edges
*/
void kruskalmst(EDGE* userenterededges, int validedgescount)
{
    int parent[maxnode];
    quicksort(userenterededges, 0, validedgescount - 1);

    // Initialize parent array for disjoint set
    for (int i = 0; i < maxnode; i++) {
        parent[i] = -1;
    }

    printf("Minimum Spanning Tree:\n");

    for (int i = 0; i < validedgescount; i++) {
        int sourceparent = findparent(parent, userenterededges[i].source);
        int destparent = findparent(parent, userenterededges[i].destination);

        // Check if including this edge does not form a cycle
        if (sourceparent != destparent) {
            printf("(%d, %d, %d)\n", userenterededges[i].source, userenterededges[i].destination, userenterededges[i].weight);
            // Add this edge to the minimum spanning tree
            unionsets(parent, sourceparent, destparent);
        } else {
            printf("Skipping edge (%d, %d, %d) as it forms a cycle.\n",
                   userenterededges[i].source, userenterededges[i].destination, userenterededges[i].weight);
        }
    }
}
/*
Funtion Name:printmst
Input Para:int parent[], int n, int graph[maxnode][maxnode]
Return Type:void
Description:This function prints the 
            minimum spanning tree edges
*/
void printmst(int parent[], int n, int graph[maxnode][maxnode])
{
    printf("Edges in the Minimum Spanning Tree:\n");
    for (int i = 1; i < n; i++)
    {
        printf("(%d, %d) Weight: %d\n", parent[i], i, graph[i][parent[i]]);
    }
}
/*
Funtion Name:minkey
Input Para:int key[], int mstset[], int n
Return Type:int
Description:It returs the minimum value in the array
*/
int minkey(int key[], int mstset[], int n)
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++) 
    {
        if (mstset[v] == 0 && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}
/*
Funtion Name:primmst
Input Para:int graph[maxnode][maxnode], int n, int src
Return Type:void
Description:It use Prim's Algorithm to construct
            the minimum spanning tree
*/
void primmst(int graph[maxnode][maxnode], int n, int src) 
{
    int parent[maxnode]; 
    int key[maxnode];    
    int mstset[maxnode]; 
    for (int i = 0; i < n; i++) 
    {
        key[i] = INT_MAX;
        mstset[i] = 0;
    }
    key[src] = 0;
    parent[src] = src; 
    for (int count = 0; count < n - 1; count++) 
    {
        int u = minkey(key, mstset, n);
        mstset[u] = 1;
        for (int v = 0; v < n; v++) 
        {
            if (graph[u][v] && mstset[v] == 0 && graph[u][v] < key[v]) 
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    printmst(parent, n, graph);
}
/*
Funtion Name:buildgraphfromdistances
Input Para:int graph[maxnode][maxnode]
Return Type:void
Description:This function read the distances 
            and the builds the graph
*/
void buildgraphfromdistances(int graph[maxnode][maxnode]) 
{
    FILE *file = fopen("distances.txt", "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int source, destination, weight;
    while (fscanf(file, "%d %d %d", &source, &destination, &weight) == 3)
    {
        graph[source][destination] = weight;
        graph[destination][source] = weight; 
    }
    fclose(file);
}
/*
Funtion Name:bfstraversal
Input Para:int graph[maxnode][maxnode], int n, int src
Return Type:void
Description:It performs the bfs traversal
*/
void bfstraversal(int graph[maxnode][maxnode], int n, int src) 
{
    int visited[maxnode] = {0}; 
    int queue[maxnode];        
    int front = -1, rear = -1;
    printf("BFS Traversal from node %d: ", src);
    visited[src] = 1;
    queue[++rear] = src;
    while (front != rear) 
    {
        int current = queue[++front];
        printf("%d ", current);
        for (int i = 0; i < n; i++)
         {
            if (graph[current][i] != 0 && !visited[i]) 
            {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
    printf("\n");
}
/*
Funtion Name:dfstraversal
Input Para:int graph[maxnode][maxnode], int n, int src, int visited[]
Return Type:void
Description:It performs the dfs traversal
*/
void dfstraversal(int graph[maxnode][maxnode], int n, int src, int visited[]) 
{
    printf("%d ", src);
    visited[src] = 1;
    for (int i = 0; i < n; i++)
     {
        if (graph[src][i] != 0 && !visited[i])
        {
            dfstraversal(graph, n, i, visited);
        }
    }
}
/*
Funtion Name:executeprimalgorithm
Input Para:void
Return Type:void
Description:It takes the source for bfs and dfs traversal
            then apply it to the MST and print the traversal
*/
void executeprimalgorithm() 
{
    int n=50, src;
    int graph[maxnode][maxnode];
    for (int i = 0; i < maxnode; i++) 
    {
        for (int j = 0; j < maxnode; j++) 
        {
            graph[i][j] = 0;
        }
    }
    buildgraphfromdistances(graph);
    printf("Enter the source node for Prim's algorithm: ");
    scanf("%d", &src);
    if (src >= 0 && src < n) 
    {
        primmst(graph, n, src);
    } 
    else
    {
        printf("Invalid source node.\n");
    }
    int bfssrc;
        printf("Enter the source node for BFS traversal: ");
        scanf("%d", &bfssrc);
        if (bfssrc >= 0 && bfssrc < n) 
        {
            bfstraversal(graph, n, bfssrc);
        } 
        else
        {
            printf("Invalid BFS source node.\n");
        }
        int dfssrc;
        printf("\nEnter the source node for DFS traversal: ");
        scanf("%d", &dfssrc);
        if (dfssrc >= 0 && dfssrc < n) 
        {
            int visited[maxnode] = {0};
            printf("DFS Traversal from node %d: ", dfssrc);
            dfstraversal(graph, n, dfssrc, visited);
            printf("\n");
        } 
        else
        {
            printf("Invalid DFS source node.\n");
        }
}

/*
Funtion Name:insertionsort
Input Para:PLACE arr[], int size
Return Type:void
Description:It performs the insertion sort based on 
            population in descending order
*/
void insertionsort(PLACE arr[], int size)
{
    int i, j;
    for (i = 1; i < size; i++) 
    {
        PLACE key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j].population > key.population) 
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
/*
Funtion Name:getnthmostpopulouscity
Input Para:PLACE arr[], int n, int size
Return Type:void
Description:It gives the information about the 
            nth most populous city
*/
void getnthmostpopulouscity(PLACE arr[], int n, int size)
{
    if (n <= 0 || n > size) 
    {
        printf("Invalid query. Please enter a valid query within the range of 1 to %d.\n", size);
        return;
    }
    printf("Information about the %d%s most populous city:\n", n, (n == 1) ? "st" : (n == 2) ? "nd" : (n == 3) ? "rd" : "th");
    printf("Index: %d\n", arr[size - n].index);
    printf("Name: %s\n", arr[size - n].name);
    printf("Population: %d\n", arr[size - n].population);
}
/*
Funtion Name:deleteedge
Input Para:int s, int d
Return Type:void
Description:It delete the user entered edges and print the 
            remaining edges in adjacency list
*/
void deleteedge(int s, int d) 
{
    FILE *file = fopen("distances.txt", "r");
    FILE *tempfile = fopen("temp.txt", "w");
    if (file == NULL || tempfile == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int source, destination, weight;
    int edgefound = 0;
    while (fscanf(file, "%d %d %d", &source, &destination, &weight) == 3)
     {
        if (source == s && destination == d)
        {
            edgefound = 1;
            printf("Edge (%d, %d, %d) deleted successfully.\n", source, destination, weight);
        }
        else
        {
            fprintf(tempfile, "%d %d %d\n", source, destination, weight);
        }
    }
    if (!edgefound) 
    {
        printf("Edge (%d, %d) does not exist.\n", s, d);
    }
    fclose(file);
    fclose(tempfile);
    remove("distances.txt");
    rename("temp.txt", "distances.txt");
    file = fopen("distances.txt", "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    printlist();
    fclose(file);
}
/*
Funtion Name:initializedistancesarray
Input Para:NIL
Return Type:void
Description:It intializes the distance array
*/
void initializedistancesarray()
{
    for (int i = 0; i < maxnode; i++) 
    {
      for (int j = 0; j < maxnode; j++) 
      {
        distances[i][j] = (i == j) ? 0 : INT_MAX;
      }
    }
}
/*
Funtion Name:populatedistancesarray
Input Para:NIL
Return Type:void
Description:It populate the distance array
*/
void populatedistancesarray()
{
    for (int i = 0; i < maxnode; i++) 
    {
        NODE* current = graph[i].head;
        while (current != NULL) 
        {
            distances[i][current->vertexnum] = current->weight;
            current = current->next;
        }
    }
}
/*
Funtion Name:
Input Para:
Return Type:
Description:
*/
void displaylogofornet()
{   
    yellow();
    printf("Welcome to the City\n");
    reset();
    red();
    printf(" /\\    /\\    /\\    /\\    /\\    /\\ \n");
    printf("/  \\  /  \\  /  \\  /  \\  /  \\  /  \\\n");
    printf("| M | | Y | | S | | O | | R | | E |\n");
    printf("\\  /  \\  /  \\  /  \\  /  \\  /  \\  / \n");
    printf(" \\/    \\/    \\/    \\/    \\/    \\/  \n");
    reset();
}
void red()
{
    printf("\033[31m");
}
void reset()
{
    printf("\033[0m");
}
void yellow()
{
    printf("\033[33m");
}
void green()
{
    printf("\033[32m");
}
void into()
{ 
  red();
  printf("*********MAIN MENU*********\n");
  reset();
  green();
  printf("enter the choice\n");
  reset();
  yellow();
  printf("1:Wants to know about connectivity in mysore\n");
  printf("2.Jumping into the Metro maze\n");
  reset();
  scanf("%d",&choice);
  switch(choice)
  {
    case 1:
        displaylogofornet();
        networkmysore();
        break;
    case 2:
        metromysore();
        break;
    default:
        printf("Thank you for coming\n");
         exit(0);
         break;             
  }
}
