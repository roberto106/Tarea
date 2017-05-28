#pragma once
#include <vector>
#include <string>
using namespace std;
class IOManager
{
public:

	static bool readFileBuffer(string filePath,vector<unsigned char> &buffer);

};