#include <lib6dof.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#define ESC 27
#define WIDTH 80
#define BUTTONS 2

int main(void) {

  l6dof_t* l6dof = l6dof_open();
  if(l6dof==NULL) {
    fprintf(stderr,"No 6DOF device found. :(\n");
    exit(1);
  }

  double pos[6]={0.0};
  void axis_callback(l6dof_axis_t axis, signed short input) {
    pos[axis]=(double)input/2048.0;
  }
  l6dof_axis_callback(l6dof,axis_callback);

  char buttons[BUTTONS]={0};
  void button_callback(l6dof_button_t button, char on) {
    buttons[button]=on;
  }
  l6dof_button_callback(l6dof,button_callback);

  printf("\n\n\n\n\n\n\n");
  ESCDELAY=25; //Curses waits too long for key sequences by default
  while(getch()!=27) {

    printf("\e[6A");

    int axis;
    for(axis=0;axis<6;axis++) {
      int x = (1+pos[axis])*(WIDTH/2-1);
      int i;
      printf("[");
      for(i=0;i<WIDTH-2;i++) {
        printf((i==x)?"X":" ");
      }
      printf("]\n");
    }

    int button;
    for(button=0;button<BUTTONS;button++) {
      printf("[ %c ]  ",buttons[BUTTONS]?'X':' ');
    }

    l6dof_check_for_events(l6dof);

  }

  return 0;
}
