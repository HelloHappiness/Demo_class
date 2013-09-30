#include<stdio.h>
#include<string.h>
#define MIN -2147483648 
#define MAX 2147483647
int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}
int main(int argc, char* argv[])
{
	FILE *in,*out;
	int max_so_far,max_ending_here,width,length,i,num[100][100];
	if(!strcmp(argv[1], "")){
		in=freopen(argv[2],"r",stdin);
		out=freopen("output.txt","w",stdout);
		max_so_far=MIN;
		max_ending_here=MIN;
		scanf("%d",&width);
		getchar();
		getchar();
		scanf("%d",&length);
		getchar();
		getchar();
		for(i=0;i<length;i++)
		{
			scanf("%d",&num[0][i]);
			getchar();
		}
		for(i=0;i<length;i++)
		{
			max_ending_here=max(max_ending_here+num[0][i],num[0][i]);
			max_so_far=max(max_so_far,max_ending_here);
		}
		printf("the max is %d\n",max_so_far);
	}
	return 0;
} 