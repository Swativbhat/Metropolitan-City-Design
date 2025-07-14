#include "mysore.h"
void metromysore()
{
    while(1)
    {   green();
        printf("enter the choice\n");
        reset();
        yellow();
        printf("-------------------------------------\n");
        printf("41.Know more about Metro\n");
        printf("42.Metro booking online website\n");
        printf("43.Return to the main menu\n");
        printf("-------------------------------------\n");
        reset();
        scanf("%d",&choice);
        switch(choice)
        {
            case 41:
             metrodocs();
             break;
            case 42:
             ticketdocs();
             break;
            default:
             into();
             break;
        }
    }
}
void metrodocs()
{
    while(1)
    {   
        green();
        printf("enter the choice\n");
        reset();
        yellow();
        printf("---------------------------------------------------------\n");
        printf("51:display metro information\n");
        printf("52:See the metro information from least ticketprice\n");
        printf("53:Enter the metro number and get it's all information\n");
        printf("54:Traversal\n");
        printf("55:Get information about metros based on journey time\n");
        printf("56:Enter the metro name and see it's information\n");
        printf("57:Return to the main menu\n");
        printf("---------------------------------------------------------\n");
        reset();
        scanf("%d",&choice);
        switch(choice)
        {
            case 51:
              METRO metros[metronum];
              readmetro(metros,metronum, "metroinfo.txt");
              displaymetro(metros,metronum);
              break;
            case 52:
              readmetro(metros, metronum, "metroinfo.txt");
              insertionsortbyticketprice(metros, metronum);
              printf("Metro information sorted by Ticket Price:\n");
              displaymetro(metros, metronum);
              break; 
            case 53:
            BSTNODE *bstroot = NULL;
              readmetro(metros, metronum, "metroinfo.txt");
              if (bstroot == NULL)
              {
                for (int i = 0; i < metronum; i++)
                {
                    bstroot = insertbstnode(bstroot, &metros[i]);
                }
              }
              printf("Enter a metro number to search: ");
              scanf("%d", &searchnumber);
              BSTNODE *searchresult = searchbstnode(bstroot, searchnumber);
              if (searchresult != NULL)
              {
                printf("\nMetro number %d found in BST.\n", searchnumber);
                displaymetroinfo(searchresult);
              }
              else
              {
                printf("\nMetro number %d not found in BST.\n", searchnumber);
              }
              break; 
            case 54:
              readmetro(metros, metronum, "metroinfo.txt");
              if (bstroot == NULL)
              {
                for (int i = 0; i < metronum; i++)
                {
                    bstroot = insertbstnode(bstroot, &metros[i]);
                }
              } 
              printf("Inorder Traversal: ");
              inordertraversal(bstroot);
              printf("\n");
              printf("Preorder Traversal: ");
              preordertraversal(bstroot);
              printf("\n");
              printf("Postorder Traversal: ");
              postordertraversal(bstroot);
              printf("\n");
              break; 
            case 55:
               readmetro(metros,metronum, "metroinfo.txt");
               mergesort(metros, 0, sizek - 1);
               printf("\nEnter maximum journey time for filtering: ");
               scanf("%d", &maxjourneytime);
               displaymetroswithinjourneytime(metros, sizek, maxjourneytime);
               break;
            case 56:
              readmetro(metros, metronum, "metroinfo.txt");
              printf("Enter the metro name to search: ");
              scanf("%s",searchname);
              searchanddisplaymetro(searchname, metros, sizek);
              break;
            default:
              metromysore();
              break;
        }
    }
}
void ticketdocs()
{
    while(1)
    {   
        green(); 
        printf("enter the choice\n");
        reset();
        yellow();
        printf("-----------------------------\n");
        printf("61:Signin(acc exist)\n");
        printf("62:Signup(create nwe acc)\n");
        printf("63:Return to main menu\n");
        printf("-----------------------------\n");
        reset();
        scanf("%d",&choice);
        switch(choice)
        {
          case 61:
             int userid= loginuser();
             if (userid != -1) 
             {
                currentuser.userid = userid;
                printf("Login successful!\n");
                mainpage();
             } 
             else 
             {
                printf("Invalid login credentials.\n");
                continue;
             }
             break;
            case 62:
                if (createuser(&currentuser) == 0)
                {
                 printf("Account successfully created!\n");
                 mainpage();
                } 
                else 
                {
                printf("Account creation failed.\n");
                  continue;
                }
                break;
            default:
                metromysore();
                break;
        }
    }
}
void mainpage()
{
    
    while(1)
    {
        green();
        printf("enter the choice\n");
        reset();
        yellow();
        printf("-----------------------------------------\n");
        printf("71:Metro ticket booking\n");
        printf("72:Monthly pass registration\n");
        printf("73.Cancel the monthly pass anytime\n");
        printf("74:Logout\n");
        printf("-----------------------------------------\n");
        reset();
        scanf("%d",&choice);
        switch(choice)
        {
            case 71:
                readmetro(metros, metronum, "metroinfo.txt");
                if (bstroot == NULL)
                {
                   for (int i = 0; i < metronum; i++)
                   {
                      bstroot = insertbstnode(bstroot, &metros[i]);
                   }
                }
                printf("Enter metro number for ticket booking: \n");
                scanf("%d", &metronumber);
                clearinputbuffer();
                printf("Searching for metro number %d in BST...\n", metronumber);
                searchresult = searchbstnode(bstroot, metronumber);
                if (searchresult != NULL)
                {
                   printf("Metro found in BST, proceed with ticket booking");
                // break;
                } 
               else
                {
                  printf("Metro with number %d not found. Please enter a valid metro number.\n", metronumber);
                }
                printf("Enter the number of tickets to book: ");
                scanf("%d", &numtickets);
                if (searchresult->metroinfo->availableseats >= numtickets)
                {
                   printf("Ticket booking in progress...\n");
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
                break;
            case 72:
                readmetro(metros, metronum, "metroinfo.txt");
                if (bstroot == NULL)
                {
                   for (int i = 0; i < metronum; i++)
                   {
                      bstroot = insertbstnode(bstroot, &metros[i]);
                   }
                }
                printf("monthly pass\n");
                MINHEAP* monthlypassheap = createminheap(10); 
                int numpasses;
                printf("Enter the number of monthly passes: ");
                scanf("%d", &numpasses);
                FILE *monthlypassfile = fopen("monthly.txt", "a");  
                if (monthlypassfile == NULL)
                {
                    perror("Error opening monthly pass file");
                    exit(EXIT_FAILURE);
                }
                for (int i = 0; i < numpasses; i++)
                {
                  printf("Enter name for Pass %d: ", i + 1);
                  scanf("%s", newpass.name);
                  printf("Enter source for Pass %d: ", i + 1);
                  scanf("%s", newpass.source);
                  printf("Enter destination for Pass %d: ", i + 1);
                  scanf("%s", newpass.destination);
                  printf("Enter start date (YYYY-MM-DD) for Pass %d: ", i + 1);
                  scanf("%s", newpass.startdate);
                  add30days(newpass.startdate, newpass.expirydate);
                  printf("Enter amount for Pass %d: ", i + 1);
                  scanf("%d", &newpass.amount);
                  insertminheap(monthlypassheap, &newpass);
                  fprintf(monthlypassfile, "%s %s %s %s %s %d\n",
                            newpass.name, newpass.source, newpass.destination,
                            newpass.startdate, newpass.expirydate, newpass.amount);
                }
                displayminheap(monthlypassheap);
                freeminheap(monthlypassheap);
                fclose(monthlypassfile);  
                break;  
            case 73:
                printf("cancellation\n");
                char cancelname[20], cancelsource[20], canceldestination[20];
                printf("Enter the name of the pass to cancel: ");
                scanf("%s", cancelname);
                printf("Enter the source of the pass: ");
                scanf("%s", cancelsource);
                printf("Enter the destination of the pass: ");
                scanf("%s", canceldestination);
                FILE* monthlyfile = fopen("monthly.txt", "r");
                if (monthlyfile == NULL)
                {
                  perror("Error opening monthly file");
                  exit(EXIT_FAILURE);
                }
                while (fgets(line, sizeof(line), monthlyfile) != NULL)
                {
                 char storedname[20], storedsource[20], storeddestination[20];
                 sscanf(line, "%s %s %s", storedname, storedsource, storeddestination);
                 if (strcmp(storedname, cancelname) == 0 &&
                 strcmp(storedsource, cancelsource) == 0 &&
                 strcmp(storeddestination, canceldestination) == 0) 
                 {
                  passindex = linenumber;
                  break;
                 }
                 linenumber++;
                }
                fclose(monthlyfile);
                if (passindex != -1)
                {
                printf("Monthly pass found on line %d. Do you want to cancel it? (1: Yes, 2: No): ", passindex);
                int cancelchoice;
                scanf("%d", &cancelchoice);
                if (cancelchoice == 1) 
                {
                  FILE* tempfile = fopen("monthly.txt", "w");
                  if (tempfile == NULL) 
                  {
                    perror("Error opening temporary monthly file");
                    exit(EXIT_FAILURE);
                  }
                   rewind(monthlyfile);  
                   linenumber = 1;
                   while (fgets(line, sizeof(line), monthlyfile) != NULL) 
                   {
                     if (linenumber != passindex) 
                     {
                      fprintf(tempfile, "%s", line);
                     }
                     linenumber++;
                    }
                     fclose(monthlyfile);
                     printf("Monthly pass canceled successfully!\n");
                    } 
                    else
                    {
                      printf("Monthly pass cancellation canceled.\n");
                    }
                }
               else
                {
                printf("Monthly pass not found.\n");
                }
                break;
            default:
            ticketdocs();
            break;    
        }
    }
}