#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "format.h"

char* human_amt(char *amt){
    int add = (strlen(amt)-4)/3;
    int amt_length = strlen(amt);
    if (amt_length<7){
        return amt;
    }
    char *hamt = malloc((sizeof(char))*(amt_length+add+1));
    char *last = amt + (amt_length-1);
    char *last_dest = hamt + ( amt_length + add -1 );
    *(last_dest+1) = '\0';
    int i = 0;
    while(i!=(amt_length)){
       if ( i>3 && (i-3)%3 == 0 ) {
          *last_dest = ','; 
          last_dest--;
       }
       *last_dest = *last;
       last--; 
       last_dest--;
       i++;
    }
    return hamt;
}

void print_border(){
    int i;
    printf("+");
    for(i=0; i<17; i++)
        printf("-");
    printf("+");
    for(i=0; i<26; i++)
        printf("-");
    printf("+");
    for(i=0; i<16; i++)
        printf("-");
    printf("+");
    for(i=0; i<16; i++)
        printf("-");
    printf("+\n");
}

void print_head(){
    int i;
    printf("|");
    for(i=0; i<7; i++)
        printf(" ");
    printf("Date");    
    for(i=0; i<6; i++)
        printf(" ");
    printf("| ");
    printf("%-24s", "Description");
    printf(" | ");
    printf("%14s", "Amount");
    printf(" | ");
    printf("%14s", "Balance");
    printf(" |\n");
}

void BubbleSortForwardList(My402List *pList, int num_items)
{
    My402ListElem *elem=NULL;
    int i=0;

    if (My402ListLength(pList) != num_items) {
        fprintf(stderr, "List length is not %1d in BubbleSortForwardList().\n", num_items);
        exit(1);
    }
    for (i=0; i < num_items; i++) {
        int j=0, something_swapped=FALSE;
        My402ListElem *next_elem=NULL;

        for (elem=My402ListFirst(pList), j=0; j < num_items-i-1; elem=next_elem, j++) {
            int cur_val=((My402dataElem*)(elem->obj))->txn_time_int, next_val=0;

            next_elem=My402ListNext(pList, elem);
            //next_val = (int)(next_elem->obj);
            next_val = ((My402dataElem*)(next_elem->obj))->txn_time_int;

            if (cur_val > next_val) {
                BubbleForward(pList, &elem, &next_elem);
                something_swapped = TRUE;
            }
        }
        if (!something_swapped) break;
    }
}

void BubbleForward(My402List *pList, My402ListElem **pp_elem1, My402ListElem **pp_elem2)
{
    My402ListElem *elem1=(*pp_elem1), *elem2=(*pp_elem2);
    void *obj1=elem1->obj, *obj2=elem2->obj;
    My402ListElem *elem1prev=My402ListPrev(pList, elem1);
    My402ListElem *elem2next=My402ListNext(pList, elem2);

    My402ListUnlink(pList, elem1);
    My402ListUnlink(pList, elem2);
    if (elem1prev == NULL) {
        (void)My402ListPrepend(pList, obj2);
        *pp_elem1 = My402ListFirst(pList);
    } else {
        (void)My402ListInsertAfter(pList, obj2, elem1prev);
        *pp_elem1 = My402ListNext(pList, elem1prev);
    }
    if (elem2next == NULL) {
        (void)My402ListAppend(pList, obj1);
        *pp_elem2 = My402ListLast(pList);
    } else {
        (void)My402ListInsertBefore(pList, obj1, elem2next);
        *pp_elem2 = My402ListPrev(pList, elem2next);
    }
}

void terminate()
{
    printf("Terminating program\n");
    exit(1);
}

long long dollar_cent(char *amt)
{
    char int_part[10];
    char frac_part[10];
    sscanf(amt, "%[^.].%s", int_part, frac_part);
    return atoll(int_part)*100 + atoll(frac_part);
}

char* cent_dollar(long long int dollar)
{
    char *amt = malloc(sizeof(char)*(1000));
    char *amt_frac = malloc(sizeof(char)*(1000));
    long long int  int_part = dollar/100;
    long long int frac_part = dollar%100;
    sprintf(amt, "%lld", int_part);
    sprintf(amt_frac, "%lld", frac_part);
    strcat(amt,".");
    if (frac_part<10)
        strcat(amt,"0");
    strcat(amt,amt_frac);
    return amt;
}

/**
 * Traverse the circular list taking into
 * account that the obj is My402ListElem ptr.
 * @author Danish Rehman
 * @param main pointer.
 */
void traverse(My402List *myList)
{
    My402ListElem *elem=NULL;

    for (elem=My402ListFirst(myList);elem != NULL; elem=My402ListNext(myList, elem)) {
        printf("---%s---\n", ((My402dataElem*)(elem->obj))->desc);
        /*printf("---%d---\n", ((My402dataElem*)(elem->obj))->txn_time_int);
        printf("---%d---\n", ((My402dataElem*)(elem->obj))->withdrawl);*/
    }
}


/**
 * Find the  obj when obj is struct pointer of
 * type My402dataElem and look for txn_time_int.
 * @author Danish Rehman
 * @param main pointer.
 * @param obj to look for.
 */
My402ListElem* My402ListFind_struct(My402List *myList, void *obj){
    My402ListElem *elem=NULL;
    int new_data = ((My402dataElem*)(obj))->txn_time_int;
    int old_data ;

    for (elem=My402ListFirst(myList);elem != NULL; elem=My402ListNext(myList, elem)) {
        old_data = ((My402dataElem*)(elem->obj))->txn_time_int;

        if (new_data == old_data)
            return elem;
    }
    return NULL;
}
