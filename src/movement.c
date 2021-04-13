#include <curses.h>

#include "gem.h"
#include "movement.h"
#include "playarea.h"

/* cursor should already be reset */
int curx = 1, cury = 1;

void get_input(void)
{
  int c = wgetch(playarea);
  switch(c)
  {
    case KEY_UP:
      cury--;
      wmove(playarea, cury, curx);
      refresh();
      break;

    case KEY_DOWN:
      cury++;
      wmove(playarea, cury, curx);
      refresh();
      break;

    case KEY_LEFT:
      curx--;
      wmove(playarea, cury, curx);
      refresh();
      break;

    case KEY_RIGHT:
      curx++;
      wmove(playarea, cury, curx);
      refresh();
      break;
  }
}
