#pragma once

#include <stdio.h>    //used for input/output
#include <memory.h>   //used for memcopy()
#include <unistd.h>   //necassary for read()
#include <termios.h>  //used to get termio structure   
#include <locale.h>
#include <wchar.h>


struct termios old = {0};
struct termios save = {0};

void setup(){



  if(tcgetattr(0, &old) < 0)
  {
    perror("tcsetaddr");
  }

  memcpy(&save, &old, sizeof(struct termios));
  //////////////////////////////////////////////////////////
  // set the ICANON and ECHO bits in the local flag 
  // to false to set the mode to non-canonical 
  // and turn off echoing inpout characters
  ////////////////////////////////////////////////////
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;

  old.c_cc[VMIN] = 0;
  old.c_cc[VTIME] = 0;

  if(tcsetattr(0, TCSANOW, &old) < 0)
  {
    perror("tcsetattr ICANON");
  }

  setlocale(LC_ALL, "en_US.UTF-8");

}


wchar_t get_char(){

  wchar_t c = 0;
  wchar_t ret = 0;
  //////////////////////////////////////////////////////////
  // create termios struct  βββββ
  ////////////////////////////////////////////////////

  if(tcgetattr(0, &old) < 0)
  {
    perror("tcsetaddr");
  }


  if(read(0, &c, 1) < 0){
    perror("read");
  }
  
  ret = c;
  if( ((c >> 7)) != 0x0){

    
    if(read(0, &ret, 1) < 0){
      perror("read");
    }
    ret = (((wchar_t)c << 8)) | ret;
  }
  
  //ret = c;


  //////////////////////////////////////////////////////////
  // set the ICANON and ECHO bits in the local flag 
  // to true
  ////////////////////////////////////////////////////

  //old.c_lflag |= ICANON;
  //old.c_lflag |= ECHO;

  if(tcsetattr(0, TCSADRAIN, &old) < 0){
    perror("Idek man");
  }



  return ret;

}


