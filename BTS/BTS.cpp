#include <iostream>
#include <vector>
#include <string>
#include "config.h"
#include "algo.h"
#include <ctime>

using namespace std;

clock_t startTime,endTime;

void indexGreedyTest(){
    vector<Route> routes = readRoutes();

    vector<int> rout;
    map<int,int> N;

    for(Route r : routes){
        rout.push_back(r.routeID);
        N[r.routeID] = config.busNumber;
    }

    startTime = clock();//计时开始

    pair<map<int, Bus>,map<int, Person>> index = loadData();

    cout << index.second.size() <<endl;

    endTime = clock();//计时结束

    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    //pair<map<int, Bus>,map<int, Person>> index_bak = make_pair(index.first,index.second);
    startTime = clock();//计时开始

    vector<int> re = indexGreedy(index.first,index.second,N,rout);

    endTime = clock();//计时结束
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    cout<<getServiceNumber(index.first,index.second,re)<<endl;
}

void scoreSelTest(){
    pair<map<int, Terminal>,map<int, Route>> p1 = readTerminals();

    map<int,int> N;

    map<int, Terminal>::iterator it;

    int count = 0;

    for(it=p1.first.begin();it!=p1.first.end();it++){
        N[it->second.terminalID] = config.pBusNumber;
        count++;
    }
    //cout<<count<<endl;

    startTime = clock();//计时开始

    pair<map<int, Bus>,map<int, Person>> index = loadData(p1.first,p1.second);

    cout << index.second.size() <<endl;

    endTime = clock();//计时结束

    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    //pair<map<int, Bus>,map<int, Person>> index_bak = make_pair(index.first,index.second);
    startTime = clock();//计时开始

    vector<int> re = ScoreSel(index.first,index.second,N,p1.first,config.lambda);

    endTime = clock();//计时结束
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    cout<<getServiceNumber(index.first,index.second,re)<<endl;
}

void greedySelTest(){
    pair<map<int, Terminal>,map<int, Route>> p1 = readTerminals();

    map<int,int> N;

    map<int, Terminal>::iterator it;

    int count = 0;

    for(it=p1.first.begin();it!=p1.first.end();it++){
        N[it->second.terminalID] = config.pBusNumber;
        count++;
    }
    //cout<<count<<endl;

    startTime = clock();//计时开始

    pair<map<int, Bus>,map<int, Person>> index = loadData(p1.first,p1.second);

    cout << index.second.size() <<endl;

    endTime = clock();//计时结束

    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    //pair<map<int, Bus>,map<int, Person>> index_bak = make_pair(index.first,index.second);
    startTime = clock();//计时开始

    vector<int> re = GreedySel(index.first,index.second,N,p1.first);

    endTime = clock();//计时结束
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    cout<<getServiceNumber(index.first,index.second,re)<<endl;
}

void buildIndexTest(){
    vector<Route> routes = readRoutes();
    vector<Person> persons = readPersons();

    cout << persons.size() <<endl;

    startTime = clock();//计时开始

    pair<map<int, Bus>,map<int, Person>> index = buildIndex(persons,routes);

    cout << index.second.size() <<endl;

    ofstream outfile1("../data/index/"+to_string(config.theta)+"_"+to_string(config.person_number)+"_bus"+".txt", ios::trunc);

    for(auto & it : index.first){
        outfile1<<it.second.toString()<<endl;
    }

    outfile1.close();

    ofstream outfile2("../data/index/"+to_string(config.theta)+"_"+to_string(config.person_number)+"_person"+".txt", ios::trunc);

    for(auto & it : index.second){
        outfile2<<it.second.toString()<<endl;
    }

    outfile2.close();

    endTime = clock();//计时结束

    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

}

void topKTest(){
    vector<Route> routes = readRoutes();

    vector<int> rout;
    map<int,int> N;

    for(Route r : routes){
        rout.push_back(r.routeID);
        N[r.routeID] = config.busNumber;
    }


    startTime = clock();//计时开始

    pair<map<int, Bus>,map<int, Person>> index = loadData();

    vector<int> re = topK(index.first,index.second,N,rout);

    cout<<re.size()<<endl;

    endTime = clock();//计时结束
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    cout<<getServiceNumber(index.first,index.second,re)<<endl;
}

void fixIntTest(){
    vector<Route> routes = readRoutes();

    vector<int> rout;
    map<int,int> N;

    for(Route r : routes){
        rout.push_back(r.routeID);
        N[r.routeID] = config.busNumber;
    }


    pair<map<int, Bus>,map<int, Person>> index = loadData();

    //cout << index.second.size() <<endl;

    //pair<map<int, Bus>,map<int, Person>> index_bak = make_pair(index.first,index.second);

    startTime = clock();//计时开始

    vector<int> re = fixInt(index.first,index.second,N,rout);

    endTime = clock();//计时结束
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    cout<<getServiceNumber(index.first,index.second,re)<<endl;
}

void partGreedyTest1(){
    vector<Route> routes = readRoutes();
    vector<Person> persons = readPersons();

    map<int,int> N;

    vector<map<int, Bus>> buses;
    vector<map<int, Person>> pers;
    vector<vector<int>> routeSet;

    for(Route r : routes){
        N[r.routeID] = 20;
    }

    for(Route r: routes){
        vector<Route> rs;
        vector<int> rId;
        rs.push_back(r);
        pair<map<int, Bus>,map<int, Person>> index = buildIndex(persons,rs);
        buses.push_back(index.first);
        pers.push_back(index.second);
        rId.push_back(r.routeID);
        routeSet.push_back(rId);

    }

    vector<vector<int>> re = partGreedy(buses, pers, N, routeSet);

    cout<<getServiceNumber2(buses,pers,re)<<endl;
}

void partGreedyTest(){

    vector<map<int, Bus>> buses;
    vector<map<int, Person>> pers;
    vector<vector<int>> routeSet;

    vector<Route> routes = readRoutes();

    vector<int> rout;
    map<int,int> N;
    int Nmin = config.busMinNumber;

    for(Route r : routes){
        rout.push_back(r.routeID);
        N[r.routeID] = config.busNumber;
    }

    pair<map<int, Bus>,map<int, Person>> index = loadData();

    cout<<index.second.size()<<endl;

    startTime = clock();//计时开始

    vector<Cluster> cluster = partition3(rout,index.first,index.second, Nmin, config.rho);

    endTime = clock();//计时结束
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    //clock_t endTime1 = clock();//计时结束

    //cout << "The partition run time is: " <<(double)(endTime1 - startTime) / CLOCKS_PER_SEC << "s" << endl;

    //cout<<cluster.size()<<endl;

    for(Cluster c: cluster){

        buses.push_back(c.busSet);
        pers.push_back(c.personSet);
        routeSet.push_back(c.routes);

    }

//    startTime = clock();//计时开始

    vector<vector<int>> re = partGreedy(buses, pers, N, routeSet);

    endTime = clock();//计时结束
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    cout<<re.size()<<endl;

    cout<<getServiceNumber2(buses,pers,re)<<endl;
}

void proPartGreedyTest(){

    vector<map<int, Bus>> buses;
    vector<map<int, Person>> pers;
    vector<vector<int>> routeSet;

    vector<Route> routes = readRoutes();

    vector<int> rout;
    map<int,int> N;
    int Nmin = config.busMinNumber;

    for(Route r : routes){
        rout.push_back(r.routeID);
        N[r.routeID] = config.busNumber;
    }

    pair<map<int, Bus>,map<int, Person>> index = loadData();

    startTime = clock();//计时开始

    vector<Cluster> cluster = partition3(rout,index.first,index.second, Nmin, config.rho);

    //clock_t endTime1 = clock();//计时结束

    //cout << "The partition run time is: " <<(double)(endTime1 - startTime) / CLOCKS_PER_SEC << "s" << endl;

    cout<<cluster.size()<<endl;

    for(Cluster c: cluster){

        buses.push_back(c.busSet);
        pers.push_back(c.personSet);
        routeSet.push_back(c.routes);

    }

    vector<vector<int>> re = proPartGreedy(buses, pers, N, routeSet);

    endTime = clock();//计时结束
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    cout<<re.size()<<endl;

    cout<<getServiceNumber2(buses,pers,re)<<endl;
}

void proGreedyTest(){
    vector<Route> routes = readRoutes();
    vector<Person> persons = readPersons();

    vector<int> rout;
    map<int,int> N;

    for(Route r : routes){
        rout.push_back(r.routeID);
        N[r.routeID] = config.busNumber;
    }

    pair<map<int, Bus>,map<int, Person>> index = loadData();;

    //cout << index.second.size() <<endl;

    //pair<map<int, Bus>,map<int, Person>> index_bak = make_pair(index.first,index.second);

    startTime = clock();//计时结束

    vector<int> re = proGreedy(index.first,index.second,N,rout);

    endTime = clock();//计时结束
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

    //cout<<"======"<<endl;

    cout<<getServiceNumber(index.first,index.second,re)<<endl;
}

int main(int argc, char *argv[]) {
//int main() {

    //indexGreedyTest();

    //partGreedyTest();

    //config.graph_alias = "nethept";
    for (int i = 0; i < argc; i++) {
        string help_str = ""
                          "BTS --algo <algo> [options]\n"
                          "BTS\n"
                          "\n"
                          "algo: \n"
                          "  topk\n"
                          "  fixint\n"
                          "  greedy\n"
                          "  progreedy\n"
                          "  partgreedy\n"
                          "  propartgreedy\n"
                          "  greedysel\n"
                          "  scoresel\n"
                          "  buildindex\n"
                          "options: \n"
                          "  --busNumber <BusNumber>\n"
                          "  --busMinNumber <busMinNumber>\n"
                          "  --personNumber <PersonNumber>\n"
                          "  --theta <theta>\n"
                          "  --epsilon <epsilon>\n"
                          "  --rho <rho>\n";

        if (string(argv[i]) == "--help") {
            cout << help_str << endl;
            exit(0);
        }
    }

    // init parameter first
    for (int i = 0; i < argc; i++) {
        string arg = argv[i];

        if (arg == "--algo") {
            config.algo = string(argv[i + 1]);
        }
        else if (arg == "--busNumber") {
            config.busNumber = atoi(argv[i + 1]);
        }
        else if (arg == "--pBusNumber") {
            config.pBusNumber = atoi(argv[i + 1]);
        }
        else if (arg == "--busMinNumber") {
            config.busMinNumber = atoi(argv[i + 1]);
        }
        else if (arg == "--personNumber") {
            config.person_number = atoi(argv[i + 1]);
        }
        else if (arg == "--theta") {
            config.theta = atoi(argv[i + 1]);
        }
        else if (arg == "--epsilon") {
            config.epsilon = atof(argv[i + 1]);
        }
        else if (arg == "--rho") {
            config.rho = atof(argv[i + 1]);
        }
        else if (arg.substr(0, 2) == "--") {
            cerr << "command not recognize " << arg << endl;
            exit(1);
        }
    }

    vector<string> possibleAlgo = {TOPK, FIXINT, GREEDY, ProGREEDY, PartGREEDY, ProPartGREEDY, BUILDINDEX, GREEDYSEL, SCORESEL};

    if (config.algo == GREEDY){

        indexGreedyTest();

    } else if(config.algo == ProGREEDY){

        proGreedyTest();

    } else if(config.algo == PartGREEDY){

        partGreedyTest();

    } else if(config.algo == ProPartGREEDY){

        proPartGreedyTest();

    } else if(config.algo == TOPK){

        topKTest();

    }else if(config.algo == FIXINT){

        fixIntTest();

    }else if(config.algo == BUILDINDEX){

        buildIndexTest();

    }else if(config.algo == GREEDYSEL){

        greedySelTest();

    }else if(config.algo == SCORESEL){

        scoreSelTest();

    }

    return 0;
}