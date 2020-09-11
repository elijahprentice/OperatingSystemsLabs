#include <stdio.h>

#include "list.h"

int main() {
  printf("Tests for linked list implementation\n");
  
  list_t* a = list_alloc();
  
  int i, j;
  for(i = 9; i > 4; i--){
    list_add_to_back(a, i);
  }
  for(j = 1; j < 5; j++){
    list_add_to_front(a, j);
  }
  list_add_at_index(a, 10, 3);
  
  list_remove_from_back(a);
  list_remove_from_front(a);
  list_remove_at_index(a, 6);
  
  list_print(a);
  
  printf("The length of the list is %d\n", list_length(a));
  
  if (list_is_in(a,4)){
    printf("4 is in the list.\n");
  } else {
    printf("4 is not in the list.\n");
  }
  
  printf("The element at index 6 %d\n", list_get_elem_at(a, 6));
  printf("10 is at index %d\n", list_get_index_of(a, 10));
  
  list_free(a);
  
  return 0;
}