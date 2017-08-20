#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>

struct student
{
  int roll_no;
  char name[80];
  float fees;
  char DOB[80];
};

typedef struct student stud;

//student stud[15];

void create(){
  printf("creating file\n");
  //int id;
  FILE *fp;
  //stud *temp=(stud*)malloc(sizeof(struct student));
  // if(temp==NULL)
  // {
  //   printf("MEMORY NOT ALLOCATED \n");
  //   exit(0);
  // }
  fp = fopen("student.dat","ab+");
  if(fp==NULL)
  {
    printf("File Creation Failed!");
    exit(0);
  }
}


void display(){
  printf("displaying file\n");
  int count=0;
  stud s;
  FILE *fp;
  fp=fopen("student.dat", "rb");
  if(fp==NULL)
  {
    printf("\n\tFile does not exist!!!\nTRY AGAIN");
    exit(0);
  }
  printf("\n---------------------------------------------------------------------------------------------------------------\n");
  printf("%-40s %-35s %-25s %-15s\n","ROLL_NO","NAME","FEES","DOB");
  printf("---------------------------------------------------------------------------------------------------------------\n");
  while((fread(&s, sizeof(s), 1, fp))==1)
  { 
  count++;
  printf("%-40d %-35s %-25f %-15s\n",s.roll_no,s.name,s.fees,s.DOB);
  }
  printf("Total number of records present are : %d", count);
  fclose(fp);
}

void append(){
  printf("appending to file\n");
  int roll_no;
  FILE *fp;
  stud *temp=(stud*)malloc(sizeof(struct student));
  
  if(temp==NULL)
  {
    printf("MEMORY NOT ALLOCATED \n");
    exit(0);
  }
   
  fp = fopen("student.dat","ab+");
  
  if(fp==NULL)
  {
    printf("File Creation Failed!");
    exit(0);
  }
 
  printf("\n*****ADDING DATA*****\n");
  printf("Enter student roll no  : ");
  scanf("%d",&roll_no);
 while((fread(temp,sizeof(stud),1,fp))==1)
 {
    if(roll_no==temp->roll_no)
	  {
	    printf("ALREADY EXISTS\n");
          fclose(fp);
          return;
          
    }
 }

  temp->roll_no=roll_no;

printf("\nEnter student name : ");
scanf("%s",temp->name);

printf("\nEnter fees : ");
scanf("%f",&temp->fees);

printf("\nEnter DOB : ");
scanf("%s",temp->DOB);

fwrite(temp, sizeof(stud), 1, fp);

fclose(fp);
printf("Record Added---\n");

}

void delete_record(){
  printf("deleting record file\n");
  stud s;
  int roll_no;
  char ch;
  FILE *fp,*ft;
  fp=fopen("student.dat", "rb");
  ft=fopen("Temp.dat", "wb");
  printf("Enter the roll number to delete : ");
  scanf("%d", &roll_no);
  while((fread(&s, sizeof(s), 1, fp))==1)
  {
    if(s.roll_no==roll_no)
    {
      printf("\nstudent roll_no : %d", s.roll_no);
      printf("\nstudent name : %s",s.name);
      printf("\nstudent fees : %f",s.fees);

      printf("\n");
      printf("Do you want to delete this record : ? (Y/N)");
      getchar();
      scanf("%c", &ch);
    }
  }
  if(ch=='y'||ch=='Y')
  {
    rewind(fp);
    while((fread(&s, sizeof(s), 1, fp))==1)
    {
      if(s.roll_no!=roll_no)
      {
        fwrite(&s, sizeof(s), 1, ft);
      }
    }
    printf("Deleted\n");
    remove("student.dat");
    rename("Temp.dat", "student.dat");
  }
  else{
    printf("No Record was deleted");
    remove("Temp.dat");
  }
  fclose(fp);
  fclose(ft);
  
}

void delete_file(){
  printf("deleting file\n");
  FILE *fp;
  fp=fopen("student.dat","rb");
  if(!fp){
    printf("No such file\n");
  }
  else{
    remove("student.dat");
    printf("File deleted\n");
  }
  
}

void edit(){
  printf("editing file\n");
  int roll_no, count=0;
  char ch;
  stud s;
  FILE *fp;
  fp=fopen("student.dat", "rb+");
  printf("Enter the id of student to modify : ");
  scanf("%d", &roll_no);
  while((fread(&s, sizeof(s), 1, fp))==1)
  {
    count++;
    if(s.roll_no==roll_no)
    {
      printf("\nstudent roll no : %d", s.roll_no);
      printf("\nstudent name : %s",s.name);
      printf("\nstudent fees : %f",s.fees);
      printf("\nstudent DOB : %s",s.DOB);
      printf("\n");
      printf("Do you want to modify this record : ? (Y/N) ");
      fflush(stdin);
      scanf("%c", &ch);
      fseek(fp, ((count-1)*sizeof(s)), 0);
    }
    if(ch=='Y'|| ch=='y')
    {
      printf("Enter the new roll no : ");
      scanf("%d",&s.roll_no);
      printf("Enter the student Name : ");
      fflush(stdin);
      scanf("%s",s.name);
      printf("\nstudent fees :");
      scanf("%f",&s.fees);
      printf("\nstudent DOB :");
      scanf("%s",s.DOB);
      fwrite(&s, sizeof(s), 1, fp);
      printf("Record Modified\n");
    }
    else
      printf("No modifications were made\n");
    fclose(fp);
  }
}

int main(){
  int ch;
  do{
    printf("\n\n\t MENU:\n\t--------------\n");
    printf("\n\t 1.Create\n\t 2.Display\n\t 3.Append\n\t4.DeleteRecord\n\t5.DeleteFile\n\t6.Edit\n\t7.Exit\n");
    printf("Enter your choice:");
    scanf("%d",&ch);
    switch(ch){
      case 1: create();
              break;
      case 2: display();
              break;
      case 3: append();
              break;
      case 4: delete_record();
              break;
      case 5: delete_file();
              break;
      case 6: edit();
              break;
      case 7: exit(0);
              break;
      default: printf("Wrong choice\n");
    }
  }while(ch!=7);
  return 0;
}