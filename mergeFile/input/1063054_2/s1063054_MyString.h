//Updated
#ifndef MYARRAY_H
#define MYARRAY_H
#include<iostream>
#include<string>
#include<exception>
#include <cstdint>
#include<cstring>

using namespace std;

template <class elemType>
class MyArray {
	

	public:
		template <class elemType1>	
		friend ostream & operator << (ostream& output, const MyArray<elemType1> &m);
		template <class elemType1>	
		friend istream & operator >> (istream& input, MyArray<elemType1> &m);


		MyArray(int n = 10);//default constructor
		MyArray(int Size, elemType value);
		MyArray(const MyArray &);//copy 
		~MyArray();
		
		MyArray& operator= (const MyArray &m); 		
		bool operator==(const MyArray&m)const;
		bool operator!=(const MyArray&m)const;
		MyArray operator+(const MyArray&)const;
		const MyArray& operator+=(const MyArray&);

		elemType& operator[](int index);	
		elemType operator[](int index) const ; 
		elemType& at(int);		//new
		elemType at(int) const;	//new

		int getSize() const;
		int getCapacity() const;
		void resize(size_t n, elemType c = '\0'); 
		void reserve(size_t n = 0);
		void shrink_to_fit();	
		void clear();			
		bool isEmpty()const;
		void printInfo()const;

		class OutOfRange;

	protected:
		elemType* list;
		int size;
		int capacity;
};
#endif //

 //For exception handing
template<class elemType>
class MyArray<elemType>::OutOfRange:public exception{
	public:
	OutOfRange(string ms):mgs(ms){}
	string what(){
		return mgs;
	}
	private:
	string mgs;
}; 

template <class elemType>
class MyVector:public MyArray<elemType>{
	public:
	MyVector(int n = 10);
	MyVector operator+(const MyVector&)const;	
};

template<class elemType>
MyVector<elemType>::MyVector(int t):MyArray<elemType>(t) 
{ 

}

//for Vector case
template <class elemType>
MyVector<elemType> MyVector<elemType>::operator+(const MyVector<elemType>&m) const{

	MyVector<elemType> temp = *this;
	while( this->size+m.size > temp.capacity){
	       	temp.reserve(temp.capacity*2); //can be if but ok	
	}

	int t = 0;
		for(int i = this->size; i < this->size+m.size; i++)
		    temp.list[i] = m.list[t++];

		temp.size = this->size+m.size; 
		return temp;

}


template <class elemType>
int MyArray<elemType>::getSize() const{
	return size;
}

template <class elemType>
int  MyArray<elemType>::getCapacity() const{
	return capacity;
}


template <class elemType>
bool  MyArray<elemType>::isEmpty()const{
	return size == 0;
}

template <class elemType>
void  MyArray<elemType>::printInfo()const{
	cout<<"Size:"<<getSize()<<endl;
	cout<<"Capacity:"<<getCapacity()<<endl;
}

//Default constructor
//

template <class elemType>
MyArray<elemType>::MyArray(int Size, elemType value){

		size = Size;
		capacity = Size;
		list = new elemType[Size];	
		for(int i = 0; i < Size;i++)
			list[i] = value;

}


template <class elemType>
MyArray<elemType>::MyArray(int n ):size(0),capacity(n){ //this time
	if(n<=0){
		cout<<"The array size must be positive.\nCreating "
		    <<"a default array with capacity 10 created."<<endl;
		capacity = 10;
		size = 0; //changed here
	}
	list = new elemType[capacity];	
}

template <class elemType>
MyArray<elemType>::MyArray(const MyArray<elemType>& otherArray){
	
	capacity = otherArray.capacity;
	size	 = otherArray.size;
	list   =  new elemType[capacity];

	for(int i = 0; i < size; i++){
		list[i] = otherArray.list[i];
	}	
}

template <class elemType>
void MyArray<elemType>::reserve(size_t n){
	if(n > capacity){
		elemType *temp = new elemType[n]();
		for(int i = 0; i < size; i++)
		    temp[i] = list[i];
		capacity = n;
		delete[] list;
		list = temp;
	}
}

template <class elemType>
void MyArray<elemType>::resize(size_t n, elemType c){
		
	while( n > capacity) reserve(capacity*2);
	
	if(n > size)
		for(int i = size; i < n;i++)
			list[i] = c;
	size = n;
}


template <class elemType>
MyArray<elemType>& MyArray<elemType>:: operator= (const MyArray<elemType>& m){//const phia truoc
	if(this != &m){
		size = m.size;
		capacity = m.capacity;	
		delete [] list;
		list = new elemType[capacity];
		for(int i = 0; i < size;i++)
			list[i] = m.list[i];
	}
	return *this;
	
}


template <class elemType>
bool MyArray<elemType>:: operator==(const MyArray&m)const{
	if(size != m.size)
		return false;
	for(int i =0; i<size;i++)
		if(list[i] !=m.list[i])
			return false;
	return true;
}

template <class elemType>
bool MyArray<elemType>::operator!=(const MyArray&m) const{
	return !(*this==m);
}


template <class elemType>
elemType& MyArray<elemType>::operator[](int index){
	//throw exception here
	return list[index];
}

template <class elemType>
elemType MyArray<elemType>::operator[](int index) const{
	//throw exception here
	return list[index];
}


template <class elemType>
MyArray<elemType>::~MyArray() {
	delete[] list ;
	list = NULL;

}

template <class elemType1>
istream& operator>> (istream& in,MyArray<elemType1> &m) {
	
	string input_string;
	getline(in,input_string);

	int the_length = input_string.length();
	while( the_length > m.capacity) m.reserve(m.capacity*2);
	m.size = the_length;
	for(int i =0; i<the_length;i++){
		m.list[i] = input_string[i];
	}

	return in;
}


template <class elemType>
ostream& operator<< (ostream& out,const MyArray<elemType> &m) {
	
	if(m.size ==0){
	       	out<<"Empty Array"<<endl;
		return out;
	}
	
	for(int i = 0; i<m.size;i++){
		out<<m.list[i]<<", "; 
	} 

	return out;
}


//for MyArray implementation

template <class elemType>
MyArray<elemType> MyArray<elemType>::operator+(const MyArray<elemType>&m) const{

	MyArray<elemType> temp = *this;
	while( this->size+m.size > temp.capacity){
	       	temp.reserve(temp.capacity*2); //can be if but ok	
	}

	int t = 0;
		for(int i = this->size; i < this->size+m.size; i++)
		    temp.list[i] = m.list[t++];

		temp.size = this->size+m.size; 
		return temp;

}


template <class elemType>
const MyArray<elemType>&  MyArray<elemType>::operator+=(const MyArray<elemType>&m){

	MyArray<elemType> temp = *this;
	while( size+m.size > temp.capacity){
	       	temp.reserve(temp.capacity*2); //can be if but ok	
	}

		int t = 0;
		for(int i = size; i < size+m.size; i++)
		    temp.list[i] = m.list[t++];

		temp.size = size+m.size; 

		*this = temp;
		return *this;
}



template<class elemType>
void  MyArray<elemType>::shrink_to_fit(){
	MyArray<elemType> temp (size);
	for(int i = 0; i<size;i++){
		temp.list[i] = list[i];
	}
	temp.size = size;
	       	 //can be if but ok		
	*this = temp;


}
 

template <class elemType>
elemType& MyArray<elemType>::at(int index){
	try{
		if(index < 0 || index >= size){
			throw MyArray::OutOfRange("MyArray::_M_range_check"); 
		}
		return list[index];

	}
	catch(MyArray::OutOfRange& e){
		cerr<< "Out of Range error: "<<e.what()<<endl;
		cerr<<"The program is now exitting!"<<endl;
		exit(1);
	}

}

template <class elemType>
elemType MyArray<elemType>::at(int index) const{
	try{
		if(index < 0 || index >= size || index >=capacity){
			throw MyArray::OutOfRange("MyArray::_M_range_check");
		}
		return list[index];

	}
	catch(MyArray::OutOfRange& e){
		cerr<< "Out of Range error: "<<e.what()<<endl;
		cerr<<"The program is now exitting!"<<endl;
		exit(1);
	}
}

template <class elemType>
void MyArray<elemType>::clear(){
	MyArray<elemType> temp ((*this).getCapacity());
	for(int i = 0; i<size;i++){
		temp.list[i] = list[i];
	}
	temp.size = 0;
	       	 //can be if but ok		
	*this = temp;

}

//Week2_started from here
class MyString:public MyArray<char>{
	public:
	       	MyString();
	// Constructs an empty string, with a length of zero characters. 
	// *default capacity = 10

	MyString( const MyString &str ); 
	// Constructs a copy of "str". (copy constructor)

	MyString( const MyString &str, size_t pos, size_t len = msize ); // (substring constructor)
	// Copies the portion of str that begins at the character position "pos" and spans "len" characters 
	// (or until the end of str, if either str is too short or if len is string::msize).

	MyString( const char *s ); 
	// Copies the array of character (C-string) pointed by s.
	// The char *s is a pointer to a null-terminated sequence of characters. (all following char* are the same/)
	// The sequence is copied as the new value for the string.

	~MyString(); 
	// Destroys the string object.

	static const size_t msize = -1;
	
	//Note: maximum size. You may use SIZE_MAX at <cstdint>, too.

	MyString& append( const MyString &str ); 
	// Appends a str on the tail of current MyString. 
	// *Return the reference of itself

	MyString substr(size_t pos, size_t len = msize) const;
	// The substring is the portion of the object that starts at character position pos and spans len characters 
	// (or until the end of the string, whichever comes first).
	// *Returns a newly constructed string object with its value initialized to a copy of a substring of this object.

	MyString& insert( size_t pos, const MyString &str);
	// Inserts a copy of a str at "pos".
	// example: str = "to be question", str2 = "the "
	// str.insert(6,str2); 
	// = to be (the )question = to be the question
	// *Return the reference of itself

	MyString& insert( size_t pos, const MyString &str, size_t subpos, size_t sublen = msize );
	// Inserts a copy of a substring of str at "pos". The substring is the portion of "str" that
	// begins at the character position subpos and spans sublen characters (or until the end of str).
	// example: str = "to be the question", str3 = "or not to be"
	// str.insert(6,str3,3,4); // to be (not )the question
	// *Return the reference of itself

	MyString& erase( size_t pos, size_t len = msize ); 
	// Erases the portion of the string value that begins at the character position pos and spans len characters 
	// (or until the end of the string, if either the content is too short or if len is string::msize.)
	// *Return the reference of itself

	size_t find( const MyString &str, size_t pos = 0 ) const;
	// Searches the portion of the string value that begins at the character position "pos" until the end of the string
	// for the first occurrence of the string str.
	// Return Value: The position of the first character of the first match. If no matches were found, the function returns MyString::msize.

	size_t find_first_of( const MyString &str, size_t pos = 0 ) const;
	// Searches the portion of the string value that begins at the character position "pos" until the end of the string
	// for the first character that matches *any* of the characters of the string str.
	// Return Value: The position of the first character that matches. If no matches are found, the function returns MyString::msize.

	//You may add several helper functions or operators here
};

//Implement section

//Constructor istruction, using the default constructor
MyString::MyString(){
	//empty
}
MyString::~MyString(){
//	cout<<"Destructor of class MyString runs, for destructor testing only"<<endl;
	//set empty
}

MyString::MyString( const MyString &str ){
	*this = str;
}

MyString::MyString( const MyString &str, size_t pos, size_t len){

			try {
				if(pos < 0 || pos>= str.getSize())
					throw MyArray::OutOfRange("MyArray::_M_range_check"); 
			int length = 0;
			if(len > str.getSize()) length = str.getSize()-pos;
			else length = len;
			
			MyString temp;
			while(length > temp.capacity) temp.reserve(temp.capacity*2);
			temp.size = length;
			int k = 0;
			for(int i = pos;i< pos+length;i++){
				temp[k] = str[i];
				k++;
			}
			*this = temp;	


			}
			catch(MyArray::OutOfRange& e){
				cerr<< "Out of Range error: "<<e.what()<<endl;
				cerr<<"Object creation failed, the program is now exit !"<<endl;
				exit(1);
			}

}

MyString::MyString( const char *s ){
			
			int length = 0;
			length = strlen(s);

			while(length > capacity) reserve(capacity*2);
						
			size = length;
					
			for(int i = 0;i< length;i++){
				list[i] = s[i];
			}
				


}

MyString&  MyString::append( const MyString &str ){
	
	int newsize = size + str.size;
	
	while(newsize > capacity) reserve(capacity*2);
	int k = 0;
	for(int i = size; i<newsize;i++){
		list[i] = str[k];
		k++;
	}
	size = newsize;

	return *this;


}

MyString MyString::substr(size_t pos, size_t len ) const{
			try {
				if(pos < 0 || pos >= size)
					throw MyArray::OutOfRange("MyArray::_M_range_check"); 

				int length = 0;
				if(len > size) length = size - pos;
				else length = len;
			
				MyString temp;
				while(length > temp.capacity) temp.reserve(temp.capacity*2);
				temp.size = length;			
				int k = 0;
				for(int i = pos;i< pos+length;i++){
					temp[k] = (*this)[i];
					k++;
				}

				return temp;

			}
			catch(MyArray::OutOfRange& e){
				cerr<< "Out of Range error: "<<e.what()<<endl;
			}

				return *this;

	

}

MyString& MyString::insert( size_t pos, const MyString &str){
			try {
				if(pos < 0 || pos >= size)
					throw MyArray::OutOfRange("MyArray::_M_range_check"); 
			int newsize = size + str.size;
		
			while(newsize > capacity) reserve(capacity*2);
			MyString k = substr(pos,size);
			
			int c = 0;
			for(int i = pos; i<pos+str.size;i++){
				list[i] = str[c];
				c++;
			}

			int m = 0;
			for(int i = pos+str.size; i< newsize;i++){
				list[i] = k[m];
				m++;
			}

			size = newsize;


			}
			catch(MyArray::OutOfRange& e){
				cerr<< "Out of Range error: "<<e.what()<<endl;
			}
				return *this;


}

MyString& MyString::insert( size_t pos, const MyString &str, size_t subpos, size_t sublen){
			try {
				if(pos < 0 || pos >= size || subpos < 0 || subpos >= size)
					throw MyArray::OutOfRange("MyArray::_M_range_check"); 


			int length = 0;

			if(sublen > str.size) length = str.size - subpos;
			else length = sublen; 

			int newsize = size + length;
		
			while(newsize > capacity) reserve(capacity*2);

			MyString k = substr(0,pos);
			MyString l = substr(pos,size-pos);
			MyString h = str.substr(subpos,length);
			k.append(h);
			k.append(l);
			size = newsize;
			*this = k;

			}
			catch(MyArray::OutOfRange& e){
				cerr<< "Out of Range error: "<<e.what()<<endl;
			}
				return *this;


}

MyString& MyString::erase( size_t pos, size_t len ){
			try {
				if(pos < 0 || pos >= size)
					throw MyArray::OutOfRange("MyArray::_M_range_check"); 

			int length = 0;

			if(len > size) length = size - pos;
			else length = len; 

			MyString temp1;
			temp1.reserve(capacity);
			int h = 0;
			for(int i = 0; i<pos;i++){
				temp1[i] = list[i];
				h++;
			}
			temp1.size = h;

			MyString temp2;
			temp2.reserve(capacity);
			int k = 0;
			for(int i = pos+length ; i<size;i++){
				temp2[k] = list[i];
				k++;
			}

			temp2.size = k;
			temp1.append(temp2);
			*this = temp1;
			
			}
			catch(MyArray::OutOfRange& e){
				cerr<< "Out of Range error: "<<e.what()<<endl;
			}
			
			return *this;

}

size_t MyString::find( const MyString &str, size_t pos  ) const{
	string my_string(list);
	string temp(str.list);
	size_t result =  my_string.find(temp,pos);
	
	if(result == string::npos) return msize;
	
	return result;
}

size_t MyString::find_first_of( const MyString &str, size_t pos  ) const{
	string my_string(list);
	string temp(str.list);
	size_t result = my_string.find_first_of(temp,pos);
	
	if(result == string::npos) return msize;
		
	return result;
}
