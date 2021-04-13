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
      refresh();
      break;

    case KEY_DOWN:
      cury++;
      refresh();
      break;

    case KEY_LEFT:
      curx--;
      refresh();
      break;

    case KEY_RIGHT:
      curx++;
      refresh();
      break;
  }

  wmove(playarea, cury, curx);
}
