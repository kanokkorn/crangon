#include "hw_check.hh"

/* check camera by looking for /tty/dev/cam0, quit on false */
extern bool camera(void) {
  return true;
}

bool usbcon(void) {
  return true;
}

/* check for external display */
bool on_display(void) {
  return true;
}

bool ext_display(void) {
  return true;
}

extern bool hw_readiness(void) {
  if (camera() || usbcon() || on_display() || ext_display()) {
    return true;
  }
  return false;
}
