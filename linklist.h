#include"common.h"

template<class ElemType>
struct Node  //节点类
{
	ElemType data;    //数据成分
	Node<ElemType>* next;   //指针成分
	//构造函数模板
	Node(); //无参数构造函数模板
	Node(ElemType item, Node<ElemType>* link = NULL);//已知数据域和指针域建立结构

};
//简单线性表类模板
template<class ElemType>
class simplelist
{
protected:
	//链表实现的数据成员
	Node<ElemType>* head; //头指针
	//辅助函数模板
	Node<ElemType>* GetElemPtr(int pos) const;
	//返回指向第position个节点的指针
	void Init();//初始化线性表
public:
	//公共操作
	simplelist(); // 无参构造函数
	virtual ~simplelist();
	int length() const;  //求线性表长度
	bool empty() const;         //判断是否为空
	void clear();         //清空线性表
	void traverse(void (*visit)(ElemType&)) const; //遍历链表
	Status getelem(int pos, ElemType& e) const; //求指定位置的元素值
	Status setelem(int pos, const ElemType& e);//设定指定位置的元素值
	Status Delete(int pos, ElemType& e);//删除元素
	int Delete(int pos);  //
	Status insert(int pos, const ElemType& e); //插入元素
	Status locatepos(int pos, ElemType& e) const;      //查找pos位置的值并且返回
	Status locatevalue(const ElemType value, int& e) const;   //查找值为value的位置
	Status addtail(const ElemType& e);             //在尾部插入一个元素
	Status addhead(const ElemType& e);             //在头部插入元素
	simplelist(const simplelist<ElemType>& source);//拷贝构造函数
	simplelist<ElemType>& operator =(const simplelist<ElemType>& source);//运算符重载
	Status creatlist(int n);  //创建链表
	Status creatlist(const simplelist<ElemType>& la, const simplelist<ElemType>& lb);//创建链表
	Status reverse();                    //反序  
	void outsidesort(int low, int high);    //排序
	Status insidesort(int temp[], int low, int high);//排序
	void Deleterepeat();         //删除重复元素
	void mergelist(simplelist<ElemType>& la, simplelist<ElemType>& lb);

};
using namespace std;
template<class ElemType>
//构造指针域为空的节点
Node<ElemType>::Node() {
	next = NULL;
}
template<class ElemType>
//构造数据域为item和指针域为link的节点
Node<ElemType>::Node(ElemType item, Node<ElemType>* link) {
	data = item;
	next = link;
}
template<class ElemType>
simplelist<ElemType>::simplelist() {
	Init();     //构造一个空链表
}
template<class ElemType>
void simplelist<ElemType>::Init() {

	head = new Node<ElemType>;
}
template<class ElemType>
Node<ElemType>* simplelist<ElemType>::GetElemPtr(int pos) const {
	if (pos == 0)               //头结点序号为零
	{
		return head;
	}
	Node<ElemType>* tmpPtr = head->next;
	int curpos = 1;
	while (tmpPtr != NULL && curpos < pos)
	{
		tmpPtr = tmpPtr->next;
		curpos++;
	}
	if (tmpPtr != NULL && curpos == pos)
	{
		return tmpPtr;
	}
	else
		return NULL;
}
template<class ElemType>
simplelist<ElemType>::~simplelist() {
	//cout << "正在析构" << endl;
	clear();
	delete head;
}
template<class ElemType>
int simplelist<ElemType>::length() const {
	int count = 0; //计数器
	for (Node<ElemType>* tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{//用tmpPtr依次指向每个元素
		count++;
	}
	return count;
}
template<class ElemType>
bool simplelist<ElemType>::empty() const {  //判断是否为空
	return head->next == NULL;
}
template<class ElemType>
void simplelist<ElemType>::clear() {
	ElemType tmp;  //临时元素值
	while (length() > 0)
	{
		Delete(1, tmp);
	}

}
template<class ElemType>
void simplelist<ElemType>::traverse(void (*visit)(ElemType&)) const { //遍历数组元素
	for (Node<ElemType>* tmp = head->next; tmp != NULL; tmp = tmp->next)
	{
		(*visit)(tmp->data);
	}
	cout << endl;
}
template<class ElemType>                               //读取第pos个位置的元素
Status simplelist<ElemType>::getelem(int pos, ElemType& e) const {
	if (pos<1 || pos>length())
	{
		return RANGE_ERROR;
	}
	else
	{
		Node<ElemType>* tmp;
		tmp = GetElemPtr(pos);
		e = tmp->data;
		return ENTRY_FOUND;
	}


}
template<class ElemType>                                   //用e为第pos位置的元素赋值
Status simplelist<ElemType>::setelem(int pos, const ElemType& e) {

	if (pos<1 || pos>length())
	{
		return RANGE_ERROR;
	}
	else
	{
		Node<ElemType>* tmp;
		tmp = GetElemPtr(pos);
		tmp->data = e;
		return ENTRY_FOUND;
	}
}
template<class ElemType>                       //删除pos位置的元素
Status simplelist<ElemType>::Delete(int pos, ElemType& e) {
	if (pos<1 || pos>length())
	{
		return RANGE_ERROR;
	}
	else
	{
		Node<ElemType>* tmpPtr;
		tmpPtr = GetElemPtr(pos - 1);
		Node<ElemType>* nextPtr = tmpPtr->next;
		tmpPtr->next = nextPtr->next;
		e = nextPtr->data;
		delete nextPtr;
		return ENTRY_FOUND;

	}
}
template<class ElemType>      //删除函数重载
int  simplelist<ElemType>::Delete(int pos) {
	if (pos<1 || pos>length())
	{
		return 0;
	}
	else
	{
		Node<ElemType>* tmpPtr;
		tmpPtr = GetElemPtr(pos - 1);
		Node<ElemType>* nextPtr = tmpPtr->next;
		tmpPtr->next = nextPtr->next;
		delete nextPtr;
		return 1;

	}
}
template<class ElemType>         //在pos位置插入e
Status simplelist<ElemType>::insert(int pos, const ElemType& e) {
	if (pos<1 || pos>length())
	{
		return RANGE_ERROR;
	}
	else
	{
		Node<ElemType>* tmpPtr;
		tmpPtr = GetElemPtr(pos - 1);
		Node<ElemType>* newPtr;
		newPtr = new Node<ElemType>(e, tmpPtr->next);
		tmpPtr->next = newPtr;
		return SUCCESS;

	}
}
template<class ElemType>         //拷贝构造函数
simplelist<ElemType>::simplelist(const simplelist<ElemType>& source) {
	Init();
	Node<ElemType>* tmpPtr1, * tmpPtr2;
	Node<ElemType>* first, * last;
	int len = source.length();
	for (int i = 1; i <= len; i++)
	{
		tmpPtr1 = source.GetElemPtr(i);
		insert(i, tmpPtr1->data);

	}
}
template<class ElemType>            //定位pos位置原素的值
Status simplelist<ElemType>::locatepos(int pos, ElemType& e) const {
	if (pos<1 || pos>length())
	{
		return RANGE_ERROR;
	}
	else
	{
		Node<ElemType>* tmpPtr;
		tmpPtr = GetElemPtr(pos);
		e = tmpPtr->data;
		return SUCCESS;
	}
}
template<class ElemType>       //定位值为value的元素的位置
Status simplelist<ElemType>::locatevalue(const ElemType value, int& e) const {
	if (length() < 1)
	{
		return RANGE_ERROR;
	}
	else
	{
		Node<ElemType>* tmpPtr = head->next;
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
template<class ElemType>           //从尾部增加元素
Status simplelist<ElemType>::addtail(const ElemType& e) {
	Node<ElemType>* tmpPtr = head;
	Node<ElemType>* newPtr;
	newPtr = new Node<ElemType>(e, NULL);
	while (tmpPtr->next != NULL)
	{
		tmpPtr = tmpPtr->next;
	}
	tmpPtr->next = newPtr;
	if (tmpPtr->next != NULL)
	{
		return SUCCESS;
	}
	else return FAILURE;
}
template<class ElemType>              //从头部添加元素
Status simplelist<ElemType>::addhead(const ElemType& e) {
	Node<ElemType>* tmpPtr = head;
	Node<ElemType>* newPtr;
	newPtr = new Node<ElemType>;
	newPtr->next = tmpPtr->next;
	tmpPtr->next = newPtr;
	newPtr->data = e;
	if (head->next != NULL)
	{
		return SUCCESS;
	}
	else return FAILURE;
}
template<class ElemType>              //构建链表
Status simplelist<ElemType>::creatlist(int n) {

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
template<class ElemType>                  //拷贝la，lb两个链表的元素
Status simplelist<ElemType>::creatlist(const simplelist<ElemType>& la, const simplelist<ElemType>& lb) {
	Node<ElemType>* tmpPtr;
	for (tmpPtr = la.head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		addtail(tmpPtr->data);
	}
	for (tmpPtr = lb.head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		addtail(tmpPtr->data);
	}
	if (length() == la.length() + lb.length())
		return SUCCESS;
	else
		return FAILURE;
}
template<class ElemType>               //将链表中元素反序
Status simplelist<ElemType>::reverse() {
	if (length() > 1)
	{
		Node<ElemType>* tmpPtra = head->next, * tmpPtrb = tmpPtra->next, * tmp = NULL;

		while (tmpPtrb != NULL)
		{                                     /**********IMPORTANT**************/
			tmp = tmpPtrb->next;               /**********IMPORTANT**************/
			tmpPtrb->next = tmpPtra;          /**********IMPORTANT**************/
			tmpPtra = tmpPtrb;                /**********IMPORTANT**************/
			tmpPtrb = tmp;                    /**********IMPORTANT**************/
		}
		head->next->next = NULL;
		head->next = tmpPtra;
		return SUCCESS;
	}
	else
		return RANGE_ERROR;
}
template<class ElemType>
void simplelist<ElemType>::outsidesort(int low, int high) {
	int* temp = new int[length() + 5];
	int i = 0, j = 0;
	for (Node<ElemType>* tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		temp[i] = tmpPtr->data;
		i++;
	}
	insidesort(temp, low, high);
	for (Node<ElemType>* tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		tmpPtr->data = temp[j];
		j++;
	}
	delete[]temp;
}
template<class ElemType>      //排序
Status simplelist<ElemType>::insidesort(int temp[], int low, int high) {
	int i = low, j = high;
	int tmp = temp[i];
	if (i >= j)
	{
		return RANGE_ERROR;
	}
	while (i < j)
	{
		while (i < j && temp[j] >= tmp)
			j--;
		if (i < j)
			temp[i] = temp[j];
		while (i < j && temp[i] <= tmp)
			i++;
		if (i < j)
			temp[j] = temp[i];

	}
	temp[i] = tmp;
	insidesort(temp, low, i - 1);
	insidesort(temp, i + 1, high);
	return SUCCESS;
}
template <class ElemType>           //删除重复元素
void simplelist<ElemType>::Deleterepeat() {
	Node<ElemType>* tmpPtra = head->next, * tmpPtrb = head;
	int tmp = 0, i = 1;;
	while (tmpPtra->next != NULL)
	{
		if (tmpPtra->data == tmpPtra->next->data)
			tmp = Delete(i + 1);
		if (tmp == 1)
		{
			i--;
			tmp = 0;
		}
		else
		{
			tmpPtrb = tmpPtra;
			tmpPtra = tmpPtra->next;
		}
		i++;
	}
}
template<class ElemType>
void simplelist<ElemType>::mergelist(simplelist<ElemType>& la, simplelist<ElemType>& lb) {
	Node<ElemType>* tmpa = la.head->next, * tmpb = lb.head->next, * tmpc;
	tmpc = la.head;
	head = tmpc;
	while (tmpa && tmpb)
	{
		if (tmpa->data < tmpb->data)
		{
			tmpc->next = tmpa;
			tmpc = tmpc->next;
			tmpa = tmpa->next;
		}
		else
		{
			tmpc->next = tmpb;
			tmpc = tmpc->next;
			tmpb = tmpb->next;
		}
	}
	tmpc->next = tmpa ? tmpa : tmpb;
	lb.clear();


}

