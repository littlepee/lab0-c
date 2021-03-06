/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)  // Return NULL if could not allocate space
        return NULL;
    q->head = NULL;

    q->q_tail = NULL;
    q->q_size = 0;

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;

    while (q->head) {
        list_ele_t *tmp = (q->head);
        q->head = (q->head)->next;
        free(tmp);
    }
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)  // Return false if q is NULL
        return false;

    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)  // could not allocate space
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;

    newh->value = strdup(s);
    if (q->q_size == 0) {
        q->q_tail = newh;
    }

    q->head = newh;
    (q->q_size)++;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)  // Return false if q is NULL
        return false;

    list_ele_t *new;
    new = malloc(sizeof(list_ele_t));
    if (new == NULL)  //  could not allocate space
        return false;

    new->next = NULL;
    new->value = strdup(s);
    if (q->q_size == 0) {
        q->head = new;
    } else {
        q->q_tail->next = new;
    }

    q->q_tail = new;
    q->q_size++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if ((q == NULL) ||
        (q->q_size == 0))  // Return false if queue is NULL or empty.
        return false;

    if (sp) {  // If sp is non-NULL
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        int string_size = strlen(tmp->value);
        string_size =
            (string_size > (bufsize - 1))
                ? (bufsize - 1)
                : string_size;  // up to a maximum of bufsize-1 characters
        strncpy(sp, tmp->value, string_size);  // copy the removed string to *sp
        sp[string_size] = '\0';                // plus a null terminator
        free(tmp);
        q->q_size--;
        return true;
    }

    return false;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)  // Return 0 if q is NULL
        return 0;
    return q->q_size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if ((q == NULL) || (q->q_size == 0))  // No effect if q is NULL or empty
        return;

    list_ele_t *next_element;
    list_ele_t *current = q->head;
    list_ele_t *previous = NULL;

    q->q_tail = q->head;

    while (current) {
        next_element = current->next;
        current->next = previous;
        previous = current;
        current = next_element;
        q->head = previous;
    }
}
