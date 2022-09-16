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

/// \brief Class Erstellung für Das Lesen der Inhalt eines Dateiees und Erstellung eines defualt Projekts
/// Die Inputcopyklasse ist die Bassisklasse für den klass Outbutapp
/// Die Klasse erbt die Daten und Implemniterung der Klasse Route, womit
/// diese ihnen zur Verfügung stehen
class Inputcopy: public Graph
{
public:
    /// \brief Erstellung eines Standard Konstruktur


    /// \brief  liest den Inhalt eine Datei, fügt den zu der übegeben vectoren
    /// Bekommt ein Datei name und leere vecktoren
    /// Liest den Inhalt und speichert den in den übergebenen Variablen durch Referenz
    /// \throw cerr falls eingegebene Datei nicht geöffnet werden kann
    /// \param fileNamee übergebene Dateiname aus der die Daten eingelesen werden
    /// \param linien Bahn linien welche aus der Datei eingelsen werden
    /// \param stationenStart der Startstation alle Strecken
    /// \param stationenTarget der target/Ziel alle Routers
    /// \param distanzKm der Distanz alle strecken  in kilometer
    /// \param dauerMin die dauer alle Strecken in Minute
    void inputcopyy(string fileNamee);

    /// \brief addierte die übergebene string vectoren und fügt den zur den vector12 zu
    /// \param vektor1  übergebene string vector1 welche addiert wird
    /// \param vektor2 übergebene sring vector2 welche addiert wird
    /// \param vector12 summe der Addition der string vectoren wird in dieses Vector gespeichert
    void towVectorAddition();

    /// \brief sortiert die übergebene string vector alphapetisch
    ///  wird gebraucht um die stationen der Bahn zur alphapetisch zu sortieren
    /// \param tosortstation der alphapetisch zusortiernde string vector
    void sortStationen();

    /// \brief löscht die Stationen die verdoppelt gespeichert worden sind
    /// \param toDeletedopplestation string vector aus der die wiederholende stationen gelöscht werden
    void deleteDuplicatedStation();

    /// \brief Diese Funktion sammelt die Inhalte eines Bahnprojekts durch das lesen aus einer Datei und das Speicher der Inhalt in den bestimmten
    ///  vectoren um damit arbeiten zu können
    /// \param filenamee  der übergebene Dateiname aus der die Daten gelesen werden
    /// \param linien in den wird die Bahn linien gespeichert
    /// \param stationenbegin der Startstation alle Strecken
    /// \param stationenend  der target/Ziel alle Routers
    /// \param distanz_km    der Distanz alle strecken  in kilometer
    /// \param distanz_min   die dauer alle Strecken in Minute
    /// \param stationsortiert  Stetionen die alphapetisch gespeichert werden und wiederholende Stationen gelöscht werden
    void stationSaveFromFileToStringVector(string filenamee);
    void setStationName(string eingabe, int stationzahl);
    void setDistanz(int strecke_nummer, double geanderte_distanz);
    void setDuration(int strecke_nummer, double geanderte_dauer);
    void deleteRoute(int ubahnzuandern);
    void addNewStation1(int streckevor, string newStation, double ditanzstrecke1, double ditanzstrecke2, int dauerstrecke1, int dauerstrecke2);
    void addNewStation2(int streckevor, string newStation, double ditanzstrecke1, int dauerstrecke1);

    /// \brief druckt die bahn Stationen einer beliebige Grapgh aus
    /// \param stationen die Name des Graphes
    void printStationenNodes(Graph& stationen);

    /// \brief druckt die strecken eine Graph aus
    /// \param strecken Name des Graphes
    void printRoute(Graph& strecken);

    /// \return die linen eines bahnes
    string getline(int position){return m_line[position];}

    /// \return die startstation aller strecken
    string getStationStart(int position){return m_stationstart[position];}

    /// \return die targetstation aller strecken
    vector<string> getStationTarget(){return m_stationtarget;}

    /// \return die distanz aller strecken in km
    vector<double> getDistanz(){return m_distanzInKm;}

    /// \return die dauer aller strecken in min
    vector<int> getDuration(){return m_dauerInMin;}

    /// \return die alphapetisch srtierte stationen eines bahnes
    string getStation(int position){return m_stationensortiert[position];}

    /// \brief definiert die übergeben alphapetisch sortierte Stationen in den übergeben Graph
    /// \param nodeingraphtodefintion Graph in der die übergebene Stationen definiert werden
    /// \param inputsortieren  übergebene alpahpetisch sortierte Stationen
    void nodeDefintion(Graph& nodeingraphtodefintion);

    /// \brief definiert die übergebene Inhalte als strecken in den übergebene Graph
    /// \param graph Graph in welche die strecken definiert werden
    /// \param linien   Bahn linien die in den Bahn gespeichert werden
    /// \param stationenbegin stationen start einer zu defniernde strecke
    /// \param stationenend  stationen target einer zu defniernde strecke
    /// \param distanz_km   distanz einer zu defniernde strecke  in km
    /// \param distanz_min  dauer einer zu defniernde strecke in min
    void defineRouteByDitanz(Graph &graph);

    ///  \brief diese Funktion nimmt die Eingabe als nummer der Station und wndelt dieser zur int und gibt diese zurück
    /// \param start  Nummer der startstation
    /// \param target  Nummer der target Station
    void inputStartTarget(int &start, int &target);

    /// \brief nimmt die Nummer der Station und sucht nach dem bestemten Node in den übergebene Graph
    /// \param input Name der Prapg in dem sich der bestimmte Node befindet
    /// \param station die Station die den namen der alphapetisch sortierte stationen beinhaltet
    /// \param inputsort die Station die den namen der alphapetisch sortierte stationen beinhaltet
    /// \return Node der gesucht Node/ station
    Node& findNode(Graph &input, int &station, vector<string>& inputsort);

    /// Diese Funktion überprüft ob ein umstieg gibt und falls ja addiert die dauer 10 minuten
    /// \param fahrplan beinhaltet die Fahrplan bzw. die Strecken des Fahrplanes als vecktor
    /// \param total_time die Dauer der Fahrt
    /// \param umsteigdauer speichert die line der strecken der fahrplan um zu gcken ob ein umstieg gebe oder nicht
    void isLinechange(deque<Edge*> &fahrplan, int &total_time, vector<string>& umsteigdauer);

    /// \brief druckt die Inhalt der strecken aus dem Fahplan durch die Ntzung der dijekstra Funktion und addiert 10 minuten
    /// zu den gesammten dauer falls eine umstieg gebe
    /// \param fahrplan die zu ausdrückende Fahrplan
    /// \param time die zu ausdruckende totaltime der Fahrtplan
    /// \param distanz die zu ausdruckende totaltime der Fahrtplan
    /// \param umsteigdauer beinhaltet die alle linien der Fahrplan um zu gucken ob die line sich ändert und dadurch 10 min zu den totaltime zu addieren
    void printTravelPlan(deque<Edge *> &fahrplan, int &time, double &distanz, vector<string> &umsteigdauer);
    void fahrtPlanFinden(Graph& graph);

    void printStationen();
    void printStrecke();
    ///  \brief diese Funktion liest die mögliche Inhalte aus der Datei Berlin.txt und speichert die Inahlte in den bestimmten vecktoren um eine mögliche Fahrplan zu erstellen
    ///  dadurch wird ein gesammte Graph mit deine Ubah linen uns stationen und strcken erstellt
    /// \param graph Graph in den die Linien und stationen und strecken definiert werden
    /// \param filenameee  Di Dateiname aus der die Daten gelesen werden
    void StationReadingFromBerlintxtfileAndNodeandEdgesDefintion(Graph& graph, string &filenameee);
    void updateStation();

    /// \brief erstellt eine Graph aus der übergebene Datei
    /// \param filename gegebene Dateiname aus der die Daten gelsen werden

    /// \brief setter Funktion to setted a Ubahn data

    void setStation(string toset){
        m_stationensortiert.push_back(toset);
    }
    void setLine(string toset){
        m_line.push_back(toset);
    }
    void setStart(string toset){
        m_stationstart.push_back(toset);
    }
    void settarget(string toset){
        m_stationtarget.push_back(toset);
    }
    void setdistanz(double newdistanz){
        m_distanzInKm.push_back(newdistanz);
    }
    void setDuration(int duration){
        m_dauerInMin.push_back(duration);
    }


    /// \brief Getter Funktionen
    /*
    void getStation(vector<string>& stationen){
        stationen = m_stationensortiert;
    }
    void getLine(vector<string>& line){
        line = m_line;
    }
    void getStart(vector<string>& start){
        start = m_stationstart;
    }
    void gettarget(vector<string>& target){
        target =  m_stationtarget;
    }
    void getdistanz(vector<double>& distanz){
        distanz = m_distanzInKm;
    }
    void getDuration(vector<int>& duration){
        duration = m_dauerInMin;
    }
    */
    void graphdefinition(Graph& graph);


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
#ifndef C23_PROJECT_INPUTCOPY_H
#define C23_PROJECT_INPUTCOPY_H

#endif //C23_PROJECT_INPUTCOPY_H
