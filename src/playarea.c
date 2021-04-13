#include <curses.h>
#include <stdlib.h>
#include <time.h>

#include "gem.h"
#include "main.h"
#include "playarea.h"

#define BORDER_HEIGHT 13
#define BORDER_WIDTH  25

#define BORDER_ENDS '-'
#define BORDER_SIDE '|'

#define GEMSIZE 12 * 24

WINDOW *playarea;
struct gem allgems[GEMSIZE];

void setup_playarea(void)
{
  int maxx = 0;
  int maxy = 0;
  getmaxyx(stdscr, maxy, maxx);

  srand(time(NULL));

  printw("ammolite v%s\n", AMMOLITE_VERSION);
  printw("Score: %d\n", 0);

  /* 12x24 grid, so a 13x25 border */
  int x = 0, y = 0;
  x = (maxx / 2) - (int)(BORDER_WIDTH / 2);
  y = (maxy / 2) - (int)(BORDER_HEIGHT / 2);

  playarea = newwin(BORDER_HEIGHT, BORDER_WIDTH, y, x);
  box(playarea, BORDER_SIDE, BORDER_ENDS);

  keypad(playarea, TRUE);
}

void destroy_playarea(void)
{
  delwin(playarea);
}

void refresh_playarea(void)
{
  wrefresh(playarea);
}

/* gems... */

int rand_in_range(int min, int max)
{
  return rand() % (max + 1 - min) + min;
}

char pick_gem_char(void)
{
  switch(rand_in_range(1, 7))
  {
    case 1:
      return GEM_AT;
      break;

    case 2:
      return GEM_ASTERISK;
      break;

    case 3:
      return GEM_EQUALS;
      break;

    case 4:
      return GEM_HASH;
      break;

    case 5:
      return GEM_PLUS;
      break;

    case 6:
      return GEM_PERCENT;
      break;

    case 7:
      return GEM_AMP;
      break;
  }

  /* make the compiler happy */
  return GEM_SELECT;
}

short pick_gem_colour(void)
{
  return rand_in_range(1, 5);
}

/* gems are stored in the array from top left
 to the bottom right */
void fill_gems(void)
{
  int i = 0, x = 0, y = 1;
  while(i != GEMSIZE - 1 && y < BORDER_HEIGHT - 1)
  {
    allgems[i].type = GEM_NORMAL;
    allgems[i].character = pick_gem_char();
    allgems[i].colour_pair = pick_gem_colour();
    allgems[i].xoffset = 0;

    x++;
    allgems[i].x = x;

    if(x >= BORDER_WIDTH - 1)
    {
      x = 0;
      y++;

      allgems[i].x = x;
      allgems[i].y = y;
      allgems[i].xoffset = 1;
    }

    //printf("x: %d  y: %d  c: %d\n", x, y, allgems[i].colour_pair);
    wattron(playarea, A_NORMAL | COLOR_PAIR(allgems[i].colour_pair));
    if(!allgems[i].xoffset)
      mvwaddch(playarea, y, x, allgems[i].character);
    else if(y != BORDER_HEIGHT - 1)
      mvwaddch(playarea, y, x + 1, allgems[i].character);

    i++;
  }

  wmove(playarea, 1, 1);
}
