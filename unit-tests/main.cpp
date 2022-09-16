#include "pch.h"

#include <regex>

namespace gl
{
    namespace test
    {    /// Bitte den pfad anpassen Die Namme der Ordner dürfen keine leerzeichen enthalten
        TEST(Network, NodeNameChanged)
        {   // Es wird überprüft ob das Ändern der Name eine Node erfolgreich ist oder nicht

            ///pfad eingabe beispiel: /home/ismail/Schreibtisch/c23_project/Berlin.txt
            // Erstellen die Daten eine Bahn durch das Lesen der Datei Berlin.txt und speicher die strecken in die membervraiablen der Klasse Network

            Network x;
            x.fileReading("/home/ismail/Schreibtisch/c23_project/Berlin.txt"); // Pfad anpassen Bitte
           // Dadruch werden die stationen der bahn sortiert und wiederholte stationen gelöscht und in m_stationensortiert gespeichert
            x.towVectorAddition();
            x.alphapetischsortieren();
            x.deleteDuplicatedStation();
            string checkname;
            {
                Graph graph;
                x.installNode(graph);
               // speichern der Name um es später zu vergleichen ob es geändert wird oder nicht
                checkname = graph.findNode("Augsburger Strasse")->name();
            }
            string isNamechanged;
            int stationnummer = x.getStation("Augsburger Strasse");
            // Ändern der Name der station zur testtest

            x.changeStationName("testtest", 1 + stationnummer); // benutzer eingabe
           // die station befindet nicht mehr in den vector weil ihre Name geändert wird, da dieser leer ist return 0
            EXPECT_EQ(x.getStation("Augsburger Strasse"), 0);
            // Die station wird in den vector gefunden deshalb wird die richtige steionnummer return
            EXPECT_EQ(x.getStation("testtest"), stationnummer);
            {
                Graph graph;
                x.installNode(graph);
             isNamechanged = graph.findNode("testtest")->name();
            }
            // Die Name des Nodes wurde erfolgreich geändert
            EXPECT_NE(isNamechanged, checkname);
        }



        TEST(Network, RouteDistanzAndDurationChange){
            // Hier wird geprüft ob das Ändern der Distanzn und dauer einer Strecke erfolgreich ist oder nicht
            Network x;
            x.fileReading("/home/ismail/Schreibtisch/c23_project/Berlin.txt");
            x.towVectorAddition();
            x.alphapetischsortieren();
            x.deleteDuplicatedStation();
            double checkdistanzvor;
            int checkdurationvor;
            {
                Graph graph;
                x.installNode(graph);
                x.installRoute(graph);
                Node& start = *graph.findNode(x.getStationStart(70));
                Node& dst =  *graph.findNode(x.getStationTarget(70));
                vector<Edge *> xx = graph.findEdges(start, dst);
               // speichern der inhalt der distanz und dauer einer Strecke um es zu vergleichen
                checkdistanzvor = xx[0]->weight();
                checkdurationvor = xx[0]->time();
            }
            // Ändern der Distanzn und dauer der Strecke 70
            //Der Nutzer gibt 71 ein weil beim ausdrücken die Zahlen mit 1
            // anfangen und nicht mit 0 deshalb werden die Zahlen um 1 subtrahiert
            x.changeDistanz(70 + 1, 1.7);
            x.changeDuration(70 + 1, 5);

            double checkdistanznach;
            int checkdurationnach;

            {
                Graph graph;
                x.installNode(graph);
                x.installRoute(graph);
                Node& start = *graph.findNode(x.getStationStart(70));
                Node& dst =  *graph.findNode(x.getStationTarget(70));
                vector<Edge *> xx = graph.findEdges(start, dst);
                // speichern die Distanz und dauer nach der Änderung
                checkdistanznach = xx[0]->weight();
                checkdurationnach = xx[0]->time();
            }
            // wir vergleichen des sitanz vor und nach und die Dauer der Strecke auch
            EXPECT_EQ(checkdistanzvor == checkdistanznach, 0);
            EXPECT_NE(checkdistanzvor, checkdistanznach);
            EXPECT_EQ(checkdurationvor == checkdurationnach, 0);
            EXPECT_NE(checkdurationvor, checkdurationnach);
            EXPECT_EQ(checkdistanznach, 1.7);
            EXPECT_EQ(checkdurationnach, 5);
        }
        TEST(Network, RouteNameChange){
            // Hier wird versucht ob das Ändern der Name eine Route möglich ist oder nicht

            Network x;
            x.fileReading("/home/ismail/Schreibtisch/c23_project/Berlin.txt");
            x.towVectorAddition();
            x.alphapetischsortieren();
            x.deleteDuplicatedStation();
            string startNameVor;
            string targetNameVor;
            {
                Graph graph;
                x.installNode(graph);
                x.installRoute(graph);
                Node& start = *graph.findNode(x.getStationStart(3));
                Node& dst =  *graph.findNode(x.getStationTarget(3));
                vector<Edge *> xx = graph.findEdges(start, dst);
                // Speichern der Name der start und zielstation vor der Änderung
                startNameVor = xx[0]->source().name();
                targetNameVor = xx[0]->destination().name();
            }

            // Ändern die Name der ziel und start station einer strecke
            x.changeStationName("Hallloo", 1 + x.getStation("Kottbusser Tor"));
            x.changeStationName("Heyyyy", 1 + x.getStation("Prinzenstr"));
            string startNameNach;
            string targetNameNach;

            {
                Graph graph;
                x.installNode(graph);
                x.installRoute(graph);
                Node& start = *graph.findNode(x.getStationStart(3));
                Node& dst =  *graph.findNode(x.getStationTarget(3));
                vector<Edge *> xx = graph.findEdges(start, dst);
              // Speichern der Name der ziel und Start station einer Strecke nach der änderung
                startNameNach = xx[0]->source().name();
                targetNameNach = xx[0]->destination().name();
            }
            // vergleich zwischen start ziel station vor dr änderung und dannach
            EXPECT_EQ(startNameVor == startNameNach, 0);
            EXPECT_NE(startNameVor, startNameNach);
            EXPECT_EQ(targetNameVor == targetNameNach, 0);
            EXPECT_NE(targetNameVor, targetNameNach);
            EXPECT_EQ(startNameNach, "Hallloo");
            EXPECT_EQ(targetNameNach, "Heyyyy");
        }

        TEST(Network, Routedelete) {
            // Hier wird versucht ob das Löschen eine Route möglich ist oder nicht
            Network x;
            x.fileReading("/home/ismail/Schreibtisch/c23_project/Berlin.txt");
            x.towVectorAddition();
            x.alphapetischsortieren();
            x.deleteDuplicatedStation();
            {       // Fall 1: wir löschen eine strecke am Ende eine Line
                // dadurch wir der line und start und zie und duratuin und distanz der strecke gelöscht
                string netstart;
                string nettarget;
                {
                    Graph graph;
                    x.installNode(graph);
                    x.installRoute(graph);
                    Node &start = *graph.findNode(x.getStationStart(188));
                    netstart = start.name();
                    Node &dst = *graph.findNode(x.getStationTarget(188));
                    nettarget = dst.name();
                    EXPECT_EQ(graph.findEdges(start, dst).size(), 1);

                }
                x.deleteRoute(189); //Benutzer eingabe
                {
                    Graph graph;
                    x.installNode(graph);
                    x.installRoute(graph);
                    Node &start = *graph.findNode(netstart);
                    Node &dst = *graph.findNode(nettarget);
                    EXPECT_EQ(graph.findEdges(start, dst).size(), 0);
                }
            }
            //Fall 2: die Station befindet sich an einer beliebigen position dadurch die strecke gelöscht und die startstation
            // aus der vorhierige Strecke mit der Ziel Station nach der zu löschende strecke vebunden damit der bahn nicht geschnitten wird
            {
                string netstart;
                string nettarget;
                string startstreckevor;
                string zielstreckenach;
                double distanzVor;
                int timeVor;
                {
                    Graph graph;
                    x.installNode(graph);
                    x.installRoute(graph);
                    Node &start = *graph.findNode(x.getStationStart(1));
                    netstart = start.name();
                    Node &dst = *graph.findNode(x.getStationTarget(1));
                    nettarget = dst.name();

                    Node &start2vor = *graph.findNode(x.getStationStart(0));
                    startstreckevor = start2vor.name();
                    Node &dst2vor = *graph.findNode(x.getStationTarget(2));
                    zielstreckenach = dst2vor.name();

                    EXPECT_EQ(graph.findEdges(start, dst).size(), 1);
                    EXPECT_EQ(graph.findEdges(start2vor, dst2vor).size(), 0);
                }
               x.deleteRoute(2); //Benutzer eingabe
                {
                    Graph graph;
                    x.installNode(graph);
                    x.installRoute(graph);
                    Node &start = *graph.findNode(netstart);
                    Node &dst = *graph.findNode(nettarget);

                    EXPECT_EQ(graph.findEdges(start, dst).size(), 0);
                    Node &startvor = *graph.findNode(startstreckevor);
                    Node &dstnach = *graph.findNode(zielstreckenach);
                    EXPECT_EQ(graph.findEdges(startvor, dstnach).size(), 1);
                    /* vorher sieht so aus
                       U1 Warschauer Str -> Schlesisches Tor: 0,8 2
                       U1 Schlesisches Tor -> Gourlitzer Bahnhof: 0,9 2 // strecke die gelöscht wird Nummer 2
                       U1 Gourlitzer Bahnhof -> Kottbusser Tor: 0,7 1
                       U1 Kottbusser Tor -> Prinzenstr: 0,9 2
                     */
                    // Es werden die zeil und startstation der zu löschende strecke auch aus dem vorhioerige und nacherige strecke
                    // gelöscht damit der bahn nicht geschnitten wird. Und die distanz und dauer der beiden strecken addiert
                    // weil der Weg zwischen der station länger wird
                    /* Nachher Siehr so aus
                       U1 Warschauer Str -> Kottbusser Tor:1.6 2
                       U1 Kottbusser Tor -> Prinzenstr: 0,9 2
                     */
                }

            }
        }
        TEST(Network, AddNewStationFall1) {
            Network x;
            x.fileReading("/home/ismail/Schreibtisch/c23_project/Berlin.txt");
            x.towVectorAddition();
            x.alphapetischsortieren();
            x.deleteDuplicatedStation();
            //Fall 1: Da addieren wir eine neue Station am ende eine Ubahn bzw. nach der letzte Strecke eine Ubahn
            string nettarget;
            {
                Graph graph;
                x.installNode(graph);
                x.installRoute(graph);
                Node &start = *graph.findNode(x.getStationStart(171));
                Node &dst = *graph.findNode(x.getStationTarget(171));
                nettarget = dst.name();
                vector<Edge *> newRoute = graph.findEdges(start, dst);
                EXPECT_EQ(newRoute[0]->weight(), x.getDistanz(171));
                EXPECT_EQ(newRoute[0]->time(), x.getDuration(171));
                EXPECT_EQ(newRoute[0]->line(), x.getline(171));
                // Wir gucken, ob die Strecke exisitert zwischen start und dst
                EXPECT_EQ(graph.findEdges(start, dst).size(), 1);
            }
            // Da der Bahn am ende einer beliebige Ubahn ist wird die strecke nur addiert
            // Das heißt wir nehemn den Ziel Station aus der vorhierige Strecke und setzten diese als
            // start der neue strecke und setzen die neue station als Zielstation der addierten Strecke
            x.addNewStation2(172, "newstation", 0.8, 2);
            {
                Graph graph;
                x.installNode(graph);
                x.installRoute(graph);
                Node &start = *graph.findNode(nettarget);
                Node &dst = *graph.findNode("newstation");
                vector<Edge *> newRoute = graph.findEdges(start, dst);
                EXPECT_EQ(newRoute[0]->weight(), x.getDistanz(172));
                EXPECT_EQ(newRoute[0]->time(), x.getDuration(172));
                EXPECT_EQ(newRoute[0]->line(), x.getline(172));
                // Hier wird geprüft ob die Strecke erfolgreich addiert wird
                // die srecke sieht wie folgendes aus: netttarget -> newstation 0.8 2
                EXPECT_EQ(graph.findEdges(start, dst).size(), 1);
            }
        }




        TEST(Network, AddNewStationFall2) {

            Network x;
            x.fileReading("/home/ismail/Schreibtisch/c23_project/Berlin.txt");
            x.towVectorAddition();
            x.alphapetischsortieren();
            x.deleteDuplicatedStation();
            //Fall 2: Da addieren wir eine neue Station nach eine beliebige strecke eine Ubahn außer die letzte
            string nettarget;
            string netTarget2;
            {
                Graph graph;
                x.installNode(graph);
                x.installRoute(graph);
                Node &start = *graph.findNode(x.getStationStart(169));
                Node &dst = *graph.findNode(x.getStationTarget(169));
                nettarget = dst.name();
                Node &dstnach = *graph.findNode(x.getStationTarget(170));
                netTarget2 = dstnach.name();

                // diese strecke wird gelöscht weil die neue station dazwischen kommt
                EXPECT_EQ(graph.findEdges(dst, dstnach).size(), 1);
            }
            // Da die strecke nicht am ende eine Line ist wird die neue Station zwischen die strecke nummer 170 und 171 addiert
            x.addNewStation1(170,"newStation", 0.9, 0.4, 3, 1);
            {
                Graph graph;
                x.installNode(graph);
                x.installRoute(graph);
                Node &start = *graph.findNode(nettarget);
                Node &dst = *graph.findNode("newStation");
                Node &dstzwei = *graph.findNode(netTarget2);
                // wir überprüfen ob die addition erfolgreich war
                // strecke zwischen der vorhierege zielstation und die neue station
                // zielstation1 -> neue station
                vector<Edge *> newRoute = graph.findEdges(start, dst);
               EXPECT_EQ(newRoute[0]->weight(), x.getDistanz(170));
              EXPECT_EQ(newRoute[0]->time(), x.getDuration(170));
                EXPECT_EQ(newRoute[0]->line(), x.getline(170));
                EXPECT_EQ(graph.findEdges(start, dst).size(), 1);
                //diese strecke wird gelöscht da die neue station dazwischen kommt
              EXPECT_EQ(graph.findEdges(start, dstzwei).size(), 0);
                 // strecke zwischen neue station  und die die der nächste strecke
                // neue station -> zielstation2
               vector<Edge *> newRoute2 = graph.findEdges(dst, dstzwei);
                EXPECT_EQ(newRoute2[0]->weight(), x.getDistanz(171));
                EXPECT_EQ(newRoute2[0]->time(), x.getDuration(171));
                EXPECT_EQ(newRoute2[0]->line(), x.getline(171));
                EXPECT_EQ(graph.findEdges(dst, dstzwei).size(), 1);
                //Hier wird geprüft ob die Strecke erfolgreich addiert wird
                // die srecke sieht wie folgendes aus: netttarget -> newstation


            }

        }
        TEST(Network, isLineChange) {

            Network x;
            x.fileReading("/home/ismail/Schreibtisch/c23_project/Berlin.txt");
            x.towVectorAddition();
            x.alphapetischsortieren();
            x.deleteDuplicatedStation();
            Graph graph;
            x.installNode(graph);
            x.installRoute(graph);
            Node &start = *graph.findNode("Alt-Tegel");
            Node &target = *graph.findNode("Augsburger Strasse");
            // zwischen start und target haben wir drei umstiegs deshalb 3 * 10 = 30
            std::deque<Edge *> path = graph.dijkstra(start, target);
            int total_time{0};
            vector<string> umsteigdauer;
            x.isLinechange(path, total_time, umsteigdauer);

            EXPECT_NE(path[8]->line(), path[9]->line());    // totaltime + 10 min
            EXPECT_NE(path[14]->line(), path[15]->line());  // totaltime + 10 min
            EXPECT_NE(path[15]->line(), path[16]->line());  // totaltime + 10 min
            EXPECT_EQ(total_time, 30);


        }
        TEST(Network, setterGetterFunktionen) {
            Network x;
            // Es Werden die setter und getter funktionen überprüft
            x.setLine("U8");
            x.setStart("Berlinerstrasse");
            x.settarget("Hallo Strasse");
            x.setDistanz(0.5);
            x.setDuration(2);
            EXPECT_EQ(x.getline(0), "U8");
            EXPECT_EQ(x.getStationStart(0), "Berlinerstrasse");
            EXPECT_EQ(x.getStationTarget(0), "Hallo Strasse");
            EXPECT_EQ(x.getDistanz(0), 0.5);
            EXPECT_EQ(x.getDuration(0), 2);
            x.towVectorAddition();
            x.alphapetischsortieren();
            x.deleteDuplicatedStation();
            EXPECT_EQ(x.getStation(0), "Berlinerstrasse");
            EXPECT_EQ(x.getStation(1), "Hallo Strasse");

        }
        TEST(Route, Routeinstall) {

            Graph graph;
            // Es wird überprüft ob das Erstellen der Route richtig ist
            // und aufrufen der funktionen line und time und weight erfolgen kann
            Node n1(graph, "Berlinerstrasse");
            Node n2(graph, "Hallo Strasse");
            Node &start = *graph.findNode("Berlinerstrasse");
            Node &target = *graph.findNode("Hallo Strasse");
            Route r1(graph, "U8", start, target, 0.5, 1);
            vector<Edge *> xx = graph.findEdges(start, target);
            EXPECT_EQ(graph.findEdges(start, target).size(), 1);
            EXPECT_EQ(graph.findEdges(target, start).size(), 0);
            EXPECT_EQ(xx[0]->line(), "U8");
            EXPECT_EQ(xx[0]->source().name(), "Berlinerstrasse");
            EXPECT_EQ(xx[0]->destination().name(), "Hallo Strasse");
            EXPECT_EQ(xx[0]->weight(), 0.5);
            EXPECT_EQ(xx[0]->time(), 1);
            Route r2(graph, "U8", target, start, 0.5, 1);
            EXPECT_EQ(graph.findEdges(target, start).size(), 1);

        }
    }

}