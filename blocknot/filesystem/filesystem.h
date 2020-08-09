#pragma once

#include <corecrt_io.h>
#include <fstream>

namespace filesystem
{
	bool is_file_avilible(const char* cFileName) //����� � ������� �����:?
	{ 
		return _access(cFileName, 0) != -1; 
	}

	void write_to_file(const char *path, const char* text)
	{
		std::ofstream out;
		out.open(path);
		if (out.is_open()) { out << text << std::endl; }
		out.close();
	}

	void read_in_file(const char* path, char *dst)
	{
		std::string line, lineOut;
		std::ifstream in(path);
		if (in.is_open())
		{
			while (getline(in, line))
			{
				lineOut += line;//����������� �������� � ����������
				lineOut += '\n';//�������� ������
			}
			strcpy(dst, lineOut.c_str());
		}
		in.close();
	}
}