#include <iostream>
#include <thread>
#include <latch>
#include <syncstream>
#include <vector>

using namespace std;


void f(char x, int i) {
    osyncstream out(cout);
    out << "from set " << x << " did action " << i << ".\n";
}


constexpr int A = 8;
constexpr int B = 5;
constexpr int C = 5;
constexpr int D = 5;
constexpr int E = 5;
constexpr int F = 7;
constexpr int G = 4;
constexpr int H = 4;
constexpr int I = 5;
constexpr int J = 9;

int main() {
    {
        osyncstream out(cout);
        out << "calc start.\n";
    }

    
    latch done_a(1);
    latch done_bc(1);
    latch done_d(1);

    
    thread t1([&]() {
        for (int i = 1; i <= A; ++i)
            f('a', i);
        done_a.count_down();

        done_a.wait();
        for (int i = 1; i <= E; ++i)
            f('e', i);
        });

   
    thread t2([&]() {
        for (int i = 1; i <= B; ++i)
            f('b', i);
        done_bc.count_down(); 

        done_bc.wait();
        for (int i = 1; i <= G; ++i)
            f('g', i);
        });

    
    thread t3([&]() {
        for (int i = 1; i <= C; ++i)
            f('c', i);
        done_bc.count_down(); 

        done_bc.wait();
        for (int i = 1; i <= H; ++i)
            f('h', i);
        });

   
    thread t4([&]() {
        for (int i = 1; i <= D; ++i)
            f('d', i);
        done_d.count_down();

        done_d.wait();
        for (int i = 1; i <= I; ++i)
            f('i', i);
        });

    
    thread t5([&]() {
        done_a.wait();
        for (int i = 1; i <= F; ++i)
            f('f', i);

        done_d.wait();
        for (int i = 1; i <= J; ++i)
            f('j', i);
        });

    
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    {
        osyncstream out(cout);
        out << "Calc end.\n";
    }

    return 0;
}