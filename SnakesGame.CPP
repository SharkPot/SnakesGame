#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<iostream.h>


struct snake
{
char value;
int x;
int y;
struct snake* next;
};
struct snake *head=NULL;

void writechar(char, int, int , int);
void writestring(char *, int, int, int);
void writestring(char screen[][30], int attr, int r, int c)
{
int i,j;
for(i=8;i<r+8;i++)
{
 for(j=0;j<c;j++)
   {
	 if(screen[i-8][j]=='o'|| screen[i-8][j]=='O'){
	 writechar(screen[i-8][j],RED,i,j);}
	 else if(screen[i-8][j]=='#'){
	 writechar(screen[i-8][j],404,i,j);}
	 else{
	 writechar(screen[i-8][j],attr,i,j);}
}
}
}

void writechar(char ch, int attr, int r, int c)
{
   char far *vdumem = (char far *)0XB8000000;
   char far *v;
   v = vdumem + r*160 + c*2;
   *v = ch;
   v++;
   *v=attr;
   }

struct snake* generatesnake(int numofnode)
{
int k,i=5,j=5;
struct snake *new_node,*temp;
for(k=0;k<numofnode;k++)
	{
	new_node=(struct snake*)malloc(sizeof(struct snake));
	if(new_node==NULL)
	return NULL;
	new_node->x=i;
	new_node->y=j;
	j++;
	new_node->value='o';
	if(head==NULL)
		{
		head=new_node;
		new_node->value='O';
		}
	else
		{
		temp=head;
		while(temp->next!=NULL)
			{temp=temp->next;}
		temp->next=new_node;
		new_node->next=NULL;
		}
	}
return head;
}
void generatefoodloc(int maxx,int maxy,int *i,int *j)
{
if(*i+5<maxx)
{*i=*i+5;}
else
{*i=*i+5-maxx;}
if(*j+5<maxy)
{*j=*j+5;}
else
{*j=*j+5-maxy;}
}
void updatefoodloc(char screen[][30],int i,int j)
{screen[i][j]='@';}
void updatesnakeloc(char screen[][30],struct snake* snakehead)
{
struct snake* temp;
temp=snakehead;
while(temp!=NULL)
	{
	screen[temp->x][temp->y]=temp->value;
	temp=temp->next;
	}
}
/*void printscreen(char screen[][10],int maxx,int maxy)
{
int i,j;

for(i=0;i<maxx;i++)
	{
	for(j=0;j<maxy;j++)
		{
		printf("%c ",screen[i][j]);
		}
		printf("\n");
		}

	}*/
void initializescreen(char screen[][30],int maxx,int maxy)
{
int i,j;
for(i=0;i<maxx;i++)
{
	for(j=0;j<maxy;j++)
	{
	screen[i][j]='_';
	}
}
}
struct snake* movement(struct snake* snakehead,int maxx,int maxy)
{
static char move='a';
if(kbhit()){
move=getch(); }delay(200);
struct snake* ptr;
ptr=snakehead;
int tempx,tempy,temp;
tempx=ptr->x;
tempy=ptr->y;
while(ptr!=NULL)
	{
	temp=ptr->x;
	ptr->x=tempx;
	tempx=temp;
	temp=ptr->y;
	ptr->y=tempy;
	tempy=temp;
	ptr=ptr->next;
	}


switch(move)
	{
	case 'w':
	snakehead->x=snakehead->x-1;
	if(snakehead->x<0)
	snakehead->x=maxx-1;
	break;
	case 'a':
	snakehead->y=snakehead->y-1;
	if(snakehead->y<0)
	snakehead->y=maxy-1;
	break;
	case 's':
	snakehead->x=snakehead->x+1;
	if(snakehead->x>maxx-1)
	snakehead->x=0;
	break;
	case 'd':
	snakehead->y=snakehead->y+1;
	if(snakehead->y>maxy-1)
	snakehead->y=0;
	break;
	default:
	exit(1);
	break;
	}
return snakehead;
}
int checkfood(int *i,int *j,struct snake* snakehead)
{
if(snakehead->x==*i && snakehead->y==*j){
return 1;}

else return 0;
}

int checkloss(struct snake* snakehead)
{
	struct snake* ptr=snakehead;
	ptr=ptr->next;
	while(ptr!=NULL)
	{
		if(snakehead->x==ptr->x && snakehead->y==ptr->y){
		return 1;
		break;}
		else{
		ptr=ptr->next;}
	}
	return 0;
}

void increasesnake(struct snake* snakehead)
{
	int prevx,prevy;
struct snake *ptr;
ptr=snakehead;
while(ptr->next!=NULL)
	{
	prevx=ptr->x;
	prevy=ptr->y;
	ptr=ptr->next;
	}
struct snake *new_node;
new_node=(struct snake*)malloc(sizeof(struct snake));
ptr->next=new_node;
new_node->x=prevx;
new_node->y=prevy;
new_node->next=NULL;
new_node->value='#';
}


int main()
{


char screen[10][30];
int i,j,maxx=10,maxy=30,c=1,n=3;
i=1;
j=1;
//char message[100]="!";
clrscr();
initializescreen(screen,maxx,maxy);
struct snake* snakehead=generatesnake(n);
generatefoodloc(maxx,maxy,&i,&j);
updatefoodloc(screen,i,j);
updatesnakeloc(screen,snakehead);
 writestring(screen,1,maxx,maxy);
printf("enter 1 for continue 0 to end \n");
scanf("%d",&c);
if(c==0){
exit(1);
}else{
while(1)
{
snakehead=movement(snakehead,maxx,maxy);
initializescreen(screen,maxx,maxy);
if(checkloss(snakehead))
{
	cout<<"Gameover\n";
	break;
}
if(checkfood(&i,&j,snakehead))
{
generatefoodloc(maxx,maxy,&i,&j);
increasesnake(snakehead);
}
updatefoodloc(screen,i,j);
updatesnakeloc(screen,snakehead);
clrscr();
 writestring(screen,1,maxx,maxy);
}}
getch();

return 0;
}
