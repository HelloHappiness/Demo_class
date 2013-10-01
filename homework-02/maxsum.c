/*
	Description: Both the width and length of the two-dimensional array in this program should be not more than 100.
*/
#include<stdio.h>
#include<string.h>
// get the bigger number between two number
int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}
void getSum()
{
	
}
//To realize the "maxsum.exe  <file name>" function
void getMax_1(int *pwidth,int *plength,int pnum[101][101])
{
	int num[101][101],i,j,PS[101][101],begin,end,max_so_far,max_ending_here,temp;
	int width=*pwidth,length=*plength;
	for(i=1;i<=width;i++)
		for(j=1;j<=length;j++)
			num[i][j]=*(pnum[i-1]+j-1);
	for(i=0;i<=width;i++)
		PS[i][0]=0;
	for(j=0;j<=length;j++)
		PS[0][j]=0;
	for(i=1;i<=width;i++)
		for(j=1;j<=length;j++)
			PS[i][j]=PS[i][j-1]+PS[i-1][j]-PS[i-1][j-1]+num[i][j];
	max_so_far=PS[1][1];
	if(width<length)
		for(begin=1;begin<=width;begin++)
			for(end=begin;end<=width;end++)
			{
				max_ending_here=PS[end][1]-PS[begin-1][1];
				for(j=2;j<=length;j++)
				{
					temp=PS[end][j]-PS[end][j-1]-PS[begin-1][j]+PS[begin-1][j-1];
					max_ending_here=max(max_ending_here+temp,temp);
					max_so_far=max(max_so_far,max_ending_here);
				}
			}
	else
		for(begin=1;begin<=length;begin++)
			for(end=begin;end<=length;end++)
			{
				max_ending_here=PS[1][end]-PS[1][begin-1];
				for(i=2;i<=width;i++)
				{
					temp=PS[i][end]-PS[i-1][end]-PS[i][begin-1]+PS[i-1][begin-1];
					max_ending_here=max(max_ending_here+temp,temp);
					max_so_far=max(max_so_far,max_ending_here);
				}
			}
	printf("%d\n",max_so_far);
}
//To get the data from the "<file name>"
int getData(int* pwidth,int* plength,int p[101][101])
{
	int i,j;
	if(scanf("%d",pwidth)!=1){
		printf("error:The format of the text you entered is wrong\n");
		return 1;
	}
	if(*pwidth>100)
	{
		printf("error:The width of the array is beyond the limit\n");
		return 1;
	}
	if(getchar()!=',')
	{
		printf("error:The format of the text you entered is wrong\n");
		return 1;
	}
	if(getchar()!='\n')
	{
		printf("error:The format of the text you entered is wrong\n");
		return 1;
	}
	if(scanf("%d",plength)!=1){
		printf("error:The format of the text you entered is wrong\n");
		return 1;
	}
	if(*plength>100)
	{
		printf("error:The length of the array is beyond the limit\n");
		return 1;
	}
	if(getchar()!=',')
	{
		printf("error:The format of the text you entered is wrong\n");
		return 1;
	}
	if(getchar()!='\n')
	{
		printf("error:The format of the text you entered is wrong\n");
		return 1;
	}
	for(i=0;i<*pwidth;i++)
		for(j=0;j<*plength;j++)
		{
			if(scanf("%d",p[i]+j)!=1){
				printf("error:The format of the text you entered is wrong\n");
				return 1;
			}
			getchar();
		}
	return 0;
}
int main(int argc, char* argv[])
{
	int width,length,num[101][101];
	if(argc==1)
	{
		printf("error:You should input filename\n");
		return -1;
	}
	else if(argc==2){
		if(freopen(argv[1],"r",stdin)==NULL){
			printf("error:You should input an exited filename\n");
			return -1;
		}
		else{
			if(getData(&width,&length,num))
				return -1;
			getMax_1(&width,&length,num);
			//printf("the max is %d\n",max_so_far);
		}
	}
	fclose(stdin);
	return 0;
}
