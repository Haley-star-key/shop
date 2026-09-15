#include <stdio.h>
#include <string.h>

struct Item {
    char code[10];
    char name[20];
    float price;
};//结构体

struct Item database[3] = {
    {"001", "Cola", 3.50},
    {"002", "Lollipop", 0.50},
    {"003", "Noodles", 6.00}
};//结构体数组

// 函数声明，以便调用,find是函数名
void find(char* code) {
    if(strcmp(code, "001") == 0) {
        printf("Cola, 3.50\n");
    }
    else if(strcmp(code, "002") == 0) {
        printf("Lollipop, 0.50\n");
    }
    else if(strcmp(code, "003") == 0) {
        printf("Noodles, 6.00\n");
    }
    else
        printf("ERROR:code not found\n");
    }


int main() {
    char line[100];
    printf("> "); 
   while(fgets(line, sizeof(line), stdin)!=0){
    line[strcspn(line,"\n")]=0;//在line里面找到\n并且使其为\0
    if(strcmp(line,"quit")==0){
        break;}
    else if(strcmp(line,"exit")==0){
        break;
    }
    else if(strcmp(line,"price")==0){
    printf("Item\tNO.\tPri.\n");
    printf("------------------\n");
    printf("cola\t001\t3.50\n");
    printf("lollipop\t002\t0.50\n");
    printf("Noodles\t003\t6.00\n");
    }
    else{
        char*token;//存放line的一个地址
        for(token=strtok(line," ");//切line,用空格切
        token!=0;//第一次切，如果检测到没有切完，进入循环
        token=strtok(0,"")//切完后会空格处会变成\0,所以从0处开始即从上一次结束的时间开始
    ){
            find(token);//函数调用，必须写在主函数像main一样的函数中
            //token是切后的数据,让其跳回上面的find函数去执行
        }
    }
    
    printf(">");
}
return 0;
};


