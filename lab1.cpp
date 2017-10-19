/*
	Justin Crisp
	Lab 1: Morse Code Binary File Reader
	Description:	Read a binary file encoded to ANSI Morse Code standard. 
					Decode the file, and save the contents of the file in ASCII
*/
#include<cstdlib>
#include<iostream> 
#include<string>
#include<vector>
#include<bitset>
#include<fstream>
#include<algorithm>
using namespace std;
/*
	- FileIO Class - 
*/
class FileIO
{
private:
	string fileName;
	ofstream outputFile;
	ifstream inputFile;
	void openFile(string fileName) { inputFile.open(fileName); }
public:
	FileIO() { fileName = ""; }
	~FileIO() { inputFile.close(); }
	string getFileName() { return fileName; }
	string requestName();
	void output(string o);
};
/*
	- FileIO::requestName - 
	requestName, prompts user for input of fileName,
	fileName is then used for creating an ifstream object.

*/
string FileIO::requestName()
{
	cout << "Please Enter file name and path." << endl;
	cin >> fileName;
	cout << "\nUsing: " << fileName << endl;
	return fileName;
}
/*
	- FileIO::output(string output)
	param: string of file output contents
	output, writes the string provided in the parameter to file output.txt
*/
void FileIO::output(string output)
{
	outputFile.open("output.txt");
	outputFile << output;
	outputFile.close();
}

class BitManipulator : public FileIO
{
private:
	ifstream binaryFile;
	string fileName;
	bitset<8> bitContainer;
	vector<bitset<8>> bit_vec;
public:
	void readBinaryFile();
	vector<bitset<8>> getBitVec() { return bit_vec; }
};
/*
	- readBinaryFile - 
*/
void BitManipulator::readBinaryFile()
{
	fileName = requestName();
	char c;
	int count = 0;
	binaryFile.open(fileName, ios::binary);
	if (binaryFile.is_open())
	{
		while (binaryFile.get(c))
			bit_vec.push_back(c);
	}
}
/*
	- MorseCodex -

*/
class MorseCodex
{
private:
	string morseCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'@:,$=!.?\"";
	string morseLiterals = "^.- ";
	vector<string> morseEncode = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-."
		, "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---.."
		, "----.", ".----.", ".--.-.", "---...", "--..--", "...-..-", "-...-", "-.-.--", ".-.-.-", "..--..", ".-..-." };
public:
	string convertToMorse(vector<bitset<8>> morseEncodedBits);
	int binaryValue(string bits);
	string morseToAscii(string morseCode);
};
/*
	- convertToMorse -
*/
string MorseCodex::convertToMorse(vector<bitset<8>> morseEncodedBits)
{
	string eightBits;
	int morseIndex;
	string morseCode;
	int doubleSpaceCap = 0;
	for (auto i = 0; i < morseEncodedBits.size(); i++)
	{
		eightBits = morseEncodedBits.at(i).to_string();
		for (auto k = 0; k < eightBits.size(); k += 2)
		{
			morseIndex = binaryValue(eightBits.substr(k, 2));
			if (morseIndex != 3 || doubleSpaceCap % 2 == 0)
				morseCode += morseLiterals[morseIndex];
			if (morseIndex == 3) doubleSpaceCap++;
		}
	}
	return morseCode;
}
/*
	- binaryValue -
*/
int MorseCodex::binaryValue(string bits)
{
	char first_bit;
	char second_bit;
	int binaryValue = 0;
	first_bit = bits.at(0);
	second_bit = bits.at(1);
	if (first_bit == '1') { binaryValue++; }
	if (second_bit == '1') { binaryValue += 2; }
	return binaryValue;
}
/*
	- morseToAscii -
*/
string MorseCodex::morseToAscii(string morseCode)
{
	int rovingIndex = 0;
	string tempConversion = "";
	vector<string> morse;
	string decodedMessage = "";
	for (auto i = 0; i < morseCode.size(); i++)
	{
		if (morseCode.at(i) == '^')
		{
			tempConversion = morseCode.substr(rovingIndex, i - rovingIndex);
			tempConversion.erase(remove_if(tempConversion.begin(), tempConversion.end(), isspace),tempConversion.end());
			morse.push_back(tempConversion);
			rovingIndex = i + 1;
		}
		if (morseCode.at(i) == ' ')
			morse.push_back(" ");
	}
	for (auto l = 0; l < morse.size(); l++)
	{
		for (auto k = 0; k < morseCharacters.size(); k++)
		{
			if (morse.at(l).compare(morseEncode[k]) == 0)
				decodedMessage += morseCharacters[k];
		}
		if (morse.at(l).compare(" ") == 0)
			decodedMessage += " ";
	}
	return decodedMessage;
}
/*
	- Main -
*/
int main()
{
	BitManipulator bitMan;
	bitMan.readBinaryFile();
	vector<bitset<8>> bitContainer = bitMan.getBitVec();
	MorseCodex codex;
	string morseCode = codex.convertToMorse(bitContainer);
	string asciiMessage = codex.morseToAscii(morseCode);
	cout << asciiMessage;
	bitMan.output(asciiMessage);
	system("pause");
}