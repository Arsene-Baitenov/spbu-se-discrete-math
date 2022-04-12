#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

map<string, string> code_dict;

struct node {
    int val;
    node* left, * right;
    string payload;
};

node* new_node(string payload, int val) {
    node* ptr = new node();
    if (ptr == NULL) {
        cout << "Error: not enought memory";
        return NULL;
    }
    ptr->payload = payload;
    ptr->val = val;
    ptr->left = NULL;
    ptr->right = NULL;
    return ptr;
}

void coding(node* ptr, string code) {
    if (ptr->payload == "") {
        coding(ptr->left, code + "0");
        ptr->left = NULL;
        coding(ptr->right, code + "1");
        ptr->right = NULL;
    }
    else {
        cout << ptr->payload << " " << code << endl;
        code_dict[ptr->payload] = code;
        free(ptr);
    }
}

bool cmp(node*& a, node*& b) {
    return (a->val > b->val);
}

int main()
{
    int blocklen = 1;
    string message = "abcbbbbbacabbacddacdbbaccbbadadaddd abcccccbacabbacbbaddbdaccbbddadadcc bcabbcdabacbbacbbddcbbaccbbdbdadaac#";
    vector<int> p;

    map<string, int> alphabet;

    for (int counter = 0; counter < message.length(); counter += blocklen) {
        string block = message.substr(counter, blocklen);
        if (alphabet.find(block) != alphabet.end()) {
            ++p[alphabet[block]];
        }
        else {
            p.push_back(1);
            alphabet[block] = p.size() - 1;
        }
    }
    vector<node*> v;
    for (auto to : alphabet) {
        v.push_back(new_node(to.first, p[to.second]));
    }

    while (v.size() > 1) {
        sort(v.begin(), v.end(), cmp);
        node* ptr = new_node("", v[v.size() - 2]->val + v[v.size() - 1]->val);
        ptr->left = v[v.size() - 2];
        ptr->right = v[v.size() - 1];
        v.pop_back();
        v.pop_back();
        v.push_back(ptr);
    }

    coding(v[0], "");

    string encoded_message = "";
    for (int counter = 0; counter < message.length(); counter += blocklen) {
        string block = message.substr(counter, blocklen);
        encoded_message += code_dict[block];
    }
    cout << encoded_message << endl;

    double H = 0, average_len = 0;
    for (auto to : alphabet) {
        H -= (double)p[to.second] * log2((double)p[to.second] / (message.length() / blocklen));
        average_len += (double)code_dict[to.first].length() * p[to.second];
    }
    average_len /= (message.length() / blocklen);
    cout << fixed << setprecision(7);
    cout << "Specific entropy: " << H / (message.length() / blocklen) << " Total entropy: " << H << endl;
    cout << "Average code length: " << average_len << endl;
    cout << "Code redundancy: " << 1 - (H / encoded_message.length()) << endl;
}