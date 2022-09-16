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

    /// \brief Erstellung eines Standard Konstruktur
    /// \brief Diese Funktion bietet die verschiedene Möglichkeiten um den Strecke zu
    /// finden oder die Daten eines Graph's zu ändern oder eine Strecke zu löschen
    /// oder eine weitere Strecke hinzufügen durch diese Funktion werden alle die
    /// genannten Möglichkeit ausgegeben und und wenn der Nutzer eine Auswahl getroffen hat
    /// wird zuerst geguckt ob die Daten einmal geändert worden sind und falls nicht dann werden die Daten aus der Berlin.txt
    /// gelesen und falls die Daten doch geändert worden sind werden die Daten aus der erstellten Datei test.txt gelesen.
    UI();

    /// \brief Diese Funktion steht für den ersten Asuswahl eines Fahrtplan dadurch wird eine neue Graph
    /// erstellt mit seine Edges und Nodes um den eingegebene Start und Target station in den Graph
    /// zu finden und den Fahrplan entsprechend auf der console auszugeben
    /// \param isdatechanges falls die daten geändert worden sind dann werden die Daten aus
    /// test.txt gelesen
    void fahrtPlanfinden(int &isdatechanges);

    /// \brief Diese Funktion bietet die möglichkeit Daten zu ändern wie die Name eine
    /// Station ode die Distanz einer strecke oder die Dauer und bietet auch die möglichkeit eine station zu löschen
    /// und die vorherige und nachherige station zu verbinden damit der Bahn line nicht geschnitten
    /// wird und am Ende gibt die geänderte Station für den Nutzer aus
    /// \param x sind die Daten geädert falls ja dann wird aus text.txt gelesen statt Berlin.txt
    /// \param filepfad
    void datenAendern(int &x, int& datachangetrue);

    /// \brief Diese Funktion bietet der Nutzer an einer neue Station hinzufügen mit ihre distanz und dauer zu
    /// den nächsten und vorherigen station falls es gebe und dann werden die geänderte Daten zuerst in test.txt ausgegeben damit die Änderung gespeichert wird
    /// \param x sind die Daten geädert falls ja dann wird aus text.txt gelesen statt Berlin.txt
    /// \param filepfad
    void datenZufuegen(int &x, int& datachangetrue);

    /// \brief Diese Funktion bietet die Möglichkeit dass die Daten aus einer andere Datei
    /// auszulesen dafür muss der Nutzer die Dateipname eine Datei der sich in den Objekt Ornder befindet und dann
    /// wird daraus die Daten gelsen und die gelesene Daten in test.tx ausgegeben damit die Änderung der
    /// Daten geseichert werden und dann werden beimnächsten Aufruf die Daten nur aus der geänderten Daten geändert
    /// \param x sind die Daten geädert falls ja dann wird aus text.txt gelesen statt Berlin.txt
    /// \param filepfad
    void dateiEinlesen(int &x, int& datachangetrue);

    /// \brief diese Funktion liest die eingabe von Nutzer als zahlen für den AUswahl eine beliebige Option
    /// \throw std::invalid_argument() falls die eingabe keine int Zahlen ist oder großse als der Auswahlanzhl ist
    /// \param groessee_als steht für den Anzahl der zu wählende Optionen
    /// \param anzahlzahleneingabe steht für die Anzahl der stellen die eingegeben dürfen
    /// \return die EIngabe als int Zahl falls keine throw ausgegeben wird
    double eingabeToDouble();
    string eingabeToString();



            /// \brief  Diese Funtkion bietet die Möglichkeit an die Stationname zu ändern und dadurch wird die diese in den Datei
    /// test.txt ausgegeben damit diese Änderung gespeichert wird und beimnächsten Aufruf werden die Daten aus der Datei test.txt
    /// gelesen damit die geänderte Version des bahnes gezeigt wird und nicht die standard Version aus Berlin.txt
    /// \param graph Stehte für den Graph in den die geänderte Daten gespeichert werden
    /// \param inputsortieren die alphabetisch zu sortierende Stationennamen die aus der Datein eingelsen werden
    /// \param linien   die linien namen die aus der Datein eingelsen werden
    /// \param stationenbegin die stationenstart der eingelesenen Strecken
    /// \param stationenend die Station target der eingelesenen Strecken
    /// \param distanz_km  der distanz einer Strecke in km
    /// \param distanz_min die Dauer einer Strecke in min
    void stationNameChange();
    /// \brief Diese Funktion bietet das Ändern von der Dauer und Distanz einer Strecke. ALso diese Funktion bietet die Eingabe der Strecke Nummer
    /// und falls diese richtig wäre wird auf den Inhalt der Vector ditanz und dauer zugegriffen und die Daten an den eingegeben Strecken Nummer geändert
    /// und dann bietet das Software die die Eingabe der neue Distanz und Dauer dann werden diese neue Daten in den Vector string gepeichtert und die alten gelöscht
    /// \param graph Graph in den die Strecken und stationen gespeichert werden
    /// \param inputsortieren die alphabetisch zu sortierende Stationennamen die aus der Datein eingelsen werden
    /// \param linien   die linien namen die aus der Datein eingelsen werden und durch der die Strecken Nummer gefunden wird
    /// \param stationenbegin die stationenstart der eingelesenen Strecken
    /// \param stationenend die Station target der eingelesenen Strecken
    /// \param distanz_km  der distanz einer Strecke in km der entsprechend der neue Eingeabe an den bestimmtet Position geändert wird
    /// \param distanz_min die Dauer einer Strecke in min der entsprechend der neue Eingeabe an den bestimmtet Position geändert wird
    void distanz_und_dauer_einer_strecke_andern();

    /// \brief Durch diese Funktion wird eine Srtrecke an eine beliebige station gelöscht diese erfolgt durch die Eingabe der
    /// Streckennummer und dann wird die Eingabe geprüft und falls das richtig wäre wird diese gelöscht und mit den vorherigen und
    /// nachherigen strecken verbindet damit der Bahnline nicht geschnitten wird und das führt zur keine Ausgabe fehler
    /// \param graph Graph in den die Strecken und stationen gespeichert werden
    /// \param m_stationensortiert die alphabetisch zu sortierende Stationennamen die aus der Datein eingelsen werden
    /// \param linien   die linien namen die aus der Datein eingelsen werden und durch der die Strecken Nummer gefunden wird
    /// \param stationenbegin die stationenstart der eingelesenen Strecken
    /// \param stationenend die Station target der eingelesenen Strecken
    /// \param distanz_km  der distanz einer Strecke in km
    /// \param distanz_min die Dauer einer Strecke in min
    void strecke_loeschen();

private:

};

#ifndef C23_PROJECT_OUTBUTAPP_H
#define C23_PROJECT_OUTBUTAPP_H

#endif //C23_PROJECT_OUTBUTAPP_H
