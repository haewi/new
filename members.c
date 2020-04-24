#include "members.h"

T_Record* goods[MAX_ITEM]; // 상품정보데이터 (전역)
int _count = 0;

int i_is_available(){
    int i;
    for(i=0; i<MAX_ITEM; i++){
        if(goods[i]==NULL) return 1;
    }
    return 0;
}

int i_first_available(){
    int i;
    for(i=0; i<MAX_ITEM; i++){
        if(goods[i]==NULL){
                return i;
        }
    }
    return -1;
}

int i_count(){
    return _count;
}

void i_create(int nu, char* n, int st, int dt){
    int index = i_first_available();
    goods[index] = (T_Record*)malloc(sizeof(T_Record));
    T_Record* p = goods[index];
    p->no = nu;
    strcpy(p->name, n);
    p->stock = st;
    p->ex_date = dt;
    _count++;
}

void i_update(T_Record* p, int n, int st, int ed){
    p->no = n;
    p->stock = st;
    p->ex_date = ed;
}
void i_delete(T_Record* p){
    int i,j;
    for(i=0; i<_count; i++){
        if(goods[i]==p) {
            for(j=i; j<_count-1; j++) goods[i] = goods[j+1];
            _count--;
            goods[_count]=NULL; 
        }
    }
    free(p);
  }  


T_Record* i_search_by_name(char* n){
    int i;
    for(i=0; i<MAX_ITEM; i++){
        if(goods[i]!=NULL && strcmp(goods[i]->name, n)==0) return goods[i];
    }
    return NULL;
}

char* i_getname(T_Record* p){
        #ifdef DEBUG
                printf("[DEBUG] Its name is (%s) \n",p->name);
        #endif
    return p->name;
}

int i_getno(T_Record* p){
        #ifdef DEBUG
                printf("[DEBUG] Its no is (%d) \n",p->no);
        #endif
    return p->no;
}

int i_getstock(T_Record* p){
        #ifdef DEBUG
                printf("[DEBUG] Its number of stock is (%d) \n",p->stock);
        #endif
    return p->stock;
}

int i_getexdate(T_Record* p){
        #ifdef DEBUG
                printf("[DEBUG] Its expiration date is (%d) \n",p->ex_date);
        #endif
    return p->ex_date;
}

void i_init(){
        int i;
        for(i=0; i<MAX_ITEM; i++){
                if(goods[i]!=NULL) {
                        free(goods[i]);
                }
                goods[i] = NULL;
 }
        _count = 0;
        #ifdef DEBUG
                printf("[DEBUG] All records deleted!! \n");
        #endif
}

char* i_to_string_save(T_Record* p){
    static char str[80];
    sprintf(str, "%d %s %d %d", p->no, p->name, p->stock, p->ex_date);
        #ifdef DEBUG
                printf("[DEBUG] All data was successfully written to the file!!");
        #endif
    return str;
}

void i_get_all(T_Record* a[]){
   int i;
    for(i=0; i<MAX_ITEM; i++){
        if(goods[i]!=NULL){
            a[i]=goods[i];

        }
    }
}

char* i_to_string(T_Record* p){
    static char str[80];
    sprintf(str, "[%d] %s / %d / %d", p->no, p->name, p->stock, p->ex_date);
    return str;
}


int timecheck(T_Record*p){
    time_t timer;
    struct tm *t;
    timer = time(NULL);
    t = localtime(&timer);
    int year, month, day, date, left_days=0;
    date =p->ex_date;
    day = date %100;
    date /=100;
    month = date%100;
    date /=100;
    year = date;
    int i_date = CalcDate(month,day);
    int c_date = CalcDate(t->tm_mon+1,t->tm_mday);
    if(year == t->tm_year+1900) left_days = abs(i_date - c_date-1);
    else if(year > t->tm_year+1900) left_days = 365- c_date + i_date;
 else if(year< t->tm_year+1900) left_days = -(365 - i_date + c_date);

    return left_days;
}

int CalcDate(int month, int day){
    int monthdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int total=0;
    for(int i=0; i<month; i++){
        total += monthdays[i];
    }
    total+=day;
    return total;
}

void i_to_nolist(T_Record* a[]){

    int size = i_count();
    int i, j;
    int rank[size];
    for(i=0; i<size; i++){
        rank[i]=0;
    }
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            if(goods[i]->no > goods[j]->no) rank[i]++;
        }
    }
    int room=0;
    while(room != size){
        for(i=0; i<size; i++){

            if(rank[i]==room){
                a[room] = goods[i];
                room++;
            }

        }
    }
}
void checkstock(T_Record*p){
  int check,a_stock;
  if(p->stock <10){
    printf("%s's stock is less 10\n",p->name);
    printf("Current stock is %d\n",p->stock);
    printf("Do you add %s's sotck?  1.Yes 2.No",p->name);
    scanf("%d",&check);
    if(check ==1){
    printf("How many stock do you want to add?");
scanf("%d",&a_stock);
    p->stock += a_stock;
    printf("After changing stock is %d\n",p->stock);
    }
    else printf("OK. Cheking Stock Finished!\n");
  }
  if(p->stock >=10){
    printf("There are enough stocks!\n");
    printf("Current stock is %d\n",p->stock);
  }
}

