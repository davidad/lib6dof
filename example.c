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
    pos[axis]=(double)input/512.0;
  }
  l6dof_axis_callback(l6dof,axis_callback);

  printf("\n\n\n\n\n\n\n");
  ESCDELAY=25; //Curses waits too long for key sequences by default
  while(getch()!=27) {

    printf("\e[6A\e[80D");

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

    l6dof_check_for_events(l6dof);

  }

  return 0;
}
