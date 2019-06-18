#ifndef ASMOPERATIONS_H
#define ASMOPERATIONS_H

#include <QString>


class AsmOperations
{
private:

   unsigned long smallAdd(unsigned long a, unsigned long b);
   unsigned long* fractionToTable(QString &f);
   QString tableToFraction(unsigned long* t, int n);
   void asmScaling(unsigned long &n);
   bool scaling(unsigned long* tab, int n);
   void normalize(unsigned long* tab, unsigned long &c, unsigned long &exp, int n);
   void rightShift(unsigned long &n);
   unsigned long smallSb(unsigned long a, unsigned long b){
       unsigned long r = 0;
      asm(
       "sbbl %%ebx, %%eax\n"
       "movl %%eax, %%ecx\n"
       :"=c"(r)
       :"a"(a), "b"(b)
       );
       return r;}
   bool checkCF();
public:
    AsmOperations();

    void addASM(QString &s1, QString &e1, QString &f1,
                QString &s2, QString &e2, QString &f2,
                QString &sR, QString &eR, QString &fR);

    bool subASM(QString &s1, QString &e1, QString &f1,
                QString &s2, QString &e2, QString &f2,
                QString &sR, QString &eR, QString &fR);

    void mulASM(QString &s1, QString &e1, QString &f1,
                QString &s2, QString &e2, QString &f2,
                QString &sR, QString &eR, QString &fR);

    void divASM(QString &s1, QString &e1, QString &f1,
                QString &s2, QString &e2, QString &f2,
                QString &sR, QString &eR, QString &fR);

    void sqrtASM(QString &s1, QString &e1, QString &f1,
                 QString &s2, QString &e2, QString &f2,
                 QString &sR, QString &eR, QString &fR);
};

#endif // ASMOPERATIONS_H
