//
// Created by ismail on 10.01.22.
//
#include <vector>
#include "UI.h"
#include<unistd.h>

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using namespace gl;
using namespace std;


// In dieser seite findet man eine anleitung zum ausdrüken von deutsche umlaute https://www.c-plusplus.net/forum/topic/39326/deutsche-umlaute
UI::UI() {
    int end_output = 0;
    int wurdendatengeandert = 1;
    int datechangetrue;
    string fileppfadoption4;
    cout << "Sehr geehrte Kundeninnen sehr geehrte Kunden,\n"
         << "Wir freuen uns dass Sie unsere App ausgew\x84hlt haben\n"
         << "Wir haben folgende Optionen f\x81r Sie zur Verf\x81gung\n";
    while(end_output == 0) {
        cout << "Bitte geben Sie die Nummer der Option ein\n"
             << "Wollen Sie\n"
             << "1- Ihre Fahrplan finden\n"
             << "2- Daten \x84ndern oder eine bestimmte Strecke Löscheen \n"
             << "3- Neue Bahn Station hinzuf\x81gen.\n"
             << "4- Daten aus einer Datein lesen und neue Bahn erstellen\n"
                "5- Sollen Stationen alphapetisch sortiert angezeigt werden?\n"
                "6- oder Nach sortierte Line angezeigt werden?\n"
             << "7- Programm beenden\n";
        int x = eingabeToInt('7', 0);

        switch (x) {
            case 1:
                fahrtPlanfinden(wurdendatengeandert);
                break;
            case 2:
                datenAendern(wurdendatengeandert, datechangetrue);
                break;
            case 3:
                datenZufuegen(wurdendatengeandert, datechangetrue);
                break;
            case 4:
                dateiEinlesen(wurdendatengeandert, datechangetrue);
                break;
            case 5:
                if(wurdendatengeandert == 1)
                {

                    fileReading("Berlin.txt");
                    towVectorAddition();
                    sortStationen();
                    deleteDuplicatedStation();
                    cout << "Folgende alphapetisch sortierte Ubahn Stationen stehen Ihnen zu verf\x81gung\n";
                    printm_Stationen();
                    wurdendatengeandert = 2;
                }
                else if(wurdendatengeandert == 3){

                    towVectorAddition();
                    sortStationen();
                    deleteDuplicatedStation();
                    cout << "Folgende alphapetisch sortierte Ubahn Stationen stehen Ihnen zu verf\x81gung\n";
                    printm_Stationen();
                    wurdendatengeandert = 2;
                }
                else if(wurdendatengeandert == 2){
                    cout << "Folgende alphapetisch sortierte Ubahn Stationen stehen Ihnen zu verf\x81gung\n";
                    printm_Stationen();
                }
                break;
            case 6:
                if(wurdendatengeandert == 1)
                {

                    fileReading("Berlin.txt");
                    towVectorAddition();
                    sortStationen();
                    deleteDuplicatedStation();
                    cout << "Folgende sortierte Ubahn Linen stehen Ihnen zu verf\x81gung\n";
                    printm_Strecke();
                    wurdendatengeandert = 2;
                }
                else if(wurdendatengeandert == 3){

                    towVectorAddition();
                    sortStationen();
                    deleteDuplicatedStation();
                    cout << "Folgende alphapetisch sortierte Ubahn Stationen stehen Ihnen zu verf\x81gung\n";
                    printm_Strecke();
                    wurdendatengeandert = 2;
                }
                else if(wurdendatengeandert == 2){
                    cout << "Folgende alphapetisch sortierte Ubahn Stationen stehen Ihnen zu verf\x81gung\n";
                    printm_Strecke();
                }
                break;
            default:
                if(datechangetrue == 2) {
                    cout << "Wollen Sie Ihre Änderung speicher?\n"
                         << "Falls ja dann geben Sie bitte 1\n"
                         << "Falls Nein dann geben Sie bitte 2\n";
                    int eingabe = eingabeToInt('2', 0);
                    if (eingabe == 1) {
                        ofstream file;
                        file.open("test.txt");
                        for (size_t i = 0; i < m_stationstart.size(); i++) {
                            file << m_line[i] << " " << m_stationstart[i] << " -> " << m_stationtarget[i] << ":" << " "
                                 << m_distanzInKm[i] << " " << m_dauerInMin[i] << endl;
                        }

                        file.close();
                        cout << "Die Daten wurden erfolgreich in den Datei mit der Name test.txt gespeichert\n"
                                "Der Datei befindet sich in den folgenden pfad\n"
                                "/home/ismail/Schreibtisch/c23_project/cmake-build-debug/test.txt\n"
                                "Falls Sie die geänderte Daten beim nächsten mal aufrufen wollen, dann geben Sie einfach die oben gennantet Datei bei der vierten Option, damit die Daten daraus eingelsen werden können\n";
                    }
                }
                end_output = 1;
                break;
        }
    }
}
void UI::fahrtPlanfinden(int &isdatechanges) {
    cout <<"Bitte Geben Sie die Nummer der folgenden Optionen ein\n"
       "1- Soll Ihre Fahrplan nach Zeit optimiert werden\n"
       "2- Soll Ihre Fahrplan nach Distanz optimiert werden\n";
    int eingabe = eingabeToInt('2', 0);

    if(isdatechanges == 1)
    {
        Graph graph;
        fileReading("Berlin.txt");
        towVectorAddition();
        sortStationen();
        deleteDuplicatedStation();
        installNode(graph);
        installRoutebyDistanz(graph);
        printm_Stationen();
        fahrtPlanFinden(graph, eingabe);
        isdatechanges = 2;
    }
    else if(isdatechanges == 3){
        Graph graph;
        towVectorAddition();
        sortStationen();
        deleteDuplicatedStation();
        installNode(graph);
        installRoutebyDistanz(graph);
        printm_Stationen();
        fahrtPlanFinden(graph, eingabe);
        isdatechanges = 2;
    }
    else if(isdatechanges == 2){
        Graph graph;
        installNode(graph);
        installRoutebyDistanz(graph);
        printm_Stationen();
        fahrtPlanFinden(graph, eingabe);
    }

}

void UI::datenAendern(int &x, int& datachangetrue) {
    if (x == 1) {
        fileReading("Berlin.txt");
        towVectorAddition();
        sortStationen();
        deleteDuplicatedStation();
        x = 2;
    }
    else if(x == 3){
        towVectorAddition();
        sortStationen();
        deleteDuplicatedStation();
        x = 2;
    }
    cout << "Bitte w\x84hlen Sie einer der folgenden Optionen aus\n"
         << "Bitte geben Sie die Nummer der Option ein\n"       //richtig
         << "1- Die Name einer Station \x84ndern\n"              //richtig
         << "2- Der distanz und dauer einer Strecke \x84ndern\n"       //richtig
         << "3- Eine Strecke L\x94schen\n"
         << "4- Zu den Ursprünglichen Programm zurückkehren\n";                     //richtig
    int auswahlEingabe = eingabeToInt('4', 0);     //richtig
    if (auswahlEingabe == 1) {
        stationNameChange();
        datachangetrue = 2;
        printm_Stationen();
        printm_Strecke();
    }
    else if (auswahlEingabe == 2) {

        distanz_und_dauer_einer_strecke_andern();
        printm_Strecke();
        datachangetrue = 2;
    }
    else if (auswahlEingabe == 3) {
        strecke_loeschen();
        printm_Strecke();
        datachangetrue = 2;
    }
}


void UI::datenZufuegen(int &x, int& datachangetrue) {
    Graph inputstation;

    if (x == 1) {
        fileReading("Berlin.txt");
        towVectorAddition();
        sortStationen();
        deleteDuplicatedStation();
        x = 2;
    }
    else if(x == 3){
        towVectorAddition();
        sortStationen();
        deleteDuplicatedStation();
        x = 2;
    }

    cout << "Bitte geben Sie die Nummer der folgenden Optionen ein\n"
         << "1- Eine neuer Bahn Station hinzufügen\n"                   //richtig
         << "2- Zu den Ursprünglichen Programm zurückkehren\n";                     //richtig
    int auswahlEingabe = eingabeToInt('2', 0);
    if(auswahlEingabe==1) {
        int h = 1;
        printm_Strecke();
        cout << "Bitte Sie nach welche Strecke die neue Station hinzugefügt wird\n"
             << "Bitte geben Sie die Strecke nummer ein\n";
        int streckevor = input_aoutputprogramm_3zahlen(m_stationstart);
        if ((m_line[streckevor - 1] == m_line[streckevor]) || (m_line[streckevor - 2].empty())) {
            cout << "Bitte geben die Name der neue Station ein\n";
            string newStation = eingabeToString();

            cout << "Bitte geben Sie die Distanz für die Folgende Strecke in km\n"
                 << "- " << m_line[streckevor] << " " << m_stationstart[streckevor] << " -> " << newStation << ": "
                 << m_distanzInKm[streckevor] << " " << m_dauerInMin[streckevor] << endl;
            double ditanzstrecke1 = eingabeToDouble();        //muss noch bearbeitet werden
            cout << "Bitte geben Sie die Dauer diese Strecke ein in min\n";
            int dauerstrecke1 = eingabeToInt('9', 0);
            cout << "Bitte geben Sie die Distanz dieser Strecke ein\n"
                 << "- " << m_line[streckevor] << " " << newStation << " -> " << m_stationtarget[streckevor] << ": "
                 << m_distanzInKm[streckevor] << " " << m_dauerInMin[streckevor] << endl;
            double ditanzstrecke2 = eingabeToDouble();       //muss noch bearbeitet werden
            cout << "Bitte geben Sie die Dauer dieser Strecke in min ein\n";
            int dauerstrecke2 = eingabeToInt('9', 0);
            addNewStation1(streckevor,  newStation, ditanzstrecke1, ditanzstrecke2, dauerstrecke1, dauerstrecke2);
            printm_Strecke();
            datachangetrue = 2;
        }
        if ((m_line[streckevor - 1] != m_line[streckevor]) || (m_line[streckevor].empty())) {
            cout << "Bitte geben die Name der Station ein\n";
            string newStation = eingabeToString();

            cout << "Bitte geben Sie die Distanz für die Folgende Strecke in km in folgende Format z.B 0.0\n"
                 << "- " << m_line[streckevor - 1] << " " << m_stationtarget[streckevor - 1] << " -> " << newStation
                 << ":" << endl;
            double ditanzstrecke1 = eingabeToDouble();    //muss noch bearbeitet werden
            cout << "Bitte geben Sie die Dauer diese Strecke ein in min in Zahlen zwischen 1 und 9\n";
            int dauerstrecke1 = eingabeToInt('9', 0);
            //Fugt die station und verbindet diese mit der vorherige Strcke und mit der Nachherige strecke
            addNewStation2(streckevor, newStation, ditanzstrecke1, dauerstrecke1);
            printm_Strecke();
            datachangetrue = 2;
        }
         }
    if(auswahlEingabe == 2) {
        switch (auswahlEingabe) {
            case 2:
                break;
            default:
                break;
        }
    }
}
void UI::dateiEinlesen(int &x, int& datachangetrue) {// muss noch berarbeitet werden
    cout << "Bitte den Pfad der Datei in folgende Format eingeben (z.B. home/ismail/Schreibtisch/c23_project/cmake-build-debug/Berlin.txt:\n";
    cout << "Bitte den Pfad der Datei in folgende Format eingeben (z.B. für Windows Nutzer C:\\Users\\ismail\\Desktop\\Metro-Berlin\\Berlin.txt:"
            "\noder für Ubuntu Nutzer: /home/ismail/Schreibtisch/c23_project/cmake-build-debug/Berlin.txt \n";
    ///pfad eingabe beispiel:
    string pfad;
    std::getline(cin, pfad, '\n');
    ifstream datei(pfad);

    while(datei.fail()){
        try {
            if(datei.fail())
                throw GraphLibException("Eingegebener Pfad enthält keine Datei");
        }
        catch (GraphLibException& s){
            cerr << " > FEHLER: " << s.what() << "\n\n > Bitte einen anderen Pfad eingeben: ";
            std::getline(cin, pfad, '\n');
            datei.open(pfad);
        }
    }
    Networkdestrokor(); // dadurch werden alle Membervariablen gelöscht
    string route;
    while(std::getline(datei, route)) { // wandeln das , zur . damit der double zahlen durch stringstream erkannt wird
        for (size_t i = 0; i < route.size(); i++) {
            if (route[i] == ',')
                route[i] = '.';
        }

        stringstream Puffer(route);
        string line, start_Station, end_Station, bow, points;
        double distanse, duration;
        Puffer >> line >> start_Station;
        Puffer >> bow;
        if (bow != "->") {
            start_Station += ' ' + bow;
            Puffer >> bow;
        }
        Puffer >> end_Station;
        if (end_Station[end_Station.size() - 1] == ':')
            end_Station[end_Station.size() - 1] = ' ';
        else {
            Puffer >> points;
            end_Station += ' ' + points;
            end_Station[end_Station.size() - 1] = ' ';
        }
        Puffer >> distanse >> duration;
        end_Station.pop_back();//leerzeichen Löschen
        setLine(line);
        setStart(start_Station);
        settarget(end_Station);
        setDuration(duration);
        setdistanz(distanse);
    }
    x = 3;
    datachangetrue = 2;
    cout << "einlesen war erfolgreich\n";
    cout << "Die Daten wurden im Rigester gespeichert durch den folgenden Optionen können "
            "Sie mit den Gespeicherten Daten beliebig arbeiten\n\n";


}

void UI::stationNameChange() {
    printm_Stationen();
    cout << "Bitte geben Sie die Nummer der staition die Sie \x84ndern wollen\n";
    int stationzahl = input_aoutputprogramm_3zahlen(m_stationensortiert);
    cout << "Bitte geben Sie die Name der neue Station\n";
    string eingabe = eingabeToString();
    setStationName(eingabe, stationzahl);

}

void UI::distanz_und_dauer_einer_strecke_andern() {
    printm_Strecke();
    cout << "Bitte geben Sie die Nummer der Strecke die Sie ändern wollen\n";
    int strecke_nummer =  input_aoutputprogramm_3zahlen(m_stationstart);
    cout << "Bitte geben Sie die Distanz in km folgende Format ein 0.0\n";

    double geanderte_distanz = eingabeToDouble();
    cout << "Bitte geben Sie die Dauer in min als zahl zwischen 1 und 9\n";
    int geanderte_dauer = eingabeToInt('9', 0);

    // Distanz ändern wird nur an einer stelle geändert weil der distanz noch nicht in edges definiert ist und damit befindet sich nur einmal in dem string bzw stehen nur gerade und nicht rückwerts
    setDistanz(strecke_nummer,geanderte_distanz);
    //Dauer ändern
    setDuration(strecke_nummer, geanderte_dauer);

 }
void UI::strecke_loeschen() {
    printm_Strecke();
    cout << "Bitte geben Sie die Nummer der Strecke ein\n";
    int ubahnzuandern = input_aoutputprogramm_3zahlen(m_stationstart);
    deleteRoute(ubahnzuandern);

}



double UI::eingabeToDouble() {
    string inputstring;
    int x = 0;
    int komma = 0;
    while (x == 0) {
        std::getline(cin, inputstring, '\n');//eingabe muss noch überprüft try catch
        try{
            if(inputstring.empty()){
                throw GraphLibException("Bitte Betätigen Sie eine Eingabe und lassen Sie die Zeile nicht Leer");
            }
        }

        catch(GraphLibException &e) {
            cerr << " > FEHLER: " << e.what() << "\n\n > Bitte einer Weitere Eingabe durchführen: " << endl;
            x = 0;
        }
        try {
            for (int i = 0; i < inputstring.size(); i++) {
                if (inputstring[i] == '.') {
                    komma = i;
                }

            }
            for (int i = 0; i < inputstring.size(); i++) {
                x = 1;
                if (inputstring[i] == '.') {
                    i++;
                }
                if (inputstring[i] < '0' || inputstring[i] > '9' || komma == 0) {
                    throw GraphLibException(
                            "Bitte geben Sie nur Zahlen zwischen 1 und 9 nur Folgende Format z.B 1.9 wird unterstützt");
                }
            }
        }
        catch (GraphLibException &e) {
            cerr << "< Fehler: \n\n" << e.what() << "Bitte Nochmal eingeben" << endl;
            x = 0;
            komma =0;
        }
    }
    double geanderte_distanz_upepruft = fromString<double>(inputstring);
    return geanderte_distanz_upepruft;
}

string UI::eingabeToString() {
    string eingabe;
    int x = 0;
    int check = 0;
    while (x == 0) {

        std::getline(cin, eingabe, '\n');
        try {
            if (eingabe.empty()) {
                throw GraphLibException("Bitte Betätigen Sie eine Eingabe und lassen Sie die Zeile nicht Leer");
            }
        }
        catch (GraphLibException &e) {
            cerr << " > FEHLER: " << e.what() << "\n\n > Bitte einer Weitere Eingabe durchführen: " << endl;
            x = 0;
        }
        try {
            if (!eingabe.empty() && (eingabe.size() < 6 || eingabe.size() > 20)) {
                throw invalid_argument("Bitte nicht kleine als 3 Buchstaben und nicht mehr als 20 Buchstaben eingeben");
            }
        }
        catch (invalid_argument &e) {
            cerr << "< Fehler: \n\n" << e.what() << "Bitte Nochmal eingeben" << endl;
            x = 0;
        }
        for (int i = 0; i < eingabe.length() && !(eingabe.size() < 6 || eingabe.size() > 20) && !eingabe.empty(); i++) {
            x = 1;

            if (eingabe[i] == ' ' && (i + 1) < eingabe.size() && eingabe[i - 1] != ' ' && eingabe[i + 1] != ' ' &&
                eingabe[0] != ' ' && eingabe[eingabe.size()] != ' ' && eingabe[1] != ' ' && eingabe[2] != ' ') {
                i++;
            } else if (eingabe[i] == '_' && (i + 1) < eingabe.size() && eingabe[i - 1] != '_' &&
                       eingabe[i + 1] != '_' && eingabe[0] != '_' && eingabe[eingabe.size()] != '_' &&
                       eingabe[1] != '_' && eingabe[2] != '_') {
                i++;
            } else if (eingabe[i] == '-' && (i + 1) < eingabe.size() && eingabe[i - 1] != '-' &&
                       eingabe[i + 1] != '-' && eingabe[0] != '-' && eingabe[eingabe.size()] != '-' &&
                       eingabe[1] != '-' && eingabe[2] != '-') {
                i++;
            }
            try {
                if ((eingabe[i] < 'A' || eingabe[i] > 'z')) {

                    string throwausgabe = "Nur Folgende Eingaben werden unterstützt Stationnamestra oder Stationname strasse oder stationname_Erweiterung oder stationnamm-erweiterung"
                                          "\nZahlen und Sonderzeichen sind nicht erlaubt außer _ und - und Leerzeichen zwischen die Statioenname falls es erfolerlich ist\n";
                    throw invalid_argument(throwausgabe);

                }
            }
            catch (invalid_argument &e) {
                cerr << "< Fehler: \n\n" << e.what() << "Bitte Nochmal eingeben" << endl;
                x = 0;
                eingabe = "";
            }
        }

    }
    return eingabe;
}