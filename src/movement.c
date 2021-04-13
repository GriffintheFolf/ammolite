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
      break;

    case KEY_DOWN:
      cury++;
      break;

    case KEY_LEFT:
      curx--;
      break;

    case KEY_RIGHT:
      curx++;
      break;
  }

  if(curx > 23)
    curx = 23;
  if(curx <= 0)
    curx = 1;
  if(cury <= 0)
    cury = 1;
  if(cury > 11)
    cury = 11;

  wmove(playarea, cury, curx);
}
