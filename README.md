*This project has been created as part of the 42 curriculum by abelov.*

# FdF

## Description

FdF renders a wireframe model of a landscape from a `.fdf` height map. Each value in
the map represents a point altitude, and neighbouring points are connected with line
segments in an isometric projection.

The project uses MiniLibX for window creation, image buffers, and keyboard/mouse
events. Line rasterization is implemented in the project with a Bresenham-style
renderer that writes into an MLX image before blitting it to the window.

## Instructions

Build the mandatory program:

```sh
make
```

Run it with a map:

```sh
./fdf resources/demo_maps/height.fdf
```

Other useful commands:

```sh
make bonus
make test
make clean
make fclean
make re
```

Current controls:

- `ESC` or keypad `5`: close the window
- Window close button: close the window
- Arrow keys: translate the model
- Mouse wheel: zoom in and out

## Resources

- 42 FdF subject v5.0
- MiniLibX documentation and sources
- X11 documentation for expose events and image formats
- Bresenham line algorithm references for integer line rasterization

AI was used as a review and planning aid: drafting staged refactor plans,
and checking implementation risks.
All code changes are reviewed and owned by the project author.
