/*******
* This program is written by Danish Rehman.
*     
*******/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include "format.h"
#include "my402list.h"

DIR* opendir(const char *name);

/**
 * Main fuction
 * @author Danish Rehman
 */
int main(int argc, char *argv[])
{
   FILE *fp = NULL;
   if ( (argc!=2 && argc!=3) ||  strcmp(argv[1], "sort")!=0 || (argc==3 && argv[2][0]=='-') ){
       fprintf(stderr, "Malformed Command.\n");
       fprintf(stderr, "The commandline syntax for warmup1 is as follows:\n");
       fprintf(stderr, "\twarmup1 sort [tfile]\n");
       fprintf(stderr, "USUAGE: Square bracketed items are optional.\n");
       fprintf(stderr, "\tIf tfile is not specified, your program should read from stdin.\n");
       terminate();
   }
   if (argc == 3){
        fp = fopen(argv[2], "r");
        if(opendir(argv[2])){
            perror("Error: It is a directory\n");
            terminate();
        }

        if(fp==NULL){
            perror("Error: Unable to open the file\n");
            terminate();
        } 
     
   }
   //fp = fopen(argv[2], "r");

   My402List *myList = parse_build(fp);

   /*Sort the list*/
   BubbleSortForwardList(myList, myList->num_members);

   /*Print the list*/
   //traverse(myList);
   publish(myList);
   return 0;
}

/**
 * Parse the input and
 * check for wrong format and
 * build a circular list.
 * @author Danish Rehman
 * @param FILE ptr pointing to file or stdin.
 * @return main pointer to circular list.
 */

My402List* parse_build(FILE *fp)
{
   char buff[1028];
   char *token;
   int withdrawl;
   char *amt;
   char *txn_time;
   char *desc;
   /*Allocate memory to list*/
   My402List *myList = malloc(sizeof(My402List));
   /*Initilialize the list*/
   My402ListInit(myList);

   if (fp == NULL)
       fp = stdin;

   while((fgets(buff, 1029, fp))!=NULL){
       /*printf("%s", buff);*/
       /* Use to split*/
       /*Initialize i again as for new line*/
       int i =1;
       if(strlen(buff)>1024){
           fprintf(stderr, "The line length is greater then 1024.\n"); 
           terminate();
       } 
       token = strtok(buff, "\t");
       withdrawl = 0;

       while (token) {
           switch (i){
               case 1:
                   /* Transaction type*/
                   if(check_sign(token))
                       terminate();
                   /* For - use 0 and + use 1*/
                   if((*token)=='-')
                       withdrawl = 1; 
                   break;
               case 2:
                   /* Transaction time*/
                   if(check_txn_time(token))
                       terminate();
                   txn_time = token;
                   break;
               case 3:
                   /* Amount*/
                   if(check_amt(token))
                       terminate();
                   amt = token;
                   break;
               case 4:
                   /* Description*/ 
                   if((desc = check_desc(token))==NULL)
                       terminate();
                   break;
           }
           i++;
           //printf("%s\n", token);
           token = strtok(NULL,"\t");
       }
       /*printf("%d,%s,%s,%s\n", withdrawl, amt, txn_time, desc);*/
       if(i!=5){
           printf("Not all the fields are available in the input\n");
           terminate();
       }

       /* Create and populate structure with values*/
       My402dataElem *dataE = create(withdrawl, amt, txn_time, desc);
       /*Check for duplicate timestamp*/
       if (My402ListFind_struct(myList,dataE)){
           printf("Duplicate timestamp\n");
           terminate();
       }

       /*Append the structure to list*/
       My402ListAppend(myList, dataE);
   }
   return myList;
}

/**
 * Create single structure.
 * @author Danish Rehman
 * @param withdrawl: can be 0, 1.
 * @param ptr to amount.
 * @param ptr to transaction time.
 * @param ptr to description. 
 * @return structure ptr to My402dataElem.
 */
My402dataElem* create(int withdrawl, char *amt, char* txn_time, char *desc)
{
       /* Create memory for the structure*/
       My402dataElem *dataE = malloc(sizeof(My402dataElem));
       dataE->withdrawl = withdrawl;
       dataE->txn_time = txn_time;
       /* Creating memory for description as desc is char ptr*/
       dataE->desc = malloc((sizeof(char))*(strlen(desc)+1));
       strcpy(dataE->desc, desc);
       /* Creating memory for amount as amt is char ptr*/
       dataE->amt = malloc((sizeof(char))*(strlen(amt)+1));
       strcpy(dataE->amt, amt);
       /* Convert char ptr to integer*/
       dataE->txn_time_int = atoi(txn_time);
       return dataE;
}

/**
 * Publish the record on to the screen.
 * @author Danish Rehman
 * @param withdrawl: can be 0, 1.
 * @param ptr to My402List.
 */
void publish(My402List *myList)
{
    My402ListElem *elem=NULL;

    print_border();
    print_head(); 
    print_border();
    /* Traverse the list and print the records*/
    for (elem=My402ListFirst(myList);elem != NULL; elem=My402ListNext(myList, elem)) {
         time_t txn_time = ((My402dataElem*)(elem->obj))->txn_time_int;
         char *desc = ((My402dataElem*)(elem->obj))->desc;
         char *amt = ((My402dataElem*)(elem->obj))->amt;
         int withd = ((My402dataElem*)(elem->obj))->withdrawl;
         /* Print records in given format*/
         print_records(txn_time, desc, amt, withd);

    }
    /* Print bordes at the bottom of table*/
    print_border();
}
