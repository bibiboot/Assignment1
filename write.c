#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "format.h"

#define MILLION "?,???,???.??"

long long int balance = 0;

/**
 * Print records.
 * @author Danish Rehman
 * @param int transaction time. 
 * @param ptr to description.
 * @param ptr to amount.
 * @param int withd.
 */
void print_records(time_t txn_time, char *desc, char *amt, int withd)
{
    printf("|");
    print_txn_time(txn_time);
    printf("|");
    print_desc(desc);
    printf("|");
    print_amt(amt, withd);
    printf("|");
    print_bal(amt, withd);
    printf("|");
    printf("\n");
}

/**
 * Print transaction time.
 * Check for transaction time.
 * @author Danish Rehman
 * @param int transaction time. 
 */
void print_txn_time(time_t txn_time)
{
    /*Wed Dec 31 21:16:40 1969*/

    char first[4];
    char second[4];
    char third[3];
    char fourth[9];
    char fiveth[5];
    char *htime = ctime(&txn_time);

    sscanf(htime, "%[^ ] %[^ ] %[^ ] %[^ ] %s", first, second, third, fourth, fiveth);
    /*printf("%s, %s, %s, %s\n", first, second, third, fiveth);*/
    htime = malloc((sizeof(char))*(3+3+2+4+3+1));

    strcpy(htime, first);
    strcat(htime, " ");
    strcat(htime, second);
    strcat(htime, " ");
    if (atoi(third)<10)
        strcat(htime, " ");
    strcat(htime, third);
    strcat(htime, " ");
    strcat(htime, fiveth);

    printf(" %s ", htime);
}

/**
 * Print transaction time.
 * Check for transaction time.
 * @author Danish Rehman
 * @param int transaction time. 
 */
void print_desc(char *desc)
{
    char *final_desc = malloc((sizeof(char))*25);
    strncpy(final_desc, desc, 24);
    printf(" %-24s ", final_desc);
}
    
/**
 * Print transaction time.
 * Check for transaction time.
 * @author Danish Rehman
 * @param int transaction time. 
 */
void print_amt(char *amt, int withd)
{
    char *million_ptr = MILLION;
    char *show_amt;
    /* Check for amount greater then 10 million*/
    if (strlen(amt)>=11)
        show_amt = million_ptr;
    else
        show_amt = human_amt(amt);
    
    if (withd)
        printf(" (%12s) ", show_amt);
    else
        printf("  %12s  ", show_amt);
}

/**
 * Print Balance after addition with last balance 
 * and current amount. If balance is negative () must
 * be added. If the absolute value of balance is greater
 * then 10 million then add ?,???,???.?? 
 * @author Danish Rehman
 * @param char ptr to amount. 
 * @param int withdrawl.
 */
void print_bal(char *amt, int withd)
{
    long long amt_int = dollar_cent(amt);
    if (withd)
        balance = balance - amt_int;
    else
        balance = balance + amt_int;
    //printf("%ll\n",balance);
    if (balance < 0){
        print_amt(cent_dollar(balance*-1), 1);
    }
    else {
        print_amt(cent_dollar(balance), 0);
    }
}
