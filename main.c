#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

void menu()
{
   printf("*-----------------------------*\n");
   printf("| 0) Cikis                    |\n");
   printf("| 1) Etiket/Kelime Aramasi    |\n");
   printf("| 2) Guncelleme               |\n");
   printf("*-----------------------------*\n");
}

void arama(char *p,char *kelime)
{
	DIR *d;
struct dirent *dir;
d=opendir(p);
if(d==NULL)
{
    printf("Tarama esnas�nda bir hata olustu...\n");
    exit(1);
}

while((dir=readdir(d))!=NULL)
{
if(strstr(dir->d_name,".txt")!=NULL)
{
	char txt_path[100];
	strcpy(txt_path,p);
	strcat(txt_path,"\\");
	strcat(txt_path,dir->d_name);
	FILE *file=fopen(txt_path,"r+");
	if(file==NULL)
	{
		printf("Dosya bulunamadi\n");
		continue;
	}
	char cumle[500];
	int satir=0;
	while(fgets(cumle,500,file)!=NULL)
	{
		satir++;
		if(strstr(cumle,kelime)!=NULL)
		{
			printf("%s %s dosyasinda %d. satirdadir\n",kelime,dir->d_name,satir);
		}
		
	}
	fclose(file);
}
 if(strchr(dir->d_name,'.')==NULL)
{
	printf("Taranan klasor = %s\n",dir->d_name);
   char path[PATH_MAX+1];
   strcpy(path,p);
   strcat(path,"\\");
   strcat(path,dir->d_name);
   arama(path,kelime);
}
	
}

}
int etiketkontrol(char etiket[])
{
	int yer1=0,yer2=0,size=0;
	if(strstr(etiket,"[[")!=NULL)
	{
		yer1=strstr(etiket,"[[")-etiket;
		size=strlen(etiket);
		if(etiket[size-2]==']' && etiket[size-1]==']')
		{
		int i=yer1+2,bosluk=0,syc=0;
		for(;i<size-2;i++)
		{
		if(isalpha(etiket[i])==0)
			{
				if(etiket[i]==' ' || etiket[i]=='_')
				{
					if(etiket[i]==' ')
					{
						bosluk++;
					}
				}
				else
				{
				return -1;
				}
			}
			else
			{
				syc++;
			}
		}
		if(bosluk<2 || syc==size-4)
		{
			return 1;
		}
		else
		{
			return -1;
		}
		}
    }
		else
		{
		return -1;
		}
	}
	else
	{
		return -1;
	}
}
void arama2(char *p,char txt[][50],int *s)
{
	DIR *d;
struct dirent *dir;
d=opendir(p);
if(d==NULL)
{
    printf("Tarama esnasinda bir hata olustu...\n");
    exit(1);
}

while((dir=readdir(d))!=NULL)
{
if(strstr(dir->d_name,".txt")!=NULL)
{
   strcpy(txt[*s],dir->d_name);
   *(s)=*(s)+1;
   
}
 if(strchr(dir->d_name,'.')==NULL)
{
   char path[PATH_MAX+1];
   strcpy(path,p);
   strcat(path,"\\");
   strcat(path,dir->d_name);
   arama2(path,txt,s);
  
  
}
	
}

}
void arama3(char *p,char etiket[][50],int *s2)
{
	DIR *d;
struct dirent *dir;
d=opendir(p);
if(d==NULL)
{
    printf("Tarama esnas�nda bir hata olustu...\n");
    exit(1);
}

while((dir=readdir(d))!=NULL)
{
if(strstr(dir->d_name,".txt")!=NULL)
{
      	char txt_path[100];
	strcpy(txt_path,p);
	strcat(txt_path,"\\");
	strcat(txt_path,dir->d_name);
	FILE *file=fopen(txt_path,"r+");
	if(file==NULL)
	{
		printf("Dosya bulunamadi\n");
		continue;
	}
	char cumle[500];
	while(fgets(cumle,500,file)!=NULL)
	{
		
			int x1=0,x2=0,x3=0;
	
while(1)
{
	if(strstr(cumle+x2,"[[")!=NULL)
	{
		x1=strstr(cumle+x2,"[[")-cumle;
		x1=x1+2;
		
		x2=strchr(cumle+x1,']')-cumle;
		
		x3=strstr(cumle+x1,"[[")-cumle;
		
		if(strchr(cumle+x1,']')!=NULL && strstr(cumle+x1,"[[")!=NULL)
		{
		
			if(x2<x3 && cumle[x2+1]==']')
			{
				char e[50];
				int j=x1,h=0;
				for(;j<x2;j++)
				{
					
					e[h]=cumle[j];
					h++;
				}
				e[h]='\0';
			
			    	int c1=0,c2=0,c3=0;
				for(;c1<strlen(e);c1++)
				{
				   if(isalpha(e[c1])==0 && e[c1]!=' ' && e[c1]!='_')
				   {
				   	c2++;
				   }	
				   else if(e[c1]==' ')
				   {
				   	c3++;
				   }
				}	
				if(c3<2 && c2==0)
				{
			    strcpy(etiket[*(s2)],e);
			    *(s2)=*(s2)+1;
	           	} 
			    
			
			}
			else
			{
				x2=x3-1;
			}
		}
		else
		{
			if(x2<0)
			{
				break;
			}
			else if(x2>0 && x3<0)
			{
				if(cumle[x2+1]==']')
				{
				char e[50];
				int j=x1,h=0;
				for(;j<x2;j++)
				{
					e[h]=cumle[j];
					h++;
				}
				e[h]='\0';
				
				int c1=0,c2=0,c3=0;
				for(;c1<strlen(e);c1++)
				{
				   if(isalpha(e[c1])==0 && e[c1]!=' ' && e[c1]!='_')
				   {
				   	c2++;
				   }	
				   else if(e[c1]==' ')
				   {
				   	c3++;
				   }
				}	
				if(c3<2 && c2==0)
				{
			    strcpy(etiket[*(s2)],e);
			    *(s2)=*(s2)+1;
		}
				
				}
				
			}
		}
	}
	else
	{
		break;
	}
	
	
	
	}
		
}
	fclose(file);
}
 if(strchr(dir->d_name,'.')==NULL)
{
   char path[PATH_MAX+1];
   strcpy(path,p);
   strcat(path,"\\");
   strcat(path,dir->d_name);
   arama3(path,etiket,s2);
  
  
}
	
}

}
void listeolustur(char etiket[][50],char list[][50],int *s2,int *s3)
{
	int i=1;
strcpy(list[0],etiket[0]);
for(;i<*(s2);i++)
{
	
int syc=0;
int j=0;

for(;j<*(s3);j++)
{
if(strcmp(etiket[i],list[j])==0)
{
	syc++;
}

}	
if(syc==0)	
	{
	strcpy(list[*(s3)],etiket[i]);
   *(s3)=*(s3)+1;	
	}
	
	
}
}
void etiketsayisi(char etiket[][50],char list[][50],int tekrar[],int *s2,int *s3)
{
	int i=0,j=0,syc=0;
	for(;i<*(s3);i++)
	{
		syc=0;
		j=0;
		for(;j<*(s2);j++)
		{
			if(strcmp(list[i],etiket[j])==0)
			{
				syc++;
			}
		}
		tekrar[i]=syc;
	}
	
}
void istenenbul(char txt[][50],char istenen[][50],int *s,int *s4)
{
int i=0,j=0,yer1=0,yer2=0;	
	for(;i<*(s);i++)
	{
				yer2=strstr(txt[i],".txt")-txt[i];
				char tmp2[50];
				strcpy(tmp2,txt[i]);
				 tmp2[yer2]='\0';
				  strcpy(istenen[*(s4)],tmp2);
            *(s4)=*(s4)+1;
		
	}
}
void listele1(char list[][50],char istenen[][50],char d[][50],int *s3,int *s4,int *s6)
{
  int i=0,j=0,ctrl=0;
  for(;i<*(s4);i++)
  {
   j=0,ctrl=0;
   for(;j<*(s3);j++)
   {
   	char tmp1[50],tmp2[50];
   	strcpy(tmp1,istenen[i]);
   	strcpy(tmp2,list[j]);
   	if(strcmp(tmp1,tmp2)==0)
   	{
   		ctrl++;
     }
   }
  	if(ctrl==0)
  	{
      strcpy(d[*(s6)],istenen[i]);
      *(s6)=*(s6)+1;
    }
  }
}
void listele2(char list[][50],char txt[][50],char d2[][50],int *s,int *s3,int *s7)
{
	int i=0,j=0,ctrl=0;
  for(;i<*(s3);i++)
  {
   j=0,ctrl=0;
   for(;j<*(s);j++)
   {
   	char tmp1[50],tmp2[50];
   	int yer1=0;
   	 	strcpy(tmp1,list[i]);
   	strcat(tmp1,".txt");
   	strcpy(tmp2,txt[j]);
   	if(strcmp(tmp1,tmp2)==0)
   	{
   		ctrl++;
     }
   }
  	if(ctrl==0)
  	{
  	strcpy(d2[*(s7)],list[i]);
	  *(s7)=*(s7)+1;	
    }
  }
}
int etiketkontrol2(char list[][50],char d[][50],char d2[][50],char kelime[],int *s3,int *s6,int *s7)
{
int i=0,j=0,k=0,yer1=0,h=0,m=0;
char etiketici[50];
yer1=strstr(kelime,"[[")-kelime;
h=yer1+2;
for(;h<strlen(kelime)-2;h++)
{
	etiketici[m]=kelime[h];
	m++;
}
etiketici[m]='\0';
for(;k<*(s6);k++)
{
	if(strcmp(etiketici,d[k])==0)
	{
		return -1;
	}
}
for(;i<*(s3);i++)
{
	if(strcmp(etiketici,list[i])==0)
	{
		int j=0;
		for(;j<*(s7);j++)
		{
			if(strcmp(etiketici,d2[j])==0)
			{
				return 0;
			}
		}
		return 1;
	}
}
return 2;

}
void guncelle1(char *p,char etiket[],char guncel[])
{
		DIR *d;
struct dirent *dir;
d=opendir(p);
if(d==NULL)
{
    printf("Tarama esnas�nda bir hata olustu...\n");
    exit(1);
}

while((dir=readdir(d))!=NULL)
{
if(strstr(dir->d_name,".txt")!=NULL)
{
	char txt_path[100],tmp[100],txt_path2[100];
	strcpy(tmp,dir->d_name);
	strcpy(txt_path,p);
	strcat(txt_path,"\\");
	strcat(txt_path,dir->d_name);
	FILE *file=fopen(txt_path,"r+");
	if(file==NULL)
	{
		printf("Dosya bulunamadi\n");
		continue;
	}
	char cumle[500];
    int syc=0;
	while(fgets(cumle,500,file)!=NULL)
	{
		if(strstr(cumle,etiket)!=NULL)
		{
	      syc++;
		}
	}
 fclose(file);
   if(syc!=0)
   {
   		FILE *file=fopen(txt_path,"r+");
	if(file==NULL)
	{
		printf("Dosya bulunamadi\n");
		continue;
	}
   	char cumle2[500];
   	  while(fgets(cumle2,500,file)!=NULL)
   	  {
   		if(strstr(cumle2,etiket)!=NULL)
			{
			int yer1=0,i=0;
				char tmp2[100];
			strcpy(tmp2,p);
	        strcat(tmp2,"\\");
			strcat(tmp2,"sahte.txt");
			strcpy(txt_path2,tmp2);
			FILE *f=fopen(tmp2,"a+");	
			if(f==NULL)
			{
				printf("Dosya acma hatasi...\n");
				exit(1);
				}	
				
			yer1=strstr(cumle2,etiket)-cumle2;	
				for(;i<yer1;i++)
				{
				     fputc(cumle2[i],f);
				}
				fputs(guncel,f);
			int size=strlen(etiket);
		int j=yer1+size;
			for(;j<strlen(cumle2);j++)
			{
			fputc(cumle2[j],f);	
			}
		fclose(f);		
		
   }
   else
   {
   	char tmp2[100];
			strcpy(tmp2,p);
	        strcat(tmp2,"\\");
			strcat(tmp2,"sahte.txt");
			FILE *f=fopen(tmp2,"a+");	
			if(f==NULL)
			{
				printf("Dosya acma hatasi...\n");
				exit(1);
				}	
		fputs(cumle2,f);
		fclose(f);			
			
   }
}
fclose(file);
int p=remove(txt_path);
 
	}
	char tmp3[100];
	strcpy(tmp3,txt_path);
    rename(txt_path2,txt_path);
}
 if(strchr(dir->d_name,'.')==NULL)
{
   char path[PATH_MAX+1];
   strcpy(path,p);
   strcat(path,"\\");
   strcat(path,dir->d_name);
   guncelle1(path,etiket,guncel);
}
	
}

}
void guncelle2(char *p,char etiket[],char guncel[])
{
		DIR *d;
struct dirent *dir;
d=opendir(p);
if(d==NULL)
{
    printf("Tarama esnas�nda bir hata olustu...\n");
    exit(1);
}

while((dir=readdir(d))!=NULL)
{
if(strstr(dir->d_name,".txt")!=NULL)
{
	char txt_path[100],tmp[100],txt_path2[100],txt_path3[100];
	strcpy(tmp,dir->d_name);
	strcpy(txt_path,p);
	strcat(txt_path,"\\");
	strcpy(txt_path3,txt_path);
	strcat(txt_path,dir->d_name);
	FILE *file=fopen(txt_path,"r+");
	if(file==NULL)
	{
		printf("Dosya bulunamadi\n");
		continue;
	}
	char cumle[500];
    int syc=0;
	while(fgets(cumle,500,file)!=NULL)
	{
		if(strstr(cumle,etiket)!=NULL)
		{
	      syc++;
		}
	}
 fclose(file);
   if(syc!=0)
   {
   		FILE *file=fopen(txt_path,"r+");
	if(file==NULL)
	{
		printf("Dosya bulunamadi\n");
		continue;
	}
   	char cumle2[500];
   	  while(fgets(cumle2,500,file)!=NULL)
   	  {
   		if(strstr(cumle2,etiket)!=NULL)
			{
			int yer1=0,i=0;
				char tmp2[100];
			strcpy(tmp2,p);
	        strcat(tmp2,"\\");
			strcat(tmp2,"sahte.txt");
			strcpy(txt_path2,tmp2);
			FILE *f=fopen(tmp2,"a+");	
			if(f==NULL)
			{
				printf("Dosya acma hatasi...\n");
				exit(1);
				}	
				
			yer1=strstr(cumle2,etiket)-cumle2;	
				for(;i<yer1;i++)
				{
				     fputc(cumle2[i],f);
				}
				fputs(guncel,f);
			int size=strlen(etiket);
		int j=yer1+size;
			for(;j<strlen(cumle2);j++)
			{
			fputc(cumle2[j],f);	
			}
		fclose(f);		
		
   }
   else
   {
   	char tmp2[100];
			strcpy(tmp2,p);
	        strcat(tmp2,"\\");
			strcat(tmp2,"sahte.txt");
			FILE *f=fopen(tmp2,"a+");	
			if(f==NULL)
			{
				printf("Dosya acma hatasi...\n");
				exit(1);
				}	
		fputs(cumle2,f);
		fclose(f);			
			
   }
}
fclose(file);
int x=remove(txt_path);
	}
	char tmp3[100];
	strcpy(tmp3,txt_path);
     rename(txt_path2,txt_path);
    
char etiketici[50];
int i=2,h=0;
for(;i<strlen(etiket)-2;i++)
{
etiketici[h]=etiket[i];
h++;	
}
etiketici[h]='\0';
int yer1=0;
if(strchr(etiketici,' ')!=NULL)
{
	yer1=strchr(etiketici,' ')-etiketici;
	etiketici[yer1]='_';
}
if(strstr(dir->d_name,etiketici)!=NULL)
{
  
  		char tmp4[100];
  		int i=2,h=0,yer3=0;
  	for(;i<strlen(guncel)-2;i++)
  	{
  	tmp4[h]=guncel[i];
	  h++;	
	}
	tmp4[h]='\0';
	if(strchr(tmp4,' ')!=NULL)
	{
		yer3=strchr(tmp4,' ')-tmp4;
			tmp4[yer3]='_';
	}
	strcat(tmp4,".txt");
	strcat(txt_path3,tmp4);
	rename(txt_path,txt_path3);
}
	
}
 if(strchr(dir->d_name,'.')==NULL)
{
   char path[PATH_MAX+1];
   strcpy(path,p);
   strcat(path,"\\");
   strcat(path,dir->d_name);
   guncelle2(path,etiket,guncel);
}
	
}

}
int main(int argc, char *argv[]) {
	 setlocale(LC_ALL,"Turkish");
    char path[]="C:\\Users\\Abra\\Desktop\\universite";
    	int derskodu=200;
    	char x[100];
    	strcpy(x,path);
    	strcat(x,"\\");
    	strcat(x,"output.txt");
   FILE *file=fopen(x,"w");
   if(file==NULL)
   {
   printf("Dosya acilamadi");
   exit(1);
   }
fclose(file);
 	int islem=-1;
	menu();
	printf("��leminizi seciniz:");
	scanf("%d",&islem);
getchar();
	while(1)
	{
		char txt[100][50];
	char etik[100][50];
    char list[100][50];
    char istenen[100][50];
    char yetim[100][50];
    	int syc=0,syc2=0,syc3=1,syc4=0,syc5=0;//sayi dizisinin eleman sayisi ile list cok boyutlu dizinin eleman sayisi kadard�r
		int *s=&syc;
		int *s2=&syc2;
		int *s3=&syc3;
		int *s4=&syc4;
		int *s5=&syc5;
    	arama2(path,txt,s);
    	arama3(path,etik,s2);
    	listeolustur(etik,list,s2,s3);
    	istenenbul(txt,istenen,s,s4);
    	int sayi[syc3];
    	etiketsayisi(etik,list,sayi,s2,s3);
		if(islem<0 || islem>2)
		{
			printf("Sectiginiz islem uygun degil\n");
			menu();
			printf("��lemi giriniz:");
			scanf("%d",&islem);
			getchar();
		}
		else{
		if(islem==0)
		{
			printf("C�k� yap�l�yor...\n");
			break;
		}
		else if(islem==1)
		{
			
	char d[100][50],d2[100][50];
	int syc6=0,syc7=0,n=0,m=0;
	int *s6=&syc6;
	int *s7=&syc7;
	   listele1(list,istenen,d,s3,s4,s6);		
        listele2(list,txt,d2,s,s3,s7);
			printf("--->�stenen etiket listesi            --->yetim etiketler listesi...\n");
	    while(n<syc6 && m<syc7)
	    {
		printf("%-35s %-45s\n",d[n],d2[m]);
		m++;
		n++;	
		}
		while(n<syc6)
		{
				printf("%s\n",d[n]);
		n++;	
		}
		while(m<syc7)
		{
				printf("                                     %-35s\n",d2[m]);
		m++;	
		}
        	char kelime[100];
			printf("L�tfen aranacak kelime ya da etiketi giriniz:\n");
		  gets(kelime);
		  etiketkontrol(kelime);
		  if(etiketkontrol(kelime)==1)
		  {
		  	printf("--->%s bir etiket...\n",kelime);
		  }
		  else
		  {
		  	printf("--->%s bir kelime...\n",kelime);
		  }
			arama(path,kelime);
				char x[100];
    	strcpy(x,path);
    	strcat(x,"\\");
    	strcat(x,"output.txt");
   FILE *file=fopen(x,"a");
   if(file==NULL)
   {
   printf("Dosya acilamadi");
   exit(1);
   }
    	 
   fputs("-->Etiket Listesi                    -->Tekrar Sayisi\n",file);
   int m2=0,n2=0;
   char d3[100][50];
   int syc8=0;
   int *s8=&syc8;
   listele2(list,txt,d3,s,s3,s8);
for(;m2<syc3;m2++)
{
  fprintf(file,"%-40s     %d\n",list[m2],sayi[m2]);
}   
fputs("\n-->Yetim Etikletler\n",file);
for(;n2<syc8;n2++)
{
	fprintf(file,"%s\n",d3[n2]);
}
fclose(file);
		}
		else
		{
			
			char etiket[100],guncel[100],d[100][50],d2[100][50];
			int syc6=0,syc7=0;
			int *s6=&syc6;
			int *s7=&syc7;
			listele1(list,istenen,d,s3,s4,s6);
			listele2(list,txt,d2,s,s3,s7);
printf("L�tfen ismi degi�tirilecek etiketi giriniz:");
gets(etiket);
while(1)
{
	if(etiketkontrol(etiket)==-1)
	{
		printf("L�tfen bir etiket giriniz...\n");
		printf("L�tfen ismi degi�tirilecek etiketi giriniz:");
gets(etiket);

	}
	else
	{
		break;
	}
}
while(1)
{
	if(etiketkontrol2(list,d,d2,etiket,s3,s6,s7)==-1)
	{
		printf("�stenen etiket g�ncellenemez\n");
			printf("L�tfen ismi degi�tirilecek etiketi giriniz:");
gets(etiket);

	}
	else if(etiketkontrol2(list,d,d2,etiket,s3,s6,s7)==0)
	{
		break;
	}
  else if(etiketkontrol2(list,d,d2,etiket,s3,s6,s7)==1)
	{
		break;
	}
	else
	{
			printf("Mevcut bir etiket giriniz...\n");
			printf("L�tfen ismi degi�tirilecek etiketi giriniz:");
            gets(etiket);
            
	}
}
printf("L�tfen etiketin g�ncellenmi� halini giriniz:([[ ]] icinde giriniz)");
gets(guncel); 			
  while(1)
  {
     	if(etiketkontrol(guncel)==-1)
	{
		printf("L�tfen uygun bir etiket giriniz...\n");
		printf("L�tfen ismi degi�tirilecek etiketi giriniz:");
gets(guncel);
	}
	else
	{
		break;
	}
  }	
 if(etiketkontrol2(list,d,d2,etiket,s3,s6,s7)==0)
 {
 	int secenek=-1,syc=0;
 	printf("Yetim etiketin txt dosays� olu�sun mu?(evet(1)-hay�r(2))");
 	scanf("%d",&secenek);
 	getchar();
 	while(syc<3)
 	{
 	if(secenek<1 || secenek>2)
	 {
	 	printf("Bir i�lem senegi giriniz...\n");
	 	printf("Yetim etiketin txt dosays� olu�sun mu?(evet(1)-hay�r(2))");
 	scanf("%d",&secenek);
 	syc++;
		 }
		 else
		 {
		 	break;
			 }	
			 if(syc==3)
			 {
			 	printf("�� hakk�n�z doldu ve txt dosyas� olu�turulmacak olarak ayarland�...\n");
			 	secenek=syc-1;
			 }
	 }
	guncelle1(path,etiket,guncel);
	 if(secenek==1)
	 {
	 	int yer1=0,yer2=0;
	 	char yol[]="C:\\Users\\Abra\\Desktop\\�niversite\\Dersler";
	 	char tmp[100];
	 	yer1=strstr(guncel,"[[")-guncel;
	 	yer2=strstr(guncel,"]]")-guncel;
	 	int i=yer1+2,h=0;
	 	char etiketici[yer2-yer1];
	 	for(;i<yer2;i++)
	 	{
	 		etiketici[h]=guncel[i];
	 		h++;
		 }
		 etiketici[h]='\0';
		 int yer4=0;
		 if(strchr(etiketici,' ')!=NULL)
		 {
		 	yer4=strchr(etiketici,' ')-etiketici;
		 	etiketici[yer4]='_';
		 }
	 	strcpy(tmp,yol);
	 	strcat(tmp,"\\");
	 	strcat(tmp,etiketici);
	 	strcat(tmp,".txt");
	 	FILE *f1=fopen(tmp,"w");
	    fprintf(f1,"Ders Kodu:BLM%d\n",derskodu);
	    fprintf(f1,"Ders Ad�:%s\n",guncel);
	    fprintf(f1,"Ders �cerigi:");
		derskodu++;
	 }	 
	 }	
else
{
	guncelle2(path,etiket,guncel);
}		
		
		 char txt[100][50];
	char etik[100][50];
    char list[100][50];
    char istenen[100][50];
    char yetim[100][50];
    	int syc=0,syc2=0,syc3=1,syc4=0,syc5=0;//sayi dizisinin eleman sayisi ile list cok boyutlu dizinin eleman sayisi kadard�r
		int *s=&syc;
		int *s2=&syc2;
		int *s3=&syc3;
		int *s4=&syc4;
		int *s5=&syc5;
    	arama2(path,txt,s);
    	arama3(path,etik,s2);
    	listeolustur(etik,list,s2,s3);
    	istenenbul(txt,istenen,s,s4);
    	int sayi[syc3];
    	etiketsayisi(etik,list,sayi,s2,s3);
					
			char outputpath[100];
			strcpy(outputpath,path);
			strcat(outputpath,"\\");
			strcat(outputpath,"output.txt");
			FILE *file=fopen(outputpath,"a");
			if(file==NULL)
			{
				printf("Dosya acma hatas�");
				exit(1);
			}
			fputs("\n G�ncel Liste!!! \n\n",file);
			fputs("-->Etiket Listesi                 -->Tekrar say�s�\n",file);
			int i=0,j=0;
			for(;i<syc3;i++)
			{
				fprintf(file,"%-35s     %d\n",list[i],sayi[i]);
			}
			fputs("\nYetim Etiket Lisyesi\n",file);
			char d3[100][50];
			int syc8=0;
			int *s8=&syc8;
			listele2(list,txt,d3,s,s3,s8);
			for(;j<syc8;j++)
			{
				fprintf(file,"%s\n",d3[j]);
			}
			fclose(file);
			
		}
		menu();
		printf("��lmeinizi seciniz:\n");
	    scanf("%d",&islem);
	   getchar();
}
	}
	
	
	


	return 0;
} 
