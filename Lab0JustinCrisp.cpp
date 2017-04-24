//  CIS29 LAB0 Grant Larkin
//  Created by Justin Crisp on 4/14/17.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <locale>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;
class Degree_list
{
private:
        string x_val_s;
        string y_val_s;
    vector<string> degree_secret;
public:
    Degree_list()
    {
        degree_secret.clear();
    }
    /*
     _void add(string degree_pair)_
     1. given degree_pair parse pair
     2. re-pair -> send to Vector for storage
    */
    void add(string degree_pair)
    {
        //Create degree pointer + temp pointer for traversal
        int s = 0;
        char c;
        string pair, x_s, y_s;
        //assuming (xxx,yyy) w/ a min of 1 x , 1 y
        for(int i = 0; i < degree_pair.size(); ++i)
        {
            c = degree_pair.at(i);
           if(c == ',')
           {
               s = 1;
           }else{
            if(isdigit(c))
            {
               switch(s)
               {
                   case 0: x_s.push_back(c);
                       break;
                   case 1: y_s.push_back(c);
                       break;
               }
            }
           }
        }
        x_val_s = x_s;
        y_val_s = y_s;
        pair = x_s + "," + y_s;
        degree_secret.push_back(pair);
    }
    /*
     _string getDegreePair(int location)_
     1. return string pair of degrees given index location
    */
    string getDegreePair(int location)
    {
        string pair;
        pair = degree_secret[location];
        //cout << degree_secret.size() << endl;
        cout << pair << endl;
        return pair;
    }
    
    //_ACCESSORS_
    
    vector<string> getVect() {return degree_secret;}
    
};
class FileIO
{
private:
    string fileName;
    fstream inputFile;
    vector<int> numbers;
public:
    FileIO()
    {
        fileName = "";
    }
    FileIO(string fileName)
    {
        this->fileName = fileName;
        openFile(fileName);
    }
    /*
     _bool openFile(string fileName)_
     1. Checks if file can be opened, using try/catch.
     2. prints fileName being opened.
     3. returns boolean true/false, for operation.
    */
    bool openFile(string fileName)
    {
        try{
        cout << "Opening File: " << fileName << endl;
        inputFile.open(fileName);
        }
        catch(const char* msg)
        {
            cerr << msg << endl;
        }
        return inputFile.is_open();
    }
    /*
     _void printFile()_
     1.Prints fileName.
     2.Prints fileContents using getLine.
    */
    void printFile()
    {
        string line;
        cout << "Printing File: " << fileName << endl;
        cout << setfill('_') << setw(42) << " " << endl;
        while(getline(inputFile,line))
        {
            cout << line << endl;
        }
        cout << setfill('_') << setw(42) << " " << endl;
        inputFile.clear(); //return fstream state to good, from EOF.
        inputFile.seekg(0, inputFile.beg);
    }
    /*
     _int numberTruncate()_
     1. collect all digits in file
     2. place digits as int, in Vector
     3. return 0 if sucess, -1 if empty
    */
    int numberTruncate()
    {
        char c;
        int i = 0;
        while(inputFile.get(c))
        {
            if(isdigit(c))
            {
                i = c - '0'; //convert char -> int
                numbers.push_back(i);
            }
        }
        if(numbers.size() == 0){
          cout << "Vector is empty." << endl;
            return -1;
        }
        inputFile.clear(); //return fstream state to good, from EOF.
        inputFile.seekg(0, inputFile.beg);
        return 0;
    }
    /*
     _void printNumber()_ 
     1. prints numbers for size() of vector
     */
    void printNumbers()
    {
        cout << "Printing digits from File: " << fileName << endl;
        cout << setfill('_') << setw(42) << " " << endl;
        for(int i = 0; i < numbers.size(); i++)
        {
            cout << numbers.at(i) << endl;
        }
        cout << setfill('_') << setw(42) << " " << endl;
    }
    /*
     _void degreeRead(Degree_list &d_list)_
     1. given a pre-defined degreeList object, parse formatted file for degrees
     2. parse is based on "(xxx,yyy)," format
    */
    void degreeRead(Degree_list &d_list)
    {
        char c;
        int s = 0;
        string builder;
        while(inputFile.get(c))
        {
            //since this format is known, we are going to split into (xxx,yyyy)
            if(c == '(') s = 0;
            else if(c == ')') s = 1;
            switch(s)
            {
                case 0: builder += c;
                    break;
                case 1:
                if(c==')')
                {
                    d_list.add(builder);
                        builder = "";
                }
                    break;
            }
        }
        inputFile.clear(); //return fstream state to good, from EOF.
        inputFile.seekg(0, inputFile.beg);
    }
     //_ACCESSORS_
    
    vector<int> getNumbers(){return numbers;}
    
    string getFileName(){return fileName;}
    
    // _MUTATORS_
    
    void setFileName(string name){ fileName = name;}
    
};

class AsciiConversion
{
private:
    struct char_arr{
        char hexa[2];
    };
    vector<char_arr> hexaList;
public:
    /*
     _char degreeToHexa(int degree)_
     1. A very lazy approach to collecting hex_values
     Note: a possible improvement can be to find the difference range,
    decode based on a % parse of the degrees.
     */
    char degreeToHexa(int degree)
    {
        if(degree <= 22) return '0';
        else if(degree <= 45) return '1';
        else if(degree <= 67) return '2';
        else if(degree <= 90) return '3';
        else if(degree <= 112) return '4';
        else if(degree <= 135) return '5';
        else if(degree <= 157) return '6';
        else if(degree <= 180) return '7';
        else if(degree <= 202) return '8';
        else if(degree <= 225) return '9';
        else if(degree <= 247) return 'A';
        else if(degree <= 270) return 'B';
        else if(degree <= 292) return 'C';
        else if(degree <= 315) return 'D';
        else if(degree <= 337) return 'E';
        else if(degree <= 360) return 'F';
        else return '-1';
    }
    /*
     _void readList(vector<string> &degrees)
     1. takes in a vector of degree pairs
     2. splits the pairs and converts to int
     3. sends the integers to degreeToHexa for final conversion
    */
    void readList(vector<string> &degrees)
    {
        char_arr h;
        string ds1, ds2, d;
        int d1,d2, pos;
        for(int i = 0; i < degrees.size(); i++)
        {
            d = degrees.at(i);
            pos = d.find(',');
            ds1 = d.substr(0,(pos));
            ds2 = d.substr((pos+1),d.length());
            d1 = stoi(ds1);
            d2 = stoi(ds2);
            h.hexa[0] = degreeToHexa(d1);
            h.hexa[1] = degreeToHexa(d2);
            hexaList.push_back(h);
        }
    }
    /* _string convert()_
     1. takes the converted hex values prints the ascii equivlent
     2. pins the values into a string.
     */
    string convert()
    {
        string hexa_sent;
        char_arr h;
        char he[2];
       long  int num = 0;
        for(int i = 0; i < hexaList.size(); i++)
        {
            h = hexaList.at(i);
            he[0] = h.hexa[0];
            he[1] = h.hexa[1];
            num = strtol(he, nullptr, 16);
            cout << (char)num;
        }

        return hexa_sent;
    }
};

int main()
{
    Degree_list d;
    AsciiConversion a;
    FileIO fileOp("Degrees.csv");
    fileOp.degreeRead(d);
    vector<string> values = d.getVect();
    a.readList(values);
    a.convert();
	cin.get();
    return 0;
}

/*
 HEXA_CONV_TABLE
0 = 0° – 22°	 4 = 91° – 112°     8 = 181° – 202°	C = 271° – 292°
1 = 23° – 45°	 5 = 113° – 135°	9 = 203° – 225° D = 293° – 315°
2 = 46° – 67° 	 6 = 136° – 157     A = 226° -247°	E = 316° – 337°
3 = 68° – 90°	 7 = 158° – 180°	B = 248° – 270°	F = 338° - 360°
 */
