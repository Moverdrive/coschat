#include<iostream>
#include<string>
#include"user.h"
#include<fstream>

//����������� �������������
//���������� �������
using namespace std;
string logins[10];
string names[10];
string Public[10];//��������� ���������
int nameCount = 0;//����� ���������� �������������
int main()
{
	setlocale(LC_ALL, "");
	//��������� ����������� ���� � ��������
	ifstream fin;
	fin.open("login.txt");
	//��������� ������ � ���������� 'char login[100]'	
	char login[100];
	while (!fin.eof())
	{
		fin.getline(login, 100);
	}
	
	//��������� ����
	fin.close();
	
	//��������� ���� � ������� �������������
	ifstream tam;
	tam.open("name.txt");
	//��������� ������ � ���������� 'char name[100]'	
	char name[100];
	while (!tam.eof())
	{
		tam.getline(name, 100);
	}
	tam.close();
	char pass[30];//������� ������ ��� �������� �����
	
	int idUser = 0;
	int begin = 0;
	for (int y = 0; y < 30; ++y) { pass[y] = 0; }//������� ������� ������
	//�������� ������ � ����� ������
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
		int p = 0;//�������������� ������� � �����
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
		for (int y = 0; y < 30; ++y) { pass[y] = 0; }//������� ������� ������
		//�������� ����� � ����� ������
		
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
			int p = 0;//�������������� ������� � �����
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
			nameCount = idUser;//������� ����� ���������� �������������
		}
	}
	//������ ����� ��� ������ � ������� �����������
	string fail[10];
	for (int i = 0; i < idUser + 1; ++i)
	{
		fail[i] = names[i] + ".txt";
	}
	do {
		std::cout << "����� ����������!                                   (exit = �����)\n";
		std::cout << "1 - ���� � ���, \n"
					 "0 - �����������\n" << "> ";
		std::cin >> pass;
		int alpha = 0;
		bool add = false;//�������, ��� ������� ����������� ����� �����
		ofstream fout;
		switch (pass[0])
		{
		case '1':
			cout << "��� ����� ������� �����" << endl;
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
				User big(idUser, names);//����� ������ ���������� ���� � ���

					std::cout << "�� ����� � ���" << endl << "����������: 1 - ������ �������������,\n"
						"	    2 - �������� � ����� ����,\n"
						"	    3 - �������� ������ ��������� ������������,\n"
						"	    4 - �������� �������� ���������, \n"
						"	    0 - ������� ����" << endl;
					std::cin >> pass; //�������� ����� ���������

				string Mes;//��������� ������������ � ����
				int person = -1;//��������� �� ������������(���� ��� ������ - ������)
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
					//��������� ���������� ���������
					cout << "sand - ��������� ���������\n esc - �������� ���������\n";
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
						//�������� � ����
						fout.open("public-chat.txt", ios::app);
						for (int i = 0; i < 10; ++i)
						{
							fout << Public[i];
						}
						fout.close();
					}
					else
					{
						cout << "��������� ��������" << endl;
					}
					break;
				case('3'):
					std::cout << "��������, ���� ������ ��������� ���������" << endl;
					std::cin >> Mes;
					cout << "sand - ��������� ���������\n esc - �������� ���������\n";
					for (int i = 0; i < nameCount; ++i)
					{
						if (Mes == names[i])
						{
							Mes = "";
							person = i;
							std::cout << "������ ���������:" << endl;
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
								//�������� � ����
								fout.open(fail[person], ios::app);
								for (int i = 0; i < 10; ++i)
								{
									fout << Public[i];
								}
								fout.close();
							}
							else
							{
								cout << "��������� ��������" << endl;
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
					//��������� ���������� ���������

					chat.open(fail[idUser], ios::in);

					while (chat.get(ch))
					{
						std::cout << ch;
					}
					chat.close();
					break;
				case '0':
					cout << big.getUserName(idUser) << " ������� ���" << endl;
				default:
					
					break;
				}
			}
			break;
		case '0':
			std::cout << "���������� ����������� ������ ������������." << endl << "������� ����� �����" << endl;
			char reg[30];
			for (int y = 0; y < 30; ++y) { reg[y] = 0; }//������� ������� ������
			std::cin >> reg;
			for (int i = 0; i < idUser + 1; ++i)
			{
				if (reg == logins[i])
				{
					std::cout << "����� ����� ��� ����������!" << endl;
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
				std::cout << "��� ��� �����?" << endl;//�������� ������������
				std::cin >> names[idUser];
			}
			//�������� � ����
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