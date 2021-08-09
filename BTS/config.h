//
// Created by 莫松松 on 2019/11/15.
//

#ifndef BTS_CONFIG_H
#define BTS_CONFIG_H

#include <string>

using namespace std;

const string FIXINT = "fixint";
const string TOPK = "topk";
const string GREEDY = "greedy";
const string ProGREEDY = "progreedy";
const string PartGREEDY = "partgreedy";
const string ProPartGREEDY = "propartgreedy";
const string GREEDYSEL = "greedysel";
const string SCORESEL = "scoresel";
const string BUILDINDEX = "buildindex";


class Config {
public:
    //string graph_alias;
    //string graph_location;
    string algo;
    int busNumber = 30;
    int pBusNumber = 60;
    int busMinNumber = 30;
    int person_number = 300000;
    int theta = 180; //sec
    float epsilon = 0.01;
    float rho = 0.2;
    double lambda = 0.2;
};

Config config;

#endif //BTS_CONFIG_H
