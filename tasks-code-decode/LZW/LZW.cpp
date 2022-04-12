#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;

void coding(string infilename, string outfilename) {
    ifstream in(infilename);
    ofstream out(outfilename);
    map<string, int> mp{ {"a", 0},{"b", 1},{"c", 2},{"d", 3},{" ", 4},{"#", 5} };
    string str = "";
    string buf = "";
    unsigned int code = -1;

    cout << "Encoded message:\n";
    while (!in.eof())
    {
        getline(in, str);
        //cout << str << endl;
        for (auto to : str) {
            buf += to;
            if (mp.find(buf) == mp.end()) {
                out << code << " ";
                cout << code << " ";
                mp[buf] = mp.size();
                buf = buf[buf.length() - 1];
            }
            code = mp[buf];
        }
    }
    out << code;
    cout << code << endl;
    
    /*for (auto to : mp) {
        cout << to.first << " " << to.second << endl;
    }*/
    in.close();
    mp.clear();
}

void decoding(string filename) {
    ifstream message(filename);
    vector <string> voc = { "a", "b", "c", "d", " ", "#"};
    map<string, int> mp{ {"a", 0},{"b", 1},{"c", 2},{"d", 3},{" ", 4},{"#", 5} };
    string buf = "";
    int code;
    cout << "Decocded message:\n";
    while (!message.eof()) {
        message >> code;
        if (code >= voc.size()) {
            buf += buf[0];
            if (mp.find(buf) == mp.end()) {
                mp[buf] = voc.size();
                voc.push_back(buf);
            }
        }else{
            buf += voc[code][0];
            if (mp.find(buf) == mp.end()) {
                mp[buf] = voc.size();
                voc.push_back(buf);
            }
            buf = voc[code];
        }
        cout << voc[code];
    }
    cout << endl;
    cout << "Substring---code\n";
    for (auto to : mp) {
        cout << to.first << "---" << to.second << endl;
    }

    message.close();
    voc.clear();
}

int main()
{
    coding("message.txt", "encoded_message.txt");
    cout << endl;
    decoding("encoded_message.txt");
}