#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class PassWord{
public:
	int Strong(string s);
	vector<int> Get_MS_N(string sJson);
private:
	void Scan(string s);
	int hasType_uppercase;
	int hasType_lowercase;
	int hasType_digital;
	int need_replace;
	int remainder[3];
	int nLen;
};