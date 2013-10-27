// libmaxsum.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "libmaxsum.h"

/*
	Description: Both the width and length of the two-dimensional array in this program should be not more than 100.
*/
FILE *out,*in;
void getMax_1(int *pwidth,int *plength,int pnum[101][101],int *m,int *wb,int *we,int *lb,int *le)
{
	int num[101][101],i,j,PS[101][101],begin,end,wbegin,wend,lbegin,lend,tbegin,tend,max_so_far,max_ending_here,temp;
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
	wbegin=1;
	wend=1;
	for(begin=1;begin<=width;begin++)		
		for(end=begin;end<=width;end++)
		{
			max_ending_here=PS[end][1]-PS[begin-1][1];
			tbegin=1;
			tend=1;
			for(j=2;j<=length;j++)
			{
				temp=PS[end][j]-PS[end][j-1]-PS[begin-1][j]+PS[begin-1][j-1];
				if(max_ending_here>0)
				{
					max_ending_here+=temp;
					tend=j;					
				}
				else{
					tbegin=j;
					tend=j;
					max_ending_here=temp;
				}
				if(max_so_far<max_ending_here)
				{
					max_so_far=max_ending_here;
						wbegin=begin;
						wend=end;
						lbegin=tbegin;
						lend=tend;	
				}
			}
		}
	*m=max_so_far;
	*wb=wbegin;
	*we=wend;
	*lb=lbegin;
	*le=lend;
}
//To get the data from the "<file name>"
int getData(int* pwidth,int* plength,int p[101][101])
{
	int i,j;
	if(fscanf_s(in,"%d",pwidth)!=1){
		fprintf_s(out,"error:The format of the text you entered is wrong\n");
		return 1;
	}
	if(*pwidth>100)
	{
		fprintf_s(out,"error:The width of the array is beyond the limit\n");
		return 1;
	}
	if(fgetc(in)!=',')
	{
		fprintf_s(out,"error:The format of the text you entered is wrong\n");
		return 1;
	}
	if(fgetc(in)!='\n')
	{
		fprintf_s(out,"error:The format of the text you entered is wrong\n");
		return 1;
	}
	if(fscanf_s(in,"%d",plength)!=1){
		fprintf_s(out,"error:The format of the text you entered is wrong\n");
		return 1;
	}
	if(*plength>100)
	{
		fprintf_s(out,"error:The length of the array is beyond the limit\n");
		return 1;
	}
	if(fgetc(in)!=',')
	{
		fprintf_s(out,"error:The format of the text you entered is wrong\n");
		return 1;
	}
	if(fgetc(in)!='\n')
	{
		fprintf_s(out,"error:The format of the text you entered is wrong\n");
		return 1;
	}
	for(i=0;i<*pwidth;i++)
		for(j=0;j<*plength;j++)
		{
			if(fscanf_s(in,"%d",p[i]+j)!=1){
				fprintf_s(out,"error:The format of the text you entered is wrong\n");
				return 1;
			}
			fgetc(in);
		}
	return 0;
}

int main_flow(int select, const char* filename)
{
	int i,j,k,width,length,gap,max,location,wb,we,lb,le;
	int num[101][101],tempnum[101][101],max_so_far[101],wbegin[101],wend[101],lbegin[101],lend[101];
	fopen_s(&out,"ouput.txt","w");
	if(select==0){
		fopen_s(&in,filename,"r");
		if(in==NULL){
			fprintf_s(out,"error:You should input an exited filename\n");
			fclose(out);
			return -1;
		}
		else {
			if(getData(&width,&length,num)) {
				fclose(in);
				fclose(out);
				return -1;
			}
			getMax_1(&width,&length,num,&max,&wb,&we,&lb,&le);
		}
	}
	else 
	{
		fopen_s(&in,filename,"r");
		if(in==NULL){
			fprintf_s(out,"error:You should input an exited filename\n");
			fclose(in);
			fclose(out);
			return -1;
		}
		else {
			if(getData(&width,&length,num)) {
				fclose(in);
				fclose(out);
				return -1;
			}
			if(select==1)
			{
				for(gap=0;gap<length;gap++){
					for(i=0;i<width;i++)
						for(j=0;j<length;j++)
							tempnum[i][(j+gap)%length]=num[i][j];
					getMax_1(&width,&length,tempnum,&max_so_far[gap],&wbegin[gap],&wend[gap],&lbegin[gap],&lend[gap]);
				}
				max=max_so_far[0];
				location=0;
				for(k=1;k<length;k++)
				{
					if(max_so_far[k]>max){
						max=max_so_far[k];
						location=k;
					}
				}
				wb=wbegin[location];
				we=wend[location];
				lb=lbegin[location]-location;
				le=lend[location]-location;
				if(lb<=0)
					lb+=length;
				if(le<=0)
					le+=length;	
			}
			else if(select==2)
			{
				for(gap=0;gap<width;gap++){	
					for(i=0;i<width;i++)
						for(j=0;j<length;j++)	
							tempnum[(i+gap)%width][j]=num[i][j];
					getMax_1(&width,&length,tempnum,&max_so_far[gap],&wbegin[gap],&wend[gap],&lbegin[gap],&lend[gap]);
				}
				max=max_so_far[0];
				location=0;
				for(k=1;k<width;k++)
				{
					if(max_so_far[k]>max){
						max=max_so_far[k];
						location=k;
					}	
				}
				wb=wbegin[location]-location;
				we=wend[location]-location;
				lb=lbegin[location];
				le=lend[location];
				if(wb<=0)
					wb+=width;
				if(we<=0)
					we+=width;		
			}
			else{
				fprintf_s(out,"please input a right order!\n");
				fclose(in);
				fclose(out);
				return -1;
			}
		}
	}
	fprintf_s(out ,"%d %d\n", width, length);
	for(i=0;i<width;i++){
		for(j=0;j<length;j++)
		{
			fprintf_s(out,"%d ",num[i][j]);	
		}
		fprintf_s(out,"\n");	
	}
	fprintf_s(out,"%d\n",max); 
    fprintf_s(out,"%d\n",lb);
    fprintf_s(out,"%d\n",le);
    fprintf_s(out,"%d\n",wb);
    fprintf_s(out,"%d\n",we);
	fclose(in);
	fclose(out);
	return 0;
}
