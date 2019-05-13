#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	fp=fopen(fname, "rb");
	if (!fp) {
		printf("%s dosyasý acilamadi", fname);
		return -1;
	}
	fp_tmp=fopen("tmp.bin", "wb");
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
		if(islem==2)
		{
			int k;
			printf("Silmek istediginiz ogrenci numarasini giriniz:");
			scanf("%d",&k);
			deleteRecord("ogrenci.bin", k);    		
		}
		if(islem==4){
			FILE *fp;
			int m=0,i;
			struct Student A;
			fp=fopen("ogrenci.bin","r+");
			if(fp==NULL) fp=fopen("ogrenci.bin","w+");
			fseek(fp,0,SEEK_END);
			m=ftell(fp)/sizeof(struct Student);
			printf("\nKayitli ogrenci sayisi : %d\n",(m-1));
			fseek(fp,0,SEEK_SET);
			for(i=0;i<m;i++)
			{
				fread(&A,sizeof(struct Student),1,fp);
				if(feof(fp)) break;
				Display(A);
			}
			fclose(fp);
		}
		if(islem==11)
			break;
	}
}
