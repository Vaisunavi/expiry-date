#include<stdio.h>
#include <time.h>
#include<string.h>
#define MAX_YR  9999
#define MIN_YR  1900
#include<stdlib.h>
struct node {
	int data,id;
	char name[50];
	struct node *left, *right;//pointer variable
	int height;
};
typedef struct node TREENODE;
int max(int a, int b)
{
    return (a > b)? a : b;//ternary operator question?statement 1(if T executed): statement2(if F executed)
}
int height(TREENODE *temp)
{
    if (temp == NULL)
        return 0;
    return 1+max(height(temp->left), height(temp->right));
}
TREENODE* LLRotate(TREENODE* x)
{
    TREENODE* y = x->left;
    TREENODE* yr = y->right;
    y->right=x;
    x->left = yr;
    x->height = height(x);
    y->height = height(y);
    return y;
}
TREENODE* RRRotate(TREENODE* x)
{
    TREENODE* y = x->right;
    TREENODE* yl = y->left;
    y->left=x;
    x->right = yl;
    x->height = height(x);
    y->height = height(y);
    return y;
}
int getBalance(TREENODE *temp)
{
    if (temp == NULL)
        return 0;
    return height(temp->left) - height(temp->right);
}
TREENODE* newNode(int value,int location,char*product)
{
	TREENODE* temp = (TREENODE*)malloc(sizeof(TREENODE));
	temp->data = value;
	temp->id = location;
	strcpy(temp->name,product);
	temp->left = temp->right = NULL;
	temp->height=0;
	return temp;
}
TREENODE* minValueNode(TREENODE* temp)
{
    TREENODE* current = temp;
	while (current && current->left != NULL)
        current = current->left;
    return current;
}
void inorder(TREENODE* temp){
	if (temp != NULL) {
		inorder(temp->left);
		printf("%s",temp->name);
		printf("\t\t\t%d",temp->id);
		//printf("%d/%d/%d\t\t",temp->day2,temp->mon2,temp->year2);
		printf("\t\t\t\t%d\n", temp->data);
		inorder(temp->right);
	}
}
TREENODE* insert(TREENODE* temp, int val,int loc,char*pro){
	if (temp == NULL){
	TREENODE *ptr=malloc(sizeof(TREENODE));
	ptr->data=val;
	ptr->id=loc;
	strcpy(ptr->name,pro);
	ptr->left=ptr->right=NULL;
	ptr->height=0;
	temp=ptr;
	}
	else{
	if (temp->data>val)
		temp->left = insert(temp->left, val,loc,pro);
	else if (temp->data < val)
		temp->right = insert(temp->right, val,loc,pro);
	}
    temp->height = height(temp);
    int balance = getBalance(temp);
    if (balance > 1 && val < temp->left->data)
        return LLRotate(temp);
    if (balance < -1 && val > temp->right->data)
        return RRRotate(temp);
    if (balance > 1 && val > temp->left->data)
    {
        temp->left =  RRRotate(temp->left);
        return LLRotate(temp);
    }
    if (balance < -1 && val < temp->right->data)
    {
        temp->right = LLRotate(temp->right);
        return RRRotate(temp);
    }	
	return temp;
}
int valid_date(int date, int mon, int year);
int valid_date(int day, int mon, int year)    
{
    int is_valid = 1, is_leap = 0;
    if (year >= 1800 && year <= 9999) 
    {        //  check whether year is a leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
        {
            is_leap = 1;
        }        // check whether mon is between 1 and 12
        if(mon >= 1 && mon <= 12)
        {            // check for days in feb
            if (mon == 2)
            {
                if (is_leap && day == 29) 
                {
                    is_valid = 1;
                }
                else if(day > 28) 
                {
                    is_valid = 0;
                }
            }            // check for days in April, June, September and November
            else if (mon == 4 || mon == 6 || mon == 9 || mon == 11) 
            {
                if (day > 30)
                {
                    is_valid = 0;
                }
            }
            // check for days in rest of the months 
            // i.e Jan, Mar, May, July, Aug, Oct, Dec
            else if(day > 31)
            {            
                is_valid = 0;
            }        
        }
        else
        {
            is_valid = 0;
        }
    }
    else
    {
        is_valid = 0;
    }
    return is_valid;
}
//structure to store date
typedef struct
{
    int yyyy;
    int mm;
    int dd;
} Date;
// Function to check leap year.
//Function returns 1 if leap year
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}// returns 1 if given date is valid.
int isValidDate(Date *validDate)
{//check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;//Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }//handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
//return 1 if successfully enter the expiry date
int enterExpiryDate(Date *getDate)
{
    printf("Enter the expiry date(DD/MM/YYY): ");
    scanf("%d/%d/%d",&getDate->dd,&getDate->mm,&getDate->yyyy);
    return isValidDate(getDate);
}//function to validate product expiry date
int checkExpiryDate(const Date* expiryDate, const Date * currentDate)
{
    if (NULL==expiryDate||NULL==currentDate)
    {
        return 0;
    }
    else
    {
        if (expiryDate->yyyy > currentDate->yyyy)
        {
            return 0;
        }
        else if (expiryDate->yyyy < currentDate->yyyy)
        {
            return 1;
        }
        else
        {
            if (expiryDate->mm > currentDate->mm)
            {
                return 0;
            }
            else if (expiryDate->mm < currentDate->mm)
            {
                return 1;
            }
            else
            {
                return (expiryDate->dd >= currentDate->dd)? 0 : 1;
            }
        }
    }
}
int main(){
	int ch;
	char name[20];
	time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    struct node* root = NULL;
	int data,id,day2,mon2,year2;
	FILE *proj;
	FILE *readfile;
    current_time = localtime(&s);
   while(1){
	printf("\n\t\tExpiry date remainder system");
	printf("\nPlease make a selection from the menu!\n");
	printf("1.Add an item\n2.Expiry remainder\n3.Product expires in?\n4.Check expiry date\n5.View History\n6.Exit\n");
	printf("enter your choice: ");
		scanf("%d",&ch);
		if(ch==1)
		{
		int day1=current_time->tm_mday, mon1=current_time->tm_mon+1, year1=current_time->tm_year+1900,d,m,y;
      int day_diff, mon_diff, year_diff,woah;   
	 time_t t;   // not a primitive datatype
    time(&t);
    ctime(&t);
  printf("enter the product id number: ");
    scanf("%d",&id);
    printf("enter the product name: ");
    scanf("%s",&name);
    printf("Enter the expiry date (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &day2, &mon2, &year2);  
	 if(!valid_date(day2, mon2, year2))
    {
        printf("Second date is invalid.\n");
        exit(0);
    }       
    if(day2 < day1)
    {      
        // borrow days from february
        if (mon2 == 3)
        {
            //  check whether year is a leap year
            if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0)) 
            {
                day2 += 29;
            }
            else
            {
                day2 += 28;
            }                        
        }        // borrow days from April or June or September or November
        else if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12) 
        {
           day2 += 30; 
        }        // borrow days from Jan or Mar or May or July or Aug or Oct or Dec
        else
        {
           day2 += 31;
        }
        mon2 = mon2 - 1;
    }
    if (mon2 < mon1)
    {
        mon2 += 12;
        year2 -= 1;
    }       
    day_diff = day2 - day1;
    mon_diff = mon2 - mon1;
    m=mon_diff*30;
    year_diff = year2 - year1;
    y=year_diff*365;
		woah=day_diff+m+y;
		if (woah<0){
			data=0;
		}
		else{
			data =woah;
		}
		proj=fopen("carpediem.txt","a+");
    fprintf(proj,"Product id:%d\n",id);
    fprintf(proj,"Product name:%s\n",name);
    fprintf(proj,"Expiry date:%d/%d/%d\n",day2,mon2,year2);
    fprintf(proj,"Validity of product:%d days\n",data);
    fprintf(proj,"%s\n", ctime(&t));
	fprintf(proj,"---------------------------------------------------\n");
	fclose(proj);
		root=insert(root,data,id,name);
		}
		if(ch==2){
			if(root==NULL){
			printf("Nothing to iterate\n");
			continue;
		}
		printf("Product Name\t\tProduct Number\t\tValid for no.of days\n");
		inorder(root);
		}
		if(ch==3){
			int day1=current_time->tm_mday, mon1=current_time->tm_mon+1, year1=current_time->tm_year+1900,
        day2, mon2, year2;
    int day_diff, mon_diff, year_diff;   
	 time_t t;   // not a primitive datatype
    time(&t);
    ctime(&t);
    printf("enter the product name: ");
    scanf("%s",&name);
    printf("Enter the expiry date (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &day2, &mon2, &year2);
    if(!valid_date(day2, mon2, year2))
    {
        printf("Second date is invalid.\n");
        exit(0);
    }    
    if(day2 < day1)
    {      
        // borrow days from february
        if (mon2 == 3)
        {            //  check whether year is a leap year
            if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0)) 
            {
                day2 += 29;
            }
            else
            {
                day2 += 28;
            }                        
        }        // borrow days from April or June or September or November
        else if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12) 
        {
           day2 += 30; 
        }        // borrow days from Jan or Mar or May or July or Aug or Oct or Dec
        else
        {
           day2 += 31;
        }
        mon2 = mon2 - 1;
    }
    if (mon2 < mon1)
    {
        mon2 += 12;
        year2 -= 1;
    }       
    day_diff = day2 - day1;
    mon_diff = mon2 - mon1;
    year_diff = year2 - year1;
    printf("The product expires in: %d years %02d months and %02d days\n", year_diff, mon_diff, day_diff);
    proj=fopen("carpediem.txt","a+");
    fprintf(proj,"Product name:%s\n",name);
    fprintf(proj,"Expiry date:%d/%d/%d\n",day2,mon2,year2);
    fprintf(proj,"The product expires in: %d years %02d months and %02d days\n", year_diff, mon_diff, day_diff);
	fprintf(proj,"%s\n", ctime(&t));
	fprintf(proj,"---------------------------------------------------\n");
	fclose(proj);
			}
		if (ch==4){
			time_t rawtime;
    struct tm * timeinfo;
    //variable to store expiry date
    Date expiryDate = {0};
    //variable to store expiry date
    Date currentDate = {0};
    int status = 0;
    int button = 0;
    status = enterExpiryDate(&expiryDate);
    if(status !=1)
    {
        printf("Please enter a valid date!\n");
        return 0;
    }
    //Get current time
    time(&rawtime);
    timeinfo = localtime(&rawtime);//compose current date
    // years since 1900
    currentDate.yyyy = timeinfo->tm_year+1900; // months since January - [0, 11]
    currentDate.mm = timeinfo->tm_mon+1;// day of the month - [1,28 or 29 or 30 or 31]
    currentDate.dd = timeinfo->tm_mday;
    printf("Enter 0 to check product expiry date  = ");
    scanf("%d",&button);
    if((button != 0))
    {
        printf("You have pressed invalid button!\n");
        return 0;
    }
    //check expiry date
    status = checkExpiryDate(&expiryDate,&currentDate);
    if(status !=0)
    {
        printf("Product has been expired!\n");
    }
    else
    {
        printf("You can use the product!\n");
    }
		}
		if(ch==5){
			int c;
			readfile = fopen("carpediem.txt", "r");
  printf("\n");
  if(readfile)
  {
    while ((c = getc(readfile)) != EOF)
    putchar(c);
    fclose(readfile);
  }
  else
  {
    printf("\nError: Unable to open the file for Reading.");
  }
		}
		if (ch==6){
			exit(0);
		}
	}
}
