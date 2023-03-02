#include <stdio.h>

#define TB_IMPL
#include "termbox.h"
#include <string.h>

#define SBLOCK 178 


/* a work in progress, copied over some code where i already got
   termbox working
   https://www.cs.uleth.ca/~holzmann/C/system/shell_commands.html
*/
//tb_set_cell(0, 0, 0x250C, TB_WHITE, TB_DEFAULT);
//tb_present()

//int wcwidth(wchar_t c);
void print_tb(const char*str, int x, int y, uint16_t fg, uint16_t bg);
int draw_win();
void draw_ui();
int draw_title();

enum {
  TITLE,
  GAME
};

typedef struct ACTOR{
  int x;
  int y;
  int z;
  char name[25] = "player";
} Actor;



Actor player;
//print out text
void print_tb(const char *str, int x, int y, uint16_t fg, uint16_t bg)
{
  while (*str) {
    uint32_t uni;
    str += tb_utf8_char_to_unicode(&uni, str);
    tb_set_cell(x, y, uni, fg, bg);
    x++;
  }
}
int draw_title() {
  int x = 3;
  int y = 3;
  tb_clear();
  print_tb("The name of the game!",   x+1,y+1, TB_WHITE, TB_DEFAULT);
  print_tb("n)ew game",               x+1,y+2, TB_WHITE, TB_DEFAULT);
  print_tb("c)ontinue existing game", x+1,y+3, TB_WHITE, TB_DEFAULT);
  print_tb("o)ptions",                x+1,y+4, TB_WHITE, TB_DEFAULT);
  print_tb("q)uit",                   x+1,y+5, TB_WHITE, TB_DEFAULT);
  tb_present();
}
int draw_win(Actor *p) {
  tb_clear();
  for(int v=0; v<20;v++){
    tb_set_cell(v,0,SBLOCK,TB_WHITE,TB_DEFAULT);
    tb_set_cell(0,v,SBLOCK,TB_WHITE,TB_DEFAULT);
  }
  
  for(int y = 0; y < 20; y++) {
    for(int x = 0; x < 20; x++) {
      //if(y == 10 && x == 10) {
      if(y == p->y && x == p->x) {
	tb_set_cell(x+1,y+1,'@', TB_MAGENTA, TB_DEFAULT);
      }
      else {
	tb_set_cell(x+1,y+1,'.', TB_WHITE, TB_DEFAULT);
      }
    }
  }
  //tb_set_cell(0,0,'a', TB_WHITE, TB_DEFAULT);
  draw_ui();
  tb_present();
}

void draw_ui() {
  print_tb("Contrl+q to exit", 25, 3, TB_WHITE, TB_DEFAULT);
  print_tb("player x:", 25, 13, TB_WHITE, TB_DEFAULT);
  
  print_tb("player y:", 25, 23, TB_WHITE, TB_DEFAULT);
  
}

//main function
int main(int argc, char **argv)
{
  /*static struct Actor player;*/
  Actor *pl = &player;
  pl->x = 10; pl->y = 10; pl->z = 0;
  strcpy(player.name, "player");
  (void) argc; (void) argv;
  printf("testing hello world game\n");
  int ret;
  ret = tb_init();
  if(ret) {
    fprintf(stderr, "tb_init() failed with error code %d\n",
	    ret);
    return 1;
  }
  tb_set_input_mode( TB_INPUT_ESC | TB_INPUT_MOUSE );
  struct tb_event ev;
  draw_title();
    
  while(tb_poll_event(&ev) == TB_OK) {
    switch(ev.type) {
    case TB_EVENT_KEY:
      printf("%c %d\n", ev.key, ev.key);
      if(ev.key == TB_KEY_CTRL_Q) {
	tb_shutdown();
	return 0;
	break;
      }
      else if(ev.key == TB_KEY_ARROW_UP) {pl->y--;}
      else if(ev.key == TB_KEY_ARROW_DOWN) {pl->y++;}
      else if(ev.key == TB_KEY_ARROW_RIGHT) {pl->x++;}
      else if(ev.key == TB_KEY_ARROW_LEFT) {pl->y++;}
      else if(ev.ch == 'n') {
	draw_win(pl);
      }
      break;
    }
  }
  return 0;
}

void scan_some_characters() {
  int ch;
  char str[10];
  /* Loop until either loop reaches 9 (need one for null character) or EOF is reached*/
  for (int loop = 0; loop < 9 && (ch = getc(stdin)) != EOF; ) {
    if (ch != ' ' ) {
      str[loop] = ch;
      ++loop;
    }
  }
  //str[loop] = 0;
  
  printf("%s", str);
}
