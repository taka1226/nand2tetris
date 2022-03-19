#include "aaa.hpp"
#include <iostream>

// 引数なしのコンストラクタ
Student::Student()
{
	ID = 0;
	name = "";
}

// 引数ありのコンストラクタ
Student::Student(int i, string n)
{
	ID = i;
	name = n;
}

// デストラクタ
Student::~Student()
{
}

void Student::setStudent(int i, string n){
	ID = i;
	name = n;
}

int Student::getID(){
	return ID;
}

string Student::getName(){
	return name;
}

bool Student::operator==(const Student &s) const{
	return (ID == s.ID && name == s.name);
}

void Student::printInfo(){
	std::cout << ID << "番の学生は" << name << "\n";
}
