#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

int process_str(char *str, char arglist[100][100],int *nargs)
{
	int i=0,j=0,k=0;
	while(str[i]!='\0')
	{
		if(str[i]=='\n')
		{
			i++;
			continue;
		}
		else if(str[i]!=' ')
		         arglist[j][k++] = str[i++];
		else
		{
		        (*nargs)++; 
			arglist[j][k]='\0';
			j++;
			k=0;
                        i++;	
		}
	}
	return 0;
}



int main(int argc, char **argv)
{
	int n,argno=0,i=0,fd1,fd2,lines=0,fd;
	char str[100], arglist[100][100];
	char path[100],buff[100], path1[100],path2[100];
        int pid;	
	while(1)
	{
		strcpy(path,"./");
		argno=0; 
		fflush(stdin);	
		n = read(0,str,100);
		str[n]='\0';
		process_str(str,arglist,&argno);
		for(i=0;i<=argno;i++)
		{
		  printf("arguments passed = %s \n",arglist[i]);
  		}
                pid = fork(); 
		
	        if(pid==0)
		{	
		   if(strcmp(arglist[0],"mycp")==0)
		   {
				printf("This is my version of cp command\n");
			strcat(path,arglist[1]);

	               	fd1 = open(path,O_RDONLY);
                        if(fd1<0)
			{
				printf("Open Error\n");
				exit(1);
			}
			strcpy(path,"./");
			strcat(path,arglist[2]);
		        printf(" dest path = %s \n",path);	
			fd2 = open(arglist[2],O_RDWR|O_CREAT, 0666);
			if(fd2<0)
			{
				printf("Open Error\n");
				exit(1);
			}
			while((n=read(fd1,buff,100))>0)
			{
			    write(fd2,buff,n);
		    	}
	    		close(fd1);
			close(fd2);		

	          }
		  else if(strcmp(arglist[0],"mymv")==0)
		  {
			strcpy(path1,"./");
			strcpy(path2,"./");
			strcat(path1,arglist[1]);
			strcat(path2,arglist[2]);
			rename(path1,path2);
		  }			
	 	  else if(strcmp(arglist[0],"myhead")==0)
		  {
			lines=0;
			fd1 = open(arglist[1], O_RDONLY);
			if(fd==-1)
			{
			   printf("Open Failed\n");
			   exit(1);
			}
			while((n=read(fd1,buff,100))>0)
			{
			  for(i=0;i<n;i++)
			  {
			    if(buff[i]=='\n')
			        lines++;
		            if(lines<=5)
			    {
		    		write(1, buff,i+1);
			    }
			  }
	 		}		 
		  }
		  else if(strcmp(arglist[0],"exit")==0)
		  {
		    exit(0);
		  } 
		}
		else if(pid>0)
		{
			wait(NULL);
		        exit(0);
		}
	}
 return 0;
}	
