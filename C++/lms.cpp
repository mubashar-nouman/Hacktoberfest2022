/*-----------------------------------------------------------
 * Description: Program that creates a database for an LMS
 *-----------------------------------------------------------*/

#include <stdio.h>
#include<conio.h>
#include <iostream>
#include <stdlib.h> // malloc() function
#define T_FILE "database.txt"
#define B_FILE "database.dat"
#define MAX 1000 
int i,j,check=0;   // i && j counters check: turn on/off the checking of errors during the function call 
int count_s;   // count_s: counter of the number of students in the database
int credit_num;  // credit number of each student (will be calculated via a mathematical formula "No need to include it in the sturct")
typedef struct {        // course name struct  {course_sub: COURSE NAME ;course_num: COURSE NUMBER}
	char course_sub[5];
	short course_num;
}course_name;
typedef enum semester{Fall=1,Spring,Summer         // ENUM TYPE TO RECORD THE SEMESTER OF COURSES "1 instead of 0 to link enum and array"
}semester;
const char *semester_name[] = { "", "FALL", "SPRING", "SUMMER"};  // 2D array to record semesters
typedef struct {    // second struct {course name ; semester of that course ; year ; grade [3] "WP"=> 2 CHAR + '\0' }
	course_name s_course;
	semester s_semester;
	short year;
	char grade[3];
}course;
typedef struct {    // birthday struct 
	short day;
	short month;
	short year;
}date_t;
typedef struct{  // personal info struct {name, address, phone number, gender, birthday, and city of birth} 
	char name[30];
	char address[30];
	long phone;
	char gender;  //'f' for female and 'm' for male
	date_t birthday;
	char city[20];
}personal_t;
typedef struct { // student struct the combination of all information {ID , personal info , courses ,course-number (number of courses taken), and GPA }  
	int ID;
	personal_t s_personal;
	course s_course[20];
	int course_number;
	float GPA;
}student;
static FILE *ptr;  			// declare a file pointer "STATIC" to make it accessible in every function 
void add_info(student*);   // add information about a student; Parameters: {pointer to student struct}
int read_binary(student *);    // Read all information from a binary file 
void print_s(student *,FILE *); //print display info used for searching purposes {second argument "stream to read"}
void write_binary(student *); // write in a binary file 
char menu(void);           // Database menu
void delete_s(student *);  // delete a student 
void search(student *);   // search for a student 
void store_txt(student *);		// store data to text file 
void read_txt(student *);     // read data form text file 
void edit(student *s);     // EXTRA CREDIT FUNCTION "EDIT"
char submenu();  		// SUBMENU ONLY FOR EDIT FUNCTION 
int main(void)
{ 
	student s[MAX];
	count_s=read_binary(s);
	puts("____________Welcome to student database____________"); // puts for the first execution only 
	// THE FUNCTION system("cls") IS USED TO CLEAR THE SCREEN JUST "user friendly" PURPOSES
	while (1)
	{
		switch (menu())
		{
			case '1':system("cls");add_info(&s[count_s]);system("cls");printf("-> THNAK YOU PLEASE ENTER YOU NEXT CHOICE\n");break;
			case '2':check=1;write_binary(s);break;
			case '3':check=1;store_txt(s);break;	
			case '4':check=1;read_binary(s);break;
			case '5':system("cls");read_txt(s);break;	
			case '6':system("cls");search(s);break;
			case '7':system("cls");delete_s(s);break;
			case '8':system("cls");edit(s);break;
			case '9':system("cls");check=0;write_binary(s);puts("End of run have a nice day :)");return 0;
			default:system("cls");fprintf(stderr,"INVALID OPERATION TRY AGAIN\n");	
		}
		fflush(stdin);
	}
	return 0;
}
char menu(void)
{
	puts("____________________________________________________");
	puts("1- Add information about a student");
	puts("2- Store the data to a binary file");
	puts("3- Store the data to text file");
	puts("4- Load the data from a binary file");
	puts("5- Read the data from a text file");
	puts("6- Search by ID number and display the information");
	puts("7- Delete information about a student");
	puts("8- Edit information about a student");
	puts("9- EXIT");
	puts("____________________________________________________");
	printf("Please enter your choice: ");
	return getchar();
}
void add_info(student *s1)
{
	puts("________Student Info________");
	printf("Enter your ID: ");
	scanf("%d",&s1->ID);
	fflush(stdin);
	printf("Enter your name: ");
	gets(s1->s_personal.name);
	fflush(stdin);
	printf("Enter your address: ");  
	gets(s1->s_personal.address);
	fflush(stdin);
	printf("Enter your phone number: ");
	scanf("%d",&s1->s_personal.phone);
	getchar();
	printf("Gender (m) for male (f) for female: ");
	scanf("%c",&s1->s_personal.gender);
	fflush(stdin);
	printf("Enter birthday format(dd/mm/yyyy): ");
	scanf("%2d/%2d/%4d",&s1->s_personal.birthday.day,&s1->s_personal.birthday.month,&s1->s_personal.birthday.year);
	fflush(stdin);
	printf("Enter your city of birth: ");
	gets(s1->s_personal.city);
	fflush(stdin);
	puts("________Course Info________");
	printf("Enter number of courses taken: ");
	scanf("%d",&s1->course_number);
	fflush(stdin);
	for (i=0;i<s1->course_number;i++)
	{
		printf("Enter course %d name: ",i+1);
		scanf("%[a-zA-Z]%d",s1->s_course[i].s_course.course_sub,&s1->s_course[i].s_course.course_num);
		fflush(stdin);
		printf("Semester taken (1) fall (2) spring (3)summer: ");
		scanf("%d",&s1->s_course[i].s_semester);
		printf("Year Taken: ");
		scanf("%4d",&s1->s_course[i].year);
		fflush(stdin);
		printf("%s%d recieved grade: ",s1->s_course[i].s_course.course_sub,s1->s_course[i].s_course.course_num);
		scanf("%s",s1->s_course[i].grade);
		while(1)
		{
			if( ((s1->s_course[i].grade[0]!='A')&&(s1->s_course[i].grade[0]!='B')&&(s1->s_course[i].grade[0]!='C')&&(s1->s_course[i].grade[0]||'D')&&(s1->s_course[i].grade[0]!='F')&&(s1->s_course[i].grade[0]!='W'))||((s1->s_course[i].grade[1]!='+')&&(s1->s_course[i].grade[1]!='-')&&(s1->s_course[i].grade[1]!='\0')&&(s1->s_course[i].grade[1]!='P')&&(s1->s_course[i].grade[1]!='F')))
			{	
				fprintf (stderr,"Incorect choice try again\n ");
				fprintf(stderr,"Enter the grade (A+, A ,A-, B+,B, B-, C+, C, C-, D+, D, D-,F, WP, W, WF) --> \n");
				fflush(stdin);
				gets(s1->s_course[i].grade);
			}
		else 
			break;
		}
		fflush(stdin);
	}
	puts("___________________________");
	printf("Enter your overall GPA: ");
	scanf("%f",&s1->GPA);
	count_s++;
}
int read_binary(student *s1)
{
	int count=0;
	(check==1 && count_s==0)?fprintf(stderr,"No data to load file is empty\n"): puts(""); // check if we want ot check errors or not 
	if((ptr=fopen(B_FILE,"rb"))==NULL)
	{
		(check==1)?fprintf(stderr,"Couldn't open the file !!!\n"):puts("");
		count=0;
	}
	else
	{	
		while (1)
		{
		 	if ((fread(&s1[count],sizeof(student),1,ptr))>0)
		 		count++;
		 	else 
			 	break;	
		}
		fclose(ptr);
		(check==1 && count!=0)? fprintf(stderr,">> The process of loading data from Binary file was successful.\n") : printf("");
	}
	return count;
}
void print_s(student *s,FILE *ptr)
{
	credit_num=0;
	fputs("----------Overall Information----------\n",ptr);
	fprintf(ptr,"- ID: %d\n",s->ID);
	fprintf(ptr,"- Name: %s\n",s->s_personal.name);
	fprintf(ptr,"- Adrees: %s\n",s->s_personal.address);
	fprintf(ptr,"- Birthday: %d/%d/%d\n",s->s_personal.birthday.day,s->s_personal.birthday.month,s->s_personal.birthday.year);
	fprintf(ptr,"- City of birth: %s\n",s->s_personal.city);
	fprintf(ptr,"- Phone Number: %.10d\n",s->s_personal.phone);
	fprintf(ptr,"- Gender: %s\n",(s->s_personal.gender=='M' || s->s_personal.gender=='m')?"Male":"Female");
	for (i=0;i<s->course_number;i++)
	{
		fprintf(ptr,"______Course %d________\n",i+1);
		fprintf(ptr,"- Course: %s%d\n",s->s_course[i].s_course.course_sub,s->s_course[i].s_course.course_num);
		fprintf(ptr,"\t-> Taken: %s %d\n",semester_name[s->s_course[i].s_semester],s->s_course[i].year);
		fprintf(ptr,"\t-> Grade: %s\n",s->s_course[i].grade);
		fputs("_________________________\n",ptr);
		credit_num=credit_num+((s[j].s_course[i].s_course.course_num)/100)%10;
	}
	fprintf(ptr,"- Total Number of credit recorded is: %d\n",credit_num);
	fprintf(ptr,"- GPA: %.2f\n",s->GPA);
}
void write_binary(student *s)
{
	if (count_s==0 && check!=0)
	{
		(check==1) ? fprintf(stderr,"No data to store enter some data first.\n"):puts("");
	}
	else 
	{
			if((ptr=fopen(B_FILE,"wb"))==NULL)
				fprintf(stderr,"The process of storing data was unsuccessful!!!\n");
			else 
			{
				for (i=0;i<count_s;i++)
				{
					fwrite(&s[i],sizeof(student),1,ptr);
				}
				(check==1) ? fprintf(stderr,">> The process of storing data to Binary file was succeesfully\n"):puts("");
			fclose(ptr);
			}
	}
	
}
void delete_s(student *s)
{
	int id_delete,flag=0;
	if (count_s!=0)
	{
		printf("ID Student: ");
		scanf("%d",&id_delete);
		fflush(stdin);
		printf("ARE YOU SURE YES(Y) NO(N): ");
		if (getchar()=='Y' || getchar()=='y')
		{
			for (i=0;i<count_s;i++)
			{
				if (s[i].ID==id_delete)
				{
					flag=1;
					if (i==0)
					{
						count_s=0;
					}
					else if ((i-1)==count_s)
					{
						count_s--;
					}
					else 
					{
						s[i]=s[i+1];
						count_s--;
					}
					check=0,write_binary(s),store_txt(s);
				}
			}
		}
		(flag==1)? fprintf(stderr,">> Student deleted successfully\n") : fprintf(stderr,">> Student not found in the database\n");
	}
	else 
		fprintf(stderr,"DATABASE IS EMPTY\n");
}
void search(student *s)
{
	int id_search;
	if (count_s!=0)
	{
		printf("Enter id to search for:");
		scanf("%d",&id_search);
		for(j=0;j<count_s;j++)
		{
			if (s[j].ID==id_search)
			{
				printf("Student found information is : \n");
				print_s(&s[j],stdout);
				break;
			}
		}
		(j==count_s) ? fprintf(stderr,"->Student with %d id number was not found in the database\n\n",id_search): puts("");
	}
	else 
		fprintf(stderr,"DATABASE IS EMPTY\n");
	
}
void store_txt(student *s)
{
	if (count_s==0 && check!=0)
		fprintf(stderr,"No data to store, enter some information first.\n");
	else
	{
		if ((ptr=fopen(T_FILE,"w"))!=NULL)
	{
		for (j=0;j<count_s;j++)
		{
			fprintf(ptr,"- ID: %d\n",s[j].ID);
			fprintf(ptr,"- Name: %s\n",s[j].s_personal.name);
			fprintf(ptr,"- Adrees: %s\n",s[j].s_personal.address);
			fprintf(ptr,"- Birthday: %d/%d/%d\n",s[j].s_personal.birthday.day,s[j].s_personal.birthday.month,s[j].s_personal.birthday.year);
			fprintf(ptr,"- City of birth: %s\n",s[j].s_personal.city);
			fprintf(ptr,"- Phone Number: %d\n",s[j].s_personal.phone);
			fprintf(ptr,"- Gender: %s\n",(s[j].s_personal.gender=='M' || s[j].s_personal.gender=='m')?"Male":"Female");
			for (i=0,credit_num=0;i<s[j].course_number;i++)
			{
				fprintf(ptr,"______Course %d________\n",i+1);
				fprintf(ptr,"- Course: %s%d\n",s[j].s_course[i].s_course.course_sub,s[j].s_course[i].s_course.course_num);
				fprintf(ptr,"\t. Taken: %s %d\n",semester_name[s[j].s_course[i].s_semester],s[j].s_course[i].year);
				fprintf(ptr,"\t. Grade: %s\n",s[j].s_course[i].grade);
				fputs("_________________________\n",ptr);
				credit_num=credit_num+((s[j].s_course[i].s_course.course_num)/100)%10;
			}
			fprintf(ptr,"- Total Number of credit recorded is: %d\n",credit_num);
			fprintf(ptr,"- GPA: %.2f\n",s[j].GPA);
			fputs("___________________________________________________\n",ptr);
		}
		fprintf(ptr,"%c",'!');
		fclose(ptr);
		(check==1) ? fprintf(stderr,">> Process of storing data to text file was succeesfully\n") : puts("");
	}
	else 
		fprintf(stderr,"Process of storing data was unsuccessful");
	}	
}
void read_txt(student *s)
{
	char *buffer;
	int size;
	if (count_s==0)
		fprintf(stderr,"No data is stored.\n");
	else
	{
		if ((ptr=fopen(T_FILE,"r"))!=NULL)
		{
			puts("The information available in the text file is: ");
			fseek(ptr, 0, SEEK_END); 		 // seek to the end of the file 
			size=ftell(ptr);       			// Get the exact size of the file 
			rewind(ptr); 					// Get the beginning of the file
			int buffer=malloc((size+1)*sizeof(char));  // Dynamic Memory Allocation
			fscanf(ptr,"%[^!]",buffer);
			close(ptr);
			puts(buffer);
		}
	else
		fprintf(stderr,"Couldn't open the file\n");
	}
}
char submenu()
{
	puts("1-NAME");
	puts("2-ADRESS");
	puts("3-PHONE NUMBER");
	puts("4-GENDER");
	puts("5-BIRTHDAY");
	puts("6-CITY OF BIRTH");
	puts("7-EDIT COURSE INFO");
	puts("8-EDIT GPA");
	fflush(stdin);
	printf("Please enter your choice (1-2-3-4-5-6-7-8): ");
	return getchar();
}
void edit (student *s1)
{
	int id;
	int done=0;
	if (count_s!=0)  // check if we have a student 
	{
		printf("ENTER ID OF STUDENT YOU WANT TO EDIT: ");
		scanf("%d",&id);
		for (j=0;j<count_s;j++)
		{
			if (s1[j].ID==id)
			break;
		}
		if (j!=count_s)
		{
			done=1;   // valid id was found 
			fflush(stdin);
			switch (submenu())
			{
				case '1':
					printf("Enter new name: ");
					gets(s1[j].s_personal.name);
					fflush(stdin);
					break;
				case '2':
					printf("Enter new address: ");  
					gets(s1[j].s_personal.address);
					fflush(stdin);
					break;
				case '3':
					printf("Enter new phone number: ");
					scanf("%d",&s1[j].s_personal.phone);
					getchar();
					break;
				case '4':
					printf("Enter new Gender (m) for male (f) for female: ");
					scanf("%c",&s1[j].s_personal.gender);
					fflush(stdin);
					break;
				case '5':
					printf("Enter new birthday, format(dd/mm/yyyy): ");
					scanf("%2d/%2d/%4d",&s1[j].s_personal.birthday.day,&s1[j].s_personal.birthday.month,&s1[j].s_personal.birthday.year);
					fflush(stdin);
					break;
				case '6':
					printf("Enter new city of birth: ");
					gets(s1[j].s_personal.city);
					fflush(stdin);
					break;
				case '7':
					puts("________Course Info________");
					printf("Enter new number of courses taken: ");
					scanf("%d",&s1[j].course_number);
					fflush(stdin);
					for (i=0;i<s1[j].course_number;i++)
					{
						printf("Enter course %d name: ",i+1);
						scanf("%[a-zA-Z]%d",s1[j].s_course[i].s_course.course_sub,&s1[j].s_course[i].s_course.course_num);
						fflush(stdin);
						printf("Semester taken (1) fall (2) spring (3)summer: ");
						scanf("%d",&s1[j].s_course[i].s_semester);
						printf("Year Taken: ");
						scanf("%4d",&s1[j].s_course[i].year);
						fflush(stdin);
						printf("%s%d recieved grade: ",s1[j].s_course[i].s_course.course_sub,s1[j].s_course[i].s_course.course_num);
						scanf("%s",s1[j].s_course[i].grade);
						fflush(stdin);
					}
					break;
				case '8':
					printf("Enter new GPA: ");
					scanf("%f",&s1[j].GPA);
					break;
			}
			system("cls");
			(done==1)? fprintf(stderr,"Process of editing done succeesful\n") : fprintf(stderr,"Error during editing please try again\n");	
		}	
	
		else 
			fprintf(stderr,"ID NOT FOUND IN THE DATABASE ENTER A VALID ID NUMBER\n");
	}
	else 
		fprintf(stderr,"Empty database enter some information first before you can edit.\n");
}
/*******************************END***************************************************/