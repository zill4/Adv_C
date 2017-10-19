/*
    Lab 0 - The Martian
    Justin L. Crisp
    CIS 29 - Grant Larkin
 
*/
#include <iostream>
#include <cstdlib>
#include <vector> 
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <cmath>
using namespace std;

struct isEmpty
{
    bool operator()(const string& s)
    {
        return s.find("", 0) != string::npos;
    }
};

//      INPUT CLASS
//  Prompt user for input regarding
//  file name.
//  No specified path is given, the user provides a known one.

class FileIO
{
private:
    string file_name;
    ofstream output_file;
public:
    string getFileName(){return file_name;}
    void requestName();
    void output(string output);
};
void FileIO::requestName()
{
    cout << "Please Enter file name and path." << endl;
    cin >> file_name;
    cout << "\nUsing: " << file_name << endl;
}
void FileIO::output(string output)
{
    output_file.open("output.txt");
    output_file << output;
    
}
//      DEGREE_READER CLASS
//  read the file searching for degrees.
//  reads line by line. Parses each line for degrees.
//  returns a string vector containing the degrees.

class Degree_reader
{
private:
    ifstream reader;
    string file_name;
    vector<string> saved_degrees;
    
public:
    void read(string file_name);
    string parse_line(string line);
    vector<string> getDegrees(){return saved_degrees;}
    template<typename Out>
    void split(string line, char delim, Out result);
    vector<string> split(string line, char delim);

};

void Degree_reader::read(string file_name)
{
    cout << "reading " << file_name << endl;
    reader.open(file_name);
    vector<string> temp;
    string line = "";
    string parsed_line = "";
    while(getline(reader,line))
    {
        parsed_line = parse_line(line);
        temp = split(parsed_line,' ');
        saved_degrees.insert(saved_degrees.end(),temp.begin(),temp.end());
    }
}

string Degree_reader::parse_line(string line)
{
    for(int i = 0; i < line.length(); i++)
    {
        if(!isdigit(static_cast<unsigned char>(line.at(i))))
        {
            line.at(i) = ' ';
        }
    }
    return line;
}
template<typename Out>
void  Degree_reader::split(string line, char delim, Out result){
    stringstream string_stream;
    string_stream.str(line);
    string temp;
    while(getline(string_stream, temp, delim )){
        *(result++) = temp;
    }
}

vector<string> Degree_reader::split(string line, char delim)
{
    vector<string> portions;
    split(line, ' ', back_inserter(portions));
    return portions;
}

//ASCII_CONVERTER CLASS
//  Convert degrees to hex
//  Convert the hex to ascii
class Ascii_converter
{
private:
    char hex_chars[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    string hex;
    string ascii;
public:
    void degreesToChar(vector<string> degrees);
    void toAscii();
    string getAscii(){return ascii;}
    char dumbSwitch(int degree);
};

void Ascii_converter::degreesToChar(vector<string> degrees)
{
    cout << "converting to hex" << endl;
    int temp;
    for(int i = 0; i < degrees.size(); i++)
    {
        if(degrees.at(i)!= "")
        {
            temp = stoi(degrees.at(i));
            hex += dumbSwitch(temp);
        
        }
        
    }
    toAscii();
}
char Ascii_converter::dumbSwitch(int degrees)
{
    char return_char = NULL;
    if(degrees < 22){ return_char = hex_chars[0];}else
    if(degrees < 45){ return_char = hex_chars[1];}else
    if(degrees < 67){ return_char = hex_chars[2];}else
    if(degrees < 90){ return_char = hex_chars[3];}else
    if(degrees < 112){ return_char = hex_chars[4];}else
    if(degrees < 135){ return_char = hex_chars[5];}else
    if(degrees < 157){ return_char = hex_chars[6];}else
    if(degrees < 180){ return_char = hex_chars[7];}else
    if(degrees < 202){ return_char = hex_chars[8];}else
    if(degrees < 225){ return_char = hex_chars[9];}else
    if(degrees < 247){ return_char = hex_chars[10];}else
    if(degrees < 270){ return_char = hex_chars[11];}else
    if(degrees < 292){ return_char = hex_chars[12];}else
    if(degrees < 315){ return_char = hex_chars[13];}else
    if(degrees < 337){ return_char = hex_chars[14];}else
    if(degrees < 360){ return_char = hex_chars[15];}
    return return_char;
}

void Ascii_converter::toAscii()
{
    cout << "converting to ascii" << endl;
    size_t len = hex.length();
    for(int i=0; i < len; i+=2)
    {
        string byte = hex.substr(i,2);
        cout << byte << "    " ;
        char chr = (char) (int)strtol(byte.c_str(), NULL, 16);
        //cout << chr;
        ascii.push_back(chr);
    }
}
        

int main()
{
    
    FileIO i;
    i.requestName();
    Degree_reader d;
    d.read(i.getFileName());
    Ascii_converter a;
    a.degreesToChar(d.getDegrees());
    string output = a.getAscii();
    cout << d.getDegrees().size() <<endl;
    cout << output << endl;
    i.output(output);
    return 0;
}
