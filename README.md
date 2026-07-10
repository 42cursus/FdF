*This project has been created as part of the 42 curriculum by abelov.*

# FdF

## Description

FdF renders a wireframe model of a landscape from a `.fdf` height map. Each value in
the map represents a point altitude, and neighbouring points are connected with line
segments. The default projection is isometric; parallel and cabinet projections are
available at runtime.

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
- `1`: isometric projection
- `2`: parallel projection
- `3`: cabinet projection
- `Space`: reset zoom, pan, rotation, and height factor
- Keypad `+` / `-`: increase or decrease height exaggeration
- Arrow keys: translate the model
- `Q`, `E`, `W`, `S`, `A`, `D`: rotate the model
- Mouse wheel: zoom toward the mouse pointer
- Middle mouse button drag: pan the model

## Rendering reference

This section documents the constants used by the renderer. They are intentionally
kept in `include/ft_fdf.h` so the projection, controls, and fitting behaviour can be
tuned without searching through the drawing code.

### Window fitting

The window size is estimated from the map dimensions before MiniLibX is initialized.
The goal is to open a reasonably sized window for the default view, then let the user
adjust it with zoom and pan.

| Constant | Value | Used for |
| --- | ---: | --- |
| `FDF_INIT_SCALE` | `20` | Initial `xy_scale` and `z_scale` before fitting |
| `FDF_WIN_MAX_WIDTH` | `1024` | Maximum window width |
| `FDF_WIN_MAX_HEIGHT` | `768` | Maximum window height |
| `FDF_WIN_WIDTH_FACTOR` | `280` | Width estimate multiplier |
| `FDF_PERCENT_DIVISOR` | `10` | Shared divisor for percentage-style calculations |
| `FDF_FIT_SCALE_NUMERATOR` | `10000` | Scale numerator used when width is capped |
| `FDF_GRID_SCALE_FACTOR` | `7` | Extra grid margin in the height estimate |
| `FDF_HEIGHT_MARGIN_DIVISOR` | `20` | Margin divisor for fitting calculations |

The width estimate starts from the longest map side:

```text
window_width = max(cols, rows) * FDF_WIN_WIDTH_FACTOR * 2 / FDF_PERCENT_DIVISOR
```

If this is wider than `FDF_WIN_MAX_WIDTH`, the width is clamped and `xy_scale` is
reduced:

```text
xy_scale = FDF_FIT_SCALE_NUMERATOR / (min(cols, rows) * FDF_GRID_SCALE_FACTOR * 2)
```

The height estimate combines altitude and grid margin:

```text
grid_margin = (cols + rows) * xy_scale / FDF_HEIGHT_MARGIN_DIVISOR
window_height = max_height * 2 * xy_scale + grid_margin
```

If the result is taller than `FDF_WIN_MAX_HEIGHT`, the height is clamped and
`z_scale` is reduced when the map has a positive maximum height.

### From map point to world point

The renderer first recenters each map point around the middle of the map. This keeps
rotation natural because the model spins around its own centre instead of around the
top-left corner.

| Symbol | Meaning |
| --- | --- |
| `col` | Column index from the map |
| `row` | Row index used by the renderer |
| `height` | Parsed altitude at `(col, row)` |
| `X`, `Y`, `Z` | Centered world-space coordinates |
| `screen_scale` | Final multiplier used by projection formulas |

```text
X = col - (cols - 1) / 2
Y = row - (rows - 1) / 2
Z = height * z_scale / xy_scale * z_factor
screen_scale = xy_scale * zoom
```

The first row in the input file is traversed with `row = rows - 1`; the last row is
traversed with `row = 0`. This preserves the intended back-to-front drawing order
for the default view.

### Rotation

Rotations are applied before projection, in this order: X, then Y, then Z. Angles are
stored in radians, and each keypress changes one angle by `FDF_ROT_STEP`.

| Constant | Value | Used for |
| --- | ---: | --- |
| `FDF_ROT_STEP` | `0.035` | Rotation amount per keypress, in radians |

| Plane | Formula |
| --- | --- |
| X | `Y' = Y * cos(angle) - Z * sin(angle)`, `Z' = Y * sin(angle) + Z * cos(angle)` |
| Y | `X' = X * cos(angle) + Z * sin(angle)`, `Z' = -X * sin(angle) + Z * cos(angle)` |
| Z | `X' = X * cos(angle) - Y * sin(angle)`, `Y' = X * sin(angle) + Y * cos(angle)` |

### Projections

Projection constants are divisors. Larger divisors make that axis visually shorter.
Parallel and cabinet projection use a depth divisor to foreshorten the receding axis.

| Constant | Value | Used for |
| --- | ---: | --- |
| `FDF_PROJ_ISO` | `1` | Isometric projection mode |
| `FDF_PROJ_PARALLEL` | `2` | Parallel projection mode |
| `FDF_PROJ_CABINET` | `3` | Cabinet projection mode |
| `FDF_ISO_X_DIVISOR` | `10` | Isometric horizontal scale |
| `FDF_ISO_Y_DIVISOR` | `20` | Isometric ground-plane vertical scale |
| `FDF_PARALLEL_DIVISOR` | `8` | Parallel projection scale |
| `FDF_PARALLEL_DEPTH_DIVISOR` | `2` | Parallel receding-axis foreshortening |
| `FDF_CABINET_X_DIVISOR` | `8` | Cabinet projection scale |
| `FDF_CABINET_DEPTH_DIVISOR` | `4` | Cabinet receding-axis foreshortening |

`W` and `H` are the window width and height. `pan_x` and `pan_y` are added at the
end so panning works the same way in every projection.

**Isometric**

```text
screen_x = (X - Y) * screen_scale / FDF_ISO_X_DIVISOR
           + W / 2 + pan_x

screen_y = H / 2
           - (X + Y) * screen_scale / FDF_ISO_Y_DIVISOR
           - Z * screen_scale / FDF_ISO_X_DIVISOR
           + pan_y
```

**Parallel**

```text
screen_x = (X + Y / FDF_PARALLEL_DEPTH_DIVISOR)
           * screen_scale / FDF_PARALLEL_DIVISOR
           + W / 2 + pan_x

screen_y = (-Y / FDF_PARALLEL_DEPTH_DIVISOR - Z)
           * screen_scale / FDF_PARALLEL_DIVISOR
           + H / 2 + pan_y
```

**Cabinet**

```text
screen_x = (X + Y / FDF_CABINET_DEPTH_DIVISOR)
           * screen_scale / FDF_CABINET_X_DIVISOR
           + W / 2 + pan_x

screen_y = (-Y / FDF_CABINET_DEPTH_DIVISOR - Z)
           * screen_scale / FDF_CABINET_X_DIVISOR
           + H / 2 + pan_y
```

### View controls

The view state is stored separately from parsed map data. Projection switches, pan,
rotation, zoom, and height exaggeration only change `t_view`; the map itself is not
modified.

| Constant | Value | Used for |
| --- | ---: | --- |
| `FDF_PAN_STEP` | `25` | Keyboard pan amount, in pixels |
| `FDF_Z_FACTOR_MIN` | `0.1` | Minimum height exaggeration |
| `FDF_Z_FACTOR_MAX` | `10.0` | Maximum height exaggeration |
| `FDF_Z_FACTOR_STEP` | `0.1` | Height exaggeration change per keypad press |
| `FDF_ZOOM_MIN` | `0.1` | Minimum zoom |
| `FDF_ZOOM_MAX` | `70` | Maximum zoom |
| `FDF_SCROLL_UP` | `4` | X11 mouse wheel-up button |
| `FDF_SCROLL_DOWN` | `5` | X11 mouse wheel-down button |
| `FDF_MOUSE_MIDDLE` | `2` | X11 middle mouse button |

Mouse wheel zoom changes the current zoom by ten percent:

```text
next_zoom = zoom +/- zoom / FDF_PERCENT_DIVISOR
```

The pan is adjusted during zoom so the point under the cursor stays under the cursor.
If the mouse has not been active yet, the window centre is used instead. Pressing
`Space` resets zoom, pan, rotation, height factor, and mouse state, but keeps the
currently selected projection.

| Input | Effect |
| --- | --- |
| `1`, `2`, `3` | Select isometric, parallel, or cabinet projection |
| Arrow keys | Pan by `FDF_PAN_STEP` |
| `W` / `S` | Rotate around X by `+/- FDF_ROT_STEP` |
| `A` / `D` | Rotate around Y by `+/- FDF_ROT_STEP` |
| `Q` / `E` | Rotate around Z by `+/- FDF_ROT_STEP` |
| Keypad `+` / `-` | Change height exaggeration by `+/- FDF_Z_FACTOR_STEP` |
| Mouse wheel | Zoom in or out |
| Middle mouse drag | Pan by pointer movement |
| `Space` | Reset the view state, preserving projection |
| `ESC`, keypad `5`, window close | Exit cleanly |

### Colour and image output

| Constant | Value | Used for |
| --- | ---: | --- |
| `WHITE_COLOR` | `0xffffff` | Default point colour |
| `FDF_RGB_RED_SHIFT` | `16` | Red channel extraction |
| `FDF_RGB_GREEN_SHIFT` | `8` | Green channel extraction |
| `FDF_RGB_MODULO` | `256` | RGB channel isolation |

Map entries can be either `height` or `height,color`. If no colour is provided,
`WHITE_COLOR` is used. Lines interpolate red, green, and blue channels separately
while Bresenham walks from one endpoint to the other.

The renderer draws into an MLX image buffer and then blits that image to the window.
Pixel writes are clipped to the valid image range `0..width-1` and `0..height-1`.

## Resources

- 42 FdF subject v5.0
- MiniLibX documentation and sources
- X11 documentation for expose events and image formats
- Bresenham line algorithm references for integer line rasterization

AI was used as a review and planning aid: drafting staged refactor plans,
and checking implementation risks.
All code changes are reviewed and owned by the project author.
