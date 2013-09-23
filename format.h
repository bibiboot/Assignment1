#include "time.h"
#include "my402list.h"

void print_records(time_t txn_time, char *desc, char *amt, int withd);
void print_txn_time(time_t txn_time);
void print_desc(char *desc);
void print_amt(char *amt, int withd);
void print_bal(char *amt, int withd);

char* human_amt(char *amt);
void print_border();
void print_head();
long long int dollar_cent(char *amt);
char* cent_dollar(long long int amt);
void terminate();

int check_sign(char* sign);
int check_txn_time(char *txn_time);
int check_amt(char *amt);
char* check_desc(char *desc);

typedef struct dataElem {
    int withdrawl;
    char *amt;
    char *txn_time;
    char *desc;
    int txn_time_int;
} My402dataElem;

void traverse(My402List *myList);

void BubbleSortForwardList(My402List *pList, int num_items);
void BubbleForward(My402List *pList, My402ListElem **pp_elem1, My402ListElem **pp_elem2);

void publish(My402List *myList);

My402List* parse_build(FILE *fp);
My402dataElem* create(int withdrawl, char *amt, char* txn_time, char *desc);

My402ListElem* My402ListFind_struct(My402List *myList, void *obj);
int isNumber(char *str);

