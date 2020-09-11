// list/list.c
// 
// Implementation for linked list.
//
// Elijah Prentice

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

list_t *list_alloc() {
  list_t *list = (list_t*) malloc(sizeof(list_t*));   //allocate space for the list
  node_t *node = (node_t*) malloc(sizeof(node_t*));   //allocate space for the head node
  
  list->head = node;   //have the head of the list point to the head node
  
  return list;
}

//code from: https://stackoverflow.com/a/6417182
void list_free(list_t *l) {
  
  node_t *temp = NULL;     //a temporary node to free up space
  
  while (l->head != NULL){
    temp = l->head;            //point to the head of the list
    l->head = l->head->next;   //make the next node the new head
    free(temp);                //free the space from the head
  }
}

void list_print(list_t *l) {
  
  node_t *current_node = l->head;   //start at the head of the list
  
  while (current_node != NULL){
    printf("%d\n", current_node->value);   //print the value of the current node
    current_node = current_node->next;     //go to the next node
  }
}

int list_length(list_t *l) {
  
  if (l->head == NULL){  //if there is no head
    return -1;
  }
  
  int length = 0;                   //start at 0
  node_t *current_node = l->head;   //start at the head
  
  while(current_node != NULL){
    length++;                            //increment the length
    current_node = current_node->next;   //go to the next node
  }
  
  return length;            //return the length
}

void list_add_to_back(list_t *l, elem value) {
  
  if (l->head == NULL){   //if there is no head
    
    l->head = (node_t *) malloc(sizeof(node_t));   //allocate space for the head node
    l->head->value = value;                        //assign the added value to the head
    l->head->next = NULL;                          //no next node
    
  } else {
    
    node_t *current_node = l->head;           //start at the head
    
    while (current_node->next != NULL){
      current_node = current_node->next;      //go to the next node until the second to last node is reached
    }
    
    current_node->next = (node_t *) malloc(sizeof(node_t));  //add a new node to the back of the list
    current_node->next->value = value;                       //add the value to the last node
    current_node->next->next = NULL;                         //no next node
  }
}
void list_add_to_front(list_t *l, elem value) {
  
  if (l->head == NULL){   //if there is no head
    
    l->head = (node_t *) malloc(sizeof(node_t));   //allocate space for the head node
    l->head->value = value;                        //assign the added value to the head
    l->head->next = NULL;                          //no next node
    
  } else {
    
    node_t *new_node = (node_t *) malloc(sizeof(node_t));  //allocate space for the new node
    
    new_node->value = value;                       //add the value to the new node
    new_node->next = l->head;                      //make the current head the next node
    l->head = new_node;                            //make the new node the head
  }
}
void list_add_at_index(list_t *l, elem value, int index) {

  if (index == 0){
    list_add_to_front(l, value);         //add to the front if the index is 0
  }
  
  node_t *current_node = l->head;        //start at the head
  
  int i = 0;
  for (i = 0; i < index - 1; i++){
    
    if(current_node->next == NULL){      //end the function if the index is too high
      return;
    }
    
    current_node = current_node->next;   //go to the next node
  }
  
  node_t *new_node = (node_t *) malloc(sizeof(node_t));   //allocate space for a new node
  
  new_node->value = value;                               //add the value to the new node
  new_node->next = current_node->next;                   //have the new node point to the next node
  current_node->next = new_node;                         //have the current node point to the new node
}

elem list_remove_from_back(list_t *l) {
  
  if(l->head == NULL){
    return -1;              //return -1 if there is no list
  }
  
  elem remove_val;
  
  if (l->head->next == NULL){
    remove_val = l->head->value;   //take the value in the head
    free(l->head);                 //free up space from the head
    return remove_val;             //return the head's value
  }
  
  node_t *current_node = l->head;   //start from the head
  
  while(current_node->next->next != NULL){
    current_node = current_node->next;        //go to the next node
  }
  
  remove_val = current_node->next->value;     //take the value of the next node
  free(current_node->next);                   //free space from the second to last node
  current_node->next = NULL;                  //the next node is NULL
  return remove_val;                          //return the value
}
elem list_remove_from_front(list_t *l) {
  
  if(l->head == NULL){
    return -1;              //return -1 if there is no list
  }
  
  elem remove_val;
  
  node_t * next_node = l->head->next;    //get the second node
  remove_val = l->head->value;           //take the value from the head node
  free(l->head);                         //free up space from the head
  l->head = next_node;                   //make the second node the new head
  
  return remove_val;                     //return the value
}
elem list_remove_at_index(list_t *l, int index) {
  
  if (index == 0){
    return list_remove_from_front(l);    //remove from the front if the index is 0
  }
  
  elem remove_val = -1;
  
  node_t *current_node = l->head;        //start at the head
  node_t *temp = NULL;                   //temporary node to free up space
  
  int i = 0;
  for (i = 0; i < index - 1; i++){
    
    if(current_node->next == NULL){
      return remove_val;                  //return -1 if the index is too high
    }
    current_node = current_node->next;    //go to the next node
  }
  
  temp = current_node->next;             //get the next node
  remove_val = temp->value;              //get the value of the next node
  current_node->next = temp->next;       //move the second next node up one space
  free(temp);                            //free up space from the temporary node
  
  return remove_val;                     //return the value
}

bool list_is_in(list_t *l, elem value) {
  
  node_t *current_node = l->head;           //start at the head
  
  while(current_node != NULL){
    
    if(current_node->value == value){
      return true;                          //if the element is found, return true
    }
    current_node = current_node->next;      //go to the next node
  }
  
  return false;             //false if the value is never found
}
elem list_get_elem_at(list_t *l, int index) {
  
  elem list_element;
  
  node_t *current_node = l->head;        //start at the head
  
  int i = 0;
  for(i = 0; i < index; i++){
    
    if(current_node->next == NULL){
      return -1;                        //return -1 if thhe index is too high
    }
    current_node = current_node->next;  //go to the next node
  }
  
  return current_node->value;            //return the value
}
int list_get_index_of(list_t *l, elem value) {
  
  int index = 0;
  node_t *current_node = l->head;          //start at the head of the list
  
  while (current_node != NULL){
    
    if(current_node->value == value){
      return index;                        //return the index if the value is reached
    }
    index++;                               //increment the index
    current_node = current_node->next;     //go to the next node
  }
  
  return -1;              //return -1 if the index is never reached
}