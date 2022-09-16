//
// Created by ismail on 10.01.22.
//
//
// Created by ismai on 07.01.2022.
//

#include "Network.h"
#include <string>
#include <charconv>
#include <stdio.h>
#include <stdlib.h>
#define MAX_DIGITS 10
void Network::changeStationName(string eingabe, int stationzahl) {


    string gesuchte_stetion = m_stationensortiert[stationzahl - 1];
//sortierte stationen ändern
    std::vector<string>::iterator it = m_stationensortiert.begin();
    *(it + (stationzahl - 1)) = eingabe;
//sortstationen(inputsortieren);
// stationbegin ändern
    std::vector<string>::iterator ft = m_stationstart.begin();
    //cout << m_stationstart[stationzahl - 1] << "\n\n";

    for (int i = 0; i < m_stationstart.size(); i++) {
        if (m_stationstart[i] == gesuchte_stetion) {
            *(ft + i) = eingabe;
            // cout << "ge\x84nderte stationbegin:    " << m_stationstart[i] << "\n\n";

        }
    }

//statinenend ändern
    std::vector<string>::iterator gt = m_stationtarget.begin();
    for (int i = 0; i < m_stationtarget.size(); i++) {
        if (m_stationtarget[i] == gesuchte_stetion) {
            *(gt + i) = eingabe;
            // cout << "ge\x84nderte stationendddd:   " << m_stationtarget[i] << "\n\n";

        }
    }

}
void Network::changeDistanz(int strecke_nummer, double geanderte_distanz) {
    std::vector<double>::iterator it = m_distanzInKm.begin();
    *(it + (strecke_nummer - 1)) = geanderte_distanz;
}
void Network::changeDuration(int strecke_nummer, double geanderte_dauer) {
    std::vector<int>::iterator iy = m_dauerInMin.begin();
    *(iy + (strecke_nummer - 1)) = geanderte_dauer;
}
void Network::deleteRoute(int ubahnzuandern) {
    if ((m_line[ubahnzuandern - 2] == m_line[ubahnzuandern - 1]) &&
        (m_line[ubahnzuandern - 1] == m_line[ubahnzuandern])) {

        //Vor und nach stationen speichern und entsprechend verbinden elemente zufügen

        m_stationstart.insert(m_stationstart.begin() + ubahnzuandern, m_stationstart[ubahnzuandern - 2]);
        m_stationtarget.insert(m_stationtarget.begin() + ubahnzuandern, m_stationtarget[ubahnzuandern]);
        m_line.insert(m_line.begin() + ubahnzuandern, m_line[ubahnzuandern - 1]);
        m_distanzInKm.insert(m_distanzInKm.begin() + ubahnzuandern,
                             m_distanzInKm[ubahnzuandern - 1] + m_distanzInKm[ubahnzuandern]);
        m_dauerInMin.insert(m_dauerInMin.begin() + ubahnzuandern,
                            m_dauerInMin[ubahnzuandern - 1] + m_dauerInMin[ubahnzuandern]);
        //Strecke Löschen
        auto linentoremove1 = m_line.begin() + (ubahnzuandern - 1);
        m_line.erase(linentoremove1);
        auto linentoremove2 = m_line.begin() + (ubahnzuandern - 2);
        m_line.erase(linentoremove2);
        auto linentoremove3 = m_line.begin() + (ubahnzuandern - 1);
        m_line.erase(linentoremove3);

        auto statbeintoremove1 = m_stationstart.begin() + (ubahnzuandern - 1);
        m_stationstart.erase(statbeintoremove1);
        auto statbeintoremove2 = m_stationstart.begin() + (ubahnzuandern - 2);
        m_stationstart.erase(statbeintoremove2);
        auto statbeintoremove3 = m_stationstart.begin() + (ubahnzuandern - 1);
        m_stationstart.erase(statbeintoremove3);


        auto statendtoremove1 = m_stationtarget.begin() + (ubahnzuandern - 1);
        m_stationtarget.erase(statendtoremove1);
        auto statendtoremove2 = m_stationtarget.begin() + (ubahnzuandern - 2);
        m_stationtarget.erase(statendtoremove2);
        auto statendtoremove3 = m_stationtarget.begin() + (ubahnzuandern - 1);
        m_stationtarget.erase(statendtoremove3);

        auto distanztoremove1 = m_distanzInKm.begin() + (ubahnzuandern - 1);
        m_distanzInKm.erase(distanztoremove1);
        auto distanztoremove2 = m_distanzInKm.begin() + (ubahnzuandern - 2);
        m_distanzInKm.erase(distanztoremove2);
        auto distanztoremove3 = m_distanzInKm.begin() + (ubahnzuandern - 1);
        m_distanzInKm.erase(distanztoremove3);

        auto dauertoremove1 = m_dauerInMin.begin() + (ubahnzuandern - 1);
        m_dauerInMin.erase(dauertoremove1);
        auto dauertoremove2 = m_dauerInMin.begin() + (ubahnzuandern - 2);
        m_dauerInMin.erase(dauertoremove2);
        auto dauertoremove3 = m_dauerInMin.begin() + (ubahnzuandern - 1);
        m_dauerInMin.erase(dauertoremove3);
        //strecke verbinden

        // Strecke an den gewollten Position hinzufügen
    }
    if (m_line[ubahnzuandern].empty() || m_line[ubahnzuandern - 1] != m_line[ubahnzuandern] ||
        (m_line[ubahnzuandern - 1] == m_line[ubahnzuandern - 2] &&
         m_line[ubahnzuandern - 1] != m_line[ubahnzuandern]) || m_line[ubahnzuandern - 2].empty()) {
        auto linentoremove1 = m_line.begin() + (ubahnzuandern - 1);
        m_line.erase(linentoremove1);
        auto statbeintoremove1 = m_stationstart.begin() + (ubahnzuandern - 1);
        m_stationstart.erase(statbeintoremove1);
        auto statendtoremove1 = m_stationtarget.begin() + (ubahnzuandern - 1);
        m_stationtarget.erase(statendtoremove1);
        auto distanztoremove1 = m_distanzInKm.begin() + (ubahnzuandern - 1);
        m_distanzInKm.erase(distanztoremove1);
        auto dauertoremove1 = m_dauerInMin.begin() + (ubahnzuandern - 1);
        m_dauerInMin.erase(dauertoremove1);
    }
    towVectorAddition();
    alphapetischsortieren();
    deleteDuplicatedStation();

}

void Network::addNewStation1(int streckevor, string newStation, double ditanzstrecke1, double ditanzstrecke2, int dauerstrecke1, int dauerstrecke2) {
//Fugt die station und verbindet diese mit der vorherige Strcke und mit der Nachherige strecke
    m_stationstart.insert(m_stationstart.begin() + streckevor, m_stationtarget[streckevor - 1]);
    m_stationstart.insert(m_stationstart.begin() + (streckevor + 1), newStation);

    m_stationtarget.insert(m_stationtarget.begin() + streckevor, newStation);
    m_stationtarget.insert(m_stationtarget.begin() + (streckevor + 1), m_stationtarget[streckevor + 1]);

    m_line.insert(m_line.begin() + streckevor, m_line[streckevor - 1]);
    m_line.insert(m_line.begin() + (streckevor + 1), m_line[streckevor - 1]);

    m_distanzInKm.insert(m_distanzInKm.begin() + streckevor, ditanzstrecke1);
    m_distanzInKm.insert(m_distanzInKm.begin() + (streckevor + 1), ditanzstrecke2);

    m_dauerInMin.insert(m_dauerInMin.begin() + streckevor, dauerstrecke1);
    m_dauerInMin.insert(m_dauerInMin.begin() + (streckevor + 1), dauerstrecke2);

    //Strecke Löschen
    auto linentoremove1 = m_line.begin() + (streckevor + 2);
    m_line.erase(linentoremove1);


    auto statbeintoremove1 = m_stationstart.begin() + (streckevor + 2);
    m_stationstart.erase(statbeintoremove1);

    auto statendtoremove1 = m_stationtarget.begin() + (streckevor + 2);
    m_stationtarget.erase(statendtoremove1);

    auto distanztoremove1 = m_distanzInKm.begin() + (streckevor + 2);
    m_distanzInKm.erase(distanztoremove1);

    auto dauertoremove1 = m_dauerInMin.begin() + (streckevor + 2);
    m_dauerInMin.erase(dauertoremove1);
    towVectorAddition();
    alphapetischsortieren();
    deleteDuplicatedStation();


}

void Network::addNewStation2(int streckevor, string newStation, double ditanzstrecke1, int dauerstrecke1) {
    m_stationstart.insert(m_stationstart.begin() + streckevor, m_stationtarget[streckevor - 1]);

    m_stationtarget.insert(m_stationtarget.begin() + streckevor, newStation);

    m_line.insert(m_line.begin() + streckevor, m_line[streckevor - 1]);

    m_distanzInKm.insert(m_distanzInKm.begin() + streckevor, ditanzstrecke1);

    m_dauerInMin.insert(m_dauerInMin.begin() + streckevor, dauerstrecke1);
    towVectorAddition();
    alphapetischsortieren();
    deleteDuplicatedStation();
}

void Network::printNodes(Graph& stationen) {

    int h = 1;
    for(auto i: stationen.nodes()){
        cout << h << "- " << *i << endl;
        h++;
    }
}
void Network::printRoute(Graph& strecken) {
    int h = 1;
    for(auto i: strecken.edges()){
        std::cout  <<  " - "  << *i << "\n";
        int h = 1;

    }


}
void Network::printm_Stationen() {
    int h = 1;
    for (auto i: m_stationensortiert) {
        cout << h << "- " << i << endl;
        h++;
    }
    h = 1;
}
void Network::printm_Strecke() {
    int h = 1;
    for (size_t i = 0; i < m_stationstart.size(); i++) {
        cout << h << "- " << m_line[i] << " " << m_stationstart[i] << " -> " << m_stationtarget[i] << ": "
             << m_distanzInKm[i] << " " << m_dauerInMin[i] << endl;
        h++;
    }
    h = 1;
}

void Network::isLinechange(deque<Edge *> &fahrplan, int &total_time, vector<string> &umsteigdauer) {

    // Diese Funktion überprüft ob es umgestiegen ist oder nicht

    int ziel = 1;
    for(auto priner: fahrplan){
        umsteigdauer.push_back(priner->line());
    }

    for(int i = 0; ziel < umsteigdauer.size(); i++) {
        if ((umsteigdauer[i] != umsteigdauer[ziel]) && !(umsteigdauer[ziel].empty()) ) {
            total_time += 10;
        }
        ziel++;
    }
}



Node& Network::findNode(Graph &graph, int &station, vector<string> &inputsort) {
    Node& start = *graph.findNode(inputsort[station - 1]);
    return start;
}

void Network::fileReading(string fileNamee){


    ifstream datei(fileNamee);
    while(datei.fail()){
        try {
            if(datei.fail())
                throw GraphLibException("Eingegebener Pfad enth\x84lt keine Datei");
        }
        catch (GraphLibException& s){
            cerr << " > FEHLER: " << s.what() << "\n\n > Bitte einen anderen Pfad eingeben: ";
            char pfadd[100];
            cin >> pfadd;
            datei.open(pfadd);
            cout << "Bitte den Pfad der Datei in folgende Format eingeben (z.B. für Windows Nutzer C:\\Users\\ismail\\Desktop\\Metro-Berlin\\Berlin.txt:"
                    "\noder für Ubuntu Nutzer: home/ismail/Schreibtisch/c23_project/cmake-build-debug/Berlin.txt ";
        }
    }
    string station;
    char pfad[100];
    stringstream Puffer;
    /*
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
    }
     */

    while (std::getline(datei, station)) {

        for (int i = 0; i < station.size(); i++) {
            if (station[i] == ',') station[i] = '.';
        }

        for (size_t i = 0; i <= station.length(); i++) {
            pfad[i] = station[i];
        }

        string line, stationbegin, bam, stationend, sam, leer;
        string distanz;
        string timemin;
        Puffer.str(pfad);
        Puffer >> line >> stationbegin >> bam >> stationend >> sam;
        unsigned int x = sam.length();
        int y = 0;
        int g = 0;
        int distanzpruef = 0;
        int yy = 0;
        if (bam != "->") stationbegin += ' ' + bam;
        if (stationend == "->") {
            stationend = sam;
            for (int i = 0; i < sam.length(); i++) {
                if (sam[i] == ':') {
                    y = 3;
                    break;
                }
            }
            for (int i = 0; i < sam.length(); i++) {
                if (sam[i] != '0' && y != 3) {
                    Puffer >> leer;
                    stationend += " " + leer;
                    g = 3;
                    y = 0;
                    break;
                }
            }
            y = 0;
        }
        if (stationend != "->") {
            for (int i = 0; i < stationend.length(); i++) {
                if (stationend[i] == ':') {
                    yy = 3;
                    break;
                }
            }
            for (int i = 0; i < stationend.length(); i++) {
                if (sam[i] != '0' && yy != 3) {
                    stationend += " " + sam;
                    y = 0;
                    break;
                }
            }
            y = 0;
        }
        ////distanz implemetierung
        int h = 0;
        if (sam[1] == '.') {
            distanz = sam;

        }
        if (leer[1] == '.') {
            distanz = leer;

        }
        if (sam[1] != '.' && leer[1] != '.' && distanz[1] != '.' && leer == "") {
            Puffer >> leer;

            distanz = leer;
        }
        if (distanz == "" && distanz != "2" && distanz != "1") {
            Puffer >> distanz;
        }
        ////Entfernung in minuten implemetierung
        int timee;
        Puffer >> timee;
        //if(stationend[i] == '0'){ y = 0; distanz = sam; break; }
        y = 0;
        yy = 0;
        h = 0;
        distanzpruef = 0;
        g = 0;
        /// löscht das : zeichen von den string
        stationend.erase(std::remove(begin(stationend), end(stationend), ':'), end(stationend));
        m_stationstart.push_back(stationbegin);
        m_stationtarget.push_back(stationend);
        m_distanzInKm.push_back(fromString<double>(distanz));
        m_dauerInMin.push_back(timee);
        m_line.push_back(line);
        line = "";
        stationbegin = "";
        bam = "";
        stationend = "";
        sam = "";
        leer = "";
        distanz = "";
        timemin = "";
        timee = 0;
        Puffer.clear();
    }


    datei.close();
}
/// fügt die bedien verktoren stationanfang und end zusammen
void Network::towVectorAddition() {

    for(size_t i = 0; i < m_stationstart.size(); i++){
        m_stationensortiert.push_back(m_stationstart[i]);
    }
    for(size_t i = 0; i < m_stationtarget.size(); i++){
        m_stationensortiert.push_back(m_stationtarget[i]);
    }

}
// srtiert die stationen alphapetisch
void Network::alphapetischsortieren() {
    sort( m_stationensortiert.begin(), m_stationensortiert.end());

}
// löscht verdopplte  stationen
///https://qastack.com.de/programming/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
void Network::deleteDuplicatedStation() {
    m_stationensortiert.erase( unique( m_stationensortiert.begin(), m_stationensortiert.end() ), m_stationensortiert.end() );

}

// Define Routes eines Graphes












void Network::installNode(Graph &graph) {

    for (size_t i = 0; i < m_stationensortiert.size(); i++) {

        new Node(graph, m_stationensortiert[i]);


    }

}
void Network::installRoute(Graph &graph) {
    for(size_t i = 0; i < m_stationstart.size(); i++) {
        Node& start = *graph.findNode(m_stationstart[i]);
        Node& target = *graph.findNode(m_stationtarget[i]);
        new Route(graph, m_line[i], start, target, m_distanzInKm[i], m_dauerInMin[i]);
        new Route(graph, m_line[i], target, start, m_distanzInKm[i], m_dauerInMin[i]);
    }
}
int Network::threePositiveIntFromStdin(vector<string> &anzahlmoeglicheelemnte) {

    int input;
    int x = 0;
    string inputstring;
    while (x == 0)
    {
        std::getline(cin, inputstring, '\n');
        try {
            if (inputstring.empty()) {
                throw invalid_argument("Bitte geben Sie eine Zahl und lassen Sie die Zeile nicht leer");
            }
        }
        catch (invalid_argument &e) {
            cerr << e.what() << endl;
            x = 0;
            inputstring = "";
        }
        for (int i = 0; i < inputstring.length(); i++) {
            x = 1;
            try {
                if (inputstring[i] < '0' || inputstring[i] > '9' || inputstring[0] == '0') {
                    string nichtgrosseals = "Falsche Eingabe: Bitte keine sonderzeichen oder Buchstaben eingeben. Bitte geben Sie Zahlen zwischen 1 und " + to_string(anzahlmoeglicheelemnte.size());
                    throw invalid_argument(nichtgrosseals);
                }
            }
            catch (invalid_argument &e) {
                cerr << e.what() << endl;
                x = 0;
                inputstring = "";
            }
        }
        try {
            if (fromString<int>(inputstring) > anzahlmoeglicheelemnte.size()) {
                string sizee = "Bitte geben Sie keine Große Zahl als " + to_string(anzahlmoeglicheelemnte.size());
                throw invalid_argument(sizee);
            }
        }
        catch (invalid_argument &e) {
            cerr << e.what() << endl;
            x = 0;
            inputstring = "";
        }

    }
    input = fromString<int>(inputstring);
    return input;
}

int Network::onePositiveIntFromStdin(char groessee_als, int anzahlzahleneingabe) {
    int input;
    int x = 0;
    string inputstring;
    while (x == 0)
    {
        std::getline(cin, inputstring, '\n');
        try {
            if (inputstring.empty()) {
                throw invalid_argument("Bitte geben Sie eine Zahl und lassen Sie die Zeile nicht leer");
            }
        }
        catch (invalid_argument &e) {
            cerr << e.what() << endl;
            x = 0;
            inputstring = "";
        }
        for (int i = 0; i < inputstring.length(); i++) {
            x = 1;

            try {
                if (inputstring[i] < '1' || inputstring[i] > groessee_als || i > anzahlzahleneingabe || inputstring[0] == '0') {
                    string throwausgabe = "Falsche Eingabe: Bitte geben Sie Zahlen zwischen 1 und ";
                    throwausgabe.push_back(groessee_als);
                    throwausgabe += "\nEs d\x81rfen nur Zahlen eingegeben werden\n";
                    throw invalid_argument( throwausgabe);
                }
            }
            catch (invalid_argument &e) {
                cerr << e.what() << endl;
                x = 0;
                inputstring = "";
            }
        }

    }
    input = fromString<int>(inputstring);
    return input;
}

void Network::Networkdestrokor() {

        if(!(m_stationensortiert.empty())){
            m_stationensortiert.clear();
        }
        if(!(m_line.empty())){
            m_line.clear();
        }
        if(!(m_stationstart.empty())){
            m_stationstart.clear();
        }
        if(!(m_stationtarget.empty())){
            m_stationtarget.clear();
        }
        if(!(m_distanzInKm.empty())){
            m_distanzInKm.clear();
        }
        if(!(m_dauerInMin.empty())){
            m_dauerInMin.clear();
        }
}

int Network::getStation(string gesuchtestation) {
    for (int i = 0; i < m_stationensortiert.size(); i++) {
        if (m_stationensortiert[i] == gesuchtestation) {
            return i;
        }
    }
    return 0;
}












