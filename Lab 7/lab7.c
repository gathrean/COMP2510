#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   DO NOT CHANGE
   1st sample struct containing 2 integers
   When sorting use x first, then y.
**/
typedef struct
{
  int x;
  int y;
} istr;

/**
   DO NOT CHANGE
   2nd sample struct containing 3 characters
   When sorting use x first, then y, and finally z.
**/
typedef struct
{
  char x;
  char y;
  char z;
} cstr;

// Custom Node struct
typedef struct node
{
  void *data;
  struct node *next;
} node;

// Custom Linked List struct
typedef struct linked_list
{
  node *head;
  size_t size;
} linked_list;

/**
   The function takes the pointer to linked list and
   a pointer to data.
   This function adds data at the end of your linked list
   However, the return value is 1 if successfully inserted
   0 otherwise
**/
int add_node(void *ll, void *data)
{
  linked_list *list = (linked_list *)ll;
  node *new_node = (node *)malloc(sizeof(node));
  if (new_node == NULL)
  {
    return 0; // Memory allocation failed
  }
  new_node->data = data;
  new_node->next = NULL;
  if (list->head == NULL)
  {
    list->head = new_node;
  }
  else
  {
    node *curr_node = list->head;
    while (curr_node->next != NULL)
    {
      curr_node = curr_node->next;
    }
    curr_node->next = new_node;
  }
  list->size++;
  return 1;
}

/**
   Remove an element at the end of the linked list
   The function takes the pointer to linked list and
   a pointer to return value (removed data)
**/
void remove_node(void *ll, void *ret)
{
  linked_list *list = (linked_list *)ll;
  node *curr_node = list->head;
  node *prev_node = NULL;
  while (curr_node != NULL && curr_node->next != NULL)
  {
    prev_node = curr_node;
    curr_node = curr_node->next;
  }
  if (curr_node == NULL)
  {
    return; // List is empty
  }
  if (prev_node == NULL)
  {
    list->head = NULL;
  }
  else
  {
    prev_node->next = NULL;
  }
  list->size--;
  memcpy(ret, curr_node->data, list->size);
  free(curr_node);
}

/**
   This function creates a linked list. This function returns
   the linked list. Returns NULL if creation fails.
   You are required to make your own custom linked list struct
 **/
void *create_ll(size_t size)
{
  linked_list *list = (linked_list *)malloc(sizeof(linked_list));
  if (list == NULL)
  {
    return NULL; // Memory allocation failed
  }
  list->head = NULL;
  list->size = size;
  return (void *)list;
}

/**
   This function merge sorts the linked list.

   The sort() function uses the linked_list struct to implement merge sort on a linked list.
   It first checks if the size of the linked list is greater than 1. If it is, it divides the
   list into two halves and recursively sorts each half. It then merges the two sorted halves
   back into the original list using the memcmp() function to compare the data.

   Finally, it frees the memory allocated for the two halves.
 **/
void sort(void *ll)
{
  linked_list *list = (linked_list *)ll;

  if (list->size > 1)
  {
    // Divide the list into two halves
    linked_list left = {.head = NULL, .size = 0};
    linked_list right = {.head = NULL, .size = 0};
    node *curr_node = list->head;
    size_t i = 0;
    while (curr_node != NULL)
    {
      if (i < list->size / 2)
      {
        add_node(&left, curr_node->data);
      }
      else
      {
        add_node(&right, curr_node->data);
      }
      curr_node = curr_node->next;
      i++;
    }

    // Recursively sort the two halves
    sort(&left);
    sort(&right);

    // Merge the two sorted halves
    node *left_node = left.head;
    node *right_node = right.head;
    curr_node = list->head;
    while (left_node != NULL && right_node != NULL)
    {
      if (memcmp(left_node->data, right_node->data, list->size) < 0)
      {
        memcpy(curr_node->data, left_node->data, list->size);
        left_node = left_node->next;
      }
      else
      {
        memcpy(curr_node->data, right_node->data, list->size);
        right_node = right_node->next;
      }
      curr_node = curr_node->next;
    }
    while (left_node != NULL)
    {
      memcpy(curr_node->data, left_node->data, list->size);
      left_node = left_node->next;
      curr_node = curr_node->next;
    }
    while (right_node != NULL)
    {
      memcpy(curr_node->data, right_node->data, list->size);
      right_node = right_node->next;
      curr_node = curr_node->next;
    }

    // Free the memory allocated for the two halves
    node *temp_node;
    while (left.head != NULL)
    {
      temp_node = left.head;
      left.head = left.head->next;
      free(temp_node);
    }
    while (right.head != NULL)
    {
      temp_node = right.head;
      right.head = right.head->next;
      free(temp_node);
    }
  }
}

/**
   Do not modify the function signature of the main function
   including spacing.
 **/
int main(int argc, char **argv)
{ // Basically do NOT touch this line
  void *cll = create_ll(sizeof(char));
  char i = 'a';
  add_node(cll, &i);
  i = 'c';
  add_node(cll, &i);
  sort(cll);
  char rv;
  remove_node(cll, &rv);
  printf("%c", rv);

  return 0;
}
