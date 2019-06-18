#include "asmoperations.h"
#include <iostream>
using namespace std;


AsmOperations::AsmOperations()
{

}

void AsmOperations::addASM(QString &s1, QString &e1, QString &f1,
                           QString &s2, QString &e2, QString &f2,
                           QString &sR, QString &eR, QString &fR){
    unsigned long c = 2;
    bool sign1 = s1.left(1).toInt();
    bool sign2 = s2.left(1).toInt();
    unsigned long  ee1 = e1.toULong(nullptr, 16);
    unsigned long  ee2 = e2.toULong(nullptr, 16);
    unsigned long * ff1 = fractionToTable(f1);
    unsigned long * ff2 = fractionToTable(f2);
    unsigned long* res = new unsigned long[32];
    if(ee1>ee2)
        while(ee1>ee2){
            if(scaling(ff1, 31))
                c = c*2+1;
            else {
                c = c*2;
            }
            ee1--;
    }
    else {
        while(ee2>ee1){
            if(scaling(ff2, 31))
                c = c*2+1;
            ee2--;
    }
    }
    asm(
    "movl $0, %edx"
    );
    for(int i = 31; i>=0; i--)
        res[i] = smallAdd(ff1[i], ff2[i]);
    if(checkCF())
        c+=1;
    asm(
    "clc");
    while(c>1)
        normalize(res, c, ee1, 31);
    fR = tableToFraction(res, 32);
    eR = QString::number(ee1, 16);
    //while(fR.right(1).toInt() == 0)
     //   fR.remove(fR.length()-1, 1);
}

bool AsmOperations::subASM(QString &s1, QString &e1, QString &f1,
                           QString &s2, QString &e2, QString &f2,
                           QString &sR, QString &eR, QString &fR){
    unsigned long c = 0;
    bool sign1 = s1.left(1).toInt();
    bool sign2 = s2.left(1).toInt();
    unsigned long  ee1 = e1.toULong(nullptr, 16);
    unsigned long  ee2 = e2.toULong(nullptr, 16);
    unsigned long * ff1 = fractionToTable(f1);
    unsigned long * ff2 = fractionToTable(f2);
    unsigned long* res = new unsigned long[32];
    if(ee1>ee2)
        while(ee1>ee2){
            if(scaling(ff1, 31))
                c = c*2+1;
            else {
                c = c*2;
            }
            ee1--;
    }
    else {
        while(ee2>ee1){
            if(scaling(ff2, 31))
                c = c*2+1;
            ee2--;
    }
    }
    asm("clc");
    for(int i = 31; i>=0; i--)
        res[i] = smallSb(ff1[i], ff2[i]);
    if(checkCF())
        c-=1;
    if(c<0)
        return false;
    while(c>1)
        normalize(res, c, ee1, 31);
    fR = tableToFraction(res, 32);
    eR = QString::number(ee1, 16);
    //while(fR.right(1).toInt() == 0)
     //   fR.remove(fR.length()-1, 1);
}

void AsmOperations::mulASM(QString &s1, QString &e1, QString &f1,
                           QString &s2, QString &e2, QString &f2,
                           QString &sR, QString &eR, QString &fR){

    bool sign1 = s1.left(1).toInt();
    bool sign2 = s2.left(1).toInt();
    bool signr = sign1^sign2;
    sR = QString::number(signr);
    unsigned long  ee1 = e1.toULong(nullptr, 16);
    unsigned long  ee2 = e2.toULong(nullptr, 16);
    unsigned long * ff1 = fractionToTable(f1);
    unsigned long * ff2 = fractionToTable(f2);
    unsigned long res[3];
    unsigned long* fres = new unsigned long[2];
    fres[1] = 0;
    //unsigned long a, b;
    asm(
    "mull %%ebx\n"
    :"=d"(res[1]), "=a"(res[2])
     :"a"(ff1[0]), "b"(ff2[0]));
    asm(
    "movl $1, %%edx\n"
    "addl %%ebx, %%ecx\n"
    "jnc after\n"
    "addl $1, %%edx\n"
    "after:\n"
    "addl %%eax, %%ecx\n"
    "jnc mend\n"
    "addl $1, %%ecx\n"
    "mend:\n"

    :"=d"(res[0]), "=c"(res[1])
    :"a"(ff1[0]), "b"(ff2[0]), "c"(res[1])
    );
    ee1 = ee1+ee2;
    fres[0] = res[1];
    fres[1] = res[2];
    while(res[0]>1)
        normalize(fres, res[0], ee1, 1);
    fR = tableToFraction(fres, 2);
    eR = QString::number(ee1);
}

void AsmOperations::divASM(QString &s1, QString &e1, QString &f1,
                           QString &s2, QString &e2, QString &f2,
                           QString &sR, QString &eR, QString &fR){

}

void AsmOperations::sqrtASM(QString &s1, QString &e1, QString &f1,
                            QString &s2, QString &e2, QString &f2,
                            QString &sR, QString &eR, QString &fR){

}

unsigned long AsmOperations::smallAdd(unsigned long a, unsigned long b){
    unsigned long r = 0;
    int c;
    asm volatile(
    "and $0x00000001, %%edx\n"
    "addl %%edx, %%eax\n"
    "addl %%ebx, %%eax\n"
    "sbbl %%edx, %%edx\n"
    "movl %%eax, %%ecx\n"
    :"=c"(r)
    :"a"(a), "b"(b)
    );
    return r;
}

unsigned long* AsmOperations::fractionToTable(QString &f){
    if(f.length()>256)
       return nullptr;
    int rest = f.length()%8;
     for(int i = 0; i< rest; i++)
        f = f+"0";
    unsigned long* tab = new unsigned long[32];
    for(int i = 0; i<32; i++){
        if(f.isEmpty())
            tab[i] = 0x0;
        else {
            unsigned long t = (f.left(8)).toULong(nullptr, 16);
            tab[i]  = t;
            f.remove(0, 8);
        }
     }
    return tab;
}

QString AsmOperations::tableToFraction(unsigned long *t, int n){
    QString result = "";
    for(int i = 0; i<n; i++){
        QString temp = QString::number(t[i], 16);
        while(temp.length()<8)
            temp = "0" + temp;
        result = result + temp;
    }
    return result;
}

void AsmOperations::asmScaling(unsigned long &n){
    asm(
    "jnc slide\n"
    "add $1, %%eax\n"
    "slide:\n"
    "shl $1, %%eax\n"
    :"=a"(n)
    :"a"(n)        );
}

bool AsmOperations::scaling(unsigned long*tab, int n){
    asm("clc");
    for(int i = n; i>=0; i--)
        asmScaling(tab[i]);
    return checkCF();
}

bool AsmOperations::checkCF(){
    bool CF;
    asm(
    "movl $0, %%ecx\n"
    "jnc end\n"
    "movl $1, %%ecx\n"
    "end:\n"
    :"=c"(CF)
    );
    return CF;
}

void AsmOperations::rightShift(unsigned long &n){
    asm(
    "jnc noCarry\n"
    "shr %%eax\n"
    "add $0x80000000, %%eax\n"
    "jmp rend\n"
    "noCarry:\n"
    "shr %%eax\n"
    "rend:"
    :"=a"(n)
    :"a"(n));
}

void AsmOperations::normalize(unsigned long *tab,unsigned long &c, unsigned long &exp, int n){
    asm("clc");
    rightShift(c);
    exp++;
    for(int i = 0; i<n; i++){
        rightShift(tab[i]);
    }
}



