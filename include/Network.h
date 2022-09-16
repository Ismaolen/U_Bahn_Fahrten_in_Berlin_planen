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

#include "Route.h"

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using namespace gl;
using namespace gl;
using namespace std;

/// \brief Class Erstellung für Das Lesen der Inhalt eines Dateiees und dadurch werden die Daten in die Membervariablen
/// deiser Klasse gespeichert und durch dieser klassen wernden bstimmte Operationen mit dem gespeicherten Daten durchgeführt
/// Die Network ist die Bassisklasse für den klass UI
/// Die Klasse erbt die Daten und Implemniterung der Klasse Graph, womit
/// diese ihnen zur Verfügung stehen
class Network: public Graph
{
public:
    /// \brief Diese Member Funktion ändert die Name der Station an einer bestimmten Position in den Vector m_stationensortiert
    /// \param eingabe Die neue Name für eine Station
    /// \param stationzahl Die Position der Station in den vector m_stationsortiert die ihre Name geändert wird
    void changeStationName(string eingabe, int stationzahl);

    /// \brief Diese Member Funktion ändert die Distanz einer Strecke an einer bestimmten Position in den Vector m_distanzInKm
    /// \param strecke_nummer  nummer der Streck die Ihre Distanz geändert wird
    /// \param geanderte_distanz neue Distanz der statt die alten Distanz sein wird
    void changeDistanz(int strecke_nummer, double geanderte_distanz);


    /// \brief Diese Member Funktion ändert die Dauer einer Strecke an einer bestimmten Position in den Vector m_dauerInMin
    /// \param strecke_nummer nummer der Streck die Ihre Dauer geändert wird
    /// \param geanderte_dauer neue Dauer der statt die alten Dauer sein wird
    void changeDuration(int strecke_nummer, double geanderte_dauer);


   /// \brief dieser Funktion pusht eine neue Elemnt in den Vector m_line
   /// \param toset string der zu den vector m_line addiert wird
    void setLine(string toset){
        m_line.push_back(toset);
    }
    /// \brief dieser Funktion pusht eine neue Elemnt in den Vector m_stationstart
    /// \param toset  string der zu den vector m_stationstart addiert wird
    void setStart(string toset){
        m_stationstart.push_back(toset);
    }
    /// \brief dieser Funktion pusht eine neue Elemnt in den Vector m_stationtarget
    /// \param toset  string der zu den vector m_stationtarget addiert wird
    void settarget(string toset){
        m_stationtarget.push_back(toset);
    }
    /// \brief dieser Funktion pusht eine neue Elemnt in den Vector m_distanzInKm
    /// \param newdistanz  double zahl der zu den vector m_distanzInKm addiert wird
    void setDistanz(double newdistanz){
        m_distanzInKm.push_back(newdistanz);
    }
    /// \brief dieser Funktion pusht eine neue Elemnt in den Vector m_dauerInMin
    /// \param duration int zahl der zu den vector m_dauerInMin addiert wird
    void setDuration(int duration){
        m_dauerInMin.push_back(duration);
    }

    /// \brief gibt die Name der Line einer Strecke an einer bestimmten Poisition
    /// \param position die Position an einer bestimmten stelle in den Vector m_line
    /// \return string LineName an eine bestimmten Position
    string getline(int position){return m_line[position];}

    /// \brief gibt die Name der startStation einer Strecke an einer bestimmten Poisition
    /// \param position die Position an einer bestimmten stelle in den Vector m_stationstart
    /// \return string Name der startStation an eine bestimmten Position
    string getStationStart(int position){
        return m_stationstart[position];}

    /// \brief gibt die Name der Zielstation einer Strecke an einer bestimmten Poisition
    /// \param position die Position an einer bestimmten stelle in den Vector m_stationtarget
    /// \return string Name der Zielstation an eine bestimmten Position
    string getStationTarget(int position){return m_stationtarget[position];}

    /// \brief gibt die Distanz einer Strecke an einer bestimmten Poisition
    /// \param position die Position an einer bestimmten stelle in den Vector m_distanzInKm
    /// \return Distanz an eine bestimmten Position
    double getDistanz(int position){return m_distanzInKm[position];}

    /// \brief gibt die Dauer einer Strecke an einer bestimmten Poisition
    /// \param position die Position an einer bestimmten stelle in den Vector m_dauerInMin
    /// \return Dauer an eine bestimmten Position
    int getDuration(int position){return m_dauerInMin[position];}

    /// \brief gibt die Name der Station an einer bestimmten Poisition
    /// \param position die Position an einer bestimmten stelle in den Vector m_stationensortiert
    /// \return string Stationname an eine bestimmten Position
    string getStation(int position){
        return m_stationensortiert[position];
    }

    /// \brief Dieser getterfunktion gibt die Position der gesuchten string in den vector m_stationensortiert
    /// \param gesuchtestation der string der gesucht wird
    /// \return position der gesuchte string in den vector m_stationensortiert
    int getStation(string gesuchtestation);

    /// \brief Dieser Funktion löscht eine Strecke an einer bestimmten position, dabei werden zwei fälle unterschieden
    /// 1- wenn die Strecke am ende eine Bahn sich befindet
    /// 2- Wenn die strecke sich nicht am ende eine Bahn befindet
    /// Die Unterscheidung dient dazu, dass der Ubahn nicht geschnitten wird
    /// \param ubahnzuandern Nummer der Strecke die gelöscht wird
    void deleteRoute(int ubahnzuandern);

    /// \brief Dieser Funktion addiert einer neue Station zur eine Bahn, wenn die Strecke nicht die letzte strecke eine bestimmten Bahn ist
    /// \param streckevor Nummer der Strecke, die dannach die neue Station hinzugefügt wird
    /// \param newStation Namme der hinzufügende Station
    /// \param ditanzstrecke1 Distanz der strecke zwischen zielstationn1 -> newstation
    /// \param ditanzstrecke2 Distanz der strecke zwischen newstation -> zielstationn2
    /// \param dauerstrecke1 Dauer der strecke zwischen zielstationn1 -> newstation
    /// \param dauerstrecke2 Dauer der strecke zwischen newstation -> zielstationn2
    void addNewStation1(int streckevor, string newStation, double ditanzstrecke1, double ditanzstrecke2, int dauerstrecke1, int dauerstrecke2);

    /// \brief Dieser Funktion addiert einer neue Station zur eine Bahn, wenn die Strecke die letzte strecke eine bestimmten Bahn ist
    /// \param streckevor
    /// \param newStation Namme der hinzufügende Station
    /// \param ditanzstrecke1 Distanz der strecke zwischen newstation -> zielstationn2
    /// \param dauerstrecke1 Dauer der strecke zwischen newstation -> zielstationn2
    void addNewStation2(int streckevor, string newStation, double ditanzstrecke1, int dauerstrecke1);

    /// \brief druckt die bahn Stationen einer beliebige Grapgh aus
    /// \param stationen die Name des Graphes
    void printNodes(Graph& stationen);

    /// \brief druckt die bahn strecken einer beliebige Grapgh aus
    /// \param strecken die Name des Graphes
    void printRoute(Graph& strecken);

    /// \brief druckt die bahn Stationen, die im vector m_stationsortiert gespeichert sind, aus
    void printm_Stationen();

    /// \brief druckt die Strecken, die in den Vectoren der Klasse Network gespeichert sind, aus
    void printm_Strecke();

    /// \brief Durch dieser Funktion wird gekuckt ob ein Umstieg gibt, und falls ja dann wird 10 min zur totalTime addiert
    /// Dieser erfolgt in dem vergleich der der Line wenn diese sich ändern dann gibt es einen Umstieg
    /// \param fahrplan vector der den Fahrplan beinhaltet
    /// \param total_time die zu ausdruckende totaltime der Fahrtplan
    /// \param umsteigdauer beinhaltet die alle linien der Fahrplan um zu gucken ob die line sich ändert und dadurch 10 min zu den totaltime zu addieren
    void isLinechange(deque<Edge*> &fahrplan, int &total_time, vector<string>& umsteigdauer);

    /// \brief Dieser Funktion findet den gesuchten Node und gibt ihn zurück
    /// \param graph in dem die Node exisitert und der Node gesucht wird
    /// \param station Die Nummer der Name die in den gescuhten Node gespeichert ist
    /// \param inputsort vector die alle Name von instalierten Nodes beinhaltet
    /// \return gesuchte Node
    Node& findNode(Graph &graph, int &station, vector<string>& inputsort);

    /// \brief  liest den Inhalt eine Datei, fügt den zu den vectoren der Klasse Network
    /// \throw GraphLibException falls eingegebene Datei nicht geöffnet werden kann oder nicht existiert
    /// \param fileNamee übergebene Dateiname aus der die Daten eingelesen werden
    void fileReading(string fileNamee);

    /// \brief addierte die m_stationStart mit m_StationTarget und fügt den zur den m_stationsortiert zu
    void towVectorAddition();

    /// \brief sortiert die membervariable m_stationsortiert alphapetisch
    ///  wird gebraucht um die stationen der Bahn zur alphapetisch zu sortieren
    void alphapetischsortieren();

    /// \brief löscht die Stationen die verdoppelt gespeichert worden sind in die membervariable m_srtationsortiert
    void deleteDuplicatedStation();

    /// \brief Dieser Funktion installiert die Nodes und nimmt die Namen der Nodes aus dem Vcetor m_stationsortiert in den übergeben Graph
    /// \param graph Der Graph in den die Nodes installiert werden
    void installNode(Graph& graph);

    /// \brief Dieser Funktion installiert die Routes in den übergeben Graph
    /// \param graph Der Graph in den die Routes installiert werden
    void installRoute(Graph &graph);

    /// \brief Diese Funtktion liest die Eingabe von drei Zahlen oder eine beliebeige Eingabe anzahlmöglichkeiten und falls
    /// diese keine Zahlen beinhaltet dann wird ein Exeption ausgegeben
    /// \throw std::invalid_argument falls die Eingabe fehlschlägt oder leer ist oder keine Zahlen beinhaltet
    /// \param anzahlmoeglicheelemnte der höchste Zahl der eingegeben werden darf
    /// \return die eingelsene Zahl als Int falls kein Exeption ausgegeben wird
    int threePositiveIntFromStdin(vector<string> &anzahlmoeglicheelemnte);

    /// \brief diese Funktion liest die eingabe von Nutzer als zahlen für den AUswahl eine beliebige Option
    /// \throw std::invalid_argument() falls die eingabe keine int Zahlen ist oder großse als der Auswahlanzhl ist
    /// \param groessee_als steht für den Anzahl der zu wählende Optionen
    /// \param anzahlzahleneingabe steht für die Anzahl der stellen die eingegeben dürfen
    /// \return die EIngabe als int Zahl falls keine throw ausgegeben wird
    int onePositiveIntFromStdin(char groessee_als, int anzahlzahleneingabe);

    /// \brief Dieser Funktion ist wie ein destruktor, der alle Membervariablen löscht
    void Networkdestrokor();

protected:
    vector<string> m_line, m_stationensortiert, m_stationtarget, m_stationstart;
    vector<double> m_distanzInKm;
    vector<int> m_dauerInMin;


};

template<class T> T fromString(const std::string& s) //steht für die Umwandlung von ein string zu double oder int ...
{
    std::istringstream stream (s);
    T t;
    stream >> t;
    return t;
}
template<typename T>        // um stellenanzahl in einer Zahl zu berechnen
size_t countDigits(T n)
{
    string tmp;

    tmp = to_string(n);
    return tmp.size();
}
#ifndef C23_PROJECT_INPUTCOPY_H
#define C23_PROJECT_INPUTCOPY_H

#endif //C23_PROJECT_INPUTCOPY_H
