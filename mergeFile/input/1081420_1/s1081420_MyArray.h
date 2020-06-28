#pragma once
#ifndef s1081420_MyArray_H
#define s1081420_MyArray_H

#include <string>
#include<iostream>
using namespace std;

template<typename T>
class MyArray {	//modify this class into a template class
	//template<typename T>
	friend ostream& operator<< (ostream& out, const MyArray<T>& right) {
		for (int i = 0; i < right.getSize(); i++) out << right[i] << " ";
		out << endl;
		return out;
	}//��X����A�����t�Ů�


	//friend istream& operator>>(istream&, MyArray&);
	public:
		MyArray(int Capacity = 10);//�w�]�Ŷ���capacity=10,size=0//�C���Ŷ��椣�����ܦ���U2���j
		MyArray(size_t Size, T value);//ex.(3,5)�}�C���e��3��5�Avalue �� type �n��template
		//Bouns->
		MyArray(T value[], int Size);//�ǤJ�@�Ӱ}�C���}�C�����e��JArray(this)��
		//Bouns<-
		MyArray(const MyArray<T> & right);//copy constructor
		~MyArray();
		const MyArray<T>& operator=(const MyArray<T>&);//assigment operator
		bool operator==(const MyArray<T>&) const;
		bool operator!=(const MyArray<T>&) const;
		MyArray<T> operator+(const MyArray<T>&) const;	//NEW�^�Ƿs���e���A�åB�쥻����̥����Ȥ���
		MyArray<T>& operator+=(const MyArray<T>&) ;		//NEW�^�ǭ�e���ק�L�����G
		T& operator[](int);//�i�ק�
		T operator[](int) const;//�ȶǭ�
		T& at(int);		//new�C�i�ק�A���d���ˬd�����e�s��(exception)
		T at(int) const;	//new�C�ȶǭȡA���d���ˬd�����e�s��(exception)

		int getSize() const { return size; };
		int getCapacity() const { return capacity; };
		void resize(size_t size, T item='\0');
		void reserve(size_t size);//�Ncapacity�����ܦ��ҶǤJ���ܼ�
		void shrink_to_fit();	//new�C�Ncapacity�Y����size
		void clear();			//new�C�M��array���e
		bool isEmpty();			//new�C�ˬd�O�_����
		/*class out_of_range : public logic_error {
		public:
			explicit out_of_range(const string& what_arg);
			explicit out_of_range(const char* what_arg);
		};*/

	private:
		int size = 0;
		int capacity = 10;
		T* data = nullptr;
};



//#include "s1081420_MyArray.cpp"
#endif // !s1081420_MyArray

