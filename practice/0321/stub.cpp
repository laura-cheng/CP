/**
This is a simple wrapper for communication with the manager.
DO NOT CHANGE THIS FILE!!!!!
**/

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <set>
#include <string>
#include <vector>
using namespace std;

// Functions to be implemented in the solution.
int predict(long long);

// Functions provided to the solution.
int history(int);
int get_experiment_type();
int get_a();
int get_b();

////////////////////////////////////////////////
namespace {  // Used in this file only.
void run();
FILE *fifo_in, *fifo_out;
void _send_msg(const string& msg);
void _send_msg(const string& msg, const int t);
int _recv_int();
long long _recv_longlong();
}  // namespace
////////////////////////////////////////////////

int main(int argc, char **argv) {
    
    // IF YOU WANT TO TEST LOCALLY ON YOUR COMPUTER,
    // 如果你想要在本地端測試你的程式，
    // COMMENT THESE TWO LINES AND UNCOMMENT THE TWO LINES BELOW.
    // 把下面這兩行註解起來，然後把更下面兩行打開，這樣就可以從命令列互動了。
//    fifo_in = fopen(argv[1], "r");
//    fifo_out = fopen(argv[2], "w");
     fifo_in = stdin;
     fifo_out = stdout;

    run();

    fclose(fifo_in);
    fclose(fifo_out);
    return 0;
}

////////////////////////////////////////////////
namespace {
void _send_msg(const string& msg) {
    fprintf(fifo_out, "%s\n", msg.c_str());
    fflush(fifo_out);
}
void _send_msg(const string& msg, const int t) {
    fprintf(fifo_out, "%s %d\n", msg.c_str(), t);
    fflush(fifo_out);
}

int _recv_int() {
    int val;
    int ret = fscanf(fifo_in, "%d", &val);
    // Receives error.
    if (val == -1 || ret != 1) {
        fclose(fifo_in);
        fclose(fifo_out);
        exit(0);
    }
    return val;
}

long long _recv_longlong() {
    long long val;
    int ret = fscanf(fifo_in, "%lld", &val);
    // Receives error.
    if (val == -1 || ret != 1) {
        fclose(fifo_in);
        fclose(fifo_out);
        exit(0);
    }
    return val;
}

void run() {
    int k = _recv_int();
    for (int i = 0; i < k; ++i) {
        long long t = _recv_longlong();
        int answer = predict(t);
        _send_msg("answer", answer);
    }
}
}  // namespace

int history(int t) {
    _send_msg("history", t);
    return _recv_int();
}

int get_experiment_type() {
    _send_msg("exp_type=?");
    return _recv_int();
}

int get_a() {
    _send_msg("a=?");
    return _recv_int();
}

int get_b() {
    _send_msg("b=?");
    return _recv_int();
}
