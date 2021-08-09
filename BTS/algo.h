//
// Created by 莫松松 on 2019/11/15.
//

#ifndef BTS_ALGO_H
#define BTS_ALGO_H

#include "load_data.h"
#include <set>


bool comp(pair<int, Bus> &o1,pair<int, Bus> &o2){
    return o1.second < o2.second;
}

bool comp2(pair<int, Bus> &o1,pair<int, Bus> &o2){
    return o1.second.influence > o2.second.influence;
}

bool comp3(pair<int, Bus> &o1,pair<int, Bus> &o2){
    return o1.second.score < o2.second.score;
}


bool comp4(PBus &o1,PBus &o2){
    return o1.arriveTime > o2.arriveTime;
}


//class compare{
//public:
//    bool operator()(pair<string, Bus> o1,pair<string, Bus> o2){
//        return o1.second.influence < o2.second.influence;
//    }
//};
//bool compare(pair<string, Bus> o1,pair<string, Bus> o2){
//    return o1.second.influence > o2.second.influence;
//}

int getServiceNumber(map<int, Bus> bus, map<int, Person>  person, vector<int> buses){

    int inf = 0;

    for(int i : buses){

        Bus b = bus[i];

        for(int j : b.persons) {

            if (!person[j].influenced) {
                person[j].influenced = true;

            }
        }

    }

    for (auto it = person.begin(); it != person.end(); ++it) {
        if(it->second.influenced)
            inf++;
    }

    return inf;

}

int getServiceNumber2(vector<map<int, Bus>> bus, vector<map<int, Person>>  person, vector<vector<int>> buses){

    int inf = 0;

    auto it1 = bus.begin();
    auto it2 = person.begin();
    auto it3 = buses.begin();


    for (; it1 != bus.end(); it1++, it2++, it3++)
    {
        for(int i : (*it3)){

            Bus b = (*it1)[i];

            for(int j : b.persons) {
                (*it2)[j].influenced = true;
            }
        }
    }

    for (auto it = person.begin(); it != person.end(); ++it) {
        for(int i =0; i< (*it).size(); i++){
            if((*it)[i].influenced)
                inf++;
        }
    }

    return inf;

}

vector<int> GreedySel(map<int, Bus> bus, map<int, Person>  person, map<int, int> N, map<int, Terminal>  terminal){

    map<int, Terminal>::iterator iter;
    int PbusID = 0;
    int n=0;
    for(iter = terminal.begin(); iter != terminal.end(); iter++){
        n += N[iter->first];
        for(int i=0;i<N[iter->first];i++){
            PbusID++;
            PBus pb;
            pb.terminalID=iter->first;
            pb.arriveTime=18000; //5:00:00
            pb.PbusID = PbusID;
            iter->second.Pbuses.push_back(pb);
        }
    }

    vector<int> result;

    int preR=0,preN=0;

    while(n>0){

        //cout<<result.size()<<endl;

        //cout<<"n = "<<n<<endl;

        if(n==preN&&result.size()==preR){
            break;
        }

        preN=n;
        preR=result.size();

        if(bus.size() <= 0){
            break;
        }

        vector< pair<int, Bus> > temp(bus.begin(),bus.end());
        sort(temp.begin(),temp.end(),comp);

        for(int i=temp.size()-1;i>=0;i--){
            Bus b = temp[i].second;
            if(b.influence==0){
                break;
            }
            if(terminal[b.St].Pbuses.size()==0){
                continue;
            }
            int pos = -1;
            int maxtime = 10000;
            for(int j=0;j<terminal[b.St].Pbuses.size();j++){
                //cout<<j<<endl;
                if(maxtime<terminal[b.St].Pbuses[j].arriveTime&&terminal[b.St].Pbuses[j].arriveTime<=b.time){
                    pos = j;
                    maxtime = terminal[b.St].Pbuses[j].arriveTime;
                }
            }

            if(pos>=0){
                result.push_back(b.busID);
                bus.erase(temp[i].first);
                for(int j : b.persons) {

                    if (!person[j].influenced) {
                        person[j].influenced = true;
                        for (int k : person[j].buses) {
                            bus[k].influence--;
                        }

                    }
                }

                PBus pbus = terminal[b.St].Pbuses[pos];
                terminal[b.St].Pbuses.erase(terminal[b.St].Pbuses.begin()+pos);
                n--;
                pbus.terminalID=b.Et;
                pbus.arriveTime += (b.time+b.T);
                if(pbus.arriveTime<86400){
                    terminal[b.Et].Pbuses.push_back(pbus);
                    n++;
                }

                break;
            }
        }
    }

    return result;

}


double computeScore(Bus b, vector<PBus> Pbuses, double lambuda, int timeMax, int influenceMax){

    if(Pbuses.size()==0){
        return 0;
    }else {
        int maxtime = -1;
        for (int j = 0; j < Pbuses.size(); j++) {
            if (Pbuses[j].arriveTime <= b.time) {
                maxtime = Pbuses[j].arriveTime;
                break;
            }
        }

        if(maxtime==-1){
            return 0;
        }

        return lambuda - lambuda * (b.time - maxtime) / (timeMax) +
               (1 - lambuda) * b.influence / influenceMax;
    }
}

vector<int> ScoreSel(map<int, Bus> bus, map<int, Person>  person, map<int, int> N, map<int, Terminal>  terminal, double lambuda){

    map<int, Terminal>::iterator iter;
    int PbusID = 0;
    int n=0;
    for(iter = terminal.begin(); iter != terminal.end(); iter++){
        n += N[iter->first];
        for(int i=0;i<N[iter->first];i++){
            PbusID++;
            PBus pb;
            pb.terminalID=iter->first;
            pb.arriveTime=18000; //5:00:00
            pb.PbusID = PbusID;
            iter->second.Pbuses.push_back(pb);
        }
    }

    vector< pair<int, Bus> > temp(bus.begin(),bus.end());
    sort(temp.begin(),temp.end(),comp);

    int influenceMax = temp.back().second.influence;

    map<int, Bus>::iterator iterb;
    for(iterb = bus.begin(); iterb != bus.end(); iterb++){

        iterb->second.score = lambuda - lambuda * (iterb->second.time - 18000) / (19*60*60) + (1 - lambuda) * iterb->second.influence / influenceMax;

    }

    vector<int> result;

    int preR=0,preN=0;

    while(n>0){

        //cout<<result.size()<<endl;

        //cout<<"n = "<<n<<endl;

        if(n==preN&&result.size()==preR){
            break;
        }

        preN=n;
        preR=result.size();

        if(bus.size() <= 0){
            break;
        }

        vector< pair<int, Bus> > temp(bus.begin(),bus.end());
        sort(temp.begin(),temp.end(),comp3);

        for(int i=temp.size()-1;i>=0;i--){
            Bus b = temp[i].second;
            if(b.score==0){
                break;
            }
            if(terminal[b.St].Pbuses.size()==0){
                continue;
            }
            int pos = -1;
            int maxtime = 10000;
            for(int j=0;j<terminal[b.St].Pbuses.size();j++){
                //cout<<j<<endl;
                if(maxtime<terminal[b.St].Pbuses[j].arriveTime&&terminal[b.St].Pbuses[j].arriveTime<=b.time){
                    pos = j;
                    maxtime = terminal[b.St].Pbuses[j].arriveTime;
                }
            }

            if(pos>=0){
                result.push_back(b.busID);
                bus.erase(temp[i].first);
                for(int j : b.persons) { //update influence

                    if (!person[j].influenced) {
                        person[j].influenced = true;
                        for (int k : person[j].buses) {
                            bus[k].influence--;
                        }

                    }
                }

                PBus pbus = terminal[b.St].Pbuses[pos];
                terminal[b.St].Pbuses.erase(terminal[b.St].Pbuses.begin()+pos);
                n--;

                sort(terminal[b.St].Pbuses.begin(),terminal[b.St].Pbuses.end(),comp4);

                for(int bu:terminal[b.St].bus){//update score

                    //cout<<bu<<endl;
                    bus[bu].score = computeScore(bus[bu], terminal[b.St].Pbuses, lambuda, 19*60*60, influenceMax);

                }

                pbus.terminalID=b.Et;
                pbus.arriveTime += (b.time+b.T);
                if(pbus.arriveTime<86400){
                    terminal[b.Et].Pbuses.push_back(pbus);
                    n++;
                    sort(terminal[b.Et].Pbuses.begin(),terminal[b.Et].Pbuses.end(),comp4);
                    for(int bu:terminal[b.Et].bus){ //update score

                        bus[bu].score = computeScore(bus[bu], terminal[b.Et].Pbuses, lambuda, 19*60*60, influenceMax);

                    }
                }

                break;
            }
        }
    }

    return result;

}


vector<int> indexGreedy(map<int, Bus> bus, map<int, Person>  person, map<int, int> N, vector<int> route){

    int n = 0;
    map<int,int> tn;
    for(int r : route){
        n += N[r];
        tn[r] = 0;
    }

    vector<int> result;

    for(int i = 0; i < n; i++){

        cout<<result.size()<<endl;

        if(bus.size() <= 0){
            break;
        }

        vector< pair<int, Bus> > temp(bus.begin(),bus.end());
        sort(temp.begin(),temp.end(),comp);

        Bus b = temp.back().second;
        int t = temp.back().first;
        temp.pop_back();

        if(b.influence == 0)
            break;

        result.push_back(b.busID);

        bus.erase(t);

        for(int j : b.persons) {

            if (!person[j].influenced) {
                person[j].influenced = true;
                for (int k : person[j].buses) {
                    bus[k].influence--;
                }

            }
        }

        ++tn[b.routeID];

        if(tn[b.routeID] >= N[b.routeID]){
            auto iter = bus.begin();
            while (iter != bus.end()) {
                if (iter->second.routeID == b.routeID) {
                    iter = bus.erase(iter);
                }
                else {
                    ++iter;
                }
            }
        }

    }

    return result;

}

vector<int> topK(map<int, Bus> bus, map<int, Person>  person, map<int, int> N, vector<int> route){

    map<int,int> tn;
    for(int r : route){
        tn[r] = 0;
    }

    vector<int> result;

    vector< pair<int, Bus> > temp(bus.begin(),bus.end());
    sort(temp.begin(),temp.end(),comp2);

    for(auto it = temp.begin(); it!= temp.end(); it++){

        if(tn[it->second.routeID] < N[it->second.routeID]){
            result.push_back(it->second.busID);
            ++tn[it->second.routeID];
        }

    }

    return result;

}

vector<int> fixInt(map<int, Bus> bus, map<int, Person>  person, map<int, int> N, vector<int> route){

    map<int,int> fixint;
    vector<int> tn(N.size());
    for(int r : route){
        fixint[r] = 19*60/N[r];
        tn[r] = 0;
    }

    int startTime = (5*60+30)*60;

    vector<int> result;

    for(auto it = bus.begin(); it!= bus.end(); it++){

        if((it->second.time-startTime)%fixint[it->second.routeID]==0 and tn[it->second.routeID] < N[it->second.routeID]){
            result.push_back(it->second.busID);
            ++tn[it->second.routeID];
        }

    }

    return result;

}

vector<int> proGreedy(map<int, Bus> bus, map<int, Person>  person, map<int,int> N, vector<int> route){

    int n = 0;
    for(int r : route){
        n += N[r];
    }

    vector<int> tn(N.size());
    vector<int> result;

    vector< pair<int, Bus> > temp(bus.begin(),bus.end());
    sort(temp.begin(),temp.end(),comp2);

    double h = temp.front().second.influence;

    while(result.size() < n){

        for(auto it2 = temp.begin(); it2 != temp.end();){

            if(result.size() < n){
                Bus b = bus[it2->first];

                if(b.influence >= h and tn[b.routeID] < N[b.routeID]){
                    result.push_back(b.busID);

                    cout<<result.size()<<endl;

                    ++tn[b.routeID];

                    //cout<<result.size()<<" "<<b.busID<<" "<<b.influence<<endl;

                    if(it2 != temp.end())
                        it2 = temp.erase(it2);

                    for(int j : b.persons){

                        if(!person[j].influenced){
                            person[j].influenced = true;
                            for(int k : person[j].buses){
                                bus[k].influence--;
                            }

                        }

                    }

                } else {
                    it2 ++;
                }

                if(b.persons.size() < h)
                    break;

            } else{
                break;
            }

        }

        if(h < 1)
            break;

        h /= (double)(1+config.epsilon);


    }

    return result;

}

vector<vector<int>> partGreedy(vector<map<int, Bus>> busSet, vector<map<int, Person>>  person,map<int, int> N, vector<vector<int>> routeSet){

    vector<vector<int>> result;
    auto it1 = busSet.begin();
    auto it2 = person.begin();
    auto it3 = routeSet.begin();

    //cout<<(*it3)[0]<<endl;

    for (; it1 != busSet.end(); it1++, it2++, it3++)
    {
        vector<int> tmp = indexGreedy(*it1, *it2, N, *it3);
        //cout<<tmp.size()<<endl;
        result.push_back(tmp);
    }

    return result;


}

vector<vector<int>> proPartGreedy(vector<map<int, Bus>> busSet, vector<map<int, Person>>  person,map<int, int> N, vector<vector<int>> routeSet){

    vector<vector<int>> result;
    auto it1 = busSet.begin();
    auto it2 = person.begin();
    auto it3 = routeSet.begin();

    //cout<<(*it3)[0]<<endl;

    for (; it1 != busSet.end(); it1++, it2++, it3++)
    {
        vector<int> tmp = proGreedy(*it1, *it2, N, *it3);
        //cout<<tmp.size()<<endl;
        result.push_back(tmp);
    }

    return result;


 }

vector<Cluster> partition3(vector<int> Routes,map<int, Bus> bus, map<int, Person> person, const int Nmin, float Rho_max){

    map<int,set<int>> Overlaps;

    map<int,int> N;

    vector<Cluster> Clusters;

    int count = 0;

    Cluster cluster;

    for(int r : Routes){ //Divide clusters by line

        count++;

        N[r] = Nmin;

        cluster.id = r;

        cluster.routes.push_back(r);

        for(auto & bu : bus){
            if(bu.second.routeID == r)
                cluster.busSet[bu.second.busID] = bu.second;
        }
        for(auto & it : person){
            if(find(it.second.routes, r)>-1)
                cluster.personSet[r] = it.second;
        }

        if(count%30==0 or Routes.size() == count){
            Clusters.push_back(cluster);
            cluster.clear();
        }
    }

    for(auto & it : person) {

        for(int i = 0; i< it.second.routes.size()-1; i++){
            for(int j=i+1; j<it.second.routes.size();j++){
                int r1 = it.second.routes[i];
                int r2 = it.second.routes[j];
                if(r1 != r2){
                    int key = r1*r1 + r2*r2;

                    auto iter = Overlaps.find(key);
                    if(iter != Overlaps.end()){
                        iter->second.insert(it.second.personID);
                    } else{
                        set<int> tmp;
                        tmp.insert(it.second.personID);
                        Overlaps[key] = tmp;
                    }
                }

            }
        }
    }



    for(auto & it : Clusters){ // compute F_min and rho for each cluster
        vector<int> re = indexGreedy(it.busSet,it.personSet,N,it.routes);
        it.Fmin = getServiceNumber(it.busSet,it.personSet,re);
        for(int i = 0; i < Routes.size(); i++){
            it.overlap.insert(Overlaps[it.id*it.id+i*i].begin(),Overlaps[it.id*it.id+i*i].end());
        }
        it.rho = (double)it.overlap.size()/it.Fmin;
    }

    sort(Clusters.begin(),Clusters.end(),compare2());

    Cluster Cmax = Clusters.back();
    Clusters.pop_back();

    while(Cmax.rho > Rho_max) {

        cout<< Clusters.size()<<" "<<Cmax.rho<<endl;

        Cluster Omax = Clusters.back();
        for (auto &it : Clusters) {
            if (Overlaps[Cmax.id^2+Omax.id^2] < Overlaps[Cmax.id^2+it.id^2]) {
                Omax = it;
            }
        }

        //merge Cmax and Omax
        int count = Cmax.Fmin + Omax.Fmin - Overlaps[Cmax.id^2+Omax.id^2].size();
        if(count<Cmax.Fmin)
            count = Cmax.Fmin;
        if(count<Omax.Fmin)
            count=Omax.Fmin;
        Cmax.Fmin = count;

        Cmax.routes.insert(Cmax.routes.end(),Omax.routes.begin(),Omax.routes.end());
        Cmax.personSet.insert(Omax.personSet.begin(),Omax.personSet.end());
        Cmax.busSet.insert(Omax.busSet.begin(),Omax.busSet.end());

        Cmax.overlap.clear();

        for (int i = 0; i < Routes.size(); i++) {

            Overlaps[i^2+Cmax.id^2].insert(Overlaps[i^2+Omax.id^2].begin(), Overlaps[i^2+Omax.id^2].end());
            Cmax.overlap.insert(Overlaps[Cmax.id*Cmax.id+i*i].begin(),Overlaps[Cmax.id*Cmax.id+i*i].end());
            Overlaps.erase(i^2+Omax.id^2);
        }

        Cmax.rho = (double) Cmax.overlap.size() / Cmax.Fmin;


        for (auto it = Clusters.begin(); it != Clusters.end();) {
            if (it->id == Omax.id) {
                it = Clusters.erase(it);
            } else {
                ++it;
            }
        }

        Clusters.push_back(Cmax);

        sort(Clusters.begin(), Clusters.end(), compare2());

        Cmax = Clusters.back();
        Clusters.pop_back();
    }


    return Clusters;


}

#endif //BTS_ALGO_H
