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

WINDOW *playarea;
struct gem allgems[12 * 24];

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
  switch(rand_in_range(1, 6))
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
  }
  
  /* make the compiler happy */
  return GEM_SELECT;
}

/* gems are stored in the array from top left
 to the bottom right */
void fill_gems(void)
{
  int i = 0, x = 0, y = 1;
  while(i != 12 * 24 - 1 && y != BORDER_HEIGHT - 1)
  {
    allgems[i].type = GEM_NORMAL;
    allgems[i].character = pick_gem_char();
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
    
    //printf("x: %d     y: %d\n", x, y);
    if(!allgems[i].xoffset)
      mvwaddch(playarea, y, x, allgems[i].character);
    else
      mvwaddch(playarea, y, x + 1, allgems[i].character);
    
    i++;
  }
}
