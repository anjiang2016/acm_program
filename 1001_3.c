#include "stdio.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

void printf_array(int* n,int len)
{
	for(int i=0;i<len;i++)
		printf("%d,",n[i]);
	printf("\n");
}

void init_array(int* n,int len)
{
	for(int i=0;i<len;i++)
		n[i]=0;
}
int devide_zmm(int n,int bydevide,int cnt)
{
	for(int i=0;i<cnt;i++)
		n=n/bydevide;
	return n;	
}
int exp10(int cnt);
void reset_array(int* n,int len)
{
	for(int i=0;i<len;i++)
        {
                
		char tmp_array[128]={'\0'};
                sprintf(tmp_array,"%d",n[len-i-1]);
                
		for(int j=len-i-strlen(tmp_array);j<len-i;j++)
		{
                        if(j<len-i-1)
			{
				int tmp = devide_zmm(n[len-i-1],10,len-i-j-1);
                          
				n[j]+=tmp;
				n[len-i-1]-=tmp*exp10(len-i-j-1);
			}
			else
				n[j]=n[len-i-1]%(10*(len-j-i));
				
		}
        }
}

int exp10(int cnt)
{
	int tmp=10;
        if(cnt==0) return 1;
        for(int i=1;i<cnt;i++)
		tmp*=10;
	return tmp;
}
void int2str(int * result,int len,char * sResult)
{
 	int ind=0;
	for(int i=0;i<len;i++)
	{
		if(result[i]==0 && result[i+1]==0)
			ind++;
		else
			break;	
	}
	for(int i=ind+1;i<len;i++)
	{
		sResult[i-ind-1]=result[i]+'0';
	}
	sResult[len-ind]='\0';
}

void  refinedExp(char * num,char * exp_num,int * result)
{
     
                        	
	int n1[128]={0};
	int n2[128]={0};
	for(int i=0;i<strlen(num);i++)
		n1[i]=num[i]-'0';

	int	len_n1=strlen(num);
	
	for(int i=0;i<strlen(exp_num);i++)
		n2[i]=exp_num[i]-'0';

	int len_n2=strlen(exp_num);
	

	init_array(result,128);
	for(int i=0;i<len_n1;i++)
	{
		for(int j=0;j<len_n2;j++)
		{
			int tmp=n1[len_n1-i-1]*n2[len_n2-j-1];
                        result[128-i-j-1]+=tmp;
		}
	}

        reset_array(result,128);
        

}
int strfind(char * str, char c)
{       
	for(int i=0;i<strlen(str);i++)
	{
		if(str[i]==c)
		return i;
	}
	return 0;
}
char *  addpoint(char * str,int npoint)
{
	int len=strlen(str);
	if(npoint>0){
        
	if(npoint<len){
		for(int i=len;i>len-npoint;i--)
			str[i]=str[i-1];
		str[len-npoint]='.';
		str[len+1]='\0';
	}
	else{
		for(int i=len+npoint-len+2;i-npoint+len-2>-1;i--)
		{
			str[i]=str[i-npoint+len-2];	
		}
              
		
		for(int i=0;i<npoint-len+2;i++)
			str[i]='0';
		str[npoint+2+1]='\0';
		str[1]='.';
	}
	}
	return str;
}
void removepoint(char *str,int npoint)
{
	int len=strlen(str);
	for(int i=len-npoint-1;i<len;i++){
		str[i]=str[i+1];
	
	}
}
void removeZero(char* str)
{
	int ind=0;
	int len=strlen(str);
        char ct = '0';
	for(int i=0;i<len;i++)
	{
		if((str[len-1-i]==ct ) && ind==i )
		{
			ind++;
		}
        }
	str[len-ind]='\0';	
}

int main(int argc,char ** argv)
{
        char ca1[128]={'\0'};
        char ca2[128]={'\0'};

	while(scanf("%s%s",ca1,ca2)==2)
	{
        int start_time=clock();       
	int result[128]={0};
        
        int npoint = 0;
        if(strfind(ca1,'.')>0)
	{
		removeZero(ca1);
        	npoint = strlen(ca1)-strfind(ca1,'.')-1;
        	removepoint(ca1,npoint);

                int tmp = atoi(ca1);
                sprintf(ca1,"%d",tmp);
        }
        npoint*=atoi(ca2);
        
        char sRes[128]={'\0'};
        sprintf(sRes,"%d",1);
	for(int i=0;i<atoi(ca2);i++)	
	{
		refinedExp(ca1,sRes,result);
		int2str(result,128,sRes);
	}
	addpoint(sRes,npoint);
        printf("%s^%s=%s(%d),",addpoint(ca1,npoint/atoi(ca2)),ca2,sRes,strlen(sRes));
        int end_time=clock();
        float diff_time = (float)(end_time-start_time);
        printf("time cost:%f ms,time unit=%d\n",diff_time/1000,CLOCKS_PER_SEC);              
     	}
}
