#include "ConsoleHandler.h"

void ConsoleHandler::splitString(string cmd, vector<string>& v)
{
    int place = 0;
    string token, delimeter = " ";

    while ((place = cmd.find(delimeter)) != string::npos)
    {
        token = cmd.substr(0, place);
        v.push_back(token);
        cmd.erase(0, place + delimeter.length());
    }
    v.push_back(cmd);

    for (string s : v)
    {
        cout << s << endl;
    }
}

void ConsoleHandler::toDate(string& str, int& y, int& m, int& d)
{
    int place = 0;
    string token, delimeter = "-";
    vector<string> v;

    while ((place = str.find(delimeter)) != string::npos)
    {
        token = str.substr(0, place);
        v.push_back(token);
        str.erase(0, place + delimeter.length());
    }
    v.push_back(str);

    y = stoi(v.at(0));
    m = stoi(v.at(1));
    d = stoi(v.at(2));
}

bool ConsoleHandler::isValidDateTime(int year, int month, int day)
{
    bool isValid = false;

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    return true;
}

bool ConsoleHandler::isNumber(string str)
{
    return (atoi(str.c_str()));
}

void ConsoleHandler::checkFunction(string firstWord, string command)
{
    vector<string> vector;

    if (firstWord == "addevent")
    {
        int y, m, d;
        string name;
        splitString(command, vector);
        toDate(vector.at(1), y, m, d);
        DateTime date(y, m, d);

        for (int i = 3; i < vector.size(); i++)
        {
             name = name + " " + vector.at(i);
        }

        if (stoi(vector.at(1)) < 1)
        {
            cout << "Negative rooms don't exist." << endl;
        }
        else if (stoi(vector.at(1)) > 20)
        {
            cout << "The halls are only 20." << endl;
        }
        else
        {
            if (isValidDateTime(y, m, d) == false)
            {
                cout << "Please enter valid DateTime!" << endl;
            }
            else
            {
                theatre.addEvent(date, stoi(vector.at(1)), name);
            }
            //hotel.printRooms();
        }
    }
    else if (firstWord == "freeseats")
    {
        int y, m, d;
        string name;
        splitString(command, vector);
        toDate(vector.at(1), y, m, d);
        DateTime date(y, m, d);
        name = vector.at(2);

        if (vector.size() == 1 || vector.size() == 2)
        {
            cout << "Please enter date and name." << endl;
        }
        else
        {
            if (isValidDateTime(y, m, d) == false)
            {
                cout << "Please enter valid DateTime!" << endl;
            }
            else
            {
                theatre.freeseats(date, name);
            }
        }
    }
    else if (firstWord == "book")
    {
        int y, m, d, row, seat;
        string name, note;
        splitString(command, vector);
        toDate(vector.at(3), y, m, d);
        DateTime date(y, m, d);
        row = stoi(vector.at(1));
        seat = stoi(vector.at(2));
        name = vector.at(4);

        for (int i = 5; i < vector.size(); i++)
        {
            note = note + " " + vector.at(i);
        }

        if (isValidDateTime(y, m, d) == false)
        {
            cout << "Please enter a valid DateTime!" << endl;
        }
        else
        {
            theatre.book(row, seat, date, name, note);
        }
    }
    else if (firstWord == "unbook")
    {
        splitString(command, vector);
        int y1, m1, d1, y2, m2, d2;
        toDate(vector.at(1), y1, m1, d1);
        toDate(vector.at(2), y2, m2, d2);
        DateTime dateFrom(y1, m1, d1);
        DateTime dateTo(y2, m2, d2);
        //theatre.report(dateFrom, dateTo);
    }
    else if (firstWord == "buy")
    {
        splitString(command, vector);
        int y1, m1, d1, y2, m2, d2;
        toDate(vector.at(2), y1, m1, d1);
        toDate(vector.at(3), y2, m2, d2);
        DateTime dateFrom(y1, m1, d1);
        DateTime dateTo(y2, m2, d2);
        //theatre.findExclamation(stoi(vector.at(1)), dateFrom, dateTo);
    }
    else if (firstWord == "bookings")
    {
        splitString(command, vector);
        int y1, m1, d1, y2, m2, d2;
        toDate(vector.at(2), y1, m1, d1);
        toDate(vector.at(3), y2, m2, d2);
        DateTime dateFrom(y1, m1, d1);
        DateTime dateTo(y2, m2, d2);
        //theatre.find(stoi(vector.at(1)), dateFrom, dateTo);
    }
    else if (firstWord == "check")
    {
        int y1, m1, d1, y2, m2, d2;
        string note;
        splitString(command, vector);
        toDate(vector.at(2), y1, m1, d1);
        toDate(vector.at(3), y2, m2, d2);
        DateTime dateFrom(y1, m1, d1);
        DateTime dateTo(y2, m2, d2);
        for (int i = 4; i < vector.size(); i++)
        {
            note = note + " " + vector.at(i);
        }

        //theatre.unavailable(stoi(vector.at(1)), dateFrom, dateTo, note);
    }
    else if (firstWord == "report")
    {
        int y1, m1, d1, y2, m2, d2;
        string note;
        splitString(command, vector);
        toDate(vector.at(2), y1, m1, d1);
        toDate(vector.at(3), y2, m2, d2);
        DateTime dateFrom(y1, m1, d1);
        DateTime dateTo(y2, m2, d2);
        for (int i = 4; i < vector.size(); i++)
        {
            note = note + " " + vector.at(i);
        }

        //theatre.unavailable(stoi(vector.at(1)), dateFrom, dateTo, note);
    }
    else
    {
        cout << "Invalid command!" << endl;
    }
}

void ConsoleHandler::open(string path)
{
    string PATH = path;

    if (f_inout.is_open())
    {
        cout << "Already opened file" << endl;
    }
    else
    {
        f_inout.open(PATH);

        if (!f_inout.is_open())
        {
            cout << "not a valid path" << endl;
            return;
        }

        cout << "Opened successfully" << endl;

        char* token;
        token = strtok(&PATH[0], "\\");

        while (token != NULL)
        {
            f_fileName = token;
            token = strtok(NULL, "\\");
        }
    }
}

void ConsoleHandler::close()
{
    if (!f_inout.is_open())
    {
        cout << "Invalid command" << endl;
        cout << "Try opening a file first. The command is open." << endl;
    }
    else
    {
        cout << "Successfully closed " << f_fileName << endl;
        f_fileName = "";
        f_filePath = "";
        f_inout.close();
    }
}

void ConsoleHandler::save()
{
    if (!f_inout.is_open())
    {
        cout << "Invalid command" << endl;
        cout << "Try opening a file first. The command is open." << endl;
    }
    else
    {
        f_inout.clear();

        //f_inout << hotel;
        cout << "Successfully saved in " << f_fileName << endl;
    }
}

void ConsoleHandler::saveAs(string path)
{
    string PATH = path;

    if (f_filePath == path)
    {
        //f_inout << hotel;
    }
    else
    {
        fstream newstream(path);

        if (!newstream.is_open())
        {
            cout << "Invalid command" << endl;
            cout << "Try opening a file first. The command is open." << endl;
        }
        else
        {
            newstream.clear();

            //newstream << hotel;

            char* token;
            token = strtok(&PATH[0], "\\");
            string currentName;

            while (token != NULL)
            {
                currentName = token;
                token = strtok(NULL, "\\");
            }

            cout << "Successfully saved in " << currentName << endl;
            newstream.close();
        }
    }
}

void ConsoleHandler::exit()
{
    if (f_inout.is_open())
    {
        f_inout.close();
    }
    cout << "Exiting the program..." << endl;
    terminate();
}

void ConsoleHandler::help()
{
    cout << "The following commands are supported :\n"
        << "open <file>    opens <file>\n"
        << "close          closes currently opened file\n"
        << "save           saves the currently open file\n"
        << "saveas <file>  saves the currently open file in <file>\n"
        << "help           prints this information\n"
        << "exit           exists the program" << endl;
}

void ConsoleHandler::processCommand(string firstWord, string command)
{
    string commandName, path = "";
    char* token;
    string _command = command;

    token = strtok(&command[0], " ");

    commandName = token;

    token = strtok(NULL, " ");

    if (token != NULL)
    {
        path = token;
    }

    if (commandName == "open")
    {
        f_filePath = path;
        open(path);
    }
    else if (commandName == "save")
    {
        save();
    }
    else if (commandName == "saveas")
    {
        if (path == "")
        {
            cout << "Invalid command.Try again!";
        }
        else
        {
            saveAs(path);
        }
    }
    else if (commandName == "close")
    {
        close();
    }
    else if (commandName == "help")
    {
        help();
    }
    else if (commandName == "exit")
    {
        exit();
    }
    else
    {
        if (f_inout.is_open())
        {
            checkFunction(firstWord, _command);
        }
        else
        {
            cout << "Invalid command" << endl;
            cout << "Try opening a file first. The command is open." << endl;
        }
    }
}