//
// Created by 莫松松 on 2019/11/15.
//

#ifndef BTS_LOAD_DATA_H
#define BTS_LOAD_DATA_H

#include <vector>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>
#include "mylib.h"
#include "config.h"
#include "algo.h"

using namespace std;

void split(const string& s,vector<int>& sv,const char flag = ' ') {
    sv.clear();
    istringstream iss(s);
    string temp;

    while (getline(iss, temp, flag)) {
        sv.push_back(stoi(temp));
    }
}

class Bus{
public:
    int busID;
    int routeID;
    int time;
    vector<int> persons;
    int influence;
    int St;
    int Et;
    int T;

    double score;

    friend bool operator < (const Bus & a, const Bus & b) {
        return a.influence < b.influence;
    }

    string toString(){
        string re = to_string(busID)+";"+to_string(routeID)+";"+to_string(time);
        for(int p: persons){
            re += (";"+to_string(p));
        }
        return re;
    }

    void StringToBus(string bus){
        vector<int> buses;
        split(bus,buses,';');

        busID = buses[0];
        routeID = buses[1];
        time = buses[2];

        for(int i = 3; i < buses.size(); i++){
            persons.push_back(buses[i]);
        }

        influence = persons.size();

    }
};



class Route {
public:
    int routeID;
    vector<int> Stops; //stop id
    vector<int> travelTimes; //travel time
    int St; // start terminal
    int Et; // end start terminal
    int T;
};

class PBus {
public:
    int PbusID;
    int terminalID; //stop id
    int arriveTime; //travel time
};

class Terminal {
public:
    int terminalID;
    vector<PBus> Pbuses; // physical bus set
    vector<int> bus; // bus service start from here
};

class Person {
public:
    int personID;
    int originLocationId;
    int destinationLocationId;
    int time;
    vector<int> routes;
    vector<int> buses;
    bool influenced;

    string toString(){
        string re = to_string(personID)+";"+to_string(originLocationId)+";"+to_string(destinationLocationId)+";"+to_string(time);
        re += (";"+to_string(routes.size())+";"+to_string(buses.size()));
        for(int r: routes){
            re += (";"+to_string(r));
        }
        for(int b: buses){
            re += (";"+to_string(b));
        }
        return re;
    }

    void StringToPerson(string person){
        vector<int> persons;
        split(person,persons,';');

        personID = persons[0];
        originLocationId = persons[1];
        destinationLocationId = persons[2];
        time = persons[3];

        influenced = false;

        if(persons.size()<5)
            return;

        int rSize = persons[4];
        int bSize = persons[5];

        for(int i = 6; i < 6 + rSize; i++){
            routes.push_back(persons[i]);
        }

        for(int i = 6 + rSize; i < persons.size(); i++){
            buses.push_back(persons[i]);
        }

    }

};

class Cluster {
public:
    int id;

    vector<int> routes;

    int Fmin = 0;

    double rho = 0;

    set<int> overlap;

    map<int, Bus> busSet;
    map<int, Person> personSet;

    void clear(){
        id = 0;
        routes.clear();
        overlap.clear();
        busSet.clear();
        personSet.clear();
    }
};

class Cluster2 {
public:
    int id;

    set<int> routes;

    int Fmin = 0;

    double rho = 0;

    set<int> overlap;

    set<int> busSet;
    set<int> personSet;
};

//vector<Route> Routes;
//vector<Person> Persons;

//map<int, Bus> BusIndex;
//map<int, Person> PersonIndex;

//vector<map<int, Bus>> BusSet;
//vector<map<int, Person>> PersonSet;
//vector<vector<int>> routeSet;

class compare2{
public:
    bool operator()(Cluster o1,Cluster o2){
        return o1.rho < o2.rho;
    }
};

vector<Route> readRoutes(){
    vector<Route> routes;
    string Routes[] = {"7", "9", "10", "13", "14", "502", "925", "77", "19", "960", "80", "325", "904", "111", "172", "903", "282", "882", "136", "27", "156", "913", "135", "386", "265", "92", "180", "12", "334", "30", "62", "141", "21", "57", "40", "979", "132", "403", "125", "854", "199", "184", "911", "853", "183", "811", "103", "33", "73", "201", "54", "990", "86", "35", "36", "947", "38", "39", "56", "966", "333", "116", "109", "60", "63", "79", "75", "6", "372", "983", "89", "291", "901", "335", "74", "88", "182", "300", "189", "358", "76", "83", "970", "48", "61", "147", "191", "139", "181", "118", "194", "160", "8", "134", "70", "950", "69", "138", "242", "292", "174", "518", "257", "371", "66", "188", "85", "190", "43", "49", "26", "142", "94", "96", "101", "106", "261", "37", "812", "700", "130", "107", "120", "912", "124", "112", "169", "945", "154", "307", "45", "254", "195", "24", "67", "157", "123", "163", "151", "72", "52", "93", "857", "158", "179", "196", "962", "249", "98", "400", "90", "5", "981", "131", "65", "31", "852", "972", "167", "53", "252", "159", "153", "133", "117", "165", "258", "161", "128", "803", "186", "197", "91", "856", "293", "82", "193", "23", "241", "168", "980", "806", "240", "166", "113", "87", "851", "262", "985", "858", "59", "173", "32", "965", "97", "246", "192", "105", "29", "2", "84", "95", "232", "315", "20", "150", "170", "47", "81", "34", "3", "121", "284", "50", "222", "177", "238", "253", "964", "200", "55", "285", "99", "22", "922", "401", "804", "855", "64", "235", "28", "251", "143", "17", "506", "4", "975", "920", "231", "800", "16", "42", "119", "187", "927", "961", "41", "176", "15", "162", "359", "859", "58", "178", "102", "228", "175", "51", "900", "155", "268", "269", "78", "317", "963", "255", "229", "145", "18", "100", "198", "140", "185", "171", "941", "302"};
    for(const string& s: Routes){
        Route route = *new Route;
        string file = "../data/route/"+s+".txt";

        FILE *fin = fopen(file.c_str(), "r");

        if(fin == nullptr)
            continue;

        int t1, t2;
        int count = 0;
        while (fscanf(fin, "%d%d", &t1, &t2) != EOF) {
            if(t2 == 0){
                count++;
                if(count == 2){
                    routes.push_back(route);
                }
                route = *new Route;
                route.routeID = stoi(s);
                if(count == 2){
                    route.routeID += 1000;
                }

            }
            route.Stops.push_back(t1);
            route.travelTimes.push_back(t2);
        }

        fclose(fin);

        routes.push_back(route);
    }

    return routes;
}


pair<map<int, Terminal>,map<int, Route>> readTerminals(){
    map<int, Terminal> TerminalIndex;
    map<int, Route> RouteIndex;
    set<int> S;

    string file = "../data/terminal.txt";
    string str;

    vector<Route> routes = readRoutes();

    ifstream infile2(file);

    while(getline(infile2,str)){
        vector<int> strs;
        split(str,strs,'\t');
        if(strs.size()==2){
            Route r;
            r.routeID=strs[0];
            r.St=str[1];
            r.Et=str[1];
            RouteIndex[r.routeID]=r;
            S.insert(str[1]);
        }else{
            Route r1,r2;
            r1.routeID=strs[0];
            r1.St=str[1];
            r1.Et=str[2];
            RouteIndex[r1.routeID]=r1;

            r2.routeID=strs[0]+1000;
            r2.St=str[2];
            r2.Et=str[1];
            RouteIndex[r2.routeID]=r2;

            S.insert(str[1]);
            S.insert(str[2]);
        }
    }

    cout<<S.size()<<endl;

    for(int t:S){
        Terminal t2;
        t2.terminalID=t;
        TerminalIndex[t]=t2;
    }

    for(auto & route : routes){
        RouteIndex[route.routeID].T = route.travelTimes.back();
    }

    return make_pair(TerminalIndex,RouteIndex);
}

vector<Person> readPersons(){
    Person person;
    vector<Person> persons;
    string file = "../data/pers3.txt";

    FILE *fin = fopen(file.c_str(), "r");

    if(fin == nullptr){
        return persons;
    }

    int t1, t2, t3, t4;
    while (fscanf(fin, "%d%d%d%d", &t1, &t2, &t3, &t4) != EOF) {

        if(t1 > config.person_number)
            break;

        person.personID = t1;
        person.originLocationId = t3;
        person.destinationLocationId = t4;

        person.time = t2;

        person.influenced = false;

        persons.push_back(person);

    }

    fclose(fin);
    return persons;
}

int find(vector<int> v, int t){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == t){
            return i;
        }
    }
    return -1;
}

pair<map<int, Bus>,map<int, Person>> buildIndex(const vector<Person>& Persons,const vector<Route>& Routes){
    int busId = 1;
    int count = 0;
    set<int> pers;
    map<int, Bus> BusIndex;
    map<int, Person> PersonIndex;
    map<string, Bus> tempIndex;
    for(Person p : Persons){
        for(Route r : Routes){
            int s = find(r.Stops, p.originLocationId);
            int t = find(r.Stops, p.destinationLocationId);
            if(s > -1 && t > -1 && s<t ){
                count ++;
                pers.insert(p.personID);
                p.routes.push_back(r.routeID);
                int time = p.time - r.travelTimes[s] - config.theta;
                int timer = (time - 1)/60 + 1 ;
                for(int i = timer * 60; i < time + config.theta; i += 60){
                    string key = to_string(r.routeID)+","+to_string(i);
                    auto it = tempIndex.find(key);
                    if(it != tempIndex.end()){
                        //cout<<tempIndex[key].busID<<" "<<r.routeID<<" "<<p.personID<<endl;
                        it->second.persons.push_back(p.personID);
                        p.buses.push_back(tempIndex[key].busID);
                    } else{
                        Bus b;
                        b.busID = busId++;
                        b.time = i;
                        b.routeID = r.routeID;
                        b.persons.push_back(p.personID);
                        p.buses.push_back(b.busID);
                        tempIndex[key] = b;
                    }
                }
            }
        }
        if(!p.buses.empty())
            PersonIndex[p.personID] = p;
    }

    for (auto & it : tempIndex){
        it.second.influence = it.second.persons.size();
        BusIndex[it.second.busID] = it.second;
    }

    //cout<<count<<" "<<pers.size()<<endl;

    return make_pair(BusIndex,PersonIndex);
}

pair<map<int, Bus>,map<int, Person>> loadData(){

    map<int, Bus> BusIndex;
    map<int, Person> PersonIndex;

    ifstream infile1("../data/index/"+to_string(config.theta)+"_"+to_string(config.person_number)+"_bus"+".txt");

    string str;
    while(getline(infile1,str)){
        Bus b;
        b.StringToBus(str);
        BusIndex[b.busID] = b;
    }

    infile1.close();

    ifstream infile2("../data/index/"+to_string(config.theta)+"_"+to_string(config.person_number)+"_person"+".txt");

    while(getline(infile2,str)){
        Person p;
        p.StringToPerson(str);
        PersonIndex[p.personID] = p;
    }

    infile2.close();

    return make_pair(BusIndex,PersonIndex);
}

pair<map<int, Bus>,map<int, Person>> loadData(map<int, Terminal>& TerminalIndex, map<int, Route> RouteIndex){

    map<int, Bus> BusIndex;
    map<int, Person> PersonIndex;

    ifstream infile1("../data/index/"+to_string(config.theta)+"_"+to_string(config.person_number)+"_bus"+".txt");

    string str;
    while(getline(infile1,str)){
        Bus b;
        b.StringToBus(str);
        map<int, Route>::iterator iter;

        iter = RouteIndex.find(b.routeID);

        if(iter != RouteIndex.end()){
            b.St=iter->second.St;
            b.Et=iter->second.Et;
            b.T=iter->second.T;
        }
        else{
            cout<<"no terminals for route "<<b.routeID<<endl;
            continue;
        }
        BusIndex[b.busID] = b;
        TerminalIndex[iter->second.St].bus.push_back(b.busID);
    }

    infile1.close();

    ifstream infile2("../data/index/"+to_string(config.theta)+"_"+to_string(config.person_number)+"_person"+".txt");

    while(getline(infile2,str)){
        Person p;
        p.StringToPerson(str);
        PersonIndex[p.personID] = p;
    }

    infile2.close();

    return make_pair(BusIndex,PersonIndex);
}

//vector<Route> getRoutes(){
//    vector<Route> r(Routes);
//    return r;
//}
//
//vector<Person> getPersons(){
//    vector<Person> p(Persons);
//    return p;
//}





#endif //BTS_LOAD_DATA_H
