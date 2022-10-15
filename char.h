#include"linklist.h"
#include<cstring>
class charstring
{
protected:
	mutable char* strval;
	int length;
public:
	charstring(){

	}
	virtual ~charstring(){

	}
	charstring(const char * source);
	charstring(const charstring& source);
	charstring(simplelist<char>& source);
	int Length() const;
	bool empty() const;
	char* Tocstr() const { return strval; }
	char& operator [](int pos) const;
	void print() const {
		std::cout<<strval<<std::endl;
	}

};
charstring::charstring(const char * source){
	length = strlen(source);
	strval = new char[length + 1];
	strcpy(strval, source);
}
charstring::charstring(const charstring &source){
	length = strlen(source.Tocstr());
	strval = new char[length + 1];
	strcpy(strval, source.Tocstr());
}
charstring::charstring(simplelist<char> &source){
	length = source.length();
	strval = new char[length + 1];
	char tmp;
	for (int i = 0; i < length; i++)
	{
		source.getelem(i+1,tmp);
		strval[i] = tmp;
	}
}
int charstring::Length() const
{
	return length;
}
bool charstring::empty() const
{
	return length == 0;
}
