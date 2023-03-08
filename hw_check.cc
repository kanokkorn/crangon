#include "hw_check.hh"

uint8_t camera(void) {
  /* TBD: camera interface not decide yet */
  return 0;
}

uint8_t usbcon(void) {
  return 0;
}

uint8_t on_display(void) {
  /* TBD: display protocol not decide yet */
  return 0;
}

uint8_t ext_display(void) {
  /* TBD: display protocol not decide yet */
  return 0;
}

uint8_t hw_readiness(void) {
  if (camera || usbcon || on_display || ext_display) {
    return 1;
  }
  return 0;
}

