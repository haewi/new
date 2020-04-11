#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAX_ITEM 5


typedef struct st_item{
    int no;		 //상품 번호     
    char name[20];	 //상품 이름
    int stock;		//상품 재고 	
    int ex_date;  	//상품 유통기한
} T_Record;

int i_is_available();
int i_first_available();
void i_create(int no, char* n, int st, int date);
T_Record* i_search_by_name(char* n);                // 이름이 일치하는 상품 레코드 포인터 찾기
void i_update(T_Record* p, int no, int st, int date);  // 특정 상품 레코드의 정보 업데이트
int i_count();
void i_delete(T_Record* p);     // 특정 상품 레코드의 상품정보 제거
void i_get_all(T_Record* a[]);  // 상품정보가 들어있는 모든 레코드 포인터의 배열을 만들기
char* i_to_string(T_Record* p); // 특정 상품 레코드의 내용을 문자열로 가져오기
char* i_getname(T_Record* p);   // 특정 상품 레코드의 상품이름 가져오기
int i_getstock(T_Record* p);  // 특정 상품 레코드의 상품재고  가져오기
int i_getexdate(T_Record* p);// 특정 상품 레코드의 상품유통기한  가져오기
int  i_getno(T_Record* p);   // 특정 상품 레코드의 상품번호  가져오기
void i_init();
char* i_to_string_save(T_Record* p);
void i_to_nolist(T_Record* a[]);
int timecheck(T_Record*p);
int CalcDate(int month, int day);
void checkstock(T_Record*p);
