#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//global variables
int user_size,admin_size,ch;
int flag[8]={0,0,0,1};
//0-phn 1-login_index 2-panel_choice 3-updatepass 4-logout 5-loginpage 6-newusr_updatedob 7-dob

//structures
typedef struct date_of_birth
{
    int day;
    int month;
    int year;
}dob;
typedef struct administrator
{
    int id;
    int paidleave;
    char password[20];
}admin;
typedef struct employee
{
    admin members;
    char user_name[20];
    dob date;
    char phone[11];
    float salary;
    float base_salary;
    int calen[31];
	int attendance_count;
}emp;

//structure variables
emp users[10]={{101,3},{102,3},{103,3},{104,3},{105,3},{106,3},{107,3},{108,3},{109,3},{110,3}};
admin admins[3]={{201},{202},{203}};

//user-defined functions
void removeNewline(char *string)
{
    string[strlen(string)-1]='\0';
}
int password_search(int choice, int index,char element[])
{
    return choice==1?!strcmp(users[index].members.password,element):!strcmp(admins[index].password,element);
}
int id_search(int choice,int target)
{
    int i;
    if (choice==1)
    {
        for (i = 0; i < user_size; i++)
        {
            if (target==users[i].members.id)
            {
                break;
            } 
        }
        return i<user_size?i:-1;
    }
    else
    {
        for (i = 0; i < admin_size; i++)
        {
            if (target==admins[i].id)
            {
                break;
            } 
        }
        return i<admin_size?i:-1;
    }
}
int valid_dob(int day,int month, int year)
{
    if (year<1940 || year>2021)
    {
        return 0;
    }
    if (month<1 || month>12)
    {
        return 0;
    }
    if (month==2)
    {
        if (year%4==0)
        {
            if (day<0 || day>29)
            {
                return 0;
            }
        }
        else
        {
            if (day<0 || day>28)
            {
                return 0;
            }
        }    
    }
    else if (month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
    {
        if (day<0 || day>31)
        {
            return 0;
        }
        
    }
    else
    {
        if (day<0 || day>30)
        {
            return 0;
        }
    }
    return 1;
}
void valid_phn(int index)
{
    unsigned long long ph;
    do
    {
        printf("Phone: ");
        scanf("%llu",&ph);
        snprintf(users[index].phone,11,"%llu",ph);
        flag[0]=0;
        for (int i = 0; i < user_size; i++)
        {
            if (i!=index && strcmp(users[index].phone,users[i].phone)==0)
            {
                flag[0]=1;
                break;
            }
        }
    } while (ph<=1000000000 || ph>=9999999999 || flag[0]);
}
int login(int choice)
{
    int count=3,id,crt_id,crt_pass;
    char pass[20];
    do
    {
        printf("\nEmployee ID: ");
        scanf("%d",&id);fflush(stdin);
        printf("Password: ");
        fgets(pass,20,stdin);//fflush(stdin);
        removeNewline(pass);
        printf("%s",pass);
        count-=1;
        crt_id=id_search(choice,id);
        printf("%d",crt_id);
        if (crt_id>=0)
        
        {
        	printf("%s",users[crt_id].members.password);
            crt_pass=password_search(choice,crt_id,pass);
            printf("%d",crt_pass);
            FILE *fp2;
            fp2=fopen("calen.txt","rb");
    		fread(users, sizeof(users),2,fp2);
            fclose(fp2);
            if(choice==1 && crt_pass)
            {
            	for(int i=0;i<31;i++)
            	{
            		if(users[crt_id].calen[i]==0)
            		{
            		    users[crt_id].calen[i]=1;
            		    break;
					}
				}
            	++users[crt_id].attendance_count;
            	if(users[crt_id].base_salary==0)
            	{
                    users[crt_id].base_salary=2000;
                }
				users[crt_id].salary=3*(users[crt_id].base_salary)+(users[crt_id].attendance_count*users[crt_id].base_salary);
            	FILE *fp3;
            	fp3=fopen("calen.txt","wb");
            	fwrite(users,sizeof(users),2, fp3);
            	fclose(fp3);
			}
            if (!crt_pass)
            {
                printf("!--Incorrect Password. You have %d try(s) left--!",count);
            }
        }
        else
        {
            printf("!--Invalid ID. You have %d try(s) left--!",count);
        }
        
    } while (count>0 && (crt_id<0 || !crt_pass));
    return crt_id!=-1 && crt_pass?crt_id:-1;
}
int update_password(int index) //userpanel
{
    char pass[20],new_pass[20];
    int crt_pass,result=1;
    do
    {
        printf("Enter Current Password: ");
        fgets(pass,20,stdin);//fflush(stdin);
        removeNewline(pass);
        crt_pass=password_search(1,index,pass);
        if (!crt_pass)
        {
            printf("!--Incorrect password. Try again--!\n");
            printf("Forgot Password? (0/1): ");
            scanf("%d",&result);fflush(stdin);
            if (result)
            {
                printf("Verify Employee ID: ");
                scanf("%d",&result);fflush(stdin);
                if (result==users[index].members.id)
                {
                    printf("Password Hint: asdf--%s--fdsa\n",users[index].members.password);
                }
                else
                {
                    result=0;
                    printf("!--Attempt Suspicious. Contact Admin--!");
                    break;
                }
            }
        }
    } while (!crt_pass);
    if (result)
    {
        do
        {
            printf("Enter New Password: ");
            fgets(new_pass,20,stdin);//fflush(stdin);
            removeNewline(new_pass);
            printf("Confrim New Password: ");
            fgets(pass,20,stdin);//fflush(stdin);
            removeNewline(pass);
            result=!strcmp(new_pass,pass);
            if (!result)
            {
                printf("!--Passwords don't match! Try again--!\n");
            }
        } while (!result);
        strcpy(users[index].members.password,new_pass);
    }
    return result;
}
void new_user() //adminpanel
{
    if (user_size<10)
    {
        printf("User's Employee ID will be %d.\n",users[user_size].members.id);
        printf("Enter Name of User %d: ",users[user_size].members.id);
        fgets(users[user_size].user_name,20,stdin);//fflush(stdin);
        removeNewline(users[user_size].user_name);
        printf("Password: ");
        fgets(users[user_size].members.password,20,stdin);//fflush(stdin);
        removeNewline(users[user_size].members.password);
        do
    	{
    		printf("Enter the date of birth in the format DD/MM/YYYY\t\n");
    		scanf("%d/%d/%d",&users[user_size].date.day,&users[user_size].date.month,&users[user_size].date.year);
    		flag[6] =	valid_dob(users[user_size].date.day,users[user_size].date.month,users[user_size].date.year);
		}while(flag[6]==0);
        valid_phn(user_size);fflush(stdin);
    }
    user_size+=1;
    FILE *fp3;
    fp3=fopen("calen.txt","wb");
    fwrite(users,sizeof(users),1, fp3);
    fclose(fp3);
}
void viewevents() //userpanel
{
    FILE *fp;
    char ch;
    fp=fopen("event.txt", "r");
    if  ( fp == NULL) 
    {
        printf("File does not exist!!");
        exit(1);
    }
    while (1)
    {
        ch=fgetc(fp);
        if (ch==EOF)
        {
            break;
        }
        printf("%c",ch);
    }
    fclose(fp);
}
void viewsalary(int index) //userpanel
{
	
	printf("You have worked for %d days in this month.\n",users[index].attendance_count);
    printf("You current monthly salary is Rs. %f\n",users[index].salary);           	
}
void viewattendance(int index) //userpanel
{
	
	
	printf("You have worked for %d days in this month.\n",users[index].attendance_count);
                for(int i=0;i<7;i++)
                printf("%d  ",users[index].calen[i]);
                printf("\n");
                for(int i=7;i<14;i++)
                printf("%d  ",users[index].calen[i]);
                printf("\n");
                for(int i=14;i<21;i++)
                printf("%d  ",users[index].calen[i]);
                printf("\n");
                for(int i=21;i<28;i++)
                printf("%d  ",users[index].calen[i]);
                printf("\n");
                for(int i=28;i<31;i++)
                printf("%d  ",users[index].calen[i]);
                printf("\n");	
}
void userleavereq(int index) //userpanel
{	int days;
	int date;
	printf("Paid leave left: %d\n",users[index].members.paidleave);
	do
	{
	    printf("Enter the number of days you want to take leave");
		scanf(" %d",&days);
	}while(days<=0);
	if(days>users[index].members.paidleave)
	{
		
		printf("You can have a maximum of 3 paid leaves, but you only have %d paid leaves.\n",users[index].members.paidleave);
		printf("The rest of the %d leaves will be considered as non paid ones.\n",days-users[index].members.paidleave);
		printf("Enter the dates you'll be on leave:\n");
		for(int i=0;i<days;i++)
		{	
		    if(i<users[index].members.paidleave)
		    {
			    do{
				    scanf("%d",&date);
			    }while(date<=1 || days>31 );
			users[index].calen[date-1]=2;	
		}
		    else
		    {
			    do{
				    scanf("%d",&date);
			    }while(date<=1 || days>31 );
			    users[index].calen[date-1]=3;
		    }
		}
	}
	else
	{
		users[index].members.paidleave-=days;
		printf("Enter the dates:\n");
		for(int i=0;i<days;i++)
		{
			
			do{
				scanf("%d",&date);
				
			}while(date<=1 || days>31 );
			users[index].calen[date-1]=2;	
		
		}
		printf("Leave confirmed!\nYou have %d paid leaves left",users[index].members.paidleave);
		
	}
	FILE *fp3;
    fp3=fopen("calen.txt","wb");
    fwrite(users,sizeof(users),1, fp3);
    fclose(fp3);	
}
void updatesalary(int index) //adminpanel
{
 int choice;
 do
 {
 	printf("The current salary of user %d is Rs %0.2f\n",index+1,users[index].salary);
	printf("\n1. Change current salary : i.e(%0.2f)\n2. Change base salary :\nEnter your choice\n",users[index].salary);
 	scanf("%d",&choice);
 }while(choice!=1 && choice!=2);
 
  if(choice==1)
 {
     printf("Enter new value of salary:\n");
     scanf("%f",&users[index].salary);

 }
else 
{
    printf("Enter new value of base salary:\n");
     scanf("%f",&users[index].base_salary);
    
}
users[index].salary=3*(users[index].base_salary)+(users[index].attendance_count*users[index].base_salary);
FILE *fp3;
            	fp3=fopen("calen.txt","wb");
            	fwrite(users,sizeof(users),1, fp3);
            	fclose(fp3);
}
void adminattendance() //adminpanel
{
	for (int i = 0; i < user_size; i++)
    {
        printf("User %d has worked for %d day.\n",users[i].members.id,users[i].attendance_count);
    }
}
void manageEvents() //adminpanel
{
    FILE *fp,*fp1;
    char ch,cc;int x;
    do
    {
        printf("1. View\n2. Delete\n3. Add\nEnter your choice: ");
        scanf("%d",&x);
        if(x==1){
            if  (( fp=fopen("event.txt", "r")) == NULL) {
                printf("File does not exist!!");
                exit(1);
            } 
            while (1)
            {
                ch=fgetc(fp);
                if (ch==EOF)
                {
                    break;
                }
                printf("%c",ch);
            }
            fclose(fp);
        }
        else if(x==2)
        {
            FILE *fileptr1, *fileptr2;
            int delete_line, temp = 1;
            fileptr1 = fopen("event.txt", "r");
            ch = getc(fileptr1);
            while (ch != EOF)
            {
                printf("%c", ch);
                ch = getc(fileptr1);
            }
            rewind(fileptr1);
            printf(" \n Enter line number of the line to be deleted:");
            scanf("%d", &delete_line);
            fileptr2 = fopen("replica.c", "w");
            ch = 'A';
            while (ch != EOF)
            {
                ch = getc(fileptr1);
                if (temp != delete_line)
                {
                    putc(ch, fileptr2);
                }
                if (ch == '\n')
                {
                    temp++;
                }
            }
            fclose(fileptr1);
            fclose(fileptr2);
            remove("event.txt");
            rename("replica.c","event.txt");
            printf("\n The contents of file after being modified are as follows:\n");
            fileptr1 = fopen("event.txt", "r");
            ch = getc(fileptr1);
            while (ch != EOF)
            {
                printf("%c", ch);
                ch = getc(fileptr1);
            }
            fclose(fileptr1);
        }
        else if(x==3)
        { FILE * fptr;
            int i,n;
            char str[100];
            char str1;
  	
            fptr = fopen("event.txt", "a+"); 
            printf(" Input the number of lines to be written : ");
            scanf("%d", &n);
            printf(" The lines are : \n");  
            fflush(stdin);
            for(i = 0; i < n+1;i++)
            {
                fgets(str, sizeof str, stdin);
                fputs(str, fptr);
            }
            fclose (fptr);
	        fptr = fopen ("event.txt", "r+");  
	        printf("\n The content of the file %s is  :\n","event.txt");
	        str1 = fgetc(fptr);
	        while (str1 != EOF)
		    {
			    printf ("%c", str1);
			    str1 = fgetc(fptr);
		    }
            fclose (fptr);
        }
        else
    printf("Invalid Option!");
    printf("Do u want to manage events again?");
    scanf("%c",&cc);
    } while (cc=='y'||cc=='Y');
}
void view_personal_details() //adminpanel
{
    for (int i = 0; i < user_size; i++)
    {
        printf("\n***USER %d***\n",users[i].members.id);
        printf("Name: %s\n",users[i].user_name);
        printf("DOB: %d/%d/%d\n",users[i].date.day,users[i].date.month,users[i].date.year);
        printf("Phone: %s\n",users[i].phone);
    }  
}
void update_personal_details(int index) //userpanel
{
    int choice;
    printf("Which of the following would you like to update?\n1. Name\n2. Date of birth\n3. Phone \n");
    do
    {
        printf("Enter your choice: ");
        scanf("%d",&choice);
    } while (choice!=1 && choice!=2  && choice!=3);
    fflush(stdin);
    switch (choice)
    {
    case 1:
        printf("Enter Name: ");
        fgets(users[index].user_name,20,stdin);
		//fflush(stdin);
        removeNewline(users[index].user_name);
        printf("Name updated successfully!\n");
        break;
    case 2:
        do
    	{
    		printf("Enter DOB (DD/MM/YYYY): ");
    		scanf("%d/%d/%d",&users[index].date.day,&users[index].date.month,&users[index].date.year);
    		flag[6] =	valid_dob(users[index].date.day,users[index].date.month,users[index].date.year);
		}while(flag[6]==0);
        printf("DOB updated successfully!\n");
        break;
    case 3:
        valid_phn(index);
        printf("Phone number updated successfully!\n");
        break;
    default:
        break;
    }
    FILE *fp3;
    fp3=fopen("calen.txt","wb");
    fwrite(users,sizeof(users),1, fp3);
    fclose(fp3);
}
int main()
{
	
    do
    {
        printf("Enter the number of Users: ");
        scanf("%d",&user_size);
    } while (user_size<1 || user_size>10);
    do
    {
        printf("Enter the number of Admins: ");
        scanf("%d",&admin_size);
    } while (admin_size<1 || admin_size>3);fflush(stdin);
    
    //user data
    printf("\n*****USER DETAILS*****\n");
    for (int i = 0; i < user_size; i++)
    {
        printf("Enter Name of User %d: ",users[i].members.id);
        fgets(users[i].user_name,20,stdin);fflush(stdin);
        removeNewline(users[i].user_name);
        printf("Password: ");
        fgets(users[i].members.password,20,stdin);fflush(stdin);
        removeNewline(users[i].members.password);
        printf("%s",users[i].members.password);
        do
    	{
    		printf("Enter the date of birth (DD/MM/YYY): ");
    		scanf("%d/%d/%d",&users[i].date.day,&users[i].date.month,&users[i].date.year);
    		flag[7] =	valid_dob(users[i].date.day,users[i].date.month,users[i].date.year);
		}while(flag[7]==0);
        valid_phn(i);fflush(stdin);
    }
    //admin data
    printf("\n*****ADMIN DETAILS*****\n");
    for (int i=0;i<admin_size;i++)
    {
        printf("Enter Password for Admin %d: ",admins[i].id);
        fgets(admins[i].password,20,stdin);//fflush(stdin);
        removeNewline(admins[i].password);
    }
    do
    {
        //login
        printf("\n*****LOGIN*****\n");
        do
        {
            printf("Select Employee Level:\n1.User\n2.Admin\n");
            scanf("%d",&ch);
        } while (ch!=1 && ch!=2);
        flag[1]=login(ch);
        if (flag[1]!=-1)
        {
            do
            {
                if (ch==1)//user-panel features
                {   
                    printf("\n*****USER PANEL FEATURES*****\n");
                    printf("What would you like to do?\n1. Update Password\n2. Manage Personal Details\n3. View Salary\n4. View Attendance\n5. Manage Leave\n6. View Events\n");
                    scanf("%d",&flag[2]);fflush(stdin);
                    switch (flag[2])
                    {
                    case 1:
                        printf("\n*****Update Password*****\n");
                        flag[3]=update_password(flag[1]);
                        break;
                    case 2:
                        printf("\n*****Personal Details*****\n");
                        update_personal_details(flag[1]);
                        break;
                    case 3:
                        printf("\n*****Salary Details*****\n");
                        viewsalary(flag[1]);
                        break;
                    case 4:
                        printf("\n*****Attendance*****\n");
                        viewattendance(flag[1]);
                        break;
                    case 5:
                        printf("\n*****Leave Management*****\n");
                        userleavereq(flag[1]);
                        break;
                    case 6:
                        printf("\nView Events\n");
                        viewevents();
                        break;
                    default:
                        printf("Invalid Choice!");
                        break;
                    }
                }
                else //admin-panel features
                {
                    printf("\n*****ADMIN PANEL FEATURES*****\n");
                    printf("What would you like to do?\n1. Add New User\n2. Manage User Personal Details\n5. Manage Events\n");
                    scanf("%d",&flag[2]);fflush(stdin);
                    switch (flag[2])
                    {
                    case 1:
                        printf("\n*****Add New User*****\n");
                        new_user();
                        break;
                    case 2:
                        printf("\n*****View User Personal Details*****\n");
                        view_personal_details();
                        break;
                    case 3:
                        printf("\n*****Manage Salary*****\n");
                        updatesalary(flag[1]);
                        break;
                    case 4:
                        printf("\n*****Manage Attendance*****\n");
                        adminattendance();
                        break;
                    case 5:
                        printf("\nManage Events\n");
                        manageEvents();
                        break;
                    default:
                        printf("Invalid Choice!");
                        break;
                    }
                }
                if (flag[3])
                {
                    printf("\nDo you want to logout? (1/0): ");
                    scanf("%d",&flag[4]);fflush(stdin);
                }
                else
                {
                    flag[3]=1;
                }
            } while (!flag[4] && flag[3]);   
        }
        else
        {
            printf("\nYou've exceeded 3 tries!");
        }
        printf("\nDo you want to go back to the Login page? (1/0): ");
        scanf("%d",&flag[5]);
    } while (flag[5]);

    return 0;
}
