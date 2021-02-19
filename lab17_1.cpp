#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

char score2grade(int score)
{
    if (score >= 80)
        return 'A';
    if (score >= 70)
        return 'B';
    if (score >= 60)
        return 'C';
    if (score >= 50)
        return 'D';
    else
        return 'F';
}

string toUpperStr(string x)
{
    string y = x;
    for (unsigned i = 0; i < x.size(); i++)
        y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string &filename, vector<string> &names, vector<int> &scores, vector<char> &grades)
{

    ifstream source;
    source.open(filename.c_str());
    string textline;
    int count = 0;
    while (getline(source, textline))
    {
        char fomat[] = "%[^:]: %d %d %d";
        int s1, s2, s3;
        char name[100];
        sscanf(textline.c_str(), fomat, name, &s1, &s2, &s3);
        names.push_back(name);
        scores.push_back(s1 + s2 + s3);
        grades.push_back(score2grade(s1 + s2 + s3));
        count++;
    }
}

void getCommand(string &command, string &key)
{
    cout << "Please input your command: ";
    string input;
    getline(cin, input);

    int sp = input.find_first_of(" ");
    command = input.substr(0, sp);
    key = input.substr(sp + 1, input.size() - sp);
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string &key)
{
    cout << "---------------------------------"
         << "\n";
    int count = 0;
    int size = names.size();
    for (int i = 0; i < size; i++)
    {

        if (toUpperStr(names[i]) == key)
        {
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            count++;
        }
    }

    if (count == 0)
    {
        cout << "Cannot found."<<"\n";
    }
    cout << "---------------------------------"
         << "\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string &key)
{
    cout << "---------------------------------"
         << "\n";
    int count;
    int size = names.size();
    for (int i = 0; i < size; i++)
    {

        char k = toUpperStr(key)[0];
        if (grades[i] == k)
        {
            cout << names[i] << " (" << scores[i] << ")"
                 << "\n";
            count++;
        }
    }
    if (count == 0)
    {
        cout << "Cannot found."<<"\n";
    }
    cout << "---------------------------------"
         << "\n";
}

int main()
{
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades;
    importDataFromFile(filename, names, scores, grades);

    do
    {
        string command, key;
        getCommand(command, key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if (command == "EXIT")
            break;
        else if (command == "GRADE")
            searchGrade(names, scores, grades, key);
        else if (command == "NAME")
            searchName(names, scores, grades, key);
        else
        {
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    } while (true);

    return 0;
}
