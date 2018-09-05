#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class Small {
public:
  int count;
  vector<string> stringVector;
  Small(int count) { this->count = count; }

  void genPosibleComninations() {
    queue<string> q;
    q.push("9");
    while (count--) {
      string s1 = q.front();
      q.pop();
      stringVector.push_back(s1);
      string s2 = s1;
      q.push(s1.append("0"));
      q.push(s2.append("9"));
    }
  }

  string findLeastMultiple(int number) {
    for (int i = 0; i < stringVector.size(); i++)
      if (stoi(stringVector[i]) % number == 0)
        return stringVector[i];
    return "No\n";
  }
};

int main() {
  int testCases, number;
  ifstream in;
  ofstream out;
  in.open("least-input");
  out.open("list-output");
  in >> testCases;
  Small s(100000);
  s.genPosibleComninations();
  while (testCases--) {
    in >> number;
    if (number > 1000000) {
      out << "Bad Input\n";
      continue;
    }
    out << s.findLeastMultiple(number) << endl;
  }
  return 0;
}
