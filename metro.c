#include "mysore.h"

/*
Funtion Name:insertbstnode
Input Para:BSTNODE *root, METRO* metro
Return Type:BSTNODE*
Description:It insert the nodes to the BST based on metro number 
*/
BSTNODE *insertbstnode(BSTNODE *root, METRO* metro)
{
    if (root == NULL)
    {
      BSTNODE *newnode = (BSTNODE *)malloc(sizeof(BSTNODE));
        if (newnode == NULL)
        {
            perror("Error allocating memory");
            exit(EXIT_FAILURE);
        }
        newnode->metronumber = metro->metronumber;
        newnode->metroinfo = metro;
        newnode->left = newnode->right = NULL;
        return newnode;
    }
    if (metro->metronumber < root->metronumber)
    {
        root->left = insertbstnode(root->left, metro);
    }
    else if (metro->metronumber > root->metronumber)
    {
        root->right = insertbstnode(root->right, metro);
    }
    return root;
}
/*
Funtion Name:searchbstnode
Input Para:BSTNODE *root, int metronumber
Return Type:BSTNODE*
Description:It search for the metro number in BST
*/
BSTNODE *searchbstnode(BSTNODE *root, int metronumber)
{
    if (root == NULL || root->metronumber == metronumber)
    {
        return root;
    }
    if (metronumber < root->metronumber)
    {
        return searchbstnode(root->left, metronumber);
    }
    return searchbstnode(root->right, metronumber);
}
/*
Funtion Name:inordertraversal
Input Para:BSTNODE *root
Return Type:void
Description:It performs the inorder traversal in BST
*/
void inordertraversal(BSTNODE *root)
{
    if (root != NULL)
    {
        inordertraversal(root->left);
        printf("%d ", root->metronumber);
        inordertraversal(root->right);
    }
}
/*
Funtion Name:preordertraversal
Input Para:BSTNODE *root
Return Type:void
Description:It performs the preorder traversal in BST
*/
void preordertraversal(BSTNODE *root)
{
    if (root != NULL)
    {
        printf("%d ", root->metronumber);
        preordertraversal(root->left);
        preordertraversal(root->right);
    }
}

/*
Funtion Name:postordertraversal
Input Para:BSTNODE *root
Return Type:void
Description:It performs the postorder traversal in BST
*/
void postordertraversal(BSTNODE *root)
{
    if (root != NULL)
    {
        postordertraversal(root->left);
        postordertraversal(root->right);
        printf("%d ", root->metronumber);
    }
}

/*
Funtion Name:readmetro
Input Para:METRO metros[], int size, const char* filename
Return Type:void
Description:It reads the metro information from
            the textfile metroinfo.txt
*/
void readmetro(METRO metros[], int size, const char* filename) 
{
    FILE* file = fopen("metroinfo.txt", "r");
    if (file == NULL) 
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) 
    {
        fscanf(file, "%d %s %s %s %d %d %d %d",
               &metros[i].metronumber,
               metros[i].metroname,
               metros[i].metrosource,
               metros[i].metrodestination,
               &metros[i].availableseats,
               &metros[i].bookedseats,
               &metros[i].ticketprice,
               &metros[i].journeytime);
    }
    fclose(file);
}
/*
Funtion Name:displaymetro
Input Para:const METRO metros[], int size
Return Type:void
Description:It display the metro information
*/
void displaymetro(const METRO metros[], int size)
{
    printf("%-10s%-15s%-15s%-15s%-10s%-10s%-10s%-10s\n",
           "M.Number", "M.Name", "Source", "Destination",
           "A.Seats", "B.Seats", "T.Price", "J.Time");
    for (int i = 0; i < size; i++)
    {
        printf("%-10d%-15s%-15s%-15s%-10d%-10d%-10d%-10d\n",
               metros[i].metronumber,
               metros[i].metroname,
               metros[i].metrosource,
               metros[i].metrodestination,
               metros[i].availableseats,
               metros[i].bookedseats,
               metros[i].ticketprice,
               metros[i].journeytime);
    }
}
/*
Funtion Name:displaymetroinfo
Input Para:BSTNODE *node
Return Type:void
Description:It display the metro information
*/
void displaymetroinfo(BSTNODE *node)
{
    if (node != NULL)
    {
        METRO* metro = node->metroinfo;
        printf("\nMetro Number: %d\n", metro->metronumber);
        printf("Metro Name: %s\n", metro->metroname);
        printf("Source: %s\n", metro->metrosource);
        printf("Destination: %s\n", metro->metrodestination);
        printf("Available Seats: %d\n", metro->availableseats);
        printf("Booked Seats: %d\n", metro->bookedseats);
        printf("Ticket Price: %d\n", metro->ticketprice);
        printf("Journey Time: %d\n", metro->journeytime);
    }
}
/*
Funtion Name:insertionsortbyticketprice
Input Para:METRO metros[], int size
Return Type:void
Description:It sort the metro information in ascending order
            based on ticket price
*/
void insertionsortbyticketprice(METRO metros[], int size)
 {
    int i, j;
    METRO key;
    for (i = 1; i < size; i++) 
    {
        key = metros[i];
        j = i - 1;
        while (j >= 0 && metros[j].ticketprice > key.ticketprice) 
        {
            metros[j + 1] = metros[j];
            j = j - 1;
        }
        metros[j + 1] = key;
    }
}
/*
Funtion Name:clearinputbuffer
Input Para:NIL
Return Type:void
Description:
*/
void clearinputbuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
/*
Funtion Name:generateuserid
Input Para:void
Return Type:int
Description:It hashes the ticket booking time 
            to generate 4-digit user id
*/
int generateuserid()
{
    time_t t;
    srand((unsigned) time(&t));
    return rand() % 10000 + 1000;  
}
/*
Funtion Name:hashfunction
Input Para:const char* str
Return Type:unsigned int
Description:It hashes the password
*/
unsigned int hashfunction(const char* str)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
    {
      hash = hash * 33 + c;
    }
    return hash;
}
/*
Funtion Name:writeusertofile
Input Para:USER user
Return Type:void
Description:It writes login information of 
           the user into user.txt file
*/
void writeusertofile(USER user)
{
    FILE* userfile = fopen(USER_FILE, "a");
    if (userfile == NULL) 
    {
        perror("Error opening user file");
        exit(EXIT_FAILURE);
    }
    fprintf(userfile, "%d %s %u\n", user.userid, user.username, hashfunction(user.password));
    fclose(userfile);
}
/*
Funtion Name:checkuserexists
Input Para:const char* username
Return Type:bool
Description:It checks whether a user with 
            the given username exists
*/
bool checkuserexists(const char* username) 
{
    FILE* userfile = fopen(USER_FILE, "r");
    if (userfile == NULL)
    {
        perror("Error opening user file");
        exit(EXIT_FAILURE);
    }
    char line[100];
    while (fgets(line, sizeof(line), userfile) != NULL) 
    {
      char storedusername[20];
      sscanf(line, "%*d %s", storedusername);
      if (strcmp(username, storedusername) == 0) 
      {
        fclose(userfile);
        return true;
      }
    }
    fclose(userfile);
    return false;
}
/*
Funtion Name:showloadingspinner
Input Para:NIL
Return Type:void
Description:It just a loading spinner 
            representation in console
*/
void showloadingspinner()
{
    const char* spinners[] = {"|", "/", "-", "\\"};
    int numspinners = sizeof(spinners) / sizeof(spinners[0]);
    int numframes = 5;
    for (int frame = 0; frame < numframes; ++frame) 
    {
        printf("\rLoading... %s", spinners[frame % numspinners]);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}
/*
Funtion Name:createuser
Input Para:USER *newuser
Return Type:USER *newuser
Description:It a creates the account for new user and
            writes the user information into history file
*/
int createuser(USER *newuser)
{
    printf("Enter your name: ");
    getchar();
    fgets(newuser->username, sizeof(newuser->username), stdin);
    newuser->username[strcspn(newuser->username, "\n")] = '\0';  
    if (checkuserexists(newuser->username)) 
    {
        printf("Username already exists. Please choose a different username.\n");
        return -1; 
    }
    printf("set password: ");
    scanf("%s", newuser->password);
    printf("Confirm password: ");
    char confirmpassword[20];
    scanf("%s", confirmpassword);
    if (strcmp(newuser->password, confirmpassword) != 0) 
    {
        printf("Passwords do not match. Account creation failed.\n");
        return -1;  
    }
    newuser->userid = generateuserid();
    writeusertofile(*newuser);
    FILE* historyfile = fopen(HISTORY_FILE, "a");
    if (historyfile == NULL)
    {
        perror("Error opening history file");
        exit(EXIT_FAILURE);
    }
    fprintf(historyfile, "%d %s %u\n", newuser->userid, newuser->username, hashfunction(newuser->password));
    fclose(historyfile);
    showloadingspinner();
    printf("Account successfully created! Your User ID is: %d\n", newuser->userid);
    return 0;  
}
/*
Funtion Name:loginuser
Input Para:void
Return Type:int
Description:This function helps user to login to the 
            website who already has account
*/
int loginuser() 
{
    char username[20];
    char password[20];
    int maxattempts = 3;  
    while (maxattempts > 0) 
    {
        printf("Enter your username: ");
        scanf("%s", username);
        printf("Enter your password: ");
        int i = 0;
        while (1) 
        {
            char ch = getch();
            if (ch == '\r' || ch == '\n') 
            {
                break;
            }  
            else if (ch == 8 && i > 0) 
            {
                printf("\b \b");
                i--;
            } 
            else 
            {
                password[i++] = ch;
                printf("*");
            }
        }
        password[i] = '\0';
        printf("\n");
        clearinputbuffer(); 
        FILE *userfile = fopen(USER_FILE, "r");
        if (userfile == NULL) 
        {
            perror("Error opening user file");
            exit(EXIT_FAILURE);
        }
        char line[100];
        while (fgets(line, sizeof(line), userfile) != NULL)
        {
            int storeduserid, storedhash;
            char storedusername[20];
            sscanf(line, "%d %s %d", &storeduserid, storedusername, &storedhash);
            if (strcmp(username, storedusername) == 0 && hashfunction(password) == storedhash) 
            {
                fclose(userfile);
                return storeduserid;
            }
        }
        fclose(userfile);
        maxattempts--;
        if (maxattempts > 0) 
        {
            printf("Incorrect username or password.\n You have %d attempts remaining.\n", maxattempts);
        } 
        else
        {
            printf("Login failed. Reconnecting.....\n");
        }
    }
    return -1;  
}
/*
Funtion Name:bookticket
Input Para:METRO* metros, int userid, BSTNODE* bstroot
Return Type:void
Description:It performs the ticket booking operation
*/
void bookticket(METRO* metros, int userid, BSTNODE* bstroot) 
{
    int metronumber, numtickets;
    printf("Enter metro number for ticket booking: ");
    scanf("%d", &metronumber);
    BSTNODE *searchresult = searchbstnode(bstroot, metronumber);
    if (searchresult == NULL) 
    {
        printf("Metro with number %d not found.\n", metronumber);
        return;
    }
    printf("Enter the number of tickets to book: ");
    scanf("%d", &numtickets);
    if (searchresult->metroinfo->availableseats >= numtickets) 
    {
        USER currentuser;
        currentuser.userid = userid;
        printf("Ticket booking in progress...\n");
        showloadingspinner();
        writehistory(&currentuser, searchresult->metroinfo, numtickets);
        searchresult->metroinfo->availableseats -= numtickets;
        searchresult->metroinfo->bookedseats += numtickets;
        updatemetroinfo(metros);
        printf("%d tickets booked successfully for Metro %d!\n", numtickets, metronumber);
    } 
    else
    {
        printf("Not enough available seats for booking.\n");
    }
}
/*
Funtion Name:updatemetroinfo
Input Para:const METRO* metros
Return Type:void
Description:It update the metro information after 
            successful metro ticket booking
*/
void updatemetroinfo(const METRO* metros)
{
    FILE* metrofile = fopen("metroinfo.txt", "w");
    if (metrofile == NULL) 
    {
        perror("Error opening metro file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < metronum; i++) 
    {
        fprintf(metrofile, "%d %s %s %s %d %d %d %d\n",
                metros[i].metronumber,
                metros[i].metroname,
                metros[i].metrosource,
                metros[i].metrodestination,
                metros[i].availableseats,
                metros[i].bookedseats,
                metros[i].ticketprice,
                metros[i].journeytime);
    }
    fclose(metrofile);
}
/*
Funtion Name:writehistory
Input Para:const USER* user, const METRO* metro, int numtickets
Return Type:void
Description:It writes the ticket booking history
            to the history.txt file
*/
void writehistory(const USER* user, const METRO* metro, int numtickets) 
{
    FILE* historyfile = fopen(HISTORY_FILE, "a");
    if (historyfile == NULL) 
    {
        perror("Error opening history file");
        exit(EXIT_FAILURE);
    }
    time_t now = time(NULL);
    fprintf(historyfile, "%d %s %d %d %s", user->userid, metro->metroname, numtickets, metro->ticketprice, ctime(&now));
    fclose(historyfile);
}
/*
Funtion Name:createminheap
Input Para:int capacity
Return Type:MINHEAP*
Description:It creates the heap(minimum heap)
*/
MINHEAP* createminheap(int capacity) 
{
    MINHEAP* minheap = (MINHEAP*)malloc(sizeof(MINHEAP));
    if (minheap == NULL)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    minheap->capacity = capacity;
    minheap->size = 0;
    minheap->heaparray = (MONTHLYPASS*)malloc(capacity * sizeof(MONTHLYPASS));
    if (minheap->heaparray == NULL) 
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    return minheap;
}
/*
Funtion Name:swap
Input Para:MONTHLYPASS* a, MONTHLYPASS* b
Return Type:void
Description:
*/
void swap(MONTHLYPASS* a, MONTHLYPASS* b) {
    MONTHLYPASS temp = *a;
    *a = *b;
    *b = temp;
}
/*
Funtion Name:heapifyup
Input Para:MINHEAP* minheap, int index
Return Type:void
Description:It heapify the heap after insertion 
            or deletion of monthly pass
*/
void heapifyup(MINHEAP* minheap, int index)
{
    int parent = (index - 1) / 2;
    while (index > 0 && strcmp(minheap->heaparray[parent].expirydate, minheap->heaparray[index].expirydate) > 0)
    {
        swap(&minheap->heaparray[parent], &minheap->heaparray[index]);
        index = parent;
        parent = (index - 1) / 2;
    }
}
/*
Funtion Name:insertminheap
Input Para:MINHEAP* minheap, MONTHLYPASS* monthlypass
Return Type:void
Description:It does the insertion operation in heap
*/
void insertminheap(MINHEAP* minheap, MONTHLYPASS* monthlypass) 
{
    if (minheap->size < minheap->capacity) 
    {
        minheap->heaparray[minheap->size] = *monthlypass;
        minheap->size++;
        heapifyup(minheap, minheap->size - 1);
    } 
    else 
    {
        printf("Heap is full. Cannot insert more monthly passes.\n");
    }
}
/*
Funtion Name:displayminheap
Input Para:MINHEAP* minheap
Return Type:void
Description:It display the minimum heap
*/
void displayminheap(MINHEAP* minheap) 
{
    printf("Monthly Passes in Min Heap (sorted by expiry date):\n");
    for (int i = 0; i < minheap->size; i++) 
    {
        printf("Name: %s, Expiry Date: %s\n", minheap->heaparray[i].name, minheap->heaparray[i].expirydate);
    }
}
/*
Funtion Name:freeminheap
Input Para:MINHEAP* minheap
Return Type:void
Description:
*/
void freeminheap(MINHEAP* minheap) 
{
    free(minheap->heaparray);
    free(minheap);
}
/*
Funtion Name:add30days
Input Para:char* startdate, char* expirydate
Return Type:void
Description:It calculates the expiry date for monthly pass
*/
void add30days(char* startdate, char* expirydate) 
{
    int year, month, day;
    sscanf(startdate, "%d-%d-%d", &year, &month, &day);
    struct tm tm = {0};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_mday += 30;
    mktime(&tm);
    snprintf(expirydate, 20, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}
/*
Funtion Name:merge
Input Para:METRO metros[], int left, int mid, int right
Return Type:void
Description:It performs the pre-operation for merge sort
*/
void merge(METRO metros[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    METRO *l = (METRO *)malloc(n1 * sizeof(METRO));
    METRO *r = (METRO *)malloc(n2 * sizeof(METRO));
    if (l == NULL || r == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < n1; i++)
        l[i] = metros[left + i];
    for (j = 0; j < n2; j++)
        r[j] = metros[mid + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (l[i].journeytime <= r[j].journeytime)
        {
            metros[k] = l[i];
            i++;
        }
        else
        {
            metros[k] = r[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        metros[k] = l[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        metros[k] = r[j];
        j++;
        k++;
    }
    free(l);
    free(r);
}
/*
Funtion Name:mergesort
Input Para:METRO metros[], int left, int right
Return Type:void
Description:It performs merge sort based on journey time
*/
void mergesort(METRO metros[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergesort(metros, left, mid);
        mergesort(metros, mid + 1, right);
        merge(metros, left, mid, right);
    }
}
/*
Funtion Name:displaymetroswithinjourneytime
Input Para:METRO metros[], int size, int maxjourneytime
Return Type:void
Description:It display the metro information in ascending order
            based on journey time
*/
void displaymetroswithinjourneytime(METRO metros[], int size, int maxjourneytime)
{
    printf("\nMetros with Journey Time within %d minutes:\n", maxjourneytime);
    printf("%-10s%-15s%-15s%-15s%-10s%-10s%-10s%-10s\n",
           "M.Number", "M.Name", "Source", "Destination",
           "A.Seats", "B.Seats", "T.Price", "J.Time");
    for (int i = 0; i < size; i++)
    {
        if (metros[i].journeytime <= maxjourneytime)
        {
            printf("%-10d%-15s%-15s%-15s%-10d%-10d%-10d%-10d\n",
                   metros[i].metronumber,
                   metros[i].metroname,
                   metros[i].metrosource,
                   metros[i].metrodestination,
                   metros[i].availableseats,
                   metros[i].bookedseats,
                   metros[i].ticketprice,
                   metros[i].journeytime);
        }
    }
}
/*
Funtion Name:buildkmptable
Input Para:const char *pattern, int *kmptable
Return Type:void
Description:It does the kmp table 
*/
void buildkmptable(const char *pattern, int *kmptable) 
{
    int m = strlen(pattern);
    int len = 0;
    int i = 1;
    kmptable[0] = 0;
    while (i < m) 
    {
        if (pattern[i] == pattern[len]) 
        {
            len++;
            kmptable[i] = len;
            i++;
        } 
        else
        {
            if (len != 0) 
            {
                len = kmptable[len - 1];
            } 
            else
            {
                kmptable[i] = 0;
                i++;
            }
        }
    }
}
/*
Funtion Name:kmpsearch
Input Para:const char *text, const char *pattern
Return Type:int
Description:It search the metro name using 
            kmp string search technique
*/
int kmpsearch(const char *text, const char *pattern) 
{
    int n = strlen(text);
    int m = strlen(pattern);
    if (m == 0) return 0; 
    int *kmptable = (int *)malloc(m * sizeof(int));
    buildkmptable(pattern, kmptable);
    int i = 0, j = 0;
    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            j++;
            i++;
        }
        if (j == m) 
        {
            free(kmptable);
            return i - j;  
        }
        else if (i < n && pattern[j] != text[i]) 
        {
            if (j != 0)
            {
                j = kmptable[j - 1];
            } 
            else
            {
                i++;
            }
        }
    }
    free(kmptable);
    return -1;
}
/*
Funtion Name:searchanddisplaymetro
Input Para:const char *searchname, METRO metros[], int size
Return Type:void
Description:It display the kmp string search result
*/
void searchanddisplaymetro(const char *searchname, METRO metros[], int size) 
{
    printf("%-10s%-15s%-15s%-15s%-10s%-10s%-10s%-10s\n",
           "M.Number", "M.Name", "Source", "Destination",
           "A.Seats", "B.Seats", "T.Price", "J.Time");
    for (int i = 0; i < size; i++) 
    {
        const char *metroname = metros[i].metroname;
        int index = kmpsearch(metroname, searchname);
        if (index != -1) 
        {
            printf("%-10d%-15s%-15s%-15s%-10d%-10d%-10d%-10d\n",
               metros[i].metronumber,
               metros[i].metroname,
               metros[i].metrosource,
               metros[i].metrodestination,
               metros[i].availableseats,
               metros[i].bookedseats,
               metros[i].ticketprice,
               metros[i].journeytime);
        }
    }
}




