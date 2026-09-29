# Algorithm Analysis

This repository contains five C++ programs from the 2025 algorithm-analysis coursework. They cover max heaps, recursive and dynamic-programming solutions, optimisation and depth-first graph traversal and shortest paths.

## Project goal

Implement different algorithmic approaches and understand how their answers, assumptions and computational work compare.

![Project goal: algorithm-analysis](docs/goals/project-focus-v1.png)

AI-generated concept illustration. Device appearance, interface layout and example graphics are illustrative, not project photographs or measured results.

## Where it could be used

The graph exercises connect to route selection and network analysis, while the heap and other data-structure exercises show how a program can organise work efficiently. The implementations can be used as small, inspectable examples for comparing algorithm choices before adapting an approach to a larger routing or resource-allocation problem. They are coursework programs, not deployed planning services.

## At a glance

![Algorithm-analysis coursework](docs/flowcharts/algorithms.png)

Each row describes an independent exercise or workflow; the repository is not one connected application. [SVG](docs/flowcharts/algorithms.svg)

## Programs

These are Sangheon Park's coursework submissions. Course references and existing AI/tool credits remain in the source.

- [HW1](ALgorithm_HW1_21800275_SangheonPark.cpp): max-heap operations.
- [HW3](ALgorithm_HW3_21800275_SangheonPark.cpp): recursive and dynamic-programming approaches to the minimum-attempt problem.
- [HW4](ALgorithm_HW4_21800275_SangheonPark.cpp): an optimisation comparison.
- [HW5](ALgorithm_HW5_21800275_SangheonPark.cpp): DFS and topological ordering for an acyclic graph.

The portfolio update added regression tests for boundary cases. They caught an out-of-bounds access for zero floors and a graph output that incorrectly presented a cyclic graph as having a topological order. This fork fixes those cases and rejects invalid graph sizes.

[HW6](ALgorithm_HW6_21800275_SangheonPark.cpp) computes shortest paths with Dijkstra and Floyd–Warshall using [homework6.data](homework6.data). Run it from the repository root. Both output matrices matched an independent shortest-path calculation for the supplied ten-city graph. [ALgorithm_DFS_CPP.cpp](ALgorithm_DFS_CPP.cpp) is an unfinished practice file, separate from the completed assignments.

## What the programs demonstrate

The heap exercise represents a priority structure as an array and maintains its ordering as values are inserted, removed or increased. HW3 solves the same minimum-attempt problem using recursion and dynamic programming: the comparison is about how the subproblems are represented and reused, not just whether both versions print an answer.

HW4 compares approaches to a knapsack problem, including exhaustive search, a greedy approach, dynamic programming and branch and bound. Its greedy calculation permits fractional filling, so that result must not be presented as an exact solution to every 0/1 knapsack instance. The timing code is useful for studying the implementations, but the archived timings are not a new performance benchmark.

HW5 explores a graph with depth-first search. A topological ordering is meaningful only for an acyclic directed graph, which is why the fork now rejects the cyclic case instead of printing a misleading order. HW6 reads a weighted matrix from a text file, interprets `INF` as no direct edge, and prints all-pairs shortest-path tables. Dijkstra repeats a single-source search; Floyd–Warshall updates distances through each possible intermediate vertex.

## Build and tests

With GCC and Python installed, run these commands from the repository root:

```sh
g++ -std=c++17 -Wall -Wextra ALgorithm_HW3_21800275_SangheonPark.cpp -o hw3
python -m unittest discover -s tests -v
```

To try the supplied shortest-path example, build HW6 and run it from the directory containing `homework6.data`:

```sh
g++ -std=c++17 -Wall -Wextra ALgorithm_HW6_21800275_SangheonPark.cpp -o hw6
./hw6
```

On Windows PowerShell, the executable is `./hw6.exe`. The output includes the graph representation and two distance tables. Matching tables on this example help check the implementations, but do not validate every disconnected graph, invalid input or edge-weight condition.

All five coursework programs and the DFS practice file compiled with GCC 14.2.0 on 28 September 2026. Five regression tests passed. Existing warnings in HW1 and HW3 remain, and the full timing experiment in HW4 was not repeated.

The [tests](tests/test_regressions.py) cover zero floors, the 10-floor/two-object case, cycles, a small DAG and invalid graph sizes. They do not establish correctness or performance for every possible input. Original course references and AI/tool attribution remain in the source.

[Original repository](https://github.com/oldprize47/Algorithm-Analysis_2025). Original history and attribution are retained.
