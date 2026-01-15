# Crangon

## Description

Crangon is an experimental program for counting small aquatic animals moving in a water flume. It is designed to run as a background process and can be paired with a front-end application like [cvmui](https://github.com) for interactive use.

![experiment](https://i.imgur.com/pyDZTjF.gif)

> A short demo of the prawn counter running on an Nvidia Jetson Nano.

## Goals

- Precisely count small aquatic animals, such as baby prawns and juvenile fish.
- Achieve over 90% counting accuracy at a water flow speed of 4 gallons per minute (GPM).

## Features

- **CLI-based:** Can be operated in a headless environment.
- **Configurable:** The image processing pipeline can be adjusted without recompiling.
- **Client-Server Architecture:** A flexible design that allows for various GUI implementations.
- **Built-in Database:** Results are stored locally in a SQLite database.

## Prerequisites

- A C++17 compliant compiler
- CMake 3.14 or later

All other dependencies are managed automatically by CMake's `FetchContent` feature, including:

- OpenCV
- spdlog
- sqlite3

## Building

To build the project, follow these steps:

```bash
git clone https://github.com/kanokkorn/crangon.git
cd crangon
mkdir build && cd build
cmake ..
make
```

## Current Project Status

- [x] Refactor the build system to use CMake's `FetchContent`.
- [x] Restructure the project to separate components.
- [ ] Re-implement the image processing pipeline.
- [ ] Add new functionalities.
- [ ] Test FreeBSD compatibility.

## License

This project is licensed under the terms of the [LICENSE](https://github.com/kanokkorn/crangon/blob/main/LICENSE) file.
