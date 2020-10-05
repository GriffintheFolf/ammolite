#include <curses.h>

#include "main.h"
#include "playarea.h"

int main(int argc, char **argv)
{
  initscr();
  cbreak();
  noecho();
  nonl();
  keypad(stdscr, TRUE);
  
  if(!has_colors())
  {
    endwin();
    fprintf(stderr, "Sorry, your terminal does not support colour!\n"\
      "ammolite requires a colour terminal to play.\n");
    return -1;
  }
  else
  {
    start_color();
  }
  
  int maxx = 0;
  int maxy = 0;
  getmaxyx(stdscr, maxy, maxx);
  
  setup_playarea();
  
  refresh();
  fill_gems();
  refresh_playarea();
  
  getchar();
  
  destroy_playarea();
  endwin();
  return 0;
}
