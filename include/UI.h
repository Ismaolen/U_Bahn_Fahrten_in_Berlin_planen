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

#include "Network.h"

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using namespace gl;
using namespace std;



/// \brief Class erstellt die Ausgabe Programm und bietet verschieden möglichkeiten um
/// die Strecke zu fineden oder Daten eines erstellten Bahnes zu ändern oder hinzufügen
/// Die Klasse erbt die Daten und Implemniterung der Klasse Network, womit
/// diese ihnen zur Verfügung stehen
class UI: public Network{
public:

    /// \brief Diese Funktion bietet die verschiedene Möglichkeiten um den Strecke zu
    /// finden oder die Daten eines Graph's zu ändern oder eine Strecke zu löschen
    /// oder eine weitere Strecke hinzufügen oder Netzdaten manuell eingeben
    /// und durch beenden dieser Funktion wird der Nutzer befragt ob er die geändert daten speichern will oder nicht
    /// durch diese Funktion werden alle die
    /// genannten Möglichkeit ausgegeben und und wenn der Nutzer eine Auswahl getroffen hat
    void run();

    /// \brief Diese Funktion steht für den ersten Asuswahl eines Fahrtplan dadurch wird eine neue Graph
    /// erstellt mit seine Edges und Nodes um den eingegebene Start und Target station in den Graph
    /// zu finden und den Fahrplan entsprechend auf der console auszugeben
    /// \param isdatechanges falls die daten geändert worden sind
    void fahrtPlanfinden(int &isdatechanges);

    /// \brief Diese Funktion findet die Fahrplan in den übergebenen Graph und
    /// guckt ob der Nutzer nach Zeit oder nach distanz will
    /// \param graph in dem die Fahrplan gesucht wird
    /// \param eingabe ob nach Zeit oder distanz gewollt ist
    void findPath(Graph& graph, int eingabe);


    /// \brief dieser Funktion druckt die Inhalt einer Fahrplan
    /// wenn der Nutzer einen Fahrplan die Nach Zeit optimiert ist sucht
    /// \param fahrplan vector der die strecken einer Fahrplan beinhaltet
    /// \param time der Total time einer Reise inklusive umsteigzeiten die durch islinechange() funktion überprüft wird
    /// \param umsteigdauer speichert den lines von fahrplan
    void optimizeDuration(deque<Edge *> &fahrplan, int &time, vector<string> &umsteigdauer);

    /// \brief dieser Funktion druckt die Inhalt einer Fahrplan
    /// wenn der Nutzer einen Fahrplan die Nach distanz optimiert ist sucht
    /// \param fahrplan vector der die strecken einer Fahrplan beinhaltet
    /// \param distanz der Total distanz einer Reise
    void optimizeDistanz(deque<Edge *> &fahrplan, double &distanz);

    /// \brief Diese Funktion bietet die möglichkeit Daten zu ändern wie die Name eine
    /// Station ode die Distanz einer strecke oder die Dauer und bietet auch die möglichkeit eine station zu löschen
    /// und die vorherige und nachherige station zu verbinden damit der Bahn line nicht geschnitten
    /// wird und am Ende gibt die geänderte Station für den Nutzer aus
    /// \param x sind die Daten geädert falls ja dann wird aus text.txt gelesen statt Berlin.txt
    /// \param filepfad
    void datenAendern(int &x, int& datachangetrue);

    /// \brief Diese Funktion bietet der Nutzer an einer neue Station hinzufügen mit ihre distanz und dauer zu
    /// den nächsten und vorherigen station falls es gebe
    /// \param x sind die Daten geädert falls ja dann wird m_stationsortiert aktualisert
    /// \param filepfad
    void datenZufuegen(int &x, int& datachangetrue);

    /// \brief Diese Funktion bietet die Möglichkeit dass die Daten aus einer andere Datei
    /// auszulesen dafür muss der Nutzer die Linke eine Datei eingeben und dann
    /// wird daraus die Daten gelsen und die gelesene Daten in
    /// und dann werden beimnächsten Aufruf die Daten nur aus der geänderten Daten geändert
    /// \param x sind die Daten geädert falls ja dann wird m_statiosortiert aktualisert
    /// \param filepfad
    void dateiEinlesen(int &x, int& datachangetrue);

    /// \brief diese Funktion liest die eingabe von Nutzer als double zahlen für den Distanz einer strecke
    /// \throw std::invalid_argument() falls die eingabe keine double Zahlen ist oder leer ist
    /// \return die Eingabe als double Zahl falls keine throw ausgegeben wird
    double positiveDoubleFromStdin();

    string stringFromStdin();

    /// \brief  Diese Funtkion bietet die Möglichkeit an die Stationname
    /// zu ändern, kein rückgabe wert
    void stationNameChange();

    /// \brief Diese Funktion bietet das Ändern von der Dauer und Distanz einer Strecke. ALso diese Funktion bietet die Eingabe der Strecke Nummer
    /// und falls diese richtig wäre wird auf den Inhalt der Vector ditanz und dauer zugegriffen und die Daten an den eingegeben Strecken Nummer geändert
    /// und dann bietet das Software die die Eingabe der neue Distanz und Dauer dann werden diese neue Daten in den Vector string gepeichtert und die alten gelöscht
    void distanz_und_dauer_einer_strecke_andern();

    /// \brief Durch diese Funktion wird eine Srtrecke an eine beliebige station gelöscht diese erfolgt durch die Eingabe der
    /// Streckennummer und dann wird die Eingabe geprüft und falls das richtig wäre wird diese gelöscht und mit den vorherigen und
    /// nachherigen strecken verbindet damit der Bahnline nicht geschnitten wird und das führt zur keine Ausgabe fehler
    void strecke_loeschen();

    /// \brief dieser Funktion bietet die mannuele eingabe der Strecken und falls keine Fehler gibt
    /// werden Daten in die Membervariablen der Klasse Network gespeichert
    /// \param x guckt ob die daten geändert worden sind oder nicht,
    /// falls ja dann werden die daten entsprechend aktualisert
    /// \param datachangetrue eine zweite überprüfung der daten dadurch wird sichergehen dass die daten geändert worden sind oder nicht
    void manuellEingabe(int& x,int& datachangetrue);

private:

};

#ifndef C23_PROJECT_OUTBUTAPP_H
#define C23_PROJECT_OUTBUTAPP_H

#endif //C23_PROJECT_OUTBUTAPP_H
