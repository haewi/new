#include "members.h"

void create_record();
void read_record();
void update_record();
void delete_record();
void list_record();
void Exdate_check();
void load_file();
void write_file();
void no_list();
void Stock_check_Add();

int main(){
        int menu;
        while(1){
                printf("\nMenu : 1.Create 2.Read 3.Update 4.Delete 5.List 6.Load file 7.Write file 8.Exdate_check 9.Stock_check_Add 10.no_list 0.Quit > ");
                scanf("%d", &menu);
                printf("\n");
                switch(menu){
                
                        case 1:
                                create_record();
                                break;
                        case 2:
                                read_record();
                                break;
                        
                        case 3:
                                update_record();
                                break;

                        case 4:
                                delete_record();
                                break;
                        
                        case 5:
                                list_record();
                                break;
                        
                        case 6:
                               load_file();
                                break;
                        
                        case 7:
                                write_file();
                                break;
                        
                        case 8:                                
                                Exdate_check();
                                break;
                        
                        case 9:
                                Stock_check_Add();
                                break;     
                        
                        case 10:
                                
                                no_list();
                                break;
                        
                        case 0:
                                default:
                                        return 0;
                }
        }
        return 0;
}

void create_record(){
    if(!i_is_available()) {
        printf("There is no space!\n");
        return;
    }
    char name[20];
    int no, stock, ex_date;
    printf("Enter a new member's info.\n");
    printf("Name > ");
    scanf("%s", name);
    if(i_search_by_name(name)) {
        printf("Duplicated name!\n");
        return;
    }
    printf("NO > ");
    scanf("%d", &no);
    printf("Stocks > ");
    scanf("%d", &stock);
    printf("Expiration date > ");
    scanf("%d", &ex_date);
    i_create(no, name, stock, ex_date);
    printf("%d",i_count());
}

void read_record(){
    char name[20];
    printf("Enter a name > ");
    scanf("%s", name);

    T_Record* p = i_search_by_name(name);
    if(p) {
        printf("Item info.\n");
        printf("No : %d\n", i_getno(p));
 printf("Name : %s\n", i_getname(p));
        printf("Stock : %d\n", i_getstock(p));
        printf("Expiration Date : %d\n", i_getexdate(p));
    }
    else {
        printf("No such item!\n");
    }
}

void update_record(){
    char name[20];
    int no, stock, ex_date;  
    printf("Enter a name > ");
    scanf("%s", name);

    T_Record* p = i_search_by_name(name);
    if(p) {
        printf("Enter a updated info.\n");
        printf("No > ");
        scanf("%d", &no);
        printf("Stock > ");
        scanf("%d", &stock);
        printf("Expiration Date > ");
        scanf("%d",&ex_date);

        i_update(p, no, stock, ex_date);
    }
    else {
        printf("No such item!\n");
    }
}

void delete_record(){
    char name[20];
    printf("Enter a name > ");
    scanf("%s", name);

    T_Record* p = i_search_by_name(name);
    if(p) {
        i_delete(p);
        printf("The record is deleted!\n");
    }
    else {
        printf("No such member!\n");
    }
}

void load_file(){
        printf("All data will be deleted and new records will be reloaded.\n");
        printf("1.Yes 0.No > ");
        int yesno;
        scanf("%d", &yesno);
        if (yesno == 0) return;
        i_init();

        FILE* f = fopen("members.txt", "r");
        char name[20];
        int no, stock, ex_date;
        while(!feof(f)){
                if(!i_is_available()) {
                        printf("[Load] There is no space!\n");
                        break;
                }
                int n = fscanf(f,"%d %s %d %d",&no, name, &stock, &ex_date);
                if (n<4) break;
                if(i_search_by_name(name)) {
                        printf("[Load] Duplicated name(%s)! loading.\n", name);
                        continue;
                }
                i_create(no, name, stock, ex_date);
                //printf("[Load] load %s\n", name);
        }
        printf("%d records are read from file!\n", i_count());
        fclose(f);

}

void write_file(){
        FILE* f = fopen("members.txt", "w");
        printf("All records.\n");
        int size = i_count();
        T_Record* records[MAX_ITEM];
        i_get_all(records);
        for(int i=0; i<size; i++){
                T_Record* p = records[i];
                fprintf(f,"%s\n", i_to_string_save(p));
        }
 fclose(f);
}

void list_record(){

        printf("All records.\n");
        int size = i_count();
        T_Record* records[MAX_ITEM];
        i_get_all(records);
        for(int i=0; i<size; i++){
                T_Record* p = records[i];
                printf("%d. %s\n", i+1, i_to_string(p));
    }
}

void Exdate_check(){
    int size = i_count();
        T_Record* records[MAX_ITEM];
        i_get_all(records);
        for(int i=0; i<size; i++){
                T_Record* p = records[i];
                printf("%d. %s ", i+1, i_getname(p));
                if(timecheck(p)>=0) printf("[Left Expiration DATE -> %d days]\n",timecheck(p));
                else if(timecheck(p)<0) printf("[Passed Expriation DATE!!! -> %d days]\n",-timecheck(p));

    }
}
void no_list(){
    printf("Sorted by no!!\n");
    int size = i_count();
        T_Record* records[MAX_ITEM];
        i_to_nolist(records);
        for(int i=0; i<size; i++){
              printf("[%d] %s %d %d\n",records[i]->no,records[i]->name,records[i]->stock,records[i]->ex_date);
        }
}

void Stock_check_Add(){
  char name[20];
    printf("Enter a name > ");
    scanf("%s", name);
    T_Record* p = i_search_by_name(name);
    checkstock(p);
}

