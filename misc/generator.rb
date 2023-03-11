# frozen_string_literal: true

Cell = Struct.new(:value, :visited, :coords)

class MazeGenerator
  attr_reader :width, :height, :grid, :total

  def initialize(width, height)
    @width = width
    @height = height
    @grid = Array.new(height) { Array.new(width) { Cell.new("X", false, nil) } }
    @total = width * height
  end

  def fill_maze
    grid.each_with_index do |row, y|
      row.each_with_index do |cell, x|
        cell.coords = [x, y]
      end
    end
  end

  def get_neighbours(coords)
    x, y = coords
    neighbours = []
    if x > 1
      neighbours << [grid[y][x - 1], grid[y][x - 2]]
    end
    if x < width - 2
      neighbours << [grid[y][x + 1], grid[y][x + 2]]
    end
    if y > 1
      neighbours << [grid[y - 1][x], grid[y - 2][x]]
    end
    if y < height - 2
      neighbours << [grid[y + 1][x], grid[y + 2][x]]
    end
    neighbours
  end

  def generate
    start_cell = grid[0][0]
    start_cell.visited = true
    start_cell.value = "*"
    stack = [start_cell]

    until stack.empty?
      current_cell = stack.last
      neighbours = get_neighbours(current_cell.coords)
      not_visited = neighbours.select { |inner, outer| !inner.visited && !outer.visited }
      if not_visited.any?
        inner, outer = not_visited.sample
        inner.value = outer.value = "*"
        inner.visited = outer.visited = true
        stack.push(inner, outer)
      else
        stack.pop(2)
      end
    end
  end

  def print_maze
    grid[height - 1][width - 1][:value] = "*"
    grid[height - 2][width - 1][:value] = "*"
    grid[height - 1][width - 2][:value] = "*"
    grid.each { |row| puts row.map(&:value).join("") }
  end
end

maze_generator = MazeGenerator.new(30, 20)
maze_generator.fill_maze
maze_generator.generate
maze_generator.print_maze
