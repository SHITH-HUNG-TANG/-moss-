#ifndef PG2MyString_H
#define PG2MyString_H
#include<iostream>
#include<stdexcept>
#include<stdio.h>
using namespace std;

class rangeException :public::logic_error {
public:
    rangeException()
        :logic_error("out_of_range exception.") {}
};
template<typename T>
class MyArray {	//modify this class into a template class
    friend ostream& operator<<(ostream& out, const MyArray& outpoint)
    {

        int temp = outpoint.size;
        /*for (int i = temp; i >= 0; i--)//除去前方空格
        {
            if (outpoint.data[i] == 0 && i != 0)
                temp--;
            if (outpoint.data[i] != 0)
            {
                break;
            }
        }*/
        for (int i = 0; i<temp; i++)
        {
            out << outpoint.data[i];
            out << ' ';
        }

        out << endl;
        return out;
    }
    friend istream& operator>>(istream& in, MyArray<T>& inpoint)
    {
        in=MyString(inpoint);
        
        return in;
    }
    
public:
    MyArray(int Cap)
    {
        if (Cap < 0)
        {
            cout << "capacity 應大於等於0" << endl;

        }
        else
        {
            data = new T[Cap];
            //  for (int i = 0; i < Cap; i++)
                  //data[i] = 0;
            capacity = Cap;
        }
    }

    MyArray(int sizetemp, T value)
        : size(0), data(nullptr), capacity(10)
    {
        data = new T[sizetemp];
        for (int i = 0; i < sizetemp; i++)
            data[i] = value;
        size = sizetemp;
    }

    MyArray() : size(0), data(nullptr), capacity(10) {}

    MyArray(const MyArray<T>& right)
        : size(right.size)
    {
        data = new T[right.capacity]();

        for (int i = 0; i < size; i++)
            data[i] = right.data[i];
        capacity = right.capacity;
    }

    bool operator==(const MyArray<T>& right) const
    {
        if (size != right.size)
            return false;
        else
        {
            int check = 0;
            for (int i = 0; i < size; i++)
            {
                if (data[i] != right.data[i])
                {
                    check++;
                    return false;
                }
            }
            if (check == 0)
                return true;
        }
    }

    bool operator!=(const MyArray<T>& right) const
    {
        if (size != right.size)
            return true;
        else
        {
            int check = 0;
            for (int i = 0; i < size; i++)
            {
                if (data[i] != right.data[i])
                {
                    check++;
                    return true;
                }
            }
            if (check == 0)
                return false;
        }
    }

    MyArray<T> operator+(const MyArray<T>& right) 	//new
    {
        MyArray temp(size + right.size);
        temp.size = size + right.size;

        for (int i = 0; i < size; i++)
            temp.data[i] = data[i];
        int j = 0;
        for (int i = size; i < size + right.size; i++)
        {
            temp.data[i] = right.data[j];
            j++;
        }
        return temp;
    }

    MyArray<T>& operator+=(const MyArray<T>& right)		//new
    {
        while ( size + right.size> capacity)
            capacity = capacity * 2;

        T* temp = new T[capacity];
        int j = 0;
        for (int i = 0; i < size; i++)
        {
            temp[i] = data[i];
        }
        for (int i = size; i < size + right.size; i++)
        {
            temp[i] = right.data[j];
            j++;
        }
        delete[]data;
        data = temp;
        size = size + right.size;
        return *this;
    }

    const MyArray<T>& operator=(const MyArray<T>& right)
    {
        delete[]data;
        size = right.size;
        capacity = right.capacity;
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = right.data[i];
        return*this;
    }

    ~MyArray()
    {
        delete[] data;
    }

   

    T& operator[](int subscript)
    {
        //check for subscript out-of-range error
        if (subscript < 0 || subscript >= size)
        {
            cout << "\nerror: subscript " << subscript << "out of range" << endl;
            exit(1);
        }
        return data[subscript];
    }

    T operator[](int subscript) const
    {
        //check for subscript out-of-range error
        if (subscript < 0 || subscript >= size)
        {
            cout << "\nError: Subscript " << subscript << "out of range" << endl;
            exit(1);
        }
        return data[subscript];
    }

    T& at(int subscript)	//new
    {
        if (subscript < 0 || subscript >= size)
            throw rangeException();
        return data[subscript];
    }

    T at(int subscript) const	//new
    {
        if (subscript < 0 || subscript >= size)
            throw rangeException();
        return data[subscript];
    }

    int getSize() const
    {
        return size;
    }

    int  getCapacity() const
    {
        return capacity;
    }

    void resize(size_t n, T c)
    {
        int cap = capacity;
        while (n > cap)
            cap = cap * 2;
        reserve(cap);
        if (n > size)
            for (int i = size; i < n; i++)
                data[i] = c;
        size = n;
    }

    void reserve(size_t n)
    {
        capacity = n;
        T* temp = new T[capacity]();

        for (int i = 0; i < size; i++)
            temp[i] = data[i];
        delete[]data;
        data = temp;
    }

    void shrink_to_fit()	//new
    {
        T* temp = new T[size]();
        for (int i = 0; i < size; i++)
            temp[i] = data[i];
        delete[]data;
        data = temp;
        capacity = size;
    }

    void clear()			//new
    {
        size = 0;
    }

    bool isEmpty()			//new
    {
        if (size == 0)
            return true;
        else

            return false;
    }


    int size = 0;
    int capacity = 10;
    T* data;
};

using namespace std;

class MyString : public MyArray<char>
{
	//friend ostream &operator<<(ostream& output, const MyString& str);

public:
	MyString():MyArray(){}
	// Constructs an empty string, with a length of zero characters. 
	// *default capacity = 10

	MyString(const MyString& str) : MyArray()
     {
         data = new char[str.capacity]();
        for (int i = 0; i < str.size; i++)
            data[i] = str.data[i];
        capacity = str.capacity;
        size = str.size;
     }
    
	// Constructs a copy of "str". (copy constructor)

    MyString(const MyString& str, size_t pos, size_t len = msize) // (substring constructor)
    {
        capacity = 10;
            while (len> capacity)
                capacity = capacity * 2;
        if (pos + len < size)
        {            
            data = new char[capacity]();
            for (int i = 0; i < len; i++)
                data[i] = str.data[pos+i];           
            size = len;
        }
        else
        {
             data = new char[capacity]();
            for (int i = 0; i+pos<size; i++)
                data[i] = str.data[pos+i];           
            size = len;
        }
    }
	// Copies the portion of str that begins at the character position "pos" and spans "len" characters 
	// (or until the end of str, if either str is too short or if len is string::msize).

	MyString(const char* s)
    {
        int len =strlen(s);
        while (len > capacity)
            capacity = capacity * 2;
        data = new char[capacity];
        for (int i = 0; i < len; i++)
            data[i] = s[i];
        size = len;
    }
	// Copies the array of character (C-string) pointed by s.
	// The char *s is a pointer to a null-terminated sequence of characters. (all following char* are the same/)
	// The sequence is copied as the new value for the string.

    ~MyString()
    {
       // delete[]data;
    }
	// Destroys the string object.

	static const size_t msize = -1;
	//Note: maximum size. You may use SIZE_MAX at <cstdint>, too.

	MyString& append(const MyString& str)
    {
        int oringinsize = size;
        resize(size + str.size,'0');
        for (int i = 0; i < str.size; i++)
            data[oringinsize + i] = str.data[i];
        return *this;
    }
	// Appends a str on the tail of current MyString. 
	// *Return the reference of itself

    MyString substr(size_t pos, size_t len = msize) const
    {
        MyString temp;
        int  cap = temp.capacity;
        if(len<0)
            len=msize;
        if (len ==msize )
        {
            len = size - pos;
        }
        while (len > cap)
            cap = cap * 2;
        temp.capacity = cap;        
        temp.data = new char[cap];
        temp.size = len;
        for (int i = 0; i < len; i++)
            temp.data[i] = data[pos + i];
        return temp;
    }

	// The substring is the portion of the object that starts at character position pos and spans len characters 
	// (or until the end of the string, whichever comes first).
	// *Returns a newly constructed string object with its value initialized to a copy of a substring of this object.

    MyString& insert(size_t pos, const MyString& str)
    {
      /*  size = size + str.size;
        while (size > capacity)
            capacity = capacity * 2;
        char* temp = new char[capacity]();
        for (int i = 0; i < pos; i++)
            temp[i] = data[i];
        for (int i =0; i < str.size; i++)
            temp[i + pos] = str[i];
        for (int i = 0; i < size - pos; i++)
            temp[str.size + pos + i] = data[pos + i];
        delete[]data;
        data = temp;
        return *this;*/
        MyString portion1, portion2;
        portion1 = substr(0, pos);
        portion2 = substr(pos, msize);
        portion1 += str;
        portion1 += portion2;
        *this = portion1;
        return *this;
    }

	// Inserts a copy of a str at "pos".
	// example: str = "to be question", str2 = "the "
	// str.insert(6,str2); 
	// = to be (the )question = to be the question
	// *Return the reference of itself

    MyString& insert(size_t pos, const MyString& str, size_t subpos, size_t sublen = msize)
    {
        MyString portion1, portion2,str1;
        portion1 = substr(0, pos);
        portion2 = substr(pos, msize);
        str1 = substr(subpos, sublen);
        portion1 += str1;
        portion1 += portion2;
        *this = portion1;
        return *this;
    }
	// Inserts a copy of a substring of str at "pos". The substring is the portion of "str" that
	// begins at the character position subpos and spans sublen characters (or until the end of str).
	// example: str = "to be the question", str3 = "or not to be"
	// str.insert(6,str3,3,4); // to be (not )the question
	// *Return the reference of itself

    MyString& erase(size_t pos, size_t len = msize)
    {       
        if (len!=msize)
        {            
            MyString portion1 = substr(0, pos);
            MyString portion2 = substr(pos+len, -1);
             portion1 += portion2;
             *this = portion1;
        }
        else
        {          
            MyString portion1 = substr(0, pos);
            *this = portion1;
        }
        return *this;
    }
	// Erases the portion of the string value that begins at the character position pos and spans len characters 
	// (or until the end of the string, if either the content is too short or if len is string::msize.)
	// *Return the reference of itself

    size_t find(const MyString& str, size_t pos = 0) const
    {
        int check;
        MyString find = str.substr(pos, str.size-pos);
        cout << "目標" << find << endl;
        for (int i = 0; i < size; i++)
        {
            check = 0;
            for (int j = 0; j < find.size; j++)
            {
                if (data[i+j] != find.data[j])
                {
                    check = 1;
                    break;
                }
            }
            if (check == 0)
                return i;
            if (i == size - 1 && check == 1)
            {
                cout << "string中不存在" << str ;
                return-1;
            }
        }
    }
	// Searches the portion of the string value that begins at the character position "pos" until the end of the string
	// for the first occurrence of the string str.
	// Return Value: The position of the first character of the first match. If no matches were found, the function returns MyString::msize.

    size_t find_first_of(const MyString& str, size_t pos = 0) const
    {
      
        MyString find = str.substr(pos, str.size-pos);
        cout << "目標" << find << endl;
        for (int i = 0; i < size; i++)
        {
           
            for (int j = 0; j < find.size; j++)
            {
                if (data[i + j] == find.data[j])
                {
                    cout << "找到" << data[i + j] << endl;
                    return i;

                }
            }
            if (i == size - 1)
            {
             
                return -1;
            }
        }
    }
	// Searches the portion of the string value that begins at the character position "pos" until the end of the string
	// for the first character that matches *any* of the characters of the string str.
	// Return Value: The position of the first character that matches. If no matches are found, the function returns MyString::msize.

	//You may add several helper functions or operators here
	//...
}; // end class MyString

#endif
