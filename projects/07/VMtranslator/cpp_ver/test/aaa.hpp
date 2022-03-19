#include <string>
using namespace std;

class Student {
private:
    int ID;
    string name;
public:
	Student(); // 引数なしのコンストラクタ
	Student(int i, string n); // 引数つきのコンストラクタ
	~Student();

	void setStudent(int i, string n);

	int getID();
	string getName();

	bool operator==(const Student& s) const; // 「等しい」ことの定義

	void printInfo();
};
