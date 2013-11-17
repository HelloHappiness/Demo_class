#include<iostream>
#include<string.h>
using namespace std;
class URL
{
public :
		char token[100];
		void input();
		void handle();
		void output();
private:
		int total;
		char keyword[30][100];
};
void URL::input()
{
	char c;
	int i=0;
	while((c=getchar())!='\n')
		if(c!=' ')
			token[i++]=c;
	token[i]='\0';
}
void URL::handle()
{
	int i=0,j;
	int l=strlen(token);
	int time=0;
	total=0;
	while(i<l)
	{
		j=0;
		if(token[i]==':'&&token[i+1]=='/'&&token[i+2]=='/')
			i=i+3;
		else if(token[i]=='/'||token[i]=='.')
			i++;
		else {
			keyword[total][j++]=token[i++];
			while(token[i]!=':'&&token[i]!='/'&&token[i]!='.'&&i<l)
					keyword[total][j++]=token[i++];
			keyword[total++][j]='\0';
		}
	}
}
void URL::output()
{
	int i;
	for(i=0;i<total-1;i++)
		printf("%s,",keyword[i]);
	printf("%s\n",keyword[i]);
}
int main()
{
	URL url;
	url.input();
	url.handle();
	url.output();
	system("pause");
	return 0;
}