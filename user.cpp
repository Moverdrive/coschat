#include "user.h"
#include<iostream>
#include<string>
using namespace std;
User::User() {}

User::User(int userID, string names[10]) : _userID(userID)
{
	for (int i = 0; i < 10; ++i)
	{
		Names[i] = names[i];
	}
}
string User::getUserName(int _userID)
{
	return Names[_userID];
}
string User::writePublic(int _userID, string userWrite,	string Public[10])
{
	string massage = this->getUserName(_userID) + "::" + userWrite + "\n";
	Public[_userID] = massage;
	return massage;
}

string User::savePublic(int _userID, string Public[10])
{
	return Public[_userID];
}
