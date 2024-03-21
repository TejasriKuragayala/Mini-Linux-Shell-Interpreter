#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/mman.h>
#include<string.h>

int main(int argc, char **argv)
{
	int fd,i;
	void *pmap, *pmap1;
	int sd, sd1;
	char buf[100], buf2[100];
        char *str;
	fd = open("testfile.txt",O_RDWR);

	if(fd==-1)
	{
		 perror("Open error\n");
		 exit(1);
	}
	pmap = mmap(0, 1000, PROT_READ|PROT_WRITE, MAP_SHARED,fd,0);

	if(pmap==MAP_FAILED)
	{
		perror("mmap error");
		close(fd);
		exit(1);
	}
	pmap1 = pmap;
	sd=read(fd, buf, 50);
	buf[sd]='\0';
	printf("The file contains before change : %s\n", buf);
/*	strncpy(pmap, "I am over writing the content",29);*/
        str = "I am over writing the content\n";
        i=0;
	while(str[i]!='\n')
	{
		*((char *)pmap + i) = str[i];
	}
	*((char *) pmap + i) = EOF;

	lseek(fd, SEEK_SET, 0);
	sd1=read(fd, buf2, 50);
	close(fd);
	buf2[sd1]='\0';
	printf("The file now contains after change : %s\n",buf2);
	munmap(pmap1,1000);
	return 0;
}	
