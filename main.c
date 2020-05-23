#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>


char Mid[32];

int CountOne=0;  // 程序计数器

// 内存
int DataMemory[16384][8];  //数据段
int CodeMemory[16384][8];  //代码段

// 通用寄存器
int DataRegister[4];  //数据寄存器
int AddressRegister[4]; //地址寄存器
int Ir[17]; //指令寄存器

// 操作码处理
int Corporation(char Content[9]){
    char CharToF[2];
    int a=0;
    for (int i=0;i<8;i++){
        CharToF[0]=Content[i];
        a+=atof(CharToF)*pow(2,7-i);
    }
    return a;
}

int Subject(char Sub[5]){
    char CharToF[2];
    int a=0;
    for (int i=0;i<4;i++){
        CharToF[0]=Sub[i];
        a+=atof(CharToF)*pow(2,3-i);
    }
    return a;
}


// 立即数处理
int Lis(char Li[17]){
    char CharToF[2];
    int a=0;
    for (int i=0;i<16;i++){
        CharToF[0]=Li[i];
        a+=atof(CharToF)*pow(2,15-i);
    }
    return a;
}


// 根据地址从内存的数据段读取数据
int GetMemorry(int Address){
    return DataMemory[Address-16384];
}
// 根据地址向内存的数据段写数据
void WriteMemorry(int Address,int Data){
    DataMemory[Address-16384]=Data
}


// 程序计数器操作
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

//算术处理方法 Finish
int Calculate(int Op,int Sub1,int Sub2,int Li){
    if (Op==2){
        if(Sub2==0){
            // 寄存器A -> A + 立即数
            DataRegister[Sub1-1]+=Li;
        } else{
            // 寄存器A -> A + 寄存器B 地址 -> 内存
            DataRegister[Sub1-1]+=GetMemorry(AddressRegister[Sub2-1]);
        }
    } else if (Op==3){
        if (Sub2==0){
            // 寄存器A -> A - 立即数
            DataRegister[Sub1-1]-=Li;
        } else{
            // 寄存器A -> A - 寄存器B 地址 -> 内存
            DataRegister[Sub1-1]-=GetMemorry(AddressRegister[Sub2-1]);
        }
    } else if (Op==4){
        if(Sub2==0){
            // 寄存器A -> A * 立即数
            DataRegister[Sub1-1]*=Li;
        } else{
            // 寄存器A -> A * 寄存器B 地址 -> 内存
            DataRegister[Sub1-1]*=GetMemorry(AddressRegister[Sub2-1]);
        }
    }else if (Op==5){
        if(Sub2==0){
            // 寄存器A -> A / 立即数
            DataRegister[Sub1-1]/=Li;
        } else{
            // 寄存器A -> A / 寄存器B 地址 -> 内存
            DataRegister[Sub1-1]/=GetMemorry(AddressRegister[Sub2-1]);
        }
    }
}

//数据传送方法  Finish
int DataTransform(int Sub1,int Sub2,int Li){
    if (Sub1>4){
        WriteMemorry(Sub2-1,DataRegister[Sub1-1]);
        // 寄存器A 内容 -> 寄存器B 地址 -> 内存

    }else if (Sub2==0){
        DataRegister[Sub1-1]=Li;
        // 立即数 -> 寄存器A

    }else{
        DataRegister[Sub1-1]=GetMemorry(AddressRegister[Sub2-1]);
        // 寄存器B 地址 内容 -> 寄存器A
    }
}

int main()
{
    char Command[33]="00000001000101010000000000000001";
    printf("%s\n",Command); //读取指令字符串 获取指针
    char Cop[9],SubOne[5],SubTwo[5],Li[17];

    // 二进制转为十进制
    strncpy(Cop,Command,8);
    strncpy(SubOne,Command+8,4);
    strncpy(SubTwo,Command+12,4);\
    strncpy(Li,Command+16,16);
    int Coporation=Corporation(Cop);
    int SubjectOne=Subject(SubOne);
    int SubjectTwo=Subject(SubTwo);
    int LiNumber=Lis(Li);
    printf("Coporation:%d\nSubject One:%d\nSubject Two:%d\nLijishu:%d",Coporation,SubjectOne,SubjectTwo,LiNumber);
    // 此处获得了操作吗 操作对象 立即数

    if (Coporation==1){
        //数据传送
        DataTransform(SubOne,SubTwo,LiNumber);

    }else if (Coporation<=5){
        //算术
        Calculate(Coporation,SubOne,SubTwo,LiNumber);

    }else if (Coporation<=8){
        //逻辑

    } else if (Coporation==9){
        //比较

    }else if (Coporation==10){
        //跳转

    }else if (Coporation==11){
        //输入

    }else if (Coporation==12){
        //输出

    }


    return 0;
}