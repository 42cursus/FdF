# Copilot Instructions for FdF

## Build, test, and lint commands

### Primary Makefile workflow
- Build the app without launching sample maps: `make fdf`
- Full default build plus GUI smoke tests: `make`
- Run the bundled smoke-test maps: `make test`
- Run one map manually: `./fdf resources/test_maps/t1.fdf`
- Clean build outputs: `make clean` or `make fclean`
- Run the 42 style checker: `make norm`

### Alternate CMake workflow
- Configure: `cmake -S . -B build`
- Build: `cmake --build build`
- Run one map from the CMake build output: `./FdF resources/test_maps/t1.fdf`

## High-level architecture

- `src/main.c` owns application startup. It initializes a single `t_fdf` state object, loads the map, computes window scaling, opens the MiniLibX window, and wires the expose, mouse, key, and destroy hooks.
- `src/load_data.c` and `src/data_convert.c` implement the parsing pipeline. Input rows are first read into a linked list of `t_map_row`, then reversed back into file order, then converted into per-row `heights[]` and `colours[]` arrays.
- `src/on_expose.c` is the render pipeline. It walks the map row by row, converts grid coordinates into projected screen points with `get_point()`, and draws each grid cell as line segments.
- `src/hooks.c` is the interaction layer. Zoom and pan mutate the shared `t_fdf` state, recreate the backing image, and trigger a full redraw.
- Rendering helpers are part of the main app, not a separate project library:
  - `src/draw_line_d.c` rasterizes lines into the current MLX image buffer with a Bresenham loop.
  - `src/check_endianness.c` provides the display endianness check used during startup.
- `lib/ft` provides utility functions used throughout parsing and error handling, especially `get_next_line`, `ft_split`, `ft_strtol`, and `ft_printf`.
- MiniLibX is used directly through both public headers and `mlx_int.h`, so parts of the app state depend on MLX internal structs such as `t_xvar`, `t_win_list`, and `t_img`.

## Key conventions

- The compile-only target is `make fdf`. The default `make` target also runs `make test`, which opens sample maps.
- The Makefile produces a lowercase `./fdf` binary, while the CMake build is configured to output `./FdF`.
- Treat the codebase as an iterative refinement of an already-submitted FdF project. Prefer targeted, behavior-aware improvements over broad rewrites unless the task explicitly calls for a redesign.
- `src/ft_fdf.h` is the central application header and owns the FdF drawing types (`t_point`, `t_rect`, `t_rgb`, `t_bres`) as well as the full `t_fdf` state definition.
- The first parsed row sets `fdf->cols`; `data_convert()` assumes every later row has the same width and exits on shorter rows.
- Map tokens support both bare heights and `height,color` entries. Colors default to `WHITE_COLOR` and `custom_colour_flag` flips on only when any explicit color is present.
- Every interactive redraw follows the same pattern: mutate `t_fdf`, call `replace_image()`, then call `on_expose()`. Preserve that flow when adding new controls.
- Projection math lives in `get_point()` and currently uses an isometric-style transform derived from `xy_scale`, `z_scale`, `zoom`, and draw offsets. Rendering changes usually need coordinated updates in both `calculate_zoom()` and `get_point()`.
- Do not reintroduce a separate `lib/fdf` library; new FdF-specific sources should be added to `SRC_FS` in the top-level Makefile.
