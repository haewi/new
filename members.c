#include "members.h"

T_Record* goods[MAX_ITEM]; // 상품정보데이터 (전역)
int _count = 0;

int i_is_available(){
    int i;
    for(i=0; i<MAX_ITEM; i++){
        if(goods[i]==NULL){
		#ifdef DEBUG
			printf("[DEBUG]Array is not empty, you can use\n");
		#endif
		return 1;
	}
    }
    return 0;
}

int i_first_available(){
    int i;
    for(i=0; i<MAX_ITEM; i++){
        if(goods[i]==NULL){
 		#ifdef DEBUG
			printf("[DEBUG]You can use %d index of array\n",i);
		#endif
		return i;
	}
    }
    return -1;
}

int i_count(){
    return _count;
}

void i_create(int no, char* n, int st, int dt){
    int index = i_first_available();
    goods[index] = (T_Record*)malloc(sizeof(T_Record));
    T_Record* p = goods[index];
    strcpy(p->name, n);  
    p->no=no;
    p->stock = st;
    p->ex_date = dt;
    _count++;
	#ifdef DEBUG
		printf("[DEBUG]Created Successfully!!\n");
	#endif
}

T_Record* i_search_by_name(char* n){
    int i;
    for(i=0; i<_count; i++){
        if(goods[i]!=NULL && strcmp(goods[i]->name, n)==0){
		#ifdef DEBUG
			printf("[DEBUG]Find! Same name of information!!\n");
		#endif
		 return goods[i];
	}
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
   int i, c=0;
    for(i=0; i<MAX_ITEM; i++){
        if(goods[i]!=NULL){
            a[c]=goods[i];
            c++;
        }
    }
}

char* i_to_string(T_Record* p){
    static char str[80];
    sprintf(str, "[%d] %s / %d / %d", p->no, p->name, p->stock, p->ex_date);
    return str;
}
