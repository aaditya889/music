#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include"../head/dump.h"

struct wav{
char riff[4];
unsigned int tot_size;
char wave[4];
unsigned char fmt[4];
unsigned int len_dat;
unsigned short type_format;
unsigned short channel;
unsigned int sample_rate;
unsigned int val1;
unsigned short bps1; 
unsigned short bps;
char dat[4];
unsigned int size_data;
};

void main(){
struct wav w;
unsigned int r,t,p;
signed short a,b,c,d,e,f;
char *data;
void *dat1;
FILE *fd;
fd = fopen("wav1.wav" ,"w");

data = (char*)malloc(800000);
dat1=data;
/*a=10000;
b=10000;
c=0;
d=0;
e=-10000;
f=-10000;
*/
/*
for(int i=0;i<66667;i++){
memcpy(dat1,&a,2);
dat1+=2;
memcpy(dat1,&b,2);
dat1+=2;
memcpy(dat1,&c,2);
dat1+=2;
memcpy(dat1,&d,2);
dat1+=2;
memcpy(dat1,&e,2);
dat1+=2;
memcpy(dat1,&f,2);
dat1+=2;
}
*/
a=0;
for(int i=0;i<200000;i++){
memcpy(dat1,&a,2);
dat1+=2;
memcpy(dat1,&a,2);
dat1+=2;
a+=5000;
}


dump(data,100);

strncpy(w.riff,"RIFF",4);
w.tot_size = 800044;
strncpy(w.wave,"WAVE",4);
strncpy(w.fmt,"fmt ",4);
strncpy(w.dat,"data",4);
w.len_dat = 16;
w.type_format = 1;
w.channel = 2;
w.sample_rate = 44100;
w.val1 = 176400;
w.bps1 = 4;
w.bps = 16;
w. size_data = 800000;



r = fwrite(&w,1,sizeof(struct wav),fd);
if(r==-1)
perror("Error!");
p=800000;
while(p>0){
t = fwrite(data,1,p,fd);
if(t==-1)
perror("Error!");
p-=t;
}
if(p==0)
printf("wrote %u bytes!\n" ,r+800000);






}









