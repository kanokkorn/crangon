#define _POSIX_SOURCE

#include <iostream>
#include <cstdlib>
#include <csignal>
#include <string>
#include <fstream>
#include <thread>
#include <atomic>
#include <chrono>
#include <future>
#include <condition_variable>

#include <spdlog/spdlog.h>
#include <jsoncpp/json/json.h>
#include "process.hh"
