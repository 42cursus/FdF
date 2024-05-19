# FdF
## A project about making a wireframe and projection rendering.

This project is about creating a simple wireframe model representation of a 3D
landscape by linking various points (x, y, z) with line segments (edges).

### Objectives:

To get familiar with the [MiniLibX](https://github.com/42Paris/minilibx-linux) library and discover the basics of graphics programming.


![Screenshot of a working programm](/resources/program_screenshot.png)

# Before you start

1. Configure submodules for the project:
   ```bash
   git submodule update --init --recursive
   ```
2. Make symlink for `mlx`:
   ```bash
   # for linux
   cd lib && ln -s mlx-linux mlx
   # for MacOS
   cd lib && ln -s mlx-macos mlx
   ```
