//Initializing the library

typedef struct l6dof_ctx l6dof_t;

/***/
l6dof_t* l6dof_open(void);
/***/

//Setting up callbacks

typedef enum {
  L6DOF_AXIS_TRANSLATE_X=0,
  L6DOF_AXIS_TRANSLATE_Y,
  L6DOF_AXIS_TRANSLATE_Z,
  L6DOF_AXIS_ROTATE_X,
  L6DOF_AXIS_ROTATE_Y,
  L6DOF_AXIS_ROTATE_Z
} l6dof_axis_t;
typedef void (*l6dof_axis_cb_t)(l6dof_axis_t, signed short pos);

/***/
void l6dof_axis_callback(l6dof_t*, l6dof_axis_cb_t);
/***/

typedef char l6dof_button_t;
typedef void (*l6dof_button_cb_t)(l6dof_button_t, char button_on);

/***/
void l6dof_button_callback(l6dof_t*, l6dof_button_cb_t);
/***/

//Checking for events, calling callbacks if necessary

/***/
void l6dof_check_for_events(l6dof_t*);
/***/

/***/
void l6dof_close(l6dof_t*);
/***/
