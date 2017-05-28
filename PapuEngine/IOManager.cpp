#include "IOManager.h"
#include <fstream>

bool IOManager::readFileBuffer(string filePath, vector<unsigned char> &buffer) {
	
	//abrir archivo
	ifstream file(filePath, ios::binary);
	if (file.fail()) {
		perror(filePath.c_str());


	}
	//manda al final
	file.seekg(0, ios::end);
	int fileSize = file.tellg();
	
	file.seekg(0, ios::beg);
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char*)&(buffer[0]), fileSize);
	file.close();
	return true;


}