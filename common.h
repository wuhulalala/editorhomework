#ifndef _TEST_H
#define _TEST_H
typedef enum { NOT_PRESENT, ENTRY_FOUND, RANGE_ERROR, SUCCESS, OVER_FLOW, FAILURE } Status;//定义枚举类型

#include<iostream>
using namespace std;
template <class ElemType>
void display(ElemType&e)
{
	cout<<e<<"  ";
}
#endif
