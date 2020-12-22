#include "Record.cpp"
#include <queue>
#include <cmath>
#include <iostream>

using namespace std;

typedef pair<string, double> pd;

class myComp {
    public:
    constexpr bool operator() (
        pd const& a,
        pd const& b
    ) const noexcept {
        return a.second > b.second;
    }
};

class KnnSequential {
    public:
    Record record_;
    KnnSequential(string filename) : record_{filename} {
        init();
    }

    KnnSequential(string filename, int N) : record_{filename} {
        init(N);
    }

    vector<Line> lines;
    void init() {
        lines = record_.load();
    }

    void init(int N) {
        lines = record_.load(N);
    }
    void print() {
        for(auto &i : lines) {
            cout << i.col[0] << " ";
        }
        cout << endl;
    }

    vector<string> nearest(int k, vector<string> array) {
        
        for(auto &line : lines) {
            pd point;
            point.first = line.col[0];
            double distance = euclidean(array, line.col);
            point.second = distance;
            pq.push(point);
        }

        for (size_t i = 0; i < k; i++)
        {
            pd point = pq.top();
            pq.pop();
            cout << point.first << endl;
        }
        
    }

    private:
    priority_queue<pd, vector<pd>, myComp> pq;

    double euclidean (vector<string> a, vector<string> b) {
        double total = 0;
        for (size_t i = 1; i <= 128; i++)
        {
            string num_a = a[i];
            total += pow((stod(num_a) - stod(b[i])), 2);
        }
        return sqrt(total);
    }
};