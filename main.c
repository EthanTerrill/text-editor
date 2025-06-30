////////////////////////////////////////////////////////////////////////////////////////
/// Copyright (C) Ethan Terrill 2025
///
/// The following code is freely available for anyone
/// to use modify or redistribute with credit attributed
///
/// The following code may not however be used for training
/// AI agents including but not limited to LLMs such as
/// ChatGPT
///
/// Ethanrobertterrill@gmail.com
////////////////////////////////////////////////////////////////////////////////
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
// Function for cleaning up and restoring terminal
///////////////////////////////////////////////////////////
void cleanup() {
  printf("\033[?25h");
  system("clear");
  tcsetattr(0, TCSANOW, &save);
}


int main(int arg_num, char* argv[]) {
  FILE* ftest;
  string s;
  char* filename = "output.c";
  setup();


  s.val = 0;
  s.next = NULL;
  s.prev = NULL;

  s.flags = CURSOR;
  mode = MODE_MOV;

  string* cursor = &s;
  wchar_t curr = 0;

  if (arg_num == 2) {
    filename = argv[1];
  }
  FILE* fo = fopen(filename, "rw");
  wprintf(L"file open-\n");
  write_file_to_string(&s, &fo);

  fclose(fo);
  wchar_t star = 0xceb2;

  wprintf(L"\n\n%lc\n", star);

  atexit(&cleanup);

  while (status) {
    wprintf(L"\033c\033[H");

    wprintf(L"\033[?25l");
    if (mode == MODE_MOV) {
      wprintf(L"[%d]\t[Move]\t[Ethan]\t[%#x]\n", curr, cursor->val);
    } else if (mode == MODE_TEXT) {
      wprintf(L"[%d]\t[Text]\t[Ethan]\n", curr);
    }
    wprintf(L"--------------------------\n");
    print_str(s);
    wprintf(L"\n--------------------------\n");

    do {
      curr = get_char();
      usleep(10000);
    } while (curr == 0);


    if (mode == MODE_TEXT) {
      parse_insert_char(curr, &cursor);
    } else if (mode == MODE_MOV) {
      parse_move(curr, &cursor);
    }
  }

  ftest = fopen(filename, "w");
  printf("file open\n");
  write_string_to_file(*(s.next), &ftest);
  fclose(ftest);
}
