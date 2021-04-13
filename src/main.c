#include <curses.h>

#include "main.h"
#include "movement.h"
#include "playarea.h"

void init_colour_pairs(void)
{
  /* regular colours */
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);

  /* special gems */
  init_pair(6, COLOR_BLACK, COLOR_RED); /* flame */
  init_pair(7, COLOR_WHITE, COLOR_CYAN); /* star */
  init_pair(8, COLOR_BLUE, COLOR_MAGENTA); /* selective */
  init_pair(9, COLOR_RED, COLOR_YELLOW); /* >9000 */
}

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
    init_colour_pairs();
  }

  int maxx = 0;
  int maxy = 0;
  getmaxyx(stdscr, maxy, maxx);

  setup_playarea();

  refresh();
  fill_gems();
  refresh();
  refresh_playarea();

  while(1 == 1)
  {
    get_input();
    refresh_playarea();
  }

  destroy_playarea();
  endwin();
  return 0;
}
