/* sql connector */
#include "sqldb.hh"

/* create db file with table if not exist */
void local_db_avaliable(void) {
  sqlite3* DB;
  if (sqlite3_open("stat.db", &DB)) {
    std::cerr << "failed to open stat.db" << sqlite3_errmsg(DB) << std::endl;
  } else {
    std::cout << "database -> stat.db connected" << std::endl;
  }
  sqlite3_close(DB);
}

void query_data(data *dataptr) {
  sqlite3* db;
  if (sqlite3_open("stat.db", &DB)) {
    std::cerr << "failed to open stat.db" << sqlite3_errmsg(DB) << std::endl;
  } else {
    std::cout << "database -> stat.db connected" << std::endl;
  }
  sqlite3_close(DB);
}
