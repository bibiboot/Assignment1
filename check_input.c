#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "format.h"

/**
 * Check transaction_type.
 * @author Danish Rehman
 * @param char pointer to transaction type.
 * @return -1 in case of error
 *          0 in case of sucess.
 */
int check_sign(char *sign)
{
    if (strlen(sign)!=1){
        fprintf(stderr, "Error: Transaction type is greater then one character.\n");
        return -1;
    }
    else if ( (*sign)!='+' && (*sign)!='-'){
        fprintf(stderr, "Error: Transaction type is neither deposit nor withdrawl. Unknown sign found.\n");
        return -1;
    }
    return 0;
}

/**
 * Check transaction time.
 * @author Danish Rehman
 * @param char pointer to transaction time.
 * @return -1 in case of error
 *          0 in case of sucess.
 */
int check_txn_time(char *txn_time)
{
    if(isNumber(txn_time)){
        fprintf(stderr, "Error: Transaction time is not a number.\n");
        return -1;
    }
    long long txn_time_int = atoll(txn_time);
    if(strlen(txn_time) >= 11){
        fprintf(stderr, "Error: Transaction time is of length greater then largest unsigned integer.\n");
        return -1;
    }
    if(txn_time_int>(long long)time(NULL)){
        fprintf(stderr, "Error: Transaction time is greater then the current time.\n");
        return -1;
    }
    /*
    else if(ctime(&txn_time_int)==-1){
        fprintf(stderr, "Error: Transaction time is of wrong format.\n");
        return -1;
    }*/
    return 0;
}

/**
 * Check the amount.
 * @author Danish Rehman
 * @param char pointer to amt.
 * @return -1 in case of error
 *          0 in case of sucess.
 */
int check_amt(char *amt)
{
    char int_part[10];
    char frac_part[10];
    sscanf(amt, "%[^.].%s", int_part, frac_part);
    //printf("%s, %s\n", int_part, frac_part);
    if(isNumber(int_part)){
        fprintf(stderr, "Error: Amount is not a number.\n");
        return -1;
    }
    if(isNumber(frac_part)){
        fprintf(stderr, "Error: Amount is not a number.\n");
        return -1;
    }
         
    if ( strlen(int_part)>7 ){
        fprintf(stderr, "Error: Amount is greater then 7 digits length.\n");
        return -1;
    } 
    
    if ( strlen(frac_part)!=2){
        fprintf(stderr, "Error: Fractional part of amount is not equal to 2.\n");
        return -1;
    }
    return 0;
}

/**
 * Check description.
 * @author Danish Rehman
 * @param char pointer to description.
 * @return NULL in case of error,
 *         modified description otherwise.
 */
char* check_desc(char *desc)
{
    while(*desc==' '){
        desc++;
    }

    if(desc[strlen(desc)-1] =='\n'){
        desc[strlen(desc)-1] = '\0';
    }

    if (strlen(desc)==0){
        fprintf(stderr, "Error: The description is empty\n");
        return NULL;
    }
    return desc;
}

int isNumber(char *str)
{
    char *temp = str;
    while(*temp!='\0'){
        if((*temp)>='0' && (*temp)<='9' )
            temp++;
        else
            return -1;
    }
    return 0;
}

