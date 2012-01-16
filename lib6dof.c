#include "lib6dof.h"
#include "hidapi.h"
#include <stdlib.h>

struct l6dof_ctx {
  hid_device* dev;
  l6dof_axis_cb_t axis_cb;
  l6dof_button_cb_t button_cb;
};

l6dof_t* l6dof_open(void) {
  hid_device* dev = NULL;
  unsigned short product_ids[] = {0xc625,0xc626,0xc627,0xc623,0x0};
  unsigned short *product_id = product_ids;
  while(dev==NULL) {
    dev=hid_open(0x046d,*(product_id++),NULL);
    if(*product_id==0x0) break;
  }
  if(dev) {
    l6dof_t* ctx = malloc(sizeof(l6dof_t));
    ctx->dev=dev;
    ctx->axis_cb=NULL;
    ctx->button_cb=NULL;
    return ctx;
  } else {
    return NULL;
  }
}

void l6dof_axis_callback(l6dof_t* ctx, l6dof_axis_cb_t axis_cb) {
  ctx->axis_cb=axis_cb;
}

void l6dof_button_callback(l6dof_t* ctx, l6dof_button_cb_t button_cb) {
  ctx->button_cb=button_cb;
}

void l6dof_check_for_events(l6dof_t* ctx) {
  unsigned char hidbuf[8];
  while(hid_read(ctx->dev,hidbuf,7)>0) {
    signed short input[6]={0,0,0,0,0,0};
    l6dof_axis_t axis=3;
    switch(hidbuf[0]) {
      case 1:
        axis=0;
      case 2:
        input[axis++] = hidbuf[1] | ((hidbuf[2])<<8);
        input[axis++] = hidbuf[3] | ((hidbuf[4])<<8);
        input[axis]   = hidbuf[5] | ((hidbuf[6])<<8);
        if(ctx->axis_cb) {
          for(axis=0;axis<6;axis++) {
            if(input[axis]) {
              ctx->axis_cb(axis,input[axis]);
            }
          }
        }
        break;
      case 3:
        if(ctx->button_cb) {
          ctx->button_cb(hidbuf[1],hidbuf[2]);
        }
        break;
    }
  }
}

void l6dof_close(l6dof_t* ctx) {
  hid_close(ctx->dev);
  free(ctx);
}
  
