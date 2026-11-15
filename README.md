# Branch 3 - Kruskal's Algorithm

My part of the group work: the main greedy algorithm that builds the cheapest network.

## What the code does

Imagine we have a bunch of towns (vertices) and possible cables between them (edges), and each cable has a cost. We want to connect all the towns but spend as little money as possible. That's exactly what Kruskal's algorithm does. Here is how it works, step by step:

1. **Sort the edges from cheapest to most expensive.** We always want to look at the cheapest option first.
2. **Pick the cheapest edge, but only if it doesn't create a loop.** If two towns are already connected somehow (even through other towns), adding another cable between them is just a waste of money. We check this using the DSU (that's Student 2's part - the `find()` and `unite()` functions).
3. **Stop once we've picked V - 1 edges.** A network with V towns only needs V - 1 cables to connect everything. Anything more would make a loop, so there's no point continuing.
4. **Add up the cost of everything we picked.** That total is the minimum network cost.

## Why it's called "greedy"

Because at every step it just grabs the cheapest safe cable without thinking about the future. Normally being greedy is a bad plan, but for this problem it actually gives the best answer. That's the neat part.

## About the files

`kruskal.cpp` has the `kruskalMST()` function which does all the steps above. The `Edge` struct (Student 1's part) and the DSU functions (Student 2's part) are also in there for now, just so the file can run on its own for testing. When we merge everything into `mst.cpp`, we'll use the real versions from Branch 1 and Branch 2.

## How fast is it?

The slowest part is sorting the edges, which takes O(E log E) time. The rest is quick because the DSU checks are almost instant.

## Quick test

The `main()` function has a small example network with 6 towns and 9 cables. Run the program and it prints the cables it picked and the total cost (12 for that example).
