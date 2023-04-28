# labyrinthia

<img align="right" src="./assets/logo.png" width="150px" alt="Labyrinthia Logo" />

Welcome to **labyrinthia**, a labyrinth generator and solver using the A*
algorithm. This project aims to provide a fast and efficient way to generate and
solve labyrinths of various sizes.

- Implements the A* algorithm for efficient solving
- Fast and efficient labyrinth generation
- Includes a visualizer in TypeScript and a generator in Ruby as bonuses
- Main code is written in C for optimal performance

# getting started

Clone the repo:

```sh
git clone git@github.com:Jabolol/labyrinthia.git .
```

Compile the C code:

```sh
make
```

To generate a labyrinth, use the following command:

```sh
./generator/generator <width> <height> [perfect] > /path/to/output.txt
```

> Solvable mazes are not square, and do not contain a `\n` at the end

To solve a labyrinth, use the following command:

```sh
./solver/solver /path/to/maze.txt > solution.txt
```

# bonuses

To visualize a labyrinth with TypeScript in the terminal run:

To generate a labyrinth with Ruby run:

```sh
ruby misc/generator.rb <width> <height> > maze.txt
```

```sh
deno run --allow-read=/path/to/maze.txt misc/solver.ts /path/to/maze.txt
```
