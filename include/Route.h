//
// Created by ismail on 10.01.22.
//
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "graph.h"
#include <iterator>
#include <cstdio>

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using namespace gl;
using namespace std;

/// \brief Dieser Klasse ist einer erweiterun der Klasse Edge die zu den strecken die Line und distanz und dauer hinzufügt
class Route : public Edge
{
public:
    /// \brief Implmentierung und Deklaration einer Konstruktor der Klasse Route
    /// der die Inhalt der klasse Efdges auf line distanz und dauer erweitert
    /// \param graph Der Graph in den die Edges instaliert werden
    /// \param line Die Line eines Strecke
    /// \param src Die start Station einer strecke
    /// \param dst Die Zielstation einer Strecke
    /// \param distance Die Distanz einer Strecke in km
    /// \param minute Die Dauer einer Strecke in min
    Route(Graph& graph, string line, Node& src, Node& dst, double distance, int minute) : Edge(graph, src, dst), m_distance(distance)
            , m_minute(minute), m_line(line){ }

    /// \brief gibt die distanz einer strecke zurück, wird als virtual gestellt damit
    /// die Funktion der Basis klasse nicht aufgerofen wird
    /// \return distanz einer strecke
    virtual double weight() const { return m_distance; }

    /// \brief gibt die Dauer einer strecke zurück, wird als virtual gestellt damit
    /// die Funktion der Basis klasse nicht aufgerofen wird
    /// \return Dauer einer strecke
    virtual int time() const { return m_minute; }

    /// \brief gibt die line einer strecke zurück, wird als virtual gestellt damit
    /// die Funktion der Basis klasse nicht aufgerofen wird
    /// \return line einer strecke
    virtual string line() const { return m_line; }

private:
    const double m_distance;
    const int m_minute;
    const string m_line;

};
#ifndef C23_PROJECT_ROUTE_H
#define C23_PROJECT_ROUTE_H

#endif //C23_PROJECT_ROUTE_H
