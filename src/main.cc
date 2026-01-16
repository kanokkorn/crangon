#include "vision/crangc.hh"
#include "database/sqldb.hh"
#include "hw/hw_check.hh"

int main(int argc, char** argv) {
  if (argc <= 1) {
    help_mesg();
    return 0;
  }
  argcheck(argv[1]);
  return 0;
}
