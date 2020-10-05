#ifndef _GEM_H_
#define _GEM_H_

#define GEM_AT       '@'
#define GEM_ASTERISK '*'
#define GEM_EQUALS   '='
#define GEM_HASH     '#'
#define GEM_PLUS     '+'
#define GEM_PERCENT  '%'
#define GEM_SELECT   '?'

enum gem_type
{
  GEM_NORMAL = 0,
  GEM_FLAME,
  GEM_STAR,
  GEM_SELECTIVE,
  GEM_9000
};

struct gem
{
  enum gem_type type;
  
  char character;
  int colour;
  int x, y;
  int xoffset;
};

#endif /* _GEM_H_ */
