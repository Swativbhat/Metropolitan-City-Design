// #include "network.c"
#include "mysore.h"
void networkmysore()
{
  while (1)
  {
    green();
    printf("enter the Choice\n");
    reset();
    yellow();
    printf("________________<<<<<<<<<<.>>>>>>>>>>>________________\n");
    printf("11.Wants to know about connectivity between cities\n");
    printf("22.Wants to know about the places in Mysore\n");
    printf("________________<<<<<<<<<<.>>>>>>>>>>>________________\n");
    reset();
    scanf("%d", &choice);
    switch (choice)
    {
    case 11:
      connectmore();
      break;
    case 22:
      knowplaces();
      break;
    default:
      into();
      break;
    }
  }
}
void connectmore()
{
  while (1)
  {
    green();
    printf("enter the Choice\n");
    reset();
    yellow();
    printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
    printf("1.Connect the more places(1--3) \n");
    printf("2.delete the connectivity\n");
    printf("3.enter the places connectivity and get back the efficient path to travel\n");
    printf("4.Confused to go somewhere!! enter where you are\n");
    printf("5.Return to main menu\n");
    printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
    reset();
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      printf("Enter number of places you want to connect\n");
      scanf("%d", &n);
      adding_edges(n);
      printlist();
      break;
    case 2:
      printf("Enter source and destination index to delete edge: ");
      scanf("%d %d", &s, &d);
      deleteedge(s, d);
      break;

    case 3:
      int validedgescount = 0;
      printf("Enter the number of edges: ");
      scanf("%d", &useredgecount);
      EDGE *userenterededges = (EDGE *)malloc(useredgecount * sizeof(EDGE));
      while (validedgescount == 0)
      {
        printf("Enter edges (source destination weight) for the graph:\n");
        for (int i = 0; i < useredgecount; i++)
        {
          printf("Edge %d: ", i + 1);
          if (scanf("%d %d %d", &userenterededges[i].source, &userenterededges[i].destination, &userenterededges[i].weight) != 3)
          {
            printf("Error reading edge %d. Please enter valid input.\n", i + 1);
            free(userenterededges);
            exit(EXIT_FAILURE);
          }
        }
        validedgescount = 0;
        for (int i = 0; i < useredgecount; i++)
        {
          if (edgepresentinfile(userenterededges[i], "distances.txt"))
          {
            validedgescount++;
          }
          else
          {
            printf("Skipping edge (%d, %d, %d) as it is not in distances.txt.\n",
                   userenterededges[i].source, userenterededges[i].destination, userenterededges[i].weight);
          }
        }
        if (validedgescount == 0)
        {
          printf("No valid edges found in distances.txt. Please enter valid edges.\n");
        }
      }
      kruskalmst(userenterededges, validedgescount);
      free(userenterededges);
      break;
    case 4:
      executeprimalgorithm();
      break;
    default:
      networkmysore();
      break;
    } // end of switch
  } // end of while
} // end of function
void knowplaces()
{
  while (1)
  {
    green();
    printf("enter the Choice\n");
    reset();
    yellow();
    printf("-----------------------------------------------------------");
    printf("31.You can see all the places in mysore\n");
    printf("32.You can see the places from least population\n");
    printf("33.You can see the places from highest population\n");
    printf("34.Enter the name of the city to search\n");
    printf("35.You can see the city names in lexicographical order\n");
    printf("36.Query about the Nth most populous city\n");
    printf("37.Return to main menu\n");
    printf("-------------------------------------------------------------");
    reset();
    scanf("%d", &choice);
    switch (choice)
    {
    case 31:
      read_from_palcestxt(data, &count);
      print_data(data, count);
      break;
    case 32:
      read_from_palcestxt(data, &count);
      bubble_sort(data, count);
      print_data(data, count);
      break;
    case 33:
      read_from_palcestxt(data, &count);
      selection_sort_desc(data, count);
      print_data(data, count);
      break;
    case 34:
      printf("Enter the cityname to search: \n");
      scanf("%s", pattern);
      read_from_palcestxt(data, &count);
      searchpatterninnames(data, count, pattern);
      break;
    case 35:
      TRIENODE *root = createnode();
      addlocationnamestotrie(root, "places.txt");
      char buffer[50];
      printtrie(root, buffer, 0);
      freetrie(root);
      break;
    case 36:
      read_from_palcestxt(data, &count);
      insertionsort(data, count);
      printf("\nEnter the N to get Nth populous city (1 to %d): ", count);
      scanf("%d", &query);
      getnthmostpopulouscity(data, query, count);
      break;
    default:
      networkmysore();
      break;
    }
  }
}