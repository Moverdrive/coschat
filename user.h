#pragma once
#include<string>
class User
{
	int _userID;//идентификатор, который определяет того, кто управляет чатом
	std::string Names[10]; //имена пользователей, у которых есть этот чат
	std::string Public[10];//сохранённые сообщения(последние 10 строк)
	std::string Private[10];//личные сообщения
public:
	User();
	User(int userID, std::string names[10]);
	std::string getUserName(int _userID);

	std::string writePublic(int _userID, std::string userWrite, std::string Public[10]);

	std::string savePublic(int _userID, std::string Public[10]);
};
