#include "uspeech.h"

bool IsVowel(char c){
	return in(c,"aeiou");
}
bool uIsVowel(char c){
	return in(c,"aeiourl");
}
bool uIsPlosive(char c){
	return in(c,"qtpdgkcb");
}
bool in(char c, String s){
	int i = 0;
	bool isin = false;
	while(i<s.length()){
		if(i == s[i]){
			isin =true;
		}
		i++;
	}
	return isin;
}
int umatch(String ing, String desired){
	int j;
	if(abs(getSyllables(ing) - getSyllables(desired))<1){
		int i;
		while(i<ing.length()){
			subChar(ing[i],desired[i]);
			i++;
		}
	}
	else{
		j = 257;
	}
	return j;
}
int getSyllables(String ing){
	int i,s;
	while(i<ing.length()){
		if((!IsVowel(ing[i]))&&IsVowel(ing[i-1])){
			s++;
		}
	}
	return s;
}
int subChar(char a, char b){
	return mapChar(a) - mapChar(b);
}
int mapChar(char a){
	if(uIsVowel(a)){
		return 0;
	}
	if(a == 'v'| a == 'p'){
		return 40;
	}
	if(a == 'g'){
		return 70;
	}
	if(a == 'z'){
		return 80;
	}
	if(a == 's'){
		return 90;
	}
	if(a == 'k'){
		return 90;
	}
}
String denoise(char c, String prev){
	if(c=='h'){
	}
	else{
		if(c != prev[prev.length()-1]){
			if(uIsVowel(prev[prev.length()-1])){
				if(!uIsVowel(prev[prev.length()-1])){
					prev= prev+String(c);
				}
			}
		}
		else{
			if(uIsPlosive(c)){
				if(!uIsPlosive(prev[prev.length()-1])){
					prev[prev.length()-1]= c;
				}
			}
		}
	}
	return prev;
	
}