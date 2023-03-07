import {
  green,
  magenta,
  dim,
} from "https://deno.land/std@0.178.0/fmt/colors.ts";

const data = new TextDecoder().decode(await Deno.readFile("./maze.txt"));

type Node = {
  walkable: boolean;
  coords: Readonly<{
    x: number;
    y: number;
  }>;
  costs: {
    g: number;
    h: number;
    f: number;
  };
  parent?: Node;
};

type Entries<T> = { [K in keyof T]: [K, T[K]] }[keyof T][];

const open: Node[] = [];
const close: Node[] = [];

const distance = (start: Node["coords"], end: Node["coords"]): number =>
  Math.sqrt((end.x - start.x) ** 2 + (end.y - start.y) ** 2);

const entries = <T extends Record<string, unknown>>(obj: T) =>
  Object.entries(obj) as Entries<Node["coords"]>;

const isIn = <T extends Node>(arr: T[], obj: T) =>
  arr.some((node) =>
    entries(node.coords).every(([k, v]) => obj.coords[k] === v)
  );

const nodeArray = data.split("\n")
  .flatMap((line, y) =>
    line.split("").map((val, x) => ({
      walkable: val === "*",
      coords: { x, y },
      costs: { g: Infinity, h: Infinity, f: Infinity },
    }))
  );

const getAdjacentNodes = (arr: Node[], { coords: { x, y } }: Node) =>
  [
    [x, y - 1],
    [x, y + 1],
    [x - 1, y],
    [x + 1, y],
  ].map(([x, y]) =>
    arr.find((node) => node.coords.x === x && node.coords.y === y)
  ).filter((node) => node);

/*
- n ==> next node
- g ==> cost of the path from the start node to n
- h ==> heuristic function that estimates the cost of the cheapest path from n to the goal
*/

const target: Node["coords"] = nodeArray.at(-1)?.coords!;
const { coords: start } = nodeArray[0];

open.push(nodeArray[0]);

const out = data.split("\n").map((l) => l.split(""));

while (open.length > 0) {
  console.clear();
  console.log(out.map((l) => l.join("")).join("\n").replaceAll("X", dim("X")));
  const node = open.sort((a, b) => a.costs.h - b.costs.h).shift()!;
  out[node.coords.y][node.coords.x] = magenta("*");
  await (new Promise((r) => setTimeout(r, 1e3 / 15)));
  close.push(node);

  if (entries(target).every(([k, v]) => node.coords[k] === v)) {
    let current = node;
    while (current.parent) {
      out[current.coords.y][current.coords.x] = green("*");
      console.clear();
      console.log(
        out.map((l) => l.join("")).join("\n").replaceAll("X", dim("X")),
      );
      await (new Promise((r) => setTimeout(r, 1e3 / 10)));
      current = current.parent;
    }
    console.clear();
    out[current.coords.y][current.coords.x] = green("*");
    console.log(
      out.map((l) => l.join("")).join("\n").replaceAll("X", dim("X")),
    );
    break;
  }

  getAdjacentNodes(nodeArray, node)
    .filter((neighbour) =>
      neighbour && neighbour.walkable && !isIn(close, neighbour)
    )
    .forEach((neighbour) => {
      if (!neighbour) return;
      const g = distance(neighbour.coords, start);
      const h = distance(neighbour.coords, target);
      const f = g + h;

      if (!isIn(open, neighbour)) {
        neighbour.parent = node;
        neighbour.costs = { g, h, f };
        open.push(neighbour);
      }
    });
}
