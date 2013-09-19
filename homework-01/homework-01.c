#include<stdio.h>
int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}
int main()
{
	int max_so_far,max_ending_here,len,i,num[1000];
	while(1){
		max_so_far=-1000;
		max_ending_here=-1000;
		printf("please input len\n");
			scanf("%d",&len);
		for(i=1;i<=len;i++)
			scanf("%d",&num[i]);
		for(i=1;i<=len;i++)
		{
			max_ending_here=max(max_ending_here+num[i],num[i]);
			max_so_far=max(max_so_far,max_ending_here);
		}
		printf("the max is %d\n",max_so_far);
	}
} 