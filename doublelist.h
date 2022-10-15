
#include"common.h"
template<class ElemType>
struct Node_D  //�ڵ���
{
	ElemType data;    //���ݳɷ�
	Node_D<ElemType>* back;   //ָ��ɷ�
	Node_D<ElemType>* next;
	//���캯��ģ��
	Node_D(); //�޲������캯��ģ��
	Node_D(const ElemType &e, Node_D<ElemType>* linkback = NULL,Node_D<ElemType> * linknext=NULL);//��֪�������ָ�������ṹ

};
//�����Ա���ģ��
template<class ElemType>
class dblist
{
protected:
	//����ʵ�ֵ����ݳ�Ա
	Node_D<ElemType>* head; //ͷָ��
	//��������ģ��
	Node_D<ElemType>* GetElemPtr(int pos) const;
	//����ָ���position���ڵ��ָ��
	void Init();//��ʼ�����Ա�
public:
	//��������
	dblist(); // �޲ι��캯��
	virtual ~dblist();
	int length() const;  //�����Ա���
	bool empty() const;         //�ж��Ƿ�Ϊ��
	void clear();         //������Ա�
	void traverse(void (*visit)(ElemType&)) const; //��������
	Status getelem(int pos, ElemType& e) const; //��ָ��λ�õ�Ԫ��ֵ
	Status setelem(int pos, const ElemType& e);//�趨ָ��λ�õ�Ԫ��ֵ
	Status Delete(int pos, ElemType& e);//ɾ��Ԫ��
	Status Delete(int pos);  //
	bool insert(int pos, const ElemType& e); //����Ԫ��
	Status locatepos(int pos, ElemType& e) const;      //����posλ�õ�ֵ���ҷ���
	Status locatevalue(const ElemType value, int& e) const;   //����ֵΪvalue��λ��
	Status addtail(const ElemType& e);             //��β������һ��Ԫ��
	Status addhead(const ElemType& e);             //��ͷ������Ԫ��
	dblist(const dblist<ElemType>& source);//�������캯��
	dblist<ElemType>& operator =(const dblist<ElemType>& source);//���������
	Status creatlist(int n);                //��������
	void reverse();                    //����  


};
template<class ElemType>
//����ָ����Ϊ�յĽڵ�
Node_D<ElemType>::Node_D() {
	next = NULL;
}
template<class ElemType>
//����������Ϊitem��ָ����Ϊlink�Ľڵ�
Node_D<ElemType>::Node_D(const ElemType& e, Node_D<ElemType>* linkback, Node_D<ElemType>* linknext ) {
	data = e;
	next = linknext;
	back = linkback;
}
template<class ElemType>
dblist<ElemType>::dblist() {
	Init();     //����һ��������
}
template<class ElemType>
void dblist<ElemType>::Init() {

	head = new Node_D<ElemType>;
	head->next = head;
	head->back = head->next;
}
template<class ElemType>
Node_D<ElemType>* dblist<ElemType>::GetElemPtr(int pos) const {
	if (pos == 0)               //ͷ������Ϊ��
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
	//cout << "��������" << endl;
	clear();
	delete head;
}
template<class ElemType>
int dblist<ElemType>::length() const {
	int count = 0; //������
	for (Node_D<ElemType>* tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{//��tmpPtr����ָ��ÿ��Ԫ��
		count++;
	}
	return count;
}
template<class ElemType>
bool dblist<ElemType>::empty() const {  //�ж��Ƿ�Ϊ��
	return head->next == head;
}
template<class ElemType>
void dblist<ElemType>::clear() {
	ElemType tmp;  //��ʱԪ��ֵ
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
