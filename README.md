# Crangon

## Description

Experimental counter and analyzer aquaculture animals with computer vision and machine learning assisted for minimizing error from human and maximizing the accuracy of counting

This project was designed to be a background process and needed a front-end application [cragui](https://github.com) to be fully functional

![experiment](https://i.imgur.com/pyDZTjF.gif)

> a short demo of progression in small prawn counter running on Nvidia Jetson Nano


## Goals
---

- image processing time <50ms per frame without sacrifice accuracy
- minimal memory footprint enough for embedded
- extensible with front-end through UDS & TCP
- fast & secure local storage
- works well with BSD Unix or Linux with musl & glibc

## Prerequisite

- OpenCV4
- CMake
- sqlite3

### Debian required packages

```bash
sudo apt install libopencv-dev libsqlite3-dev cmake
```

### FreeBSD required packages

```sh
sudo pkg install opencv libsqlite3-dev cmake
```

### Thought
---

- consider alternative computer vision frameworks like `ccv`
- rewrite in c language for portability

### Current project status
---

[ ] reimplement image processing pipeline from previous project.
[ ] add an additional functionally 
[ ] check and test FreeBSD compatibility with target hardware.
[ ] build and test project against FreeBSD version of libraries.

## License
---

See [LICENSE](https://github.com/kanokkorn/crangon/blob/main/LICENSE)
