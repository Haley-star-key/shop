#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// 1. 商品结构体
 struct item{
    char id[20];      
    char name[50];    
    double price;     
} ;

// 2. 购物车结构体,不过用到取别名的方式
typedef struct {
    char id[20];      
    int count;        
} CartItem;

// 【核心】将商店和购物车定义为全局变量，放在 main 函数外面
// 这样所有函数都能直接访问，而且可以在这里直接初始化数据
struct item store[3] = {
    {"001", "Cola", 3.50},
    {"002", "Lollipop", 0.50},
    {"003", "Noodles", 6.00}
};

CartItem cart[50]; // 购物车数组，意思是现在有cart可以存放50个CartItem的数组
int cart_count = 0;      // 初始化

 //查找商品在商店中的位置，如果找不到返回 -1
int findstore(char* id) {//因为不需要print出结果,最后要返回一个整型所以前面是int
    for (int i = 0; i < 3; i++) {
        if (strcmp(store[i].id, id) == 0) {//先执行里面的store[i].id,意思是
            //先从store里找到第i个元素的id,再与,后面的id进行比较
            return i; // 找到了，返回它在 store 数组中的下标
        }
    }
    return -1;//必须写return,不然会报错，因为返回的值是数值的下标.store里又有3个
    //所以数值不能写0，1，2,因为数组下标不为负数，所以查找不到自然是负数
}

// 查找商品在当前购物车中的位置，如果不在购物车里返回 -1
int find_cart(char* id) {
    for (int i = 0; i < cart_count; i++) {
        if (strcmp(cart[i].id, id) == 0) {
            return i; // 找到了，返回它在 cart 数组中的下标
        }
    }
    return -1;
}

// 计算
void print_cart() {
    if (cart_count == 0) {
        printf("price=0\n");
        return;
    }
    printf("\nnow:\n");//两个换行符使看起来更好看
    for (int i = 0; i < cart_count; i++) {
        int storeIdx = findstore(cart[i].id);//for循环的目的是让每一个商品信息都来一次
        printf("%s  %.2f x%d =%.2f\n", 
               store[storeIdx].name, 
               store[storeIdx].price, 
               cart[i].count, 
               store[storeIdx].price * cart[i].count);
    }
}

//  添加商品进购物车
void addToCart(char* id) {
    int cartIdx = find_cart(id);//find_cart这个函数会接收数据，id就是传给他的数据
//cartIdx就是储存函数返回值的，即拿到一个下标
    int storeIdx = findstore(id);
    
    if (cartIdx != -1) {//！=50意思就是商品在购物车里已经存在了
        cart[cartIdx].count++;//就可以让其数量加一
    } 
    else {// 如果购物车里没有这个商品，新增一条记录
        strcpy(cart[cart_count].id, store[storeIdx].id);//string copy
        //将第二个的字符串复制到第一个里面去,在store里面找一个下标为storeIdx的id
        cart[cart_count].count = 1;//cart_count是现在购物车里的商品数
        //用此时的商品数作为在cart中的下标去找到对应的格子，要注意的是此时由于
        //上一段代码这个对应的格子实际上已经储存了id了，此时让这个位置的数量为1
        //就是在让这个格子被占用
        cart_count++; // 购物车种类数 +1，感觉有点类似循环
    }
}

// 减少商品 
void cut(char* id) {
    int cartIdx = find_cart(id);
    cart[cartIdx].count--;//--就是减一和++一样
    //找到其在购物车的下标所对应的位置的count，让其减一
    // 如果数量减到 0 了，就从购物车中删除它
    if (cart[cartIdx].count == 0) {
        // 用数组最后一个元素覆盖当前元素，实现删除
        cart[cartIdx] = cart[cart_count - 1];//有很多数据，结构体可以直接赋值
        cart_count--;
    }
    print_cart();
}

// 清空
void drop() {
    cart_count = 0;
    printf("empty\n");
}

// 打印小票
    void checkout() {
    if (cart_count == 0) {
        printf("cart is empty.\n");
        return;
    }

    printf("\n--------- Receipt ---------\n");
    printf("%s %s %s %s\n", "Item", "Pri.", "Qty", "Amount");
    printf("----------------------------\n");
    
    double total = 0.00;//初始化
    
    for (int i = 0; i < cart_count; i++) {
        int storeIdx = findstore(cart[i].id);
        double amount = store[storeIdx].price * cart[i].count;
        total += amount;
        
        printf("%s %.2f x%d =%.2f\n", 
               store[storeIdx].name, 
               store[storeIdx].price, 
               cart[i].count, 
               amount);
    }
    
    printf("----------------------------\n");
    printf("Total      = %.2f\n",total);
    cart_count=0;
    
}
int main() {
    char line[100];
    printf("> "); 
   while(fgets(line, sizeof(line), stdin)!=0){
    line[strcspn(line,"\n")]=0;//在line里面找到\n并且使其为\0
    if(strcmp(line,"drop")==0){
        drop();
    }
    else if(strcmp(line,"checkout")==0){
        checkout();
    }
    else if(strcmp(line,"print")==0){
        print_cart();
    }
    
    else if(line[0]=='-'){//字符用单引号，字符串才用双引号
        cut(line+1);//line+1就是从字符串的第二个字符开始
        //line在单独使用时表示[0]的字符，只有是line[x]时才表示第x个字符
    }
    else {
        char*token;//存放line的一个地址
        for(token=strtok(line," ");//切line,用空格切
        token!=0;//第一次切，如果检测到没有切完，进入循环
        token=strtok(0,"")){//切完后会空格处会变成\0,所以从0处开始即从上一次结束的时间开始
            //函数调用，必须写在主函数像main一样的函数中
            //token是切后的数据,让其跳回上面的find函数去执行
           if(token[0]=='-'){
            cut(token+1);
           }
           else{
            addToCart(token);}
        }
        print_cart();
    }
    
    printf(">");
}
return 0;
};