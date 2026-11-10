#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
//定义Persion结构体
struct Person {
    char name[50];		//名字
    int age;			//年龄
    int height;		//身高
    int weight;		//体重
};
//创建Persion结构体
struct Person Person_create(char name[50], int age, int height, int weight)
{
    struct Person who;
    strcpy(who.name,name);
    //who.name = name;	//复制名字并存在结构体的name中
    who.age = age;					 	//将年龄存在结构体的age中
    who.height = height;			//将身高存在结构体中
    who.weight = weight;			//将体重存在结构体中

    return who;								//返回结构体
}
//销毁结构体
/*void Person_destroy(struct Person who)
{

    free(who.name);					//释放name所占的内存
    free(who);								//释放结构体所占内存
}*/
//打印结构体中信息
void Person_print(struct Person who)
{
    printf("Name: %s\n", who.name);				//打印名字
    printf("\tAge: %d\n", who.age);				//年龄
    printf("\tHeight: %d\n", who.height);	//身高
    printf("\tWeight: %d\n", who.weight);	//体重
}

int main(int argc, char *argv[])
{
    // make two people structures
    struct Person joe = Person_create(
            "Joe Alex", 32, 64, 140);

    struct Person frank = Person_create(
            "Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    //printf("Joe is at memory location %p:\n", joe);
    Person_print(joe);

    //printf("Frank is at memory location %p:\n", frank);
    Person_print(frank);

    // make everyone age 20 years and print them again
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    frank.age += 20;
    frank.weight += 20;
    Person_print(frank);

    // destroy them both so we clean up
   // Person_destroy(joe);
   // Person_destroy(frank);

    return 0;
}
