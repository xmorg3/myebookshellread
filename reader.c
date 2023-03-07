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
/*set everything up, converting if needed*/
int init_reader(char *filename, char *filearg, int bookmark, int manpage);

/*drawing text to the screen*/
int draw_title(char *filename, char *filearg, int bookmark, int manpage);


int init_reader(char *filename, char *filearg, int bookmark, int manpage)
{
  /* run a conversion filename should = the text file result*/ 
}

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
int draw_title(char *filename, char *filearg, int bookmark, int manpage) {
  int x = 3;
  int y = 3;
  tb_clear();
  print_tb("eBook reader - in dev.",   2,1, TB_WHITE, TB_DEFAULT);
  print_tb("------------------------------------------", 2,2, TB_WHITE, TB_DEFAULT);

  /*print_tb("%s", the string we awked*/
  print_tb("q to exit", 2, 15, TB_WHITE, TB_DEFAULT);
  tb_present();
}
int draw_win() {
  tb_clear();
  for(int v=0; v<20;v++){
    tb_set_cell(v,0,SBLOCK,TB_WHITE,TB_DEFAULT);
    tb_set_cell(0,v,SBLOCK,TB_WHITE,TB_DEFAULT);
  }
  
  //tb_set_cell(0,0,'a', TB_WHITE, TB_DEFAULT);
  draw_ui();
  tb_present();
}

void draw_ui() {
  print_tb("q to exit", 25, 3, TB_WHITE, TB_DEFAULT);
  print_tb("player x:", 25, 13, TB_WHITE, TB_DEFAULT);
  
  print_tb("player y:", 25, 23, TB_WHITE, TB_DEFAULT);
  
}

//main function
int main(int argc, char *argv[])
{
  /*
    gcc -o myprog myprog.c
    would result in the following values internal to GCC:
    argc :     4
    argv[0] :     gcc
    argv[1] :     -o
    argv[2] :     myprog
    argv[3] :     myprog.c
   */
  if(argc > 1) {
    char *filearg = argv[1];
  } else {
    char *filearg = "nofile";
    /*display usage*/
  }
  if(argc > 2) {
    int bookmark = atoi(argv[2]);
  } else {int bookmark = 0;} //assuming bookmark; 0 if not an int
  if(argc > 3) {
    int manpage = 1;
  } else {int manpage = 0;}
  
  int ret;
  ret = tb_init();
  if(ret) {
    fprintf(stderr, "tb_init() failed with error code %d\n", ret);
    return 1;
  }
  tb_set_input_mode( TB_INPUT_ESC | TB_INPUT_MOUSE );
  struct tb_event ev;
  /*draw_title();*/
    
  while(tb_poll_event(&ev) == TB_OK) {
    draw_title(filearg, bookmark, manpage);
    switch(ev.type) {
    case TB_EVENT_KEY:
      printf("%c %d\n", ev.key, ev.key);
      if(ev.key == TB_KEY_CTRL_Q) {
	tb_shutdown();
	return 0;
	break;
      }
      else if(ev.ch == 'q') {
	tb_shutdown();
        return 0;
        break;
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
