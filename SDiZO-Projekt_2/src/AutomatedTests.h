#pragma once

class AutomatedTests {
public:
    // test all mst algorithms
    static void mst();

    // test all spf algorithms
    static void spf();

    // test prim algorithm
    static void mstPrim();

    // test kruskal algorithm
    static void mstKruskal();

    // test dijkstra algorithm
    static void spfDijkstra();

    // test bellman-ford algorithm
    static void spfBellmanFord();

    // test all ffa algorithms (here is only one)
    static void ffa();
};
