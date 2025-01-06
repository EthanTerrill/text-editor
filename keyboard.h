#pragma once

#include "text_editor.h"
#include "string.h"
//#include "terminal.h"

void parse_insert_char(wchar_t curr, string** cursor){

  (*cursor)->flags &= ~CURSOR;
  switch(curr){

    case 4283163: // up
      move_cursor_up(cursor);
    break;
    case 4348699: //down
      move_cursor_down(cursor);
    break;
    case 4414235: //right
       
      move_cursor_right(cursor);
      
    break;
    case 4479771: //left
      
      move_cursor_left(cursor);
      
    break;

    case 127:
    delete_character(cursor);

    break;

    case 27:
      mode = MODE_MOV;
    break;


    
    default:
    append_string(*cursor, curr);
    *cursor = (*cursor)->next;
    
    break;
  }
  (*cursor)->flags |= CURSOR;
}

void parse_move(wchar_t curr, string** cursor){

  (*cursor)->flags &= ~CURSOR;
  switch(curr){

    case 'h':
      move_cursor_left(cursor);


      break;
    case 'l':
      move_cursor_right(cursor);



      break;
    case 'j':
      move_cursor_down(cursor);


      break;
    case 'k':
      move_cursor_up(cursor);

      
      break;
    case 'i':
      mode = MODE_TEXT;



      break;
    case 'a':
      move_cursor_right(cursor);
      mode = MODE_TEXT;
    break;
    case 'e':



      status = 0;
    break;
  }

  (*cursor)->flags |= CURSOR;
}


