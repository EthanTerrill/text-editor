#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//#include "keyboard.h"
#include "text_editor.h"
#include <wchar.h>

typedef struct string {

  unsigned char flags;
  wchar_t val;
  struct string* next;
  struct string* prev;
  
} string;

#define CURSOR 0x1

#define IS_CURSOR (string s) 0x01 & s.flags

int get_indentation(string* cursor){
  
  string* copy = cursor;
  int ret = 0;

  while(copy->prev != NULL && copy->val != '\n'){
    
    ret++;
    copy = copy->next;
  }
  return ret;
}

static inline void copy_indentation(string** cursor, int indentation){


  for (int i = 0; i < indentation && (*cursor)->next != NULL; i++) {
    *cursor = (*cursor)->next;
  }

}

static inline void move_cursor_left(string** cursor){
  if((*cursor)->prev != NULL) {

    *cursor = (*cursor)->prev;
  } 
  
} 

static inline void move_cursor_right(string** cursor){
  if((*cursor)->next != NULL) {
    *cursor = (*cursor)->next;
  }
  if((*cursor)->next != NULL && (*cursor)->next->val == '\n'){
  //  *cursor = (*cursor)->next;
  }
}
static inline void move_cursor_down(string** cursor){
 
  move_cursor_right(cursor);
  while((*cursor)->next != NULL && (*cursor)->val != '\n')
  {
    move_cursor_right(cursor);
  }
  //move_cursor_right(cursor);


}
static inline void move_cursor_up(string** cursor){
  move_cursor_left(cursor);
  while((*cursor)->prev != NULL && (*cursor)->val != '\n')
  {
    move_cursor_left(cursor);
  }
  move_cursor_left(cursor);
  while((*cursor)->prev != NULL && (*cursor)->val != '\n')
  {
    move_cursor_left(cursor);
  }
 
  if((*cursor)->prev != NULL)
    move_cursor_down(cursor);

}




void append_string(string* cursor, wchar_t c){

 
  if(cursor->next != NULL){

    //printf("___");
    string* new;
    string* next;


    next = cursor->next;

    new = (string*)malloc(sizeof(string));
    new->val = c;
    next->flags = 0;

    new->prev = cursor;
    new->next = next;

    cursor->next = new;
    next->prev = new;
    
  }
  else{

    cursor->next = (string*)malloc(sizeof(string));
    cursor->next->val = c;
    cursor->next->prev = cursor;
    cursor->next->next = NULL;
  }

  
};

void delete_character(string** cursor){

  //while(cursor->next != NULL){
    //cursor = cursor->next;
  //}
  if((*cursor)->prev !=NULL)
  {

    string* nex = (*cursor)->next;



    move_cursor_left(cursor);
    if(nex != NULL)
      nex->prev = (*cursor);
    
    free((*cursor)->next);
    (*cursor)->next = nex;
  }

};



void print_str(string s){

  if(s.prev != NULL && s.prev->flags & CURSOR){

    if(mode == MODE_MOV){
      wprintf(L"\033[48;5;231m");
      wprintf(L"\033[38;5;0m");
    }  

    if(mode == MODE_TEXT){

      wprintf(L"\033[4m");
    }


    if(s.val == '\n' || s.val == '\t'){
      wprintf(L" ");

      wprintf(L"\033[0;0m\033[24m");
    }

  }

  
  wprintf(L"%lc", s.val);

  
  if(s.prev != NULL && s.prev->flags & CURSOR){
    
    if(mode == MODE_MOV)
      wprintf(L"\033[0;0m");

    if(mode == MODE_TEXT)
      wprintf(L"\033[24m");
  }

  if(s.next != NULL){
    print_str(*(s.next));
  }
  else if(s.flags & CURSOR){
   if(mode == MODE_MOV){
      wprintf(L"\033[48;5;231m");
      wprintf(L"\033[38;5;0m");
    }  

    if(mode == MODE_TEXT){

      wprintf(L"\033[4m");
    }


    wprintf(L" ");

    wprintf(L"\033[0;0m\033[24m");

 
  }
};

// string* get_prev(string* s){
//   if(s->prev != NULL){
//     return s->prev;
//   }
//   else{
//     return s;
//   }
// }
// string* get_next(string* s){
//   if(s->next != NULL){
//     return s->next;
//   }
//   else{
//     return s;
//   }
// }
//
void free_string(string* s){

  string* cursor = s;
  while(cursor->next != NULL) {

    if(cursor->prev != NULL){
      //free(cursor->prev);
    }
    cursor = cursor->next;
  }
  while(cursor->prev !=NULL){
    if(cursor->next != NULL)
      free(cursor->next);

    cursor = cursor->prev;
  }
  
}

void write_string_to_file(string s, FILE** f){


   
  //   if(s.val != '\377')
  fprintf(*f, "%lc", s.val);

  if(s.next != NULL)
  {
    write_string_to_file(*(s.next), f);
  }

};

void write_file_to_string(string* s, FILE** f){


    //fprintf(*f, "%c", s.val);
    wchar_t c;
    if(fscanf(*f, "%lc", &c) == 1)
    {

      append_string(s, c);
      write_file_to_string(s->next, f);
    }

};



