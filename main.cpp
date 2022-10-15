#include"editor.h"

using namespace std;
int main()
{
	char infName[256],outfName[256];
	cout<<"输入文件名（默认：file_in.txt）:";

	strcpy(infName,read(cin).Tocstr());
	if(strlen(infName)==0)
	{
		strcpy(infName,"file_in.txt");
	}
	cout<<"输出文件名（默认：file_out.txt）:";
	strcpy(outfName,read(cin).Tocstr());
	if(strlen(outfName)==0)
	{
		strcpy(outfName,"file_out.txt");
	}
	Editor text(infName,outfName);
	while(text.GetCommand())
	{
		text.Runcommand();
	}
	return 0;
}
