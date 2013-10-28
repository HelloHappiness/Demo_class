#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20
#define maxtry 100000
int totalnum=0;
char phrase_array[100][100];
char result_array[100][100];
int DX[8]={-1,-1,0,1,1,1,0,-1};
int DY[8]={0,1,1,1,0,-1,-1,-1};
void sort()
{
	int i,j;
	char s[100];
	 for(i=1;i<=totalnum;i++)
          for(j=i+1;j<=totalnum;j++)
                if(strlen(phrase_array[i])<strlen(phrase_array[j])){
                	strcpy(s,phrase_array[i]);
                	strcpy(phrase_array[i],phrase_array[j]);
                	strcpy(phrase_array[j],s);
                }                            
}
void input(FILE **p)
{
	int i=0,j;
	while(fscanf(*p,"%s",phrase_array[++totalnum])!=-1);
	totalnum--; 
	sort();	
 	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
			result_array[i][j]=' ';
}
void insertword(char *phrase,int location_x,int location_y,int location_d)
{
	int i;
	for(i=0;i<strlen(phrase);i++)
	{
		result_array[location_x][location_y]=phrase[i];
		location_x+=DX[location_d];
		location_y+=DY[location_d];
	}
}
int calculate(char *phrase,int x,int y,int d)
{
	int i,score=0;
	for(i=0;i<strlen(phrase);i++)
	{	
		if(x>N||x<1||y>N||y<1)
			return -1;
		else if(phrase[i]==result_array[x][y])
			score++;
		else if(result_array[x][y]!=' ')
			return -1;
		x+=DX[d];
		y+=DY[d];
	}
}
int locateofrand(char *phrase,int *location_x,int *location_y,int *location_d)
{
	int best=-1;
	int i,x,y,d,temp;
	for(i=1;i<=maxtry;i++)
	{
		x=rand()%N+1;
		y=rand()%N+1;
		d=rand()%8;
		temp=calculate(phrase,x,y,d);
		if(temp>best)
		{
			best=temp;
			*location_x=x;
			*location_y=y;
			*location_d=d;
		}
	}
	return best;
}
void workprocess()
{
	int location_x,location_y,location_d,i,j,judge;
 	srand((int)time(0));
  	for(i=1;i<=totalnum;i++){
  		judge=locateofrand(phrase_array[i],&location_x,&location_y,&location_d);
    	if(judge==-1){
			printf("please change the value of N!\n");
		}
  		insertword(phrase_array[i],location_x,location_y,location_d);
    }
}
void output(FILE **p)
{
	int i,j;
	for(i=1;i<=N;i++){
 		for(j=1;j<=N;j++)
   			fprintf(*p,"%c",result_array[i][j]);
      	fprintf(*p,"\n");
   }
}
int main(int argc, char *argv[])
{
	FILE *in,*out;
	in=fopen("input.txt","r");
	out=fopen("result.txt","w");
	input(&in);
	workprocess();
	output(&out);	
	return 0;
}
