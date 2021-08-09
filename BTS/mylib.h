//
// Created by 莫松松 on 2019/11/15.
//

#ifndef BTS_MYLIB_H
#define BTS_MYLIB_H
#include <string>
#include <cstdio>
#include <iostream>
#include <deque>

using namespace std;

#define FOR(i, n) for(int (i)=0; (i)<((int)(n)); (i)++)

string __n_variable(string t, int n);

#define __expand_nv(x) __n_variable(t, x)<< t##x << " "

template<class T0>
void ___debug(string t, T0 t0, ostream &os) {
    os << __expand_nv(0);
}

template<class T0, class T1>
void ___debug(string t, T0 t0, T1 t1, ostream &os) {
    os << __expand_nv(0) << __expand_nv(1);
}

template<class T0, class T1, class T2>
void ___debug(string t, T0 t0, T1 t1, T2 t2, ostream &os) {
    os << __expand_nv(0) << __expand_nv(1) << __expand_nv(2);
}

template<class T0, class T1, class T2, class T3>
void ___debug(string t, T0 t0, T1 t1, T2 t2, T3 t3, ostream &os) {
    os << __expand_nv(0) << __expand_nv(1) << __expand_nv(2) << __expand_nv(3);
}

template<class T0, class T1, class T2, class T3, class T4>
void ___debug(string t, T0 t0, T1 t1, T2 t2, T3 t3, T4 t4, ostream &os) {
    os << __expand_nv(0) << __expand_nv(1) << __expand_nv(2) << __expand_nv(3) << __expand_nv(4);
}

template<class T0>
void ___debug(string t, deque<T0> t0, ostream &os) {
    os << __n_variable(t, 0);
    FOR(i, SIZE(t0))os << t0[i] << " ";
}

template<class T0>
void ___debug(string t, vector<T0> t0, ostream &os) {
    os << __n_variable(t, 0);
    FOR(i, SIZE(t0))os << t0[i] << " ";
}

template<class T0, class T1>
void ___debug(string t, vector<pair<T0, T1> > t0, ostream &os) {
    os << __n_variable(t, 0);
    FOR(i, SIZE(t0))os << t0[i].F << "," << t0[i].S << " ";
}

#define ASSERT(v) {if (!(v)) {cerr<<"ASSERT FAIL @ "<<__FILE__<<":"<<__LINE__<<endl; exit(1);}}
#define INFO(...) do {\
     ___debug( #__VA_ARGS__,  __VA_ARGS__,cout); cout<<endl; \
    } while(0)
#define ASSERTT(v, ...) {if (!(v)) {cerr<<"ASSERT FAIL @ "<<__FILE__<<":"<<__LINE__<<endl; INFO(__VA_ARGS__); exit(1);}}

using namespace std;

static void program_start(int argc, char **argv) {

    cout << "--------------start------------" << endl;
    string combine = "";
    for (int i = 1; i < argc; i++) {
        combine += argv[i];
        combine += " ";
    }
    cout << "args:" << combine << endl;
}

static void program_stop() {
    cout << "--------------stop------------" << endl;
    cout << endl;
    cout << endl;
    cout << endl;

}

#endif //BTS_MYLIB_H
