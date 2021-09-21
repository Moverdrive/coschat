#include<iostream>
#include<string>
#include"user.h"
#include<fstream>

//регистрация пользователей
//сохранение логинов
using namespace std;
string logins[10];
string names[10];
string Public[10];//хранилище сообщений
int nameCount = 0;//общее количество пользователей
int main()
{
	setlocale(LC_ALL, "");
	//загружаем сохраненный файл с логинами
	ifstream fin;
	fin.open("login.txt");
	//переносим данные в переменную 'char login[100]'	
	char login[100];
	while (!fin.eof())
	{
		fin.getline(login, 100);
	}
	
	//закрываем файл
	fin.close();
	
	//загружаем файл с именами пользователей
	ifstream tam;
	tam.open("name.txt");
	//переносим данные в переменную 'char name[100]'	
	char name[100];
	while (!tam.eof())
	{
		tam.getline(name, 100);
	}
	tam.close();
	char pass[30];//рабочий массив для передачи строк
	
	int idUser = 0;
	int begin = 0;
	for (int y = 0; y < 30; ++y) { pass[y] = 0; }//обнулим рабочий массив
	//собираем логины в общий массив
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			if (login[j] - 48 == idUser)
			{
				++idUser;
				begin = j + 1;
				break;
			}
		}
		int p = 0;//дополнительный счётчик в цикле
		for (int k = begin; k < 30; ++k)
		{
			if (login[k] != idUser + 48)
			{
				pass[p] = login[k];
				++p;
			}
			else
			{
				break;
			}
		}
		logins[i] = pass;	
	}
	
	{
		int idUser = 0;
		int begin = 0;
		for (int y = 0; y < 30; ++y) { pass[y] = 0; }//обнулим рабочий массив
		//собираем имена в общий массив
		
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 200; ++j)
			{
				if (name[j] - 48 == idUser)
				{
					++idUser;
					begin = j + 1;
					break;
				}
			}
			int p = 0;//дополнительный счётчик в цикле
			for (int k = begin; k < 30; ++k)
			{
				if (name[k] != idUser + 48)
				{
					pass[p] = name[k];
					++p;
				}
				else
				{
					break;
				}
			}
			names[i] = pass;
			nameCount = idUser;//получим общее количество пользователей
		}
	}
	//создаём имена для файлов с личными сообщениями
	string fail[10];
	for (int i = 0; i < idUser + 1; ++i)
	{
		fail[i] = names[i] + ".txt";
	}
	do {
		std::cout << "Добро пожаловать!                                   (exit = выход)\n";
		std::cout << "1 - вход в чат, \n"
					 "0 - регистрация\n" << "> ";
		std::cin >> pass;
		int alpha = 0;
		bool add = false;//условие, при котором добавляется НОВЫЙ логин
		ofstream fout;
		switch (pass[0])
		{
		case '1':
			cout << "Для входа введите логин" << endl;
			cin >> pass;
			for (int i = 0; i < 10; ++i)
			{
				if (pass == logins[i])
				{
					idUser = i;
					break;
				}
				else
				{
					continue;
				}
			}
			while (pass[0] != '0')
			{
				User big(idUser, names);//здесь должен начинаться вход в чат

					std::cout << "Вы вошли в чат" << endl << "Управление: 1 - список пользователей,\n"
						"	    2 - написать в общем чате,\n"
						"	    3 - написать личное сообщение пользователю,\n"
						"	    4 - смотреть входящие сообщения, \n"
						"	    0 - главное меню" << endl;
					std::cin >> pass; //ожидание ввода оператора

				string Mes;//сообщение пользователя в чате
				int person = -1;//указатель на пользователя(если нет такого - ошибка)
				ifstream chat;
				switch (pass[0])
				{
				case('1'):
					for (int i = 0; i < nameCount; ++i)
					{
						std::cout << (i + 1) << ". " << big.getUserName(i) << endl;
					}
					break;
				case '2':
					//открываем предыдущие сообщения
					cout << "sand - отправить сообщение\n esc - отменить сообщение\n";
					chat.open("public-chat.txt", ios::in);
					char ch;
					while (chat.get(ch))
					{
						std::cout << ch;
					}
					chat.close();
					std::cout << big.getUserName(idUser) << '>';
					for (int i = 0; i < 10; ++i)
					{
						string meaw;
						std::cin >> meaw;
						if (meaw == "sand")
						{
							break;
						}
						else if (meaw == "esc")
						{
							Mes = "1";
							break;
						}
						else
						{
							Mes += meaw + ' ';
						}
					}
					if (Mes != "1")
					{
						std::cout << big.writePublic(idUser, Mes, Public);
						big.savePublic(idUser, Public);
						//упаковка в файл
						fout.open("public-chat.txt", ios::app);
						for (int i = 0; i < 10; ++i)
						{
							fout << Public[i];
						}
						fout.close();
					}
					else
					{
						cout << "Сообщение отменено" << endl;
					}
					break;
				case('3'):
					std::cout << "Напишите, кому хотите отправить сообщение" << endl;
					std::cin >> Mes;
					cout << "sand - отправить сообщение\n esc - отменить сообщение\n";
					for (int i = 0; i < nameCount; ++i)
					{
						if (Mes == names[i])
						{
							Mes = "";
							person = i;
							std::cout << "Пишите сообщение:" << endl;
							for (int i = 0; i < 10; ++i)
							{
								string meaw;
								std::cin >> meaw;
								if (meaw == "sand")
								{
									break;
								}
								else if (meaw == "esc")
								{
									Mes = "1";
									break;
								}
								else
								{
									Mes += meaw + ' ';
								}
							}
							if (Mes != "1")
							{
								std::cout << big.writePublic(idUser, Mes, Public);
								big.savePublic(idUser, Public);
								//упаковка в файл
								fout.open(fail[person], ios::app);
								for (int i = 0; i < 10; ++i)
								{
									fout << Public[i];
								}
								fout.close();
							}
							else
							{
								cout << "Сообщение отменено" << endl;
							}
							break;
						}
						else
						{
							continue;
						}
					}
					break;
				case '4':
					//открываем предыдущие сообщения

					chat.open(fail[idUser], ios::in);

					while (chat.get(ch))
					{
						std::cout << ch;
					}
					chat.close();
					break;
				case '0':
					cout << big.getUserName(idUser) << " покинул чат" << endl;
				default:
					
					break;
				}
			}
			break;
		case '0':
			std::cout << "Начинается регистрация нового пользователя." << endl << "Введите новый логин" << endl;
			char reg[30];
			for (int y = 0; y < 30; ++y) { reg[y] = 0; }//обнулим рабочий массив
			std::cin >> reg;
			for (int i = 0; i < idUser + 1; ++i)
			{
				if (reg == logins[i])
				{
					std::cout << "Такой логин уже существует!" << endl;
					add = false;
					break;
				}
				else
				{
					add = true;
					++alpha;
					continue;
				}
			}
			if (alpha == idUser || add)
			{
				logins[idUser] = reg;
			}
			if (add)
			{
				std::cout << "Как Вас зовут?" << endl;//проверка уникальности
				std::cin >> names[idUser];
			}
			//упаковка в файл
			fout.open("login.txt");
			for (int i = 0; i < idUser + add; ++i)
			{
				if (i <= idUser)
				{
					fout << i;
				}
				fout << logins[i];
			}
			fout.close();
			fout.open("name.txt");

			for (int i = 0; i < idUser + add; ++i)
			{
				if (i <= idUser)
				{
					fout << i;
				}
				fout << names[i];
			}
			fout.close();
			break;
		default:
			break;
		}
	}while (pass[0] != 'e');
}
