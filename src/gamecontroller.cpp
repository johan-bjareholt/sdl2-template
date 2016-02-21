#include "gamecontroller.h"

bool controller_enabled = false;
SDL_GameController* controller = NULL;

/*
// Joystick
SDL_CONTROLLER_AXIS_INVALID
SDL_CONTROLLER_AXIS_LEFTX
SDL_CONTROLLER_AXIS_LEFTY
SDL_CONTROLLER_AXIS_RIGHTX
SDL_CONTROLLER_AXIS_RIGHTY
SDL_CONTROLLER_AXIS_TRIGGERLEFT
SDL_CONTROLLER_AXIS_TRIGGERRIGHT
SDL_CONTROLLER_AXIS_MAX
// Buttons
SDL_CONTROLLER_BUTTON_INVALID
SDL_CONTROLLER_BUTTON_A
SDL_CONTROLLER_BUTTON_B
SDL_CONTROLLER_BUTTON_X
SDL_CONTROLLER_BUTTON_Y
SDL_CONTROLLER_BUTTON_BACK
SDL_CONTROLLER_BUTTON_GUIDE
SDL_CONTROLLER_BUTTON_START
SDL_CONTROLLER_BUTTON_LEFTSTICK
SDL_CONTROLLER_BUTTON_RIGHTSTICK
SDL_CONTROLLER_BUTTON_LEFTSHOULDER
SDL_CONTROLLER_BUTTON_RIGHTSHOULDER
SDL_CONTROLLER_BUTTON_DPAD_UP
SDL_CONTROLLER_BUTTON_DPAD_DOWN
SDL_CONTROLLER_BUTTON_DPAD_LEFT
SDL_CONTROLLER_BUTTON_DPAD_RIGHT
SDL_CONTROLLER_BUTTON_MAX
*/


bool load_controller (int i) {
    SDL_Joystick* js = SDL_JoystickOpen(i);
    if (!js) {
      return false;
    }
    log_debug("Found controller!");

    /*
        SDL_GameController
    */

    // Open controller
    /*controller = SDL_GameControllerOpen(i);
    if (!controller){
      printf("Found controller, but could not open\n");
    }*/

    /*
        SDL_Joystick
    */

    // Get controller name
    const char* controller_name = SDL_JoystickName(js);
    if (controller_name) {
        log_debug("Found controller with joystick name:");
        log_debug(controller_name);
    } else {
        log_debug("Joystick has no game controller named:");
        log_debug(controller_name);
    }


    // Get controller GUID
    SDL_JoystickGUID controller_guid;
    controller_guid = SDL_JoystickGetGUID(js);
    char controller_guid_str[1024];
    SDL_JoystickGetGUIDString(controller_guid, controller_guid_str, sizeof(controller_guid_str));
    log_debug("Controller GUID:");
    log_debug(controller_guid_str);

    int num_axes = SDL_JoystickNumAxes(js);
    int num_buttons = SDL_JoystickNumButtons(js);
    int num_hats = SDL_JoystickNumHats(js);
    int num_balls = SDL_JoystickNumBalls(js);

    /*printf("%s \"%s\" axes:%d buttons:%d hats:%d balls:%d\n",
           controller_guid_str, controller_name,
           num_axes, num_buttons, num_hats, num_balls);*/

    SDL_JoystickClose(js);
    return true;
}

void find_controllers () {
	SDL_Init(SDL_INIT_JOYSTICK);
	int num_joysticks = SDL_NumJoysticks();
  int i;
  for(i = 0; i < num_joysticks && !controller_enabled; ++i)
  {
    if (load_controller(i)){
      controller_enabled = true;
    }
  }
  if (controller_enabled){
    log_debug("Selected controller: ");
    log_debug(SDL_GameControllerName (controller));
    //printf("Using mapping: %s\n", SDL_GameControllerMapping (controller));
  }
  else { log_debug("No controller connected"); }
}
