#define _POSIX_SOURCE

#include <iostream>
#include <cstdlib>
#include <csignal>
#include <string>
#include <fstream>
#include <thread>

#include <unistd.h>
#include <sys/types.h>

#include <spdlog/spdlog.h>
#include <jsoncpp/json/json.h>
#include "process.hh"
