#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
class Employee
{
    int eno;
    char name[30];
    int salary;

public:
    void getdata()
    {
        cout << "\nEnter Emp No ";
        cin >> eno;
        cout << "\nEnter name ";
        cin >> name;
        cout << "\nEnter salary ";
        cin >> salary;
    }
    void putdata()
    {
        cout << "\n"
             << eno << "\t" << name << "\t" << salary;
    }

    int geteno()
    {
        return eno;
    }
};
int main()
{
    system("cls");
    Employee obj;
    ifstream fin;
    ofstream fout;
    int choice1, temp, f;
    char choice2;
    do
    {
        // system("cls");
        cout << "\n### MENU ###";
        cout << "\n1.Add record";
        cout << "\n2.Search record";
        cout << "\n3.Delete record";
        cout << "\n4.Display all";
        cout << "\n5.Exit:";
        cin >> choice1;

        switch (choice1)
        {
        case 1:
            fout.open("record.bin", ios::app | ios::binary);
            do
            {
                system("cls");
                obj.getdata();
                fout.write((char *)&obj, sizeof(obj));

                cout << "\naAdd more(Y/N)";
                cin >> choice2;

            } while (choice2 != 'N');

            cout << "\nRecord added successfully";
            fout.close();
            break;

        case 2:
            fin.open("record.bin", ios::binary);
            if (!fin)
            {
                cout << "\nFile not exist";
                break;
            }
            cout << "\nEnter Employee No to search ";
            cin >> temp;

            cout << "\ndata is";
            while (1)
            {
                fin.read((char *)&obj, sizeof(obj));
                if (fin.eof())
                    break;

                if (obj.geteno() == temp)
                {
                    cout << "\nData found";
                    cout << "\nEmp_No\tName\tSalary";
                    obj.putdata();
                    f = 1;
                    break;
                }
            }

            fin.close();
            if (f == 0)
            {
                cout << "\nData not found";
            }
            break;

        case 3:
            fin.open("record.bin", ios::binary);
            if (!fin)
            {
                cout << "File not exist";
                break;
            }

            fout.open("temp.bin");
            cout << "\nEnter Employee No to delete";
            cin >> temp;

            // cout<<"\nEmp_no\tName\tSalary";
            while (1)
            {
                fin.read((char *)&obj, sizeof(obj));
                if (fin.eof())
                    break;

                if (obj.geteno() == temp)
                {
                    f = 1;
                }
                else
                {
                    fout.write((char*)&obj,sizeof(obj));
                    fin.read((char*)&obj,sizeof(obj));
                }
                
            }
            fout.close();
            fin.close();
            if (f == 0)
            {
                cout << temp << " not found";
            }
             
            
            remove("record.bin");
            rename("temp.bin", "record.bin");
            break;

        case 4:
            fin.open("record.bin", ios::binary);

            if (fin)
            {

                cout << "\nEmp_no\tName\tSalary";
                while (1)
                {
                    fin.read((char *)&obj, sizeof(obj));
                    if (fin.eof())
                        break;

                    obj.putdata();
                }
                fin.close();
            }
            break;

            cout << "\nGood bye";
            break;
        default:
            cout << "Invalid choice";
            break;
        }
       getch();
    } while (choice1 != 5);

    return 0;
}