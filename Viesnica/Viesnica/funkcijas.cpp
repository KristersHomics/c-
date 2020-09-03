#include "Header.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

bool checkfordigitsandsymbols(std::string text) {
	if (text.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)
	{
		return true;
	}
	else {
		return false;
	}
}



bool parbauditlielaisburts(std::string text) {
	return islower(text[0]);
}

bool check_usrn_surn(std::string text) {
	if (parbauditlielaisburts(text) || checkfordigitsandsymbols(text)) {
		std::cout << "\n Ievadits neatlauts simbols. \n";
		return true;
	}else
		return false;
}

bool kluda_parole(std::string parole, std::string atkartotaparole) {
	if (parole != atkartotaparole) {
		std::cout << "\n Kljuda ievade! Meginiet velreiz... \n";
		return true;
	}
	return false;
}

bool kluda_epasts(std::string epasts) {
	for (int x = 0; x < epasts.size(); x++) {
		int ch = epasts[x];
		if (ch == '@') {
			return false;
		}
	}
	std::cout << "\n Kluda ievade! Meginiet velreiz... \n";
	return true;
}

int isSubstring(std::string s1, std::string s2)
{
	int M = s1.length();
	int N = s2.length();

	for (int i = 0; i <= N - M; i++) {
		int j;
		for (j = 0; j < M; j++)
			if (s2[i + j] != s1[j])
				break;

		if (j == M)
			return i;
	}

	return -1;
}