#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(1)
#define MAX_Student 100

struct Date
{
	int day;
	int month;
	int year;
};
struct Student
{
	int studentNumber;
	char name[25];
	char surname[25];
	struct Date bdate;
	float math;
	float science;
	float turkish;
};


int stdCount = 0;

int cmp(const void *a, const void *b) {
    // compare function for qsort
    // this is the user-supplied compare function always required by qsort
    // qsort does not know or care about the data type, only its dimensions
    // so I cast the void pointers to our local data type
    struct Student *aa = (struct Student*)a;
    struct Student *bb = (struct Student*)b;
    if(aa->studentNumber > bb->studentNumber) return 1;
    if(aa->studentNumber < bb->studentNumber) return -1;
    return 0;
}

int sortbyNumber(){
	// set up
	printf("fonk basi buradasiniz");
	struct Student A;
	struct Student * data;
	FILE *file;
    file = fopen("ogrenci.bin", "r");
    if(file == NULL) {
        printf("File error\n");                     // finish messages with a newline
        return 1;
    }
	data = (struct Student *) malloc(MAX_Student * sizeof(struct Student));
	

	if(data == NULL) {
        printf("Memory error\n");
        return 1;
    }
	while(fread(&A,sizeof(struct Student),1,file)){
	
	//while(fscanf(file, "%d %s %s %d/%d/%d %f %f %f",&studentNumber,&A.name,&A.surname, &A.bdate.day, &A.bdate.month, &A.bdate.year, &A.math, &A.science, &A.turkish) == 9) {
	    if(stdCount >= MAX_Student) {
            printf("Too many student\n");
            break;
        }
        data[stdCount].studentNumber = A.studentNumber;             // make a copy of the strings
        //data[stdCount].name = A.name,25,stdin;
        //data[stdCount].surname = A.surname;
        data[stdCount].bdate.day = A.bdate.day;         // copy the data
        data[stdCount].bdate.month = A.bdate.month; 
        data[stdCount].bdate.year = A.bdate.year; 
        data[stdCount].math = A.math;
        data[stdCount].science = A.science;
        data[stdCount].turkish = A.turkish;
        stdCount++;                                     // track the number of records
    }
    fclose(file);

	qsort(data, stdCount, sizeof *data, cmp);

	// print the data

    printf("\n StdNumber\tDTarih\tMnot\tFNot\tTNot\tName\n");
    for(int c=0; c<stdCount; c++) {
        sprintf(A.name, "%d %d", data[c].studentNumber, data[c].math);   // to make alignment easy
        printf("%d %d %s \n",  data[c].studentNumber,data[c].math, A.name);
    }
}



void ReadbyKeyboard(struct Student *X)
{
	char c;
	printf("Ogrenci Numarasi :");
	scanf("%d",&X->studentNumber);
	c=getchar();
	printf("Ogrenci Adi : ");
	fgets(X->name,25,stdin);
	printf("Ogrenci Soyadi : ");
	fgets(X->surname,25,stdin);
	printf("Dogum Tarihi : ");
	scanf("%d/%d/%d",&X->bdate.day,&X->bdate.month,&X->bdate.year);
	printf("Matematik Notu :");
	scanf("%f",&X->math);
	printf("Fen Notu : ");
	scanf("%f",&X->science);
	printf("Turkce Notu : ");
	scanf("%f",&X->turkish);
}

void Display(struct Student X)
{
	char c;
	printf("Ogrenci Numarasi :%d\n",X.studentNumber);
	printf("Ogrenci Adi : %s\n", X.name);
	printf("Ogrenci Soyadi : %s\n",X.surname);
	printf("Dogum Tarihi : %d/%d/%d\n",X.bdate.day,X.bdate.month,X.bdate.year);
	printf("Matematik Notu :%f\n",X.math);
	printf("Fen Notu : %f\n",X.science);
	printf("Turkce Notu : %f\n",X.turkish);
	return;
}

int deleteRecord(char *fname, int i) {
	FILE *fp;
	FILE *fp_tmp;
	int found=0;
	struct Student A;

	fp=fopen(fname, "r+");
	if (!fp) {
		printf("%s dosyasý acilamadi", fname);
		return -1;
	}
	fp_tmp=fopen("tmp.bin", "w+");
	if (!fp_tmp) {
		printf("Tmp dosyasi acilamadi.");
		return -1;
	}
	
	while (fread(&A,sizeof(struct Student),1,fp) != NULL) {
		if (i==A.studentNumber) {
			printf("Kayit bulundu ve silindi.\n\n");
			found=1;
		} else {
			fwrite(&A, sizeof(struct Student), 1, fp_tmp);
		}
	}
	if (! found) {
		printf("No record(s) found with the requested number: %d\n\n", i);
	}

	fclose(fp);
	fclose(fp_tmp);

	remove(fname);
	rename("tmp.bin", fname);

	return 0;
}
/*
int sirala(char *fname){
	struct Student A[100];
	struct Student temp;
	FILE *fp, *ft;
	int i=0,size,j;
	char ch; 
 
	fp=fopen(fname,"r+");
	if(fp==NULL)
	{ 
	printf("\n Cannot open the file \n");
	exit(0);
	}
	while(ch!=EOF)
	{
	//fread(fp,"%d %s %s %d/%d/%d %f %f %f",&A[i].studentNumber,A[i].name,A[i].surname, &A[i].bdate.day, &A[i].bdate.month, &A[i].bdate.year, &A[i].math, &A[i].science, &A[i].turkish);  
	fread(&A[i],sizeof(struct Student),1,fp);
	ch=fgetc(fp); 
	i++;  
	} 
	size=i-1;
	for(i=1;i<size;++i)
		for(j=0;j<size-i;j++)
			if(strcmp(A[j+1].name,A[j].name)<0)
			{
				temp=A[j];
				A[j]=A[j+1];
				A[j+1]=temp;
			}
	ft=fopen("sorted.bin","w+");
	for(i=0;i<size;i++)
	//fwrite(fp,"%d %s %s %d/%d/%d %f %f %f \n",A[i].studentNumber,A[i].name,A[i].surname, A[i].bdate.day, A[i].bdate.month, A[i].bdate.year, A[i].math, A[i].science, A[i].turkish);
	fwrite(&A[i], sizeof(struct Student), 1, ft);
	printf("\n The file is sorted successfully and saved as sorted.bin \n \n");

}*/






int main(){
	int islem;
	
	while(1) {
		printf("1 - Ogrenci Kaydi Ekle\n");
		printf("2 - Ogrenci Kaydi Sil\n");
		printf("3 - Ogrenci Kaydi Guncelle\n");
		printf("4 - Tum ogrencileri listele\n");
		printf("5 - Kayitlari ogrenci numarasina gore sirala\n");
		printf("6 - Kayitlari isimlerine gore sirala\n");
		printf("7 - Kayitlari matematik notuna gore sirala\n");
		printf("8 - Kayitlari fen notuna gore sirala\n");
		printf("9 - Kayitlari turkce notuna gore sirala\n");
		printf("10 - Sirali kayitlari 'sorted.bin''e yaz\n");
		printf("11 - Cikis\n");
		printf("Seciminizi Giriniz : ");
		
		scanf("%d",&islem);
		
		//kayýt ekleme
		if(islem==1){
			FILE *fp;
			struct Student A;
			fp=fopen("ogrenci.bin","r+");
			if(fp==NULL) fp=fopen("ogrenci.bin","w+");
			ReadbyKeyboard(&A);
			fseek(fp,0,SEEK_END);
			fwrite(&A,sizeof(struct Student),1,fp);
			fclose(fp);
		}
		//kayýt silme
		if(islem==2)
		{
			int l;
			printf("Silmek istediginiz ogrenci numarasini giriniz:");
			scanf("%d",&l);
			deleteRecord("ogrenci.bin", l);    		
		}
		//kayýt güncelleme
		if(islem==3){
			//eklenecek
		}
		//kayýtlarý listele
		if(islem==4){
			FILE *fp;
			int m=0,i;
			struct Student A;
			fp=fopen("ogrenci.bin","r+");
			if(fp==NULL) fp=fopen("ogrenci.bin","w+");
			fseek(fp,0,SEEK_END);
			m=ftell(fp)/sizeof(struct Student);
			printf("\nKayitli ogrenci sayisi : %d\n",m);
			fseek(fp,0,SEEK_SET);
			for(i=0;i<m;i++)
			{
				fread(&A,sizeof(struct Student),1,fp);
				if(feof(fp)) break;
				Display(A);
			}
			fclose(fp);
		}
		//ogr numarasýna göre listeleme
		if(islem==5){
			sortbyNumber();
		}
		//ogr adýna göre listeleme
		if(islem==6){
			//sirala("ogrenci.bin");
		}
		//sirali kayitlari yaz
		if(islem==10){
			FILE *fp;
			int m=0,i;
			struct Student A;
			fp=fopen("sorted.bin","r+");
			if(fp==NULL) fp=fopen("sorted.bin","w+");
			fseek(fp,0,SEEK_END);
			m=ftell(fp)/sizeof(struct Student);
			printf("\nKayitli ogrenci sayisi : %d\n",m);
			fseek(fp,0,SEEK_SET);
			for(i=0;i<m;i++)
			{
				fread(&A,sizeof(struct Student),1,fp);
				if(feof(fp)) break;
				Display(A);
			}
			fclose(fp);
		}
		//çýkýþ
		if(islem==11)
			break;
	}
}
