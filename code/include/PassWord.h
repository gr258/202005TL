#include <string>
#include <algorithm>
using namespace std;

class PassWord{
public:
	int Strong(string s);
private:
	void clear();
	void Scan(string &s);
	int hasType_uppercase;
	int hasType_lowercase;
	int hasType_digital;
	int need_replace;
	int remainder[3];
	int nLen;
};