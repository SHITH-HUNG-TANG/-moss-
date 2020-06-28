#ifndef PG2MyString_H
#define PG2MyString_H
#include <iostream>
#include<string>
#include "s1071221_MyArray_hw701.h"
using namespace std;

class MyString :public MyArray<char>
{
	//friend ostream &operator<<(ostream& output, const MyString& str);
	friend ostream& operator<<(ostream& output, const MyString&str)
	{
		for (int i = 0; i < str.size; i++)
			output << str.data[i];
		return output;
	}
	friend istream& operator>>(istream& input, MyString& str)
	{
		string number;
		input >> number;
		str.size = number.size();
		for (int i = 0; i < str.size; i++)
		{
			str.data[i] = number[i];
		}
		return input;
	}
public:
	MyString();
	//�c�y�@�ӪŦr�Ŧ�A���׬��s�Ӧr�šC
	// *�q�{�e�q= 10

	MyString(const MyString& str);
	//�c�y�� str�����ƥ��C �]�ƻs�c�y��ơ^

	MyString(const MyString& str, size_t pos, size_t len = msize); // �]�l�r�Ŧ�c�y��ơ^
	//�ƻs�q�r�Ŧ�m�� pos���}�l�ø�V�� len���Ӧr�Ū�str����
	//�]�Ϊ���str�������A�p�Gstr�ӵu��len�Ostring :: msize�^

	MyString(const char* s);
	//�ƻss���V���r�š]C�r�Ŧ�^�ƲաC
	// char * s�O���V�Hnull�פ�r�ŧǦC�����w�C �]�H�U�Ҧ��r��*�ۦP/�^
	//�N�ǦC�ƻs���r�Ŧꪺ�s�ȡC

	~MyString();
	// Destroys the string object.

	static const size_t msize = -1;
	//Note: maximum size. You may use SIZE_MAX at <cstdint>, too.

	MyString& append(const MyString& str);
	//�b��eMyString���������[�@��str
	// *��^�ۨ����ޥ�

	MyString substr(size_t pos, size_t len = msize) const;
	//�l�r�Ŧ�O��H���@�����A�q�r�Ŧ�mpos�}�l�ø�Vlen�Ӧr��
	//�]�Ϊ���r�Ŧ꥽���A�H����̬��ǡ^
	// *��^�@�ӷs�c�y���r�Ŧ��H�A��Ȫ�l�Ƭ��ӹ�H���l�r�Ŧꪺ�ƥ�

	MyString& insert(size_t pos, const MyString& str);
	// Inserts a copy of a str at "pos".
	// example: str = "to be question", str2 = "the "
	// str.insert(6,str2); 
	// = to be (the )question = to be the question
	// *Return the reference of itself

	MyString& insert(size_t pos, const MyString& str, size_t subpos, size_t sublen = msize);
	// Inserts a copy of a substring of str at "pos". The substring is the portion of "str" that
	// begins at the character position subpos and spans sublen characters (or until the end of str).
	// example: str = "to be the question", str3 = "or not to be"
	// str.insert(6,str3,3,4); // to be (not )the question
	// *Return the reference of itself

	MyString& erase(size_t pos, size_t len = msize);
	// Erases the portion of the string value that begins at the character position pos and spans len characters 
	// (or until the end of the string, if either the content is too short or if len is string::msize.)
	// *Return the reference of itself

	size_t find(const MyString& str, size_t pos = 0) const;
	// Searches the portion of the string value that begins at the character position "pos" until the end of the string
	// for the first occurrence of the string str.
	// Return Value: The position of the first character of the first match. If no matches were found, the function returns MyString::msize.

	size_t find_first_of(const MyString& str, size_t pos = 0) const;
	// Searches the portion of the string value that begins at the character position "pos" until the end of the string
	// for the first character that matches *any* of the characters of the string str.
	// Return Value: The position of the first character that matches. If no matches are found, the function returns MyString::msize.

	//You may add several helper functions or operators here
	//...
}; // end class MyString

#endif