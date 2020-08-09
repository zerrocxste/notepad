#pragma once

#include <string>

class word_and_latters
{
public:
	word_and_latters(void) {};
	word_and_latters(int word, int latters) : word(word), latters(latters) {};
	
	void clear() {
		word = latters = 0;
	}

	int word, latters;
};

char russian_abc[63] = //https://inter-net.pro/javascript/arr-alphabet
{ 
	'�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�', 
	'�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�',

	'�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', 
	'�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�' 
};

namespace utils
{
	word_and_latters calc_word_and_latters(std::string text)
	{
		word_and_latters buff; buff.clear();
		bool s_ok = false;
		for (int i = 0; i < text.size(); i++)
		{
			if (text[i] != ' ') s_ok = true;
			if (s_ok)
			{
				if ((text[i] == ' ' && text[i - 1] != ' ')
					|| (i == (text.size() - 1) && text[i] != ' '))
					buff.word++;
				if (buff.word > 1 && text[i - 1] == '\n' && text[i] == ' ') //wtf
					buff.word--;
				if (text[i] != ' ')
					buff.latters++;
				if (text[i] == '\n')
					buff.latters--;
				for (int j = 0; j < 63; j++) //fix double ++latters na russkoi raskladke / govno
				{
					if (text[i] == russian_abc[j])
						buff.latters--;
				}
			}
		}
		return buff;
	}
}