# Crangon

## Description

Experiment program for counting very small aquatic animal that moving in water flume

This project is a background process, it is needed a front-end application [cvmui](https://github.com) to be interactive

![experiment](https://i.imgur.com/pyDZTjF.gif)

> a short demo of progression in small prawn counter running on Nvidia Jetson Nano


## Goals
---

- Precision counting very small aquatic animal like baby prawn, Juvenile fish and such
- Achieve +90% counting accuracy at water flow speed of 4 gallons per minute (gpm)

## Prerequisite

- OpenCV4
- CMake
- sqlite3
- spdlog

### Debian required packages

```bash
sudo apt install cmake libopencv-dev libsqlite3-dev libspdlog-dev 
```

### FreeBSD required packages

```sh
sudo pkg install opencv libspdlog libsqlite3-dev cmake
```

### Thought
---

- simple CLI program - can be used without display
- configure file - modified image processing pipeline without recompile whole program
- server-client architecture - this approach make GUI development more flexible
- built-in database - result are save in local database

### Current project status
---

[ ] reimplement image processing pipeline from previous project.
[ ] add an additional functionally 
[ ] check and test FreeBSD compatibility with target hardware.
[ ] build and test project against FreeBSD version of libraries.

## License
---

See [LICENSE](https://github.com/kanokkorn/crangon/blob/main/LICENSE)
