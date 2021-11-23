#include "graph.h"
#include <iostream>
#include <regex>
#include <sstream>

//! @file main.cpp
//! @version 1.0
//! @author Carsten Thomas
//! @date December 2020

using namespace gl;

//! @brief class specializing class edge into a unidirectional route, with distance as a member variable
//! distance is also used to define the weight of the route, thereby influencing the Dijkstra search for the shortest path
class Route : public Edge
{
public:
    Route(Graph& g, Node& src, Node& dst, double distance) : Edge(g, src, dst), m_distance(distance)
    {}

    virtual double weight() const { return m_distance; }

private:
    const double m_distance;
};

int main()
{
    // net is the parent graph, representing a part of the S-Bahn net of Berlin
    Graph net;

    // nodes are the S-Bahn stations in the net
    Node alexanderplatz(net, "Alexanderplatz");
    Node ostkreuz(net, "Ostkreuz");
    Node brandenburger_tor(net, "Brandenburger Tor");
    Node grenzallee(net, "Grenzallee");
    Node funkturm(net, "Funkturm");
    Node zitadelle_spandau(net, "Zitadelle Spandau");
    Node strandbad_wannsee(net, "Strandbad Wannsee");
    Node gruenau(net, "Gruenau");

    // routes are the connections between the nodes (S-Bahn stations)
    // for each connection, two routes are required since routes are ubidirectional
    Route r1f(net, alexanderplatz, ostkreuz, 6.2);
    Route r1b(net, ostkreuz, alexanderplatz, 6.2);
    Route r2f(net, ostkreuz, gruenau, 14.6);
    Route r2b(net, gruenau, ostkreuz, 14.6);
    Route r3f(net, grenzallee, gruenau, 12.8);
    Route r3b(net, gruenau, grenzallee, 12.8);
    Route r4f(net, alexanderplatz, grenzallee, 11.2);
    Route r4b(net, grenzallee, alexanderplatz, 11.2);
    Route r5f(net, brandenburger_tor, alexanderplatz, 2.3);
    Route r5b(net, alexanderplatz, brandenburger_tor, 2.3);
    Route r6f(net, funkturm, alexanderplatz, 10.2);
    Route r6b(net, alexanderplatz, funkturm, 10.2);
    Route r7f(net, grenzallee, funkturm, 14.9);
    Route r7b(net, funkturm, grenzallee, 14.9);
    Route r8f(net, strandbad_wannsee, funkturm, 11.2);
    Route r8b(net, funkturm, strandbad_wannsee, 11.2);
    Route r9f(net, zitadelle_spandau, funkturm, 8.5);
    Route r9b(net, funkturm, zitadelle_spandau, 8.5);

    // list all nodes and edges
    std::cout << "Stations:\n";
    for (auto station : net.nodes())
        std::cout << "  - " << *station << "\n";

    std::cout << "\nRoutes:\n";
    for (auto route : net.edges())
        std::cout << "  - " << *route << "\n";

    Node& start = zitadelle_spandau;
    Node& target = gruenau;

    // find shortest path
    std::deque<Edge*> path = net.dijkstra(start, target);

    double total_dist{ 0 };
    std::cout << "\nRoute from " << start.name() << " to " << target.name() << ":\n";
    for (auto route : path)
    {
        std::cout << "  - " << *route << " (" << route->weight() << " km)\n";
        total_dist += route->weight();
    }
    std::cout << "In total " << total_dist << " km\n";
}