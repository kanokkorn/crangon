# Crangon

## Description

Experimental counter and analyzer aquaculture animals with state-of-the-art computer vision and machine learning for minimizing error from human and maximizing the accuracy of counting

This project was designed to reduce human error when counting by hand and exceed human speed with unbeatable process time.

A machine has already been evaluated by counting against 250 baby prawns with approximately 95% accuracy using less than 2 minutes, with increase water flow rate. accuracy dropped slightly to 90% due to frame skipping in visual processing.

To maximize effiency, we'll be using minimal Debian/FreeBSD to allow us to customize every processes, task and finest adjustment to system to ensure we aren't waste any compute power.

![experiment](https://i.imgur.com/pyDZTjF.gif)

> a short demo of progession in baby prawn counter running on Nvidia Jetson Nano

## Goals
---

- Precision baby prawn counter with ±5% error rate against 2000 prawn with less than 3 minutes operate time.
- Modern and accessible user interface with focus on user and machine operator experience.
- Design a machine with modularity to be expandable, customizable and upgradable.


## Preresquisite

- OpenCV4
- JSON

### Debian

```bash
sudo apt install libopencv-dev libjson-dev
```

### FreeBSD

```
sudo pkg install opencv jsoncpp
```

### Thought
---

- consider alternative computer vision frameworks like `ccv`
- rewrite in c language for portability

### Current project status
---

- Check and test FreeBSD compatibility with target hardware.
- Build and test project against FreeBSD's version of libraries.

## License
---

See [LICENSE](https://github.com/kanokkorn/crangon/blob/main/LICENSE)
