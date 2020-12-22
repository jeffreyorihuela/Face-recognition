#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Line {
    public:
    vector<string> col;
};

class Record {
    public:
    Record(string filename_) : filename(filename_) {}

    vector<Line> load() {
        vector<Line> lines;
        fstream file;
        file.open(filename, ios::in | ios::out);
        string line;
        while(file) {
            getline(file, line);
            if(line.size() < 2) break;
            vector<string> tokens = split(line, ",");
            Line line_;
            for (auto &i: tokens) {
                line_.col.push_back(i);
            }
            lines.push_back(line_);
        }
        file.close();
        return lines;
    }

    vector<Line> load(int i) {
        vector<Line> lines;
        fstream file;
        file.open(filename, ios::in | ios::out);
        string line;
        int count = 0;
        while(file) {
            if(count < i) {
                getline(file, line);
                if(line.size() < 2) break;
                vector<string> tokens = split(line, ",");
                Line line_;
                for (auto &i: tokens) {
                    line_.col.push_back(i);
                }
                lines.push_back(line_);
            } else {
                break;
            }
            count++;

        }   
        file.close();
        return lines;
    }

    vector<string> readLine(int i) {
        fstream file;
        file.open(filename, ios::in | ios::out);
        string line;
        int raw = 0;
        while(file) {
            getline(file, line);
            if (raw == i) {
                vector<string> tokens = split(line, ",");
                return tokens;
            }
            raw++;
        }
    }

    private:
    string filename;
    vector<string> split (string s, string delimeter) {
        vector<string> tokens;
        string token;
        size_t pos=0;
        while((pos = s.find(delimeter)) != string::npos) {
            token = s.substr(0, pos);
            tokens.push_back(token);
            s.erase(0, pos+delimeter.length());
        }
        tokens.push_back(s);
        return tokens;
    }
};