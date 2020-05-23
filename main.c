#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int CountOne=0;  // 程序计数器

// 内存
char DataMemory[16384][8];  //数据段
char CodeMemory[16384][8];  //代码段

// 通用寄存器
char DataRegister[4];  //数据寄存器
char AddressRegister[4]; //地址寄存器



char ReadFromFile(char CommandContent[512]) //读取指令
{
    FILE *fw = fopen("Command.txt", "r");
    fclose(fw);
    return "00000001000100000000000000000000";
}

int ProgramCount(int type){
    if (type==1){
        CountOne+=4;
        return 1;
    }else if (type==2){
        CountOne-=4;
        return 1;
    }else if (type==3){
        return CountOne;
    }
}

int main()
{
    char *Command;
    char CommandContent[512] = "Hello";
    ReadFromFile(CommandContent); //读取指令字符串 获取指针
    printf("%c\n", *Command);
    printf("Hello, World!\n");
    return 0;
}