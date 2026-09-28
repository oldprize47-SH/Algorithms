# Algorithm Analysis

This repository contains five C++ coursework programs from my algorithm-analysis coursework. They cover max heaps, recursive and dynamic-programming solutions, optimisation and depth-first graph traversal and shortest paths.

## Programs

- [HW1](ALgorithm_HW1_21800275_SangheonPark.cpp): max-heap operations.
- [HW3](ALgorithm_HW3_21800275_SangheonPark.cpp): recursive and dynamic-programming approaches to the minimum-attempt problem.
- [HW4](ALgorithm_HW4_21800275_SangheonPark.cpp): an optimisation comparison.
- [HW5](ALgorithm_HW5_21800275_SangheonPark.cpp): DFS and topological ordering for an acyclic graph.

During the portfolio cleanup, I added regression tests for boundary cases. They caught an out-of-bounds access for zero floors and a graph output that incorrectly presented a cyclic graph as having a topological order. This fork fixes those cases and rejects invalid graph sizes.

[HW6](ALgorithm_HW6_21800275_SangheonPark.cpp) computes shortest paths with Dijkstra and Floyd–Warshall using [homework6.data](homework6.data). Run it from the repository root. Both output matrices matched an independent shortest-path calculation for the supplied ten-city graph. [ALgorithm_DFS_CPP.cpp](ALgorithm_DFS_CPP.cpp) is an unfinished practice file, separate from the completed assignments.

## Build and tests

With GCC and Python installed, run these commands from the repository root:

```sh
g++ -std=c++17 -Wall -Wextra ALgorithm_HW3_21800275_SangheonPark.cpp -o hw3
python -m unittest discover -s tests -v
```

All five coursework programs and the DFS practice file compiled with GCC 14.2.0 on 28 September 2026. Five regression tests passed. Existing warnings in HW1 and HW3 remain, and the full timing experiment in HW4 was not repeated.

The [tests](tests/test_regressions.py) cover zero floors, the 10-floor/two-object case, cycles, a small DAG and invalid graph sizes. They do not establish correctness or performance for every possible input. Original course references and AI/tool attribution remain in the source.

[Original repository](https://github.com/oldprize47/Algorithm-Analysis_2025). Original history and attribution are retained.
