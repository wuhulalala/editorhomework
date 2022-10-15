
#include"common.h"
template<class ElemType>
struct Node_D  //节点类
{
	ElemType data;    //数据成分
	Node_D<ElemType>* back;   //指针成分
	Node_D<ElemType>* next;
	//构造函数模板
	Node_D(); //无参数构造函数模板
	Node_D(const ElemType &e, Node_D<ElemType>* linkback = NULL,Node_D<ElemType> * linknext=NULL);//已知数据域和指针域建立结构

};
//简单线性表类模板
template<class ElemType>
class dblist
{
protected:
	//链表实现的数据成员
	Node_D<ElemType>* head; //头指针
	//辅助函数模板
	Node_D<ElemType>* GetElemPtr(int pos) const;
	//返回指向第position个节点的指针
	void Init();//初始化线性表
public:
	//公共操作
	dblist(); // 无参构造函数
	virtual ~dblist();
	int length() const;  //求线性表长度
	bool empty() const;         //判断是否为空
	void clear();         //清空线性表
	void traverse(void (*visit)(ElemType&)) const; //遍历链表
	Status getelem(int pos, ElemType& e) const; //求指定位置的元素值
	Status setelem(int pos, const ElemType& e);//设定指定位置的元素值
	Status Delete(int pos, ElemType& e);//删除元素
	Status Delete(int pos);  //
	bool insert(int pos, const ElemType& e); //插入元素
	Status locatepos(int pos, ElemType& e) const;      //查找pos位置的值并且返回
	Status locatevalue(const ElemType value, int& e) const;   //查找值为value的位置
	Status addtail(const ElemType& e);             //在尾部插入一个元素
	Status addhead(const ElemType& e);             //在头部插入元素
	dblist(const dblist<ElemType>& source);//拷贝构造函数
	dblist<ElemType>& operator =(const dblist<ElemType>& source);//运算符重载
	Status creatlist(int n);                //创建链表
	void reverse();                    //反序  


};
template<class ElemType>
//构造指针域为空的节点
Node_D<ElemType>::Node_D() {
	next = NULL;
}
template<class ElemType>
//构造数据域为item和指针域为link的节点
Node_D<ElemType>::Node_D(const ElemType& e, Node_D<ElemType>* linkback, Node_D<ElemType>* linknext ) {
	data = e;
	next = linknext;
	back = linkback;
}
template<class ElemType>
dblist<ElemType>::dblist() {
	Init();     //构造一个空链表
}
template<class ElemType>
void dblist<ElemType>::Init() {

	head = new Node_D<ElemType>;
	head->next = head;
	head->back = head->next;
}
template<class ElemType>
Node_D<ElemType>* dblist<ElemType>::GetElemPtr(int pos) const {
	if (pos == 0)               //头结点序号为零
	{
		return head;
	}
	Node_D<ElemType>* tmpPtr = head->next;
	int curpos = 1;
	while (tmpPtr != head && curpos < pos)
	{
		tmpPtr = tmpPtr->next;
		curpos++;
	}
	if (tmpPtr != head && curpos == pos)
	{
		return tmpPtr;
	}
	else
		return NULL;
}
template<class ElemType>
dblist<ElemType>::~dblist() {
	//cout << "正在析构" << endl;
	clear();
	delete head;
}
template<class ElemType>
int dblist<ElemType>::length() const {
	int count = 0; //计数器
	for (Node_D<ElemType>* tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{//用tmpPtr依次指向每个元素
		count++;
	}
	return count;
}
template<class ElemType>
bool dblist<ElemType>::empty() const {  //判断是否为空
	return head->next == head;
}
template<class ElemType>
void dblist<ElemType>::clear() {
	ElemType tmp;  //临时元素值
	while (length() > 0)
	{
		Delete(1, tmp);
	}

}
template<class ElemType>
void dblist<ElemType>::traverse(void (*visit)(ElemType&)) const {
	for (Node_D<ElemType>* tmp = head->next; tmp != head; tmp = tmp->next)
	{
		(*visit)(tmp->data);
	}
	cout << endl;
}
template<class ElemType>
Status dblist<ElemType>::getelem(int pos, ElemType& e) const {
	if (pos<1 || pos>length())
	{
		return RANGE_ERROR;
	}
	else
	{
		Node_D<ElemType>* tmp;
		tmp = GetElemPtr(pos);
		e = tmp->data;
		return ENTRY_FOUND;
	}


}
template<class ElemType>
Status dblist<ElemType>::setelem(int pos, const ElemType& e) {

	if (pos<1 || pos>length())
	{
		return RANGE_ERROR;
	}
	else
	{
		Node_D<ElemType>* tmp;
		tmp = GetElemPtr(pos);
		tmp->data = e;
		return ENTRY_FOUND;
	}
}
template<class ElemType>
Status dblist<ElemType>::Delete(int pos, ElemType& e) {
	if (pos<1 || pos>length())
	{
		return RANGE_ERROR;
	}
	else
	{
		Node_D<ElemType>* tmpPtr;
		tmpPtr = GetElemPtr(pos - 1);
		Node_D<ElemType>* nextPtr = tmpPtr->next;
		tmpPtr->next = nextPtr->next;
		e = nextPtr->data;
		delete nextPtr;
		return ENTRY_FOUND;

	}
}
template<class ElemType>
Status dblist<ElemType>::Delete(int pos) {
	if (pos<1 || pos>length())
	{
		return RANGE_ERROR;
	}
	else
	{
		Node_D<ElemType>* tmpPtr;
		tmpPtr = GetElemPtr(pos - 1);
		Node_D<ElemType>* nextPtr = tmpPtr->next;
		tmpPtr->next = nextPtr->next;
		delete nextPtr;
		return ENTRY_FOUND;

	}
}
template<class ElemType>
bool dblist<ElemType>::insert(int pos, const ElemType& e) {
	if (pos<1 || pos>length()+1)
	{
		return false;
	}
	else if(pos==1&&length()==0)
	{
		Node_D<ElemType> * tmpPtr=new Node_D<ElemType>(e,head,head);
		head->next=tmpPtr;
		return true;
	}
	else
	{
		Node_D<ElemType>* tmpPtr;
		tmpPtr = GetElemPtr(pos );
		
		Node_D<ElemType>* tmp=new Node_D<ElemType>(e,tmpPtr->back,tmpPtr);
		tmpPtr->back->next = tmp;
		tmpPtr->back=tmp;
		return true;

	}
}
template<class ElemType>
dblist<ElemType>::dblist(const dblist<ElemType>& source) {
	Init();
	Node_D<ElemType>* tmpPtr1, * tmpPtr2;
	Node_D<ElemType>* first, * last;
	int len = source.length();
	for (int i = 1; i <= len; i++)
	{
		tmpPtr1 = source.GetElemPtr(i);
		insert(i, tmpPtr1->data);

	}
}
template<class ElemType>
Status dblist<ElemType>::locatepos(int pos, ElemType& e) const {
	if (pos<1 || pos>length())
	{
		return RANGE_ERROR;
	}
	else
	{
		Node_D<ElemType>* tmpPtr;
		tmpPtr = GetElemPtr(pos);
		e = tmpPtr->data;
		return SUCCESS;
	}
}
template<class ElemType>
Status dblist<ElemType>::locatevalue(const ElemType value, int& e) const {
	if (length() < 1)
	{
		return RANGE_ERROR;
	}
	else
	{
		Node_D<ElemType>* tmpPtr = head->next;
		while (tmpPtr->data != value && tmpPtr != NULL)
		{
			tmpPtr = tmpPtr->next;
		}
		if (tmpPtr->data == value)
		{
			return SUCCESS;
		}
		else return NOT_PRESENT;
	}
}
template<class ElemType>
Status dblist<ElemType>::addtail(const ElemType& e) {
	Node_D<ElemType>* tmpPtr = head;
	Node_D<ElemType>* newPtr;
	while (tmpPtr->next != head)
	{
		tmpPtr = tmpPtr->next;
	}

	newPtr = new Node_D<ElemType>(e, tmpPtr,head);
	tmpPtr->next = newPtr;
	if (newPtr->next == head)
	{
		return SUCCESS;
	}
	else return FAILURE;
}
template<class ElemType>
Status dblist<ElemType>::addhead(const ElemType& e) {
	Node_D<ElemType>* tmpPtr = head;
	Node_D<ElemType>* newPtr;
	newPtr = new Node_D<ElemType>;
	newPtr->next = tmpPtr->next;
	tmpPtr->next = newPtr;
	newPtr->data = e;
	if (head->next != NULL)
	{
		return SUCCESS;
	}
	else return FAILURE;
}
template<class ElemType>
Status dblist<ElemType>::creatlist(int n) {

	ElemType tmp;
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		addhead(tmp);
	}
	reverse();
	if (length() == n)
	{
		return SUCCESS;
	}
	else return FAILURE;
}
template<class ElemType>
void dblist<ElemType>::reverse() {
	Node_D<ElemType>* tmpPtra = head->next, * tmpPtrb = head->next->next, * tmp = NULL;

	while (tmpPtrb != head)
	{                                     /**********IMPORTANT**************/
		tmp = tmpPtrb->next;              /**********IMPORTANT**************/
		tmpPtrb->next = tmpPtra;          /**********IMPORTANT**************/
		tmpPtra = tmpPtrb;                /**********IMPORTANT**************/
		tmpPtrb = tmp;                    /**********IMPORTANT**************/
	}
	head->next->next = head;
	head->next = tmpPtra;

}
