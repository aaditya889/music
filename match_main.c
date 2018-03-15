#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include"../head/dump.h"
#include<dirent.h>

struct dets{
char name[50];
char band[50];
char album[50];
};

void print_dets(int a){
FILE *fd;
char *st;
int r;
struct dets *dets1;
st=malloc(200);
fd=fopen("./database/dat","r");
if(fd==NULL)
perror("Error opening database:");
fseek(fd,sizeof(struct dets)*a,SEEK_CUR);
r=fread(st,1,sizeof(struct dets),fd);
if(r!=sizeof(struct dets)){
perror("error reading song data:");
printf("read %d bytes" ,r);
return;
}
dets1=(struct dets *)st;
printf("Song name: %sArtist: %sAlbum: %s",dets1->name,dets1->band,dets1->album);
return;
}


void * readdata(FILE * fd2,char *data,unsigned int *size,unsigned int *dat_size){
unsigned int r;
unsigned char fl=0;
void *ptr,*st;
r = fread(data,1,8,fd2);
if(r!=8){
printf("Failed!\n");
return 0;
}
/*
printf("read first %d bytes:\n" ,r);

dump(data,r);
*/
*size =*((unsigned int *)(data+4));

//printf("si = %d\n" ,si);

r = fread(data+8,1,*size-8,fd2);
if(r!=*size-8){
printf("Failed!\n");
return 0;
}
ptr = data;
st = data;
for(int i=0;i<200;i++,ptr++){
if(!strncmp(ptr,"data",4)){
fl=1;
break;}
}

if(!fl){
printf("cant find 'data' 1!\n");
return 0;}

ptr+=4;

*dat_size = *((unsigned int *)ptr);

ptr+=4;		//now ptr contains the address of start of data segment.
return ptr;


}


char ** opendirect(int *k){

DIR *dir;
struct dirent *ent;
char **a;
a=malloc(8*50);

int x=0;
if ((dir = opendir ("./data")) != NULL) {
  /* print all the files and directories within directory */
  while ((ent = readdir (dir)) != NULL)
	a[x++]=ent->d_name;
  closedir (dir);
}
 else {
  /* could not open directory */
  perror ("");
  return 0;
}
*k=x;
return a;
}





int playsound( char *filename ) {
    char command[256];
    int status;

    /* create command to execute */
    sprintf( command, "aplay -c 1 -q -t wav %s", filename );

    /* play sound */
    status = system( command );
     
    return status;
}



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


//main ================================================================================================================================

void main(int argc, char *argv[]){
struct wav w;
unsigned int r,t,p;
int x=0;
signed short a,b,c,d,e,f;
unsigned int si,dat_si,dat_si2;
int num_dirs;
char *ptr,*ptr2;
char fl=0;
char *data,*data2,**dirs;

if(argc<2){
printf("not enough args --> gcc match.c <clip file>\n");
return;}

dirs=opendirect(&num_dirs);

printf("Finding the song details for the clip...\n");
playsound(argv[1]);

FILE *fd,*fd2;
for(int tt=2;tt<num_dirs;tt++){		//start main for loop
char ab[50];
sprintf(ab,"./data/%s" ,dirs[tt]);
//printf("current file--> %s\n" ,ab);

fd2 = fopen(argv[1] ,"rb");		//clip
fd = fopen(ab,"rb");		//actual song

if(fd2==NULL){
perror("Error 1!");
return;}
if(fd==NULL){
perror("Error 2!");
return;}

data = (char*)malloc(50000000);
data2 = (char*)malloc(50000000);


if(!(ptr=readdata(fd,data,&si,&dat_si))){
printf("can't read 1st file!\n");
return;}
if(!(ptr2=readdata(fd2,data2,&si,&dat_si2))){
printf("can't read 2nd file!\n");
return;}

fl = 0;
x=0;
int l=1;

while(x<=(signed)(dat_si-dat_si2)){
//printf("ran!\n");
l=memcmp(ptr,ptr2,dat_si2);
if(l==0){
printf("Found a match!\n\n");
print_dets(tt-2);
fl=1;
break;	
}
ptr++;
x++;
}
if(fl)
break;
free(data);
free(data2);
fclose(fd);
fclose(fd2);

}		//end main for loop



}










