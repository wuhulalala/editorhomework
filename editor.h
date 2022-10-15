#include<fstream>
#include<string>
#include"char.h"
#include"doublelist.h"
using namespace std;
class Editor
{
	private:
		dblist<charstring> textBuffer;
		int curLineNo;
		ifstream inFile;
		ofstream outFile;
		char userCommand;   
		bool UsersayYes();
		bool NextLine();
		bool PreviousLine();
		bool GotoLine();
		bool DeleteLine();
		bool ChangeSubString();
		bool InsertLine();
		bool ChangeLine();
		void ReadFile();
		void WriteFile();
		void FindString();
		void View();
	public:
		Editor(char infName[],char outFile[]);
		~Editor(){
			inFile.close();
			outFile.close();
		}
		bool GetCommand();
		void  Runcommand();
};
using namespace std;	
void contac(charstring &target,const charstring &source)
{
	const char *cFirst=target.Tocstr();
	const char *cSecond=source.Tocstr();
	char *cTarget=new char[strlen(cFirst)+strlen(cSecond)+1];
	strcpy(cTarget,cFirst);
	strcat(cTarget,cSecond);
	target=cTarget;
	delete[]cTarget;
}
int Index(const charstring &target,const charstring &pattern)
{
	const char *cTarget=target.Tocstr();
	const char *cPattern=pattern.Tocstr();
	const char *ptr=strstr(cTarget,cPattern);
	if(ptr==NULL)
	{
		return -1;
	}
	else
	{
		return ptr-cTarget;
	}
}

charstring read(istream &input)
{
	char temp[256];
	input.getline(temp,256);
	return temp;
}
void wirte(const charstring &s)
{
	s.print();
}
void copy(charstring & target,charstring & source)
{		
	strcpy(target.Tocstr(),source.Tocstr());

}
void  copy(charstring & target ,charstring &source,int n)
{
	
	char * ctarget=target.Tocstr();
	char * csource=source.Tocstr()+n;
	strcpy(ctarget,csource);
}
charstring substring(const charstring &s,int pos,int len)
{
	char* tmp=new char[len+1];
	tmp=s.Tocstr()+pos+1;
	return tmp;
	
}
bool operator == (const charstring &first,const charstring &second)
{
	if(strcmp(first.Tocstr(),second.Tocstr())==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator < (const charstring &first,const charstring &second)
{
	if((strcmp(first.Tocstr(),second.Tocstr()))<0)
	{
		return true;
		
	}
	else
	{
		return false;
	}
}
bool operator > (const charstring &first,const charstring &second)
{
	if((strcmp(first.Tocstr(),second.Tocstr()))>0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator >= (const charstring &first,const charstring &second)
{
	if((strcmp(first.Tocstr(),second.Tocstr()))>=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator <= (const charstring &first,const charstring &second)
{ if((strcmp(first.Tocstr(),second.Tocstr()))<=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator !=(const charstring &first,const charstring & second)
{
	if((strcmp(first.Tocstr(),second.Tocstr()))!=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Editor::Editor(char infName[],char outfName[])
{
	inFile.open(infName);

	outFile.open(outfName);
	if(!inFile)
	{
		cout<<"打开文件失败"<<endl;
		exit(1);
	}
	if(!outFile)
	{
		cout<<"打开输出文件失败"<<endl;
		exit(2);
	}
	ReadFile();
}
bool Editor::GetCommand()
{
	charstring curLine;
	if(curLineNo!=0)
	{
		textBuffer.getelem(curLineNo,curLine);
		cout<<curLineNo<<":"<<curLine.Tocstr()<<endl<<"?";
	}
	else
	{
		cout<<"文件缓存空"<<endl<<"?";
	}
	cin>>userCommand;
	userCommand=tolower(userCommand);
	while(cin.get()!='\n');
	
	
		if(userCommand=='q')
		{
			return false;
		}
		else
		{
			return true;
		}
	
	
}	
void Editor::Runcommand()
{
	switch(userCommand)
	{
		case 'b':
			if(textBuffer.empty())
			{
				cout<<"警告：文本缓存空"<<endl;

			}
			else
			{
				curLineNo=1;
			}
			break;
		case 'c':
			if(textBuffer.empty())
			{
				cout<<"警告：文本缓存为空"<<endl;
			}
			else if(!ChangeLine())
			{
				cout<<"警告： 替换操作失败";
			}
			break;
		case 'd':
			if(!textBuffer.empty())		
			{
				
				DeleteLine();
			}
			break;
		case 'e':
			if(textBuffer.empty())
			{
				cout<<"警告：文本缓存为空"<<endl;
			}
			else
			{
				curLineNo=textBuffer.length();
			}
		case 'f':
			if(textBuffer.empty())
			{
				cout<<"警告：文本缓存为空"<<endl;
			}
			else
			{
				FindString();
			}
		case 'g':
			if(!GotoLine())
			{
				cout<<"错误： 操作失败"<<endl;
			}
			break;
		case '?':
		case 'h':
			cout<<"有效命令：b(egin),c(hange),d(elete),e(nd)"<<endl<<"g(o),h(elp),n(ext),p(revious)"<<endl
				<<"q(uit),r(ead),v(iew),w(rite),f(indString),change(s)ubstring,i(sertline)"<<endl;
			break;
		case 'i':
			if(!InsertLine())
			{
				cout<<"错误：操作失败"<<endl;

			}
			break;
		case 'n':
			if(!NextLine())
			{
				cout<<"错误：操作失败"<<endl;
			}
			break;
			if(!NextLine())
			{
				cout<<"错误：操作失败"<<endl;
			}
			break;
		case 'p':
			if(!PreviousLine())
			{
				cout<<"错误：无前一行"<<endl;
			}
			break;
		case 'r':
			ReadFile();
			break;
		case 'v':
			View();
			break;
		case 'w':
			if(textBuffer.empty())
			{
				cout<<"警告：文本缓存为空"<<endl;
			}
			else
			{
				WriteFile();

			}
			break;
		case 's':
			if(!textBuffer.empty())
			{
				ChangeSubString();
			}
			break;
		default:
			cout<<"输入有效命令或者输入'?'或者'h'来获取帮助"<<endl;
			break;
}
}
void  Editor::ReadFile()
{
	bool proceed=true;
	if(!textBuffer.empty())
	{
		cout<<"文本缓存非空；读入文件时将覆盖它"<<endl;
		cout<<"回答yes将执行此操作"<<endl;
		if(proceed=UsersayYes())
		{
			textBuffer.clear();
		}
	}
	int lineNumber=1;
	while(proceed)
	{
		char temp[256];
		inFile.getline(temp,256);
		charstring inString(temp);
		if(inFile.eof())
		{

			proceed=false;
			if(strlen(inString.Tocstr())>0)
			{
				textBuffer.addtail(inString);
			}
		}
		else
		{
			textBuffer.addtail(inString);
			lineNumber++;
		}
	}
	if(textBuffer.empty())
	{
		curLineNo=0;
	}
	else
	{
		curLineNo=1;
	}
	
}
bool Editor::UsersayYes()
{
	char *tmp;
	cin>>tmp;
	for(int i=0;i<strlen(tmp);i++)
	{
		tmp[i]=tolower(tmp[i]);
	}
	if(strcmp(tmp,"yes")==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Editor::WriteFile()
{
	charstring temp;
	for(int i=1;i<=textBuffer.length();i++)
	{
		textBuffer.getelem(i,temp);
		outFile<<temp.Tocstr()<<endl;

	}
}
bool Editor::InsertLine()
{
	int lineNumber;
	cout<<"请输入指定行号"<<endl;
	cin>>lineNumber;
	while(cin.get()!='\n')
	{
		cout<<"输入新字符串";
	}
	charstring toInsert=read(cin);
	if(textBuffer.insert(lineNumber,toInsert))
	{
		curLineNo=lineNumber;
		return true;
	}
	else
	{
		return false;
	}
}
void Editor::FindString()
{
	int index;
	cout<<"输入被查找的字符串"<<endl;
	charstring searchString=read(cin);
	charstring curLine;
	textBuffer.getelem(curLineNo,curLine);
	while((index=Index(curLine,searchString))==-1)
	{
		if(curLineNo<textBuffer.length())
		{
			curLineNo++;
			textBuffer.getelem(curLineNo,curLine);
		}
		else
		{
			break;
		}
	}
	if(index==-1)
	{
		cout<<"查找串失败";
	}
	else
	{
		cout<<curLine.Tocstr()<<endl;
		for(int i=0;i<index;i++)
		{
			cout<<" ";
		}
		for(int j=0;j<strlen(searchString.Tocstr());j++)
		{
			cout<<"^";
		}
	}
	cout<<endl;
	
}
bool Editor::ChangeSubString()
{
	int index;
	cout<<"输入被查找的字符串"<<endl;
	charstring searchString=read(cin);
	charstring curLine;
	textBuffer.getelem(curLineNo,curLine);
	while((index=Index(curLine,searchString))==-1)
	{
		if(curLineNo<textBuffer.length())
		{
			curLineNo++;
			textBuffer.getelem(curLineNo,curLine);
		}
		else
		{
			break;
		}
	}
	if(index==-1)
	{
		cout<<"查找串失败";
		return false;
	}
	else
	{
		char temp[256];
		cout<<"输入替换字符串:";
		cin>>temp;
		string line=curLine.Tocstr();
		string str=searchString.Tocstr();
		line=line.replace(line.begin()+index,line.begin()+index+strlen(searchString.Tocstr()),temp);
		strcpy(temp,line.c_str());
		charstring tmpPtr(temp);
		textBuffer.setelem(curLineNo,tmpPtr);

		return true;
	}
	
}
bool Editor::NextLine()
{
	if(curLineNo<textBuffer.length())
	{
		curLineNo++;
		return true;
	}
	else
	{
		cout<<"已经是最后一行";
		return false;
	}
}
bool Editor::PreviousLine()
{
	if(curLineNo>1)
	{
		curLineNo--;
		return true;
	}
	else
	{
		cout<<"已经达到第一行";
		return false;
	}
}
void Editor::View()
{
	charstring temp;
	for(int i=0;i<textBuffer.length();i++)
	{
		textBuffer.getelem(i+1,temp);
		cout<<temp.Tocstr()<<endl;

	}

}
bool Editor::GotoLine()
{
	cout<<"输入你想要转到的行数:";
	int linenumber;
	cin>>linenumber;
	if(linenumber>=1&&linenumber<=textBuffer.length())
	{
		curLineNo=linenumber;
		return true;
	}
	else
	{
		return false;
	}

}
bool Editor::DeleteLine()
{
	charstring temp;
	if(textBuffer.length()==0)
	{
		cout<<"文本已经为空"<<endl;
		return false;
	}
	else
	{
		textBuffer.Delete(curLineNo);
		curLineNo--;
		return true;
	}
	
}
bool Editor::ChangeLine()
{
	char temp[256];
	int num;
	cout<<"输入想要改变的行：";
	cin>>num;
	getchar();
	cout<<"输入想要改变的内容:";
	cin.getline(temp,256);
	charstring str(temp);
	textBuffer.setelem(num,str);
	return true;
}

