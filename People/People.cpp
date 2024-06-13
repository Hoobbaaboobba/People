// People.cpp : main project file.


#include "stdafx.h" 
#include <clocale>
#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 
#include <string.h> 
#include <malloc.h> 

 
using namespace std; 
using namespace System; 
using namespace System::IO; 
 
#define ENTER 13 
#define ESC 27 
#define UP 72 
#define DOWN 80 
 
struct z { 
 char name[30];
 long salary; 
 char profession[20];
 char data[13];  
 int children; 
}; 
struct sp {
char fio[20];
char profession[20];
struct sp* pred;
struct sp* sled;
} *spisok;

int menu(int); 
void max(struct z*, int);   
void text_data(char *s,char *sd);
void age(struct z* people, int);
void listing(struct z*, int);
void alfalist(struct z*, int);
void vstavka(struct z*,char*, int);
void diagram(struct z*, int);
void hard(struct z*, int);



int main(array<System::String ^> ^args) 
{ 
	char dan[7][70]={ 
 "Кто из опрошенных зарабатывает больше всего в месяц            ",   
 "Кто самый молодой из опрошенных                                ",  
 "Список с зарплатой более N руб.                                ",  
 "Алфавитный список всех опрошенных                              ",  
 "Существует два разных человека с одинаковым количеством детей  ",  
 "Диаграмма. Количество детей у опрошенных                       ",  
 "Выход                                                          "    
}; 
char BlankLine[ ]="                                                                 "; 
int NC; 
 int i,n; 
 FILE *in; 
 struct z *people; 
 setlocale(LC_CTYPE,"Russian"); 
 Console::CursorVisible::set(false);
 Console::BufferHeight=Console::WindowHeight; 
 Console::BufferWidth=Console::WindowWidth; 
 if((in=fopen("People.dat","r"))==NULL) 
  { 
  printf("\nФайл People.dat не открыт !"); 
  _getch(); exit(1); 
 } 
 fscanf(in,"%d",&NC); 
 people=(struct z*)malloc(NC*sizeof(struct z)); 
 
 for(i=0;i<NC;i++) 
  fscanf(in,"%s%ld%s%s%d",people[i].name, 
   &people[i].salary, people[i].profession, people[i].data, 
   &people[i].children); 
 for(i=0;i<NC;i++) 
  printf("\n%-20s %10ld %+15s %+15s %5d", 
   people[i].name, 
   people[i].salary, people[i].profession, people[i].data, 
   people[i].children); 
 getch(); 
 Console::Clear(); 
while(1) 
  { 
  Console::ForegroundColor=ConsoleColor::Green; 
  Console::BackgroundColor=ConsoleColor::Black; 
  Console::Clear();
  Console::ForegroundColor=ConsoleColor::Black; 
  Console::BackgroundColor=ConsoleColor::Green; 
  Console::CursorLeft=10; 
  Console::CursorTop=4; 
  printf(BlankLine); 
  for(i=0;i<7;i++) 
  { 
  Console::CursorLeft=10; 
  Console::CursorTop=i+5; 
  printf(" %s ",dan[i]); 
  } 
  Console::CursorLeft=10; 
  Console::CursorTop=12; 
  printf(BlankLine); 
  n = menu(7); 
  switch(n) { 
    case 1: max(people, NC); break; 
    case 2: age(people, NC); break; 
    case 3: listing(people, NC); break; 
    case 4: alfalist(people, NC); break; 
    case 5: hard(people, NC); break; 
    case 6: diagram(people, NC); break; 
    case 7: exit(0); 
    } 
  } 
  return 0; 
   
} 
int menu(int n) 
{ 
	char dan[7][70]={ 
 "Кто из опрошенных зарабатывает больше всего в месяц            ",   
 "Кто самый молодой из опрошенных                                ",  
 "Список с зарплатой более N руб.                                ",  
 "Алфавитный список всех опрошенных                              ",  
 "Существует два разных человека с одинаковым количеством детей  ",  
 "Диаграмма. Количество детей у опрошенных                       ",  
 "Выход                                                          "    
}; 
char BlankLine[ ]="                                                                 "; 
int y1=0,y2=n-1; 
char c=1; 
while (c!=ESC) 
{ 
  switch(c) { 
   case DOWN: y2=y1; y1++; break; 
   case UP: y2=y1; y1--; break; 
   case ENTER: return y1+1; 
   } 
  if(y1>n-1){y2=n-1;y1=0;} 
  if(y1<0) {y2=0;y1=n-1;} 
  Console::ForegroundColor=ConsoleColor::Blue; 
  Console::BackgroundColor=ConsoleColor::White; 
  Console::CursorLeft=11; 
  Console::CursorTop=y1+5; 
  printf("%s",dan[y1]); 
  Console::ForegroundColor=ConsoleColor::Black; 
  Console::BackgroundColor=ConsoleColor::Green; 
  Console::CursorLeft=11; 
  Console::CursorTop=y2+5; 
  printf("%s",dan[y2]); 
  c=getch(); 
  }  
exit(0); 
} 
void max(struct z* people, int NC)
{
int i=0; struct z best;
strcpy(best.name,people[0].name);
best.salary=people[0].salary;
for(i=1;i<NC;i++)
if (people[i].salary>best.salary)
{
strcpy(best.name,people[i].name);
best.salary=people[i].salary;
}
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::Black;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Больше всего %d руб.",best.salary);
Console::CursorLeft=10;
Console::CursorTop=16;
printf("Зарабатывает участник опроса %s",best.name);
getch();
}
void text_data(char *s,char *sd)
{
char s0[3],month[12][9]={
"января","февраля","марта","апреля","мая","июня",
"июля","августа","сентября","октября","ноября","декабря"};
strcpy(s,sd+8);
strcat(s," ");
strncpy(s0,sd+5,2); s0[2]=0;
strcat(s,month[ atoi(s0)-1]);
strcat(s," ");
strncat(s,sd,4);
return;
}
void age(struct z* people, int NC)
{
int i;
char s[17];
struct z* best=people;
for(i=1;i<NC;i++)
if (strcmp(people[i].data,best->data)>0)
best=&people[i];
text_data(s,best->data);
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::Black;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Участник %s, является самым молодым",best->name);
Console::CursorLeft=10;
Console::CursorTop=16;
printf("С датой рождения %s года",s);
getch();
}
void listing(struct z* people, int NC)
{
int i, salary_input;
struct z* nt;
Console::ForegroundColor=ConsoleColor::White;
Console::BackgroundColor=ConsoleColor::Black;
Console::Clear();
printf("Введите зарплату в рублях: ");
scanf("%d",&salary_input); 
printf("\n\r  Список опрошенных с зарплатой более %ld руб.", salary_input);
printf("\n\r=====================================================\n\r");
for(i=0,nt=people;i<NC;nt++,i++)
	if (nt->salary>salary_input)
	printf("\n\r %-20s %d руб.",nt->name,nt->salary);
getch();
Console::Clear();
}

void vstavka(struct z* people, char* fio, int NC) {
    int i;
    struct sp *nov, *nt, *z = 0;
    for (nt = spisok; nt != 0 && strcmp(nt->fio, fio) < 0; z = nt, nt = nt->sled);
    if (nt && strcmp(nt->fio, fio) == 0) return;
    nov = (struct sp*)malloc(sizeof(struct sp));
    strcpy(nov->fio, fio);
	nov->pred=z;
    nov->sled = nt;
	for (i = 0; i < NC; i++) {
        if (strcmp(people[i].name, fio) == 0) {
            strcpy(nov->profession, people[i].profession);
            break;
        }
    }
    if (!z) spisok = nov;
    else z->sled = nov;
	if(nt) nt->pred=nov;
	nov->sled = nt;
	return;
}

void alfalist(struct z* people, int NC) {
    int i, n;
    struct sp* nt;
	struct sp* z;
    Console::ForegroundColor = ConsoleColor::White;
    Console::BackgroundColor = ConsoleColor::Black;
    Console::Clear();
    if (!spisok) {
        for (i = 0; i < NC; i++) {
            vstavka(people, people[i].name, NC);
        }
    }
    Console::Clear();
	printf("\n Алфавитный список опрошенных");
	printf("\t\t           Алфавитный список опрошенных в обратном порядке");
    printf("\n ===================================\t");
    printf("\t========================================================\n");
	for (nt = spisok; nt != 0; nt = nt->sled) {
        printf("\n %-20s %s", nt->fio, nt->profession);
    }
    for (nt = spisok, z=0; nt != 0; z=nt, nt = nt->sled);
    for(nt=z; nt!=0; nt=nt->pred)
    {	
		Console::CursorLeft=48;
		Console::CursorTop=4+n;
        printf(" %-20s %s", nt->fio, nt->profession);
		n+=1;
    }
    getch();
}

void hard(struct z *people, int NC){
    int i, j;
    for(i = 0; i < NC; i++){
        for(j = i + 1; j < NC; j++){
            if(people[i].children == people[j].children){
                Console::ForegroundColor = ConsoleColor::White;
                Console::BackgroundColor = ConsoleColor::Black;
                Console::CursorLeft = 10;
                Console::CursorTop = 15;
                printf("Существует два разных человека с одинаковым количеством детей");
                Console::CursorLeft = 10;
                Console::CursorTop = 16;
                printf("%s с %ld детей и %s с %ld детей", people[i].name, people[i].children, people[j].name, people[j].children);
                getch();
                return; // Прекращаем выполнение функции после первого совпадения
            }
        }
    }

    Console::ForegroundColor = ConsoleColor::White;
    Console::BackgroundColor = ConsoleColor::Black;
    Console::CursorLeft = 10;
    Console::CursorTop = 15;
    printf("В файле Peoples.dat не найдено двух разных людей с одинаковым количеством детей");
    getch();
}
void diagram(struct z *people, int NC)
{
    int k = 1, l = 0, len = 0, i, flag, NColor = 0;
	System::ConsoleColor Color;

    Console::ForegroundColor = ConsoleColor::White;
    Console::BackgroundColor = ConsoleColor::Black;
    Console::Clear();
	printf("Диаграмма по количеству детей у участников опроса");
label:
    for (i = 0, l = 0; i < NC; i++) {
        if (people[i].children == k-1) {
            l++;}}
    double percent = (100.0 / NC) * l;
    int space = percent / 2;
	Console::BackgroundColor = ConsoleColor::Black;
    printf("\n \n \r детей %d (%.2lf%%)", k-1, percent);
    Console::BackgroundColor=++Color; NColor++;
    Console::CursorTop = 2*k;
	Console::CursorLeft = 20;
    for (len = 0; len < space; len++){printf(" ");}
	if (k == 6) {
		flag = 1;
	}
    if (flag == 0) {
        k++;
        goto label;
    }
	getch();
}