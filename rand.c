#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>


#include "text_editor.h"
#include "string.h"
#include "keyboard.h"
#include "terminal.h"



///////////////////////////////////////////////////////////////
// basic function for getting the key
///////////////////////////////////////////////////////////




FILE* ftest;

string s;

void cleanup(){

  printf("\033[?25h");
  system("clear");

  free_string(&s);

  tcsetattr(0, TCSANOW, &save);
}


int main(int arg_num, char* argv[]){


  setup();


  s.val = 0;
  s.next = NULL;
  s.prev = NULL;

  s.flags = CURSOR;
  mode = MODE_MOV;

  string* cursor = &s;
  wchar_t curr = 0;

  FILE* fo = fopen("output.c", "r");
  printf("file open-\n");
  write_file_to_string(&s, &fo);

  fclose(fo);
  //sleep(1);

  atexit(&cleanup);
  while(status) {



    printf("\033c\033[H");

    printf("\033[?25l");
    if(mode == MODE_MOV){

      printf("[%d]\t[Move]\t[Ethan]\n", curr);
    }
    else if(mode == MODE_TEXT){

      printf("[%d]\t[Text]\t[Ethan]\n", curr);
    }
    printf("--------------------------\n");
    print_str(s);
    printf("\n--------------------------\n");
    
    do{
      curr = get_char();
      
      usleep(10000);
    } while(curr == 0);
     
    if(mode == MODE_TEXT){
      parse_insert_char(curr,&cursor);
    }
    else if(mode == MODE_MOV){

      parse_move(curr, &cursor);
    }
    

    //system("clear");
    //printf("%d", curr);


    //printf("\n");
  };

  //print_str(s);



  ftest = fopen("output.c", "w");
  printf("file open\n");
  write_string_to_file(*(s.next), &ftest);
  fclose(ftest);






}



