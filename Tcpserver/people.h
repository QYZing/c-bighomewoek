#ifndef PEOPLE_H
#define PEOPLE_H

#include<iostream>
#include<string>
using namespace std;
class people
{
public:
    people();
    string name;//昵称
    string ID;//账号
    string pin;//密码
    people(const people &p);
    people operator=(people &p);
};

#endif // PEOPLE_H
