/*
 * File: sq.hh
 * Author: kanokkorn kornkankit <kanokorn@outlook.jp>
 */

#ifndef __SQ_H__
#define __SQ_H__

#include <sqlite3.h>
#include <spdlog/spdlog.h>

void send_sq(void) {
  sqlite3 *db;
  int rc;
  rc = sqlite3_open("store.db", &db);
  if (rc) {
    spdlog::critical("error -> can't open database: %s", sqlite3_errmsg(db));
    exit(1);
  } else {
    spdlog::info("open database sucessfully");
  }
  sqlite3_close(db);
}

#endif /* __SQ_H__ */
