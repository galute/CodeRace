//
//  main.c
//  CardReader
//
//  Created by James  Millen on 05/11/2016.
//  Copyright © 2016 James  Millen. All rights reserved.
//

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>

#define CREDIT_CARD_NUM_LEN 16
#define SUCCESS 1
#define FAILURE 0 // memset() to 0 will default card_type.result to FAILURE

int file_p = -1;
struct timeval tv1, tv2, diff;
int counter = 0;


typedef struct card_type
{
    char number[CREDIT_CARD_NUM_LEN + 1];
    int reversed[CREDIT_CARD_NUM_LEN + 1];
    int result;
    struct card_type *next_p;
} card_t;

void ShowResult(card_t *card_p)
{
    if (card_p->result == SUCCESS)
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
}

void Cleanup(card_t *card_p)
{
    card_t *ptr = card_p->next_p;
    
    do
    {
        free(card_p);
        card_p = ptr;
        if (card_p != NULL)
        {
            ptr = card_p->next_p;
        }
    } while (card_p != NULL);
}

void CheckCard(card_t *card_p)
{
    int odd_accumulator = 0;
    int even_accumulator = 0;
    int i,j;
    
    // We could just process the digits of the card number in reverse order
    // but they have to be converted from strings to numbers so put them
    // in reverse order as part of that conversion. This makes the code
    // a little easier to read and understand.
    for (i = 0, j = CREDIT_CARD_NUM_LEN - 1; i < CREDIT_CARD_NUM_LEN; i++,j--)
    {
        char next_char = card_p->number[i + 1];
        card_p->number[i + 1] = '\0';
        
        card_p->reversed[j] = atoi(&card_p->number[i]);
        card_p->number[i + 1] = next_char;
    }
    
    for (i = 0; i < CREDIT_CARD_NUM_LEN; i++)
    {
        // Odd/Even processing appears reversed because of 0 based index
        if (i%2 == 0)
        {
            odd_accumulator += card_p->reversed[i];
        }
        else
        {
            int even_num = card_p->reversed[i] * 2;
            
            if (even_num > 9)
            {
                even_num -= 10;
            }
            
            even_accumulator += even_num;
        }
    }
    
    if ((odd_accumulator + even_accumulator)%10 > 0)
    {
        card_p->result = FAILURE;
    }
    else
    {
        card_p->result = SUCCESS;
    }
}

void ReadCreditCard(card_t *card_p)
{
    ssize_t sz = 0;
    
    sz = read(file_p, card_p->number, CREDIT_CARD_NUM_LEN + 1);
    
    if (sz != CREDIT_CARD_NUM_LEN + 1)
    {
        printf("Error readin file : %s\n", strerror(errno));
    }
}

int
timeval_subtract (result, x, y)
struct timeval *result, *x, *y;
{
    /* Perform the carry for the later subtraction by updating y. */
    if (x->tv_usec < y->tv_usec) {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000) {
        int nsec = (x->tv_usec - y->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }
    
    /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;
    
    /* Return 1 if result is negative. */
    return x->tv_sec < y->tv_sec;
}

int main(int argc, const char * argv[]) {
    int num_cards=500000;
    int i;
    int result;
    card_t * start_p = NULL;
    card_t **temp_pp = &start_p;
    file_p = open("/Users/jmillen/Code/CodeRace/temp.txt", O_RDONLY);
    
    if (file_p == -1)
    {
        printf("failed to open file. %s\n", strerror(errno));
    }
    
    gettimeofday(&tv1, NULL);
    
    for (i = 0; i < num_cards; i++)
    {
        *temp_pp = malloc(sizeof(card_t));
        memset(*temp_pp, 0, sizeof(card_t));
        
        ReadCreditCard(*temp_pp);
        
        temp_pp = &((*temp_pp)->next_p);
    }
    
    temp_pp = &start_p;
    
    // Process the numbers
    while(*temp_pp != NULL)
    {
        CheckCard(*temp_pp);
        ShowResult(*temp_pp);
        
        temp_pp = &((*temp_pp)->next_p);
    }
    
    gettimeofday(&tv2, NULL);
    
    result = timeval_subtract(&diff, &tv2, &tv1);
    
    printf("Time is %ld:%d\n", diff.tv_sec, diff.tv_usec);
    
    Cleanup(start_p);
    close(file_p);
    return 0;
}
