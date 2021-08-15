#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<conio.h>




void add(FILE *fp);
FILE *del(FILE *fp);
void modify(FILE *fp);
void display(FILE *fp);
void search(FILE *fp);
void printChar(char ch, int n);
void printMain();


struct student {
	char name[100];
	int standard;
	char section;
	int roll;
	float mark[5];
	float total;
	char grade;

};

FILE *fp;
int main() {

	FILE *fp;
	student s;
	int option;
	char another;

	if((fp=fopen("studentinfo.txt","rb+")) == NULL){
		if((fp=fopen("studentinfo.txt","wb+")) == NULL)
		{
			printf("CAN NOT OPEN FILE...ERROR");
		}
	}
	
	printMain();
	printf("\n\n\t\tCREATED BY Krishnaai Naik");
	printf("\n\t\tPress any key to continue");
	getch();
	
	while(1)
	{
		printMain();
		printf("\n\t");
		printChar('-',65);
		
		printf("\n\n\t\t\t1. ADD STUDENT");
		printf("\n\n\t\t\t2. DELETE STUDENT");
		printf("\n\n\t\t\t3. MODIFY STUDENT");
		printf("\n\n\t\t\t4. DISPLAY STUDENTS LIST");
		printf("\n\n\t\t\t5. SEARCH STUDENT");
		printf("\n\n\t\t\t0. EXIT");
		
		
		printf("\n\n\t\tEnter Your Option:- ");
		scanf("%d", &option);
		
		switch(option)
		{
			case 0:
				return 1;
				break;
			case 1:
				add(fp);
				break;
			case 2:
				fp = del(fp);
				break;
			case 3 :
				modify(fp);
				break;
			case 4:
				display(fp);
				break;
			case 5:
				search(fp);
				break;
			default:
				printf("\n\t\tYou Pressed Wrong Option:-");
				getch();
				exit(0);
		}	
	}
	
	return 1;

}




//-------- printing character ch at n times printChar()----
void printChar(char ch, int n)
{
	while(n--)
	{
		putchar(ch);
	}
}


//----------main line i.e. printMain()------
void printMain()
{
	system("cls");
	printf("\n\n\t");
	printChar('-',15);
	printf("JAWAHAR NAVODAYA VIDALAYA");
	printChar('-',15);
	printf("\n");
	printChar('-',15);
	printf("ANNUAL REPROT CARD");
	printChar('-',15);
	printf("\n");
}

//------------ADDING STUDENT-----------
void add(FILE *fp)
{
	printMain();
	
	char another = 'y';
	student s;
	int i;
	float total;
	char grade;
	
	fseek(fp,0,SEEK_END);
	while(another=='y' || another=='Y')
	{
		printf("\n\n\t\tEnter full namr of the student: \t");
		fflush(stdin);
		fgets(s.name,100,stdin);
		s.name[strlen(s.name)-1]='\0';
		
		printf("\n\n\t\tEnter RollNumber: \t");
		scanf("%d",&s.roll);
		
		printf("\n\n\t\tEnter Your Standard: \t");
		scanf("%d",&s.standard);
		
		printf("\n\n\t\tEnter Your Section: \t");
		fflush(stdin);
		scanf("%c",&s.section);
		
		printf("\n\n\tMarks Secured out of 100 : ");
		for(i=0,total=0;i<5;i++){
			scanf("%f",s.mark[i]);
			total+=s.mark[i];
		}
		
		total/=500;
		s.total=total;
		if(total<=500 && total>=450)
			s.grade='A';
	    else if(total<450 && total>=400)
			s.grade='B';
		else if(total<400 && total>=350)
			s.grade='C';
		else if(total<350 && total>=300)
			s.grade='D';
		else if(total<300 && total>=200)
			s.grade='E';
		else if(s.grade<+200)
			s.grade='F';
			
			
		fwrite(&s,sizeof(s),1,fp);
		
		printf("\n\n\t\tWnat to enter another student (Y/n): \t");
		fflush(stdin);
		another=getchar();	
		
	}
}


//------- DELETEING THE RECORD OF A STUDENT-------
FILE *del(FILE *fp)
{
	printMain();
	student s;
	int flag=0, tempRoll, siz=sizeof(s);
	FILE *ft;
	
	if((ft=fopen("temp.txt","wb+"))==NULL)
	{
		printf("\n\n\t\t\t!!!! ERROR!!!!!\n\t\t");
		system("pause");
		return fp;
	}
	
	printf("\n\n\tEnter Roll Number of Student to Delete the Record:");
	printf("\n\n\t\tRoll No.:");
	scanf("%d",&tempRoll);
	
	rewind(fp);
	
	while((fread(&s,siz,1,fp))==1)
	{
		 if(s.roll==tempRoll){
		    flag=1;
    		printf("\n\tRecord Deleted for");
   		    printf("\n\n\t\t%s\n\n\t\t%d\n\n\t\t%d\n\t\n\n\t\t%c",s.name,s.standard,s.roll,s.section);
            continue;
    }

    fwrite(&s,siz,1,ft);
	}
	
	fclose(fp);
	fclose(ft);

	remove("studentinfo.txt");
	rename("temp.txt","studentinfo.txt");

	if((fp=fopen("studentinfo.txt","rb+"))==NULL)
	{
    	printf("ERROR");
    	return  NULL;
	}

	if(flag==0) printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND \n\t");

	printChar('-',65);
	printf("\n\t");
	system("pause");
	return fp;
	
}


//-------MODIFY THE RECORDS OF THE STUDENTS-----
void modify(FILE * fp)
{
	printMain();
	
	student s;
	int i,flag=0,tempRoll,siz=sizeof(s);
	float total;
	
	printf("\n\n\tEnter Roll Number of Student to MODIFY the Record : ");
	scanf("%d",&tempRoll);
	
	rewind(fp);
	
	while((fread(&s,siz,1,fp))==1)
	{
	    if(s.roll==tempRoll)
	        {flag=1;
	        break;
	        }
	        
	
	if(flag==1)
	    {
	    fseek(fp,-siz,SEEK_CUR);
	    printf("\n\n\t\tRECORD FOUND");
	    printf("\n\n\t\tEnter New Data for the Record");
	
	    printf("\n\n\t\tEnter full namr of the student: \t");
			fflush(stdin);
			fgets(s.name,100,stdin);
			s.name[strlen(s.name)-1]='\0';
			
			printf("\n\n\t\tEnter RollNumber: \t");
			scanf("%d",&s.roll);
			
			printf("\n\n\t\tEnter Your Standard: \t");
			scanf("%d",&s.standard);
			
			printf("\n\n\t\tEnter Your Section: \t");
			fflush(stdin);
			scanf("%c",&s.section);
			
			printf("\n\n\tMarks Secured out of 100 : ");
			for(i=0,total=0;i<5;i++){
				scanf("%f",s.mark[i]);
				total+=s.mark[i];
			}
			
			total/=500;
			s.total=total;
			if(total<=500 && total>=450)
				s.grade='A';
		    else if(total<450 && total>=400)
				s.grade='B';
			else if(total<400 && total>=350)
				s.grade='C';
			else if(total<350 && total>=300)
				s.grade='D';
			else if(total<300 && total>=200)
				s.grade='E';
			else if(s.grade<+200)
				s.grade='F';
	
	    fwrite(&s,sizeof(s),1,fp);
	}
	
	else printf("\n\n\t!!!! ERROR !!!! RECORD NOT FOUND");
	
	printf("\n\n\t");
	system("pause");

}
}


//--------------display the list of the entered students---
void display(FILE *fp){
	printMain();
    student s;
    int i,siz=sizeof(s);

    rewind(fp);

    while((fread(&s,siz,1,fp))==1)
    {
        printf("\n\t\tNAME : %s",s.name);
        printf("\n\n\t\tSTANDARD : %d",s.standard);
        printf("\n\n\t\tROLL : %d",s.roll);
        printf("\n\n\t\tSECTION : %c",s.section);
        printf("\n\n\tMarks Secured out of 100-- ");

        for(i=0;i<5;i++)
            printf("| %.3f |",s.mark[i]);
        printf("\n\n\t\tTotal Marks Secured : %.2f\n\t",s.total);
        printf("\n\n\t\tGrade : %c",s.grade);
        printChar('-',65);
    }
    printf("\n\n\n\t");
    printChar('-',65);
    printf("\n\n\t");
    system("pause");
    
}
    




//=--------SEARCH OF THE RECORDD-------
void search(FILE *fp)
{
		printMain();
		
		int tempRoll,flag,siz,i;
		student s;
		char another='y';
		
		siz=sizeof(s);
		
		while(another=='y'||another=='Y')
		{
		printf("\n\n\tEnter Roll Number of Student to search the record : ");
		scanf("%d",&tempRoll);
		
		rewind(fp);
		
		while((fread(&s,siz,1,fp))==1)
		{
		    if(s.roll==tempRoll)
		        {flag=1;
		        break;
		        }
		}
		
		if(flag==1)
		    {
		    printf("\n\t\tNAME : %s",s.name);
	        printf("\n\n\t\tSTANDARD : %d",s.standard);
	        printf("\n\n\t\tROLL : %d",s.roll);
	        printf("\n\n\t\tSECTION : %c",s.section);
	        printf("\n\n\tMarks Secured out of 100-- ");
	
	        for(i=0;i<5;i++)
	            printf("| %.3f |",s.mark[i]);
	        printf("\n\n\t\tTotal Marks Secured : %.2f\n\t",s.total);
	        printf("\n\n\t\tGrade : %c",s.grade);
	        printChar('-',65);
		
		}
		else printf("\n\n\t\t!!!! ERROR RECORD NOT FOUND !!!!");
		
		
		printf("\n\n\t\tWant to enter another search (Y/N)");
		fflush(stdin);
		another=getchar();
		}
	}


