/* configuration of crangon daemon */
#include "stats.hh"

enum class ErrorStatus {
    SUCCESS = 0,
    INVALID_INPUT,
    FILE_NOT_FOUND,
    OUT_OF_MEMORY,
    NETWORK_ERROR,
};

// Create a map to store error messages for each status
const std::map<ErrorStatus, std::string> errorMessages = {
    {ErrorStatus::SUCCESS, "Operation successful"},
    {ErrorStatus::INVALID_INPUT, "Invalid input provided"},
    {ErrorStatus::FILE_NOT_FOUND, "File not found"},
    {ErrorStatus::OUT_OF_MEMORY, "Out of memory"},
    {ErrorStatus::NETWORK_ERROR, "Network error occurred"},
    // Add more error messages as needed
};

// Function to get the error message for a given status
std::string getErrorMessage(ErrorStatus status) {
    auto it = errorMessages.find(status);
    if (it != errorMessages.end()) {
        return it->second;
    } else {
        return "Unknown error";
    }
}

int resultCommit(void) {
  sqlite3* DB;
  if (sqlite3_open("stat.db", &DB)) {
    std::cerr << "failed to open stat.db" << sqlite3_errmsg(DB) << std::endl;
    return 1;
  }
  std::cout << "database -> stat.db connected" << std::endl;
  return 0;
}
