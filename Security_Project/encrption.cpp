#include "encrption.h"
#include "ui_encrption.h"
#include<fileencrypt.h>
#include"des.h"

#include <QFileDialog>
#include <QMessageBox>
#include <string.h>
#include <stdio.h>
//#include<conio.h>
#include <stdlib.h>
#include<math.h>


#define Nb 4
int Nr=0;
int Nk=0;

//HELOOOOOOOOOOOOOOOOOOOOOOOOOOOO
using namespace std;

//*****************Variables for AES***********************
unsigned char in[16], out[16], state[4][4];
 char *sttrr=new char[1000];
//******************Variables for DES algo************************

int key[64]=
{
    0,0,0,1,0,0,1,1,
    0,0,1,1,0,1,0,0,
    0,1,0,1,0,1,1,1,
    0,1,1,1,1,0,0,1,
    1,0,0,1,1,0,1,1,
    1,0,1,1,1,1,0,0,
    1,1,0,1,1,1,1,1,
    1,1,1,1,0,0,0,1
};
class Des
{
public:
    int keyi[16][48],
        total[64],
        left[32],
        right[32],
        ck[28],
        dk[28],
        expansion[48],
        z[48],
        xor1[48],
        sub[32],
        p[32],
        xor2[32],
        temp[64],
        pc1[56],
        ip[64],
        inv[8][8];

    char final[1000];
    void IP();
    void PermChoice1();
    void PermChoice2();
    void Expansion();
    void inverse();
    void xor_two();
    void xor_oneE(int);
    void xor_oneD(int);
    void substitution();
    void permutation();
    void keygen();
    char * Encrypt(char *);
    char * Decrypt(char *);
};
Des d1;
void Des::IP() //Initial Permutation
{
    int k=58,i;
    for(i=0; i<32; i++)
    {
        ip[i]=total[k-1];
        if(k-8>0)  k=k-8;
        else       k=k+58;
    }
    k=57;
    for( i=32; i<64; i++)
    {
        ip[i]=total[k-1];
        if(k-8>0)   k=k-8;
        else     k=k+58;
    }
}
void Des::PermChoice1() //Permutation Choice-1
{
    int k=57,i;
    for(i=0; i<28; i++)
    {
        pc1[i]=key[k-1];
        if(k-8>0)    k=k-8;
        else      k=k+57;
    }
    k=63;
    for( i=28; i<52; i++)
    {
        pc1[i]=key[k-1];
        if(k-8>0)    k=k-8;
        else         k=k+55;
    }
    k=28;
    for(i=52; i<56; i++)
    {
        pc1[i]=key[k-1];
        k=k-8;
    }

}
void Des::Expansion() //Expansion Function applied on `right' half
{
    int exp[8][6],i,j,k;
    for( i=0; i<8; i++)
    {
        for( j=0; j<6; j++)
        {
            if((j!=0)||(j!=5))
            {
                k=4*i+j;
                exp[i][j]=right[k-1];
            }
            if(j==0)
            {
                k=4*i;
                exp[i][j]=right[k-1];
            }
            if(j==5)
            {
                k=4*i+j;
                exp[i][j]=right[k-1];
            }
        }
    }
    exp[0][0]=right[31];
    exp[7][5]=right[0];

    k=0;
    for(i=0; i<8; i++)
        for(j=0; j<6; j++)
            expansion[k++]=exp[i][j];
}
void Des::PermChoice2()
{
    int per[56],i,k;
    for(i=0; i<28; i++) per[i]=ck[i];
    for(k=0,i=28; i<56; i++) per[i]=dk[k++];

    z[0]=per[13];
    z[1]=per[16];
    z[2]=per[10];
    z[3]=per[23];
    z[4]=per[0];
    z[5]=per[4];
    z[6]=per[2];
    z[7]=per[27];
    z[8]=per[14];
    z[9]=per[5];
    z[10]=per[20];
    z[11]=per[9];
    z[12]=per[22];
    z[13]=per[18];
    z[14]=per[11];
    z[15]=per[3];
    z[16]=per[25];
    z[17]=per[7];
    z[18]=per[15];
    z[19]=per[6];
    z[20]=per[26];
    z[21]=per[19];
    z[22]=per[12];
    z[23]=per[1];
    z[24]=per[40];
    z[25]=per[51];
    z[26]=per[30];
    z[27]=per[36];
    z[28]=per[46];
    z[29]=per[54];
    z[30]=per[29];
    z[31]=per[39];
    z[32]=per[50];
    z[33]=per[46];
    z[34]=per[32];
    z[35]=per[47];
    z[36]=per[43];
    z[37]=per[48];
    z[38]=per[38];
    z[39]=per[55];
    z[40]=per[33];
    z[41]=per[52];
    z[42]=per[45];
    z[43]=per[41];
    z[44]=per[49];
    z[45]=per[35];
    z[46]=per[28];
    z[47]=per[31];
}
void Des::xor_oneE(int round) //for Encrypt
{
    int i;
    for(i=0; i<48; i++)
        xor1[i]=expansion[i]^keyi[round-1][i];
}
void Des::xor_oneD(int round) //for Decrypt
{
    int i;
    for(i=0; i<48; i++)
        xor1[i]=expansion[i]^keyi[16-round][i];
}

void Des::substitution()
{
    int s1[4][16]=
    {
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
    };

    int s2[4][16]=
    {
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
    };

    int s3[4][16]=
    {
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
    };

    int s4[4][16]=
    {
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
    };

    int s5[4][16]=
    {
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
    };

    int s6[4][16]=
    {
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
    };

    int s7[4][16]=
    {
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
    };

    int s8[4][16]=
    {
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
    };
    int a[8][6],k=0,i,j,p,q,count=0,g=0,v;

    for(i=0; i<8; i++)
    {
        for(j=0; j<6; j++)
        {
            a[i][j]=xor1[k++];
        }
    }

    for( i=0; i<8; i++)
    {
        p=1;
        q=0;
        k=(a[i][0]*2)+(a[i][5]*1);
        j=4;
        while(j>0)
        {
            q=q+(a[i][j]*p);
            p=p*2;
            j--;
        }
        count=i+1;
        switch(count)
        {
        case 1:
            v=s1[k][q];
            break;
        case 2:
            v=s2[k][q];
            break;
        case 3:
            v=s3[k][q];
            break;
        case 4:
            v=s4[k][q];
            break;
        case 5:
            v=s5[k][q];
            break;
        case 6:
            v=s6[k][q];
            break;
        case 7:
            v=s7[k][q];
            break;
        case 8:
            v=s8[k][q];
            break;
        }

        int d,i=3,a[4];
        while(v>0)
        {
            d=v%2;
            a[i--]=d;
            v=v/2;
        }
        while(i>=0)
        {
            a[i--]=0;
        }

        for(i=0; i<4; i++)
            sub[g++]=a[i];
    }
}

void Des::permutation()
{
    p[0]=sub[15];
    p[1]=sub[6];
    p[2]=sub[19];
    p[3]=sub[20];
    p[4]=sub[28];
    p[5]=sub[11];
    p[6]=sub[27];
    p[7]=sub[16];
    p[8]=sub[0];
    p[9]=sub[14];
    p[10]=sub[22];
    p[11]=sub[25];
    p[12]=sub[4];
    p[13]=sub[17];
    p[14]=sub[30];
    p[15]=sub[9];
    p[16]=sub[1];
    p[17]=sub[7];
    p[18]=sub[23];
    p[19]=sub[13];
    p[20]=sub[31];
    p[21]=sub[26];
    p[22]=sub[2];
    p[23]=sub[8];
    p[24]=sub[18];
    p[25]=sub[12];
    p[26]=sub[29];
    p[27]=sub[5];
    p[28]=sub[21];
    p[29]=sub[10];
    p[30]=sub[3];
    p[31]=sub[24];
}

void Des::xor_two()
{
    int i;
    for(i=0; i<32; i++)
    {
        xor2[i]=left[i]^p[i];
    }
}

void Des::inverse()
{
    int p=40,q=8,k1,k2,i,j;
    for(i=0; i<8; i++)
    {
        k1=p;
        k2=q;
        for(j=0; j<8; j++)
        {
            if(j%2==0)
            {
                inv[i][j]=temp[k1-1];
                k1=k1+8;
            }
            else if(j%2!=0)
            {
                inv[i][j]=temp[k2-1];
                k2=k2+8;
            }
        }
        p=p-1;
        q=q-1;
    }
}

char * Des::Encrypt(char *Text1)
{
    int a1,j,nB,m,iB,k,K,B[8],n,d,round;
    size_t i;
    char *Text=new char[1000];
    strcpy(Text,Text1);
    i=strlen(Text);
    int mc=0;
    a1=i%8;
    if(a1!=0) for(j=0; j<8-a1; j++,i++) Text[i]=' ';
    Text[i]='\0';
    keygen();
    for(iB=0,nB=0,m=0; m<(strlen(Text)/8); m++) //Repeat for TextLenth/8 times.
    {
        for(iB=0,i=0; i<8; i++,nB++)
        {
            n=(int)Text[nB];
            for(K=7; n>=1; K--)
            {
                B[K]=n%2;  //Converting 8-Bytes to 64-bit Binary Format
                n/=2;
            }
            for(; K>=0; K--) B[K]=0;
            for(K=0; K<8; K++,iB++) total[iB]=B[K]; //Now `total' contains the 64-Bit binary format of 8-Bytes
        }
        IP(); //Performing initial permutation on `total[64]'
        for(i=0; i<64; i++) total[i]=ip[i]; //Store values of ip[64] into total[64]

        for(i=0; i<32; i++) left[i]=total[i]; //     +--> left[32]
        // total[64]--|
        for(; i<64; i++) right[i-32]=total[i]; //            +--> right[32]
        for(round=1; round<=16; round++)
        {
            Expansion(); //Performing expansion on `right[32]' to get  `expansion[48]'
            xor_oneE(round); //Performing XOR operation on expansion[48],z[48] to get xor1[48]
            substitution();//Perform substitution on xor1[48] to get sub[32]
            permutation(); //Performing Permutation on sub[32] to get p[32]
            xor_two(); //Performing XOR operation on left[32],p[32] to get xor2[32]
            for(i=0; i<32; i++) left[i]=right[i]; //Dumping right[32] into left[32]
            for(i=0; i<32; i++) right[i]=xor2[i]; //Dumping xor2[32] into right[32]
        }
        for(i=0; i<32; i++) temp[i]=right[i]; // Dumping   -->[ swap32bit ]
        for(; i<64; i++) temp[i]=left[i-32]; //    left[32],right[32] into temp[64]

        inverse(); //Inversing the bits of temp[64] to get inv[8][8]
        /* Obtaining the Cypher-Text into final[1000]*/
        k=128;
        d=0;
        for(i=0; i<8; i++)
        {
            for(j=0; j<8; j++)
            {
                d=d+inv[i][j]*k;
                k=k/2;
            }
            final[mc++]=(char)d;
            k=128;
            d=0;
        }
    } //for loop ends here
    final[mc]='\0';
    return(final);
}
char * Des::Decrypt(char *Text1)
{
    int j,nB,m,iB,k,K,B[8],n,d,round;
    size_t i;
    char *Text=new char[1000];
    unsigned char ch;
    strcpy(Text,Text1);
    i=strlen(Text);
    keygen();
    int mc=0;
    for(iB=0,nB=0,m=0; m<(strlen(Text)/8); m++) //Repeat for TextLenth/8 times.
    {
        for(iB=0,i=0; i<8; i++,nB++)
        {
            ch=Text[nB];
            n=(int)ch;//(int)Text[nB];
            for(K=7; n>=1; K--)
            {
                B[K]=n%2;  //Converting 8-Bytes to 64-bit Binary Format
                n/=2;
            }
            for(; K>=0; K--) B[K]=0;
            for(K=0; K<8; K++,iB++) total[iB]=B[K]; //Now `total' contains the 64-Bit binary format of 8-Bytes
        }
        IP(); //Performing initial permutation on `total[64]'
        for(i=0; i<64; i++) total[i]=ip[i]; //Store values of ip[64] into total[64]

        for(i=0; i<32; i++) left[i]=total[i]; //     +--> left[32]
        // total[64]--|
        for(; i<64; i++) right[i-32]=total[i]; //            +--> right[32]
        for(round=1; round<=16; round++)
        {
            Expansion(); //Performing expansion on `right[32]' to get  `expansion[48]'
            xor_oneD(round);
            substitution();//Perform substitution on xor1[48] to get sub[32]
            permutation(); //Performing Permutation on sub[32] to get p[32]
            xor_two(); //Performing XOR operation on left[32],p[32] to get xor2[32]
            for(i=0; i<32; i++) left[i]=right[i]; //Dumping right[32] into left[32]
            for(i=0; i<32; i++) right[i]=xor2[i]; //Dumping xor2[32] into right[32]
        } //rounds end here
        for(i=0; i<32; i++) temp[i]=right[i]; // Dumping   -->[ swap32bit ]
        for(; i<64; i++) temp[i]=left[i-32]; //    left[32],right[32] into temp[64]

        inverse(); //Inversing the bits of temp[64] to get inv[8][8]
        /* Obtaining the Cypher-Text into final[1000]*/
        k=128;
        d=0;
        for(i=0; i<8; i++)
        {
            for(j=0; j<8; j++)
            {
                d=d+inv[i][j]*k;
                k=k/2;
            }
            final[mc++]=(char)d;
            k=128;
            d=0;
        }
    } //for loop ends here
    final[mc]='\0';
    char *final1=new char[10000];
    for(i=0,j=strlen(Text); i<strlen(Text); i++,j++)
        final1[i]=final[j];
    final1[i]='\0';
    return(final);
}
void Des::keygen()
{
    PermChoice1();

    int i,j,k=0;
    for(i=0; i<28; i++)
    {
        ck[i]=pc1[i];
    }
    for(i=28; i<56; i++)
    {
        dk[k]=pc1[i];
        k++;
    }
    int noshift=0,round;
    for(round=1; round<=16; round++)
    {
        if(round==1||round==2||round==9||round==16)
            noshift=1;
        else
            noshift=2;
        while(noshift>0)
        {
            int t;
            t=ck[0];
            for(i=0; i<28; i++)
                ck[i]=ck[i+1];
            ck[27]=t;
            t=dk[0];
            for(i=0; i<28; i++)
                dk[i]=dk[i+1];
            dk[27]=t;
            noshift--;
        }
        PermChoice2();
        for(i=0; i<48; i++)
            keyi[round-1][i]=z[i];
    }
}
///*******************************************************************

//******************Variables for RSA algo**************************
long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100],  i;
long en[100];
long mi[100];
char msg[100];
int prime(long int);
void ce();
long int cd(long int);
void encryptRSA();
void decrypt();
//*******************************************************************


///************************ Encryption using Ceaser Cypher *****************************/////
string encryptCeaser(string text, int s)
{
    string result = "";

    // traverse text
    for (int i=0;i<text.length();i++)
    {
        // apply transformation to each character
        // Encrypt Uppercase letters
        if (isupper(text[i]))
            result += char(int(text[i]+s-65)%26 +65);

    // Encrypt Lowercase letters
    else
        result += char(int(text[i]+s-97)%26 +97);
    }

    // Return the resulting string
    return result;
}
string decryptCeaser(string text, int s)
{
    s=26-s;
    string result = "";

    // traverse text
    for (int i=0;i<text.length();i++)
    {
        // apply transformation to each character
        // Encrypt Uppercase letters
        if (isupper(text[i]))
            result += char(int(text[i]+s-65)%26 +65);

    // Encrypt Lowercase letters
    else
        result += char(int(text[i]+s-97)%26 +97);
    }

    // Return the resulting string
    return result;
}


//////******Functions for RSA algo********************///////////////////////
int prime(long int pr)
{
    int i;
    j = sqrt(pr);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}

void ce()
{
    int k;
    k = 0;
    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        flag = prime(i);
        if (flag == 1 && i != p && i != q)
        {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}
long int cd(long int x)
{
    long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}
void encryptRSA()
{
    long int pt, ct, key = e[0], k;
    size_t len;
    i = 0;
    len = strlen(msg);
    while (i != len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = '\0';
   /* cout << "\nTHE ENCRYPTED MESSAGE IS\n";
    for (i = 0; en[i] != -1; i++)
        printf("%c", en[i]);*/
}

void decrypt()
{
    long int pt, ct, key = d[0], k;
    i = 0;
    while (en[i] != '\0')
    {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
   /* cout << "\nTHE DECRYPTED MESSAGE IS\n";
    for (i = 0; m[i] != -1; i++)
        printf("%c", m[i]);*/
}
////////////////////////********************************************//////////////////////////


Encrption::Encrption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Encrption)
{
    ui->setupUi(this);
    this->setFixedSize(700,700);
    ui->label1->setStyleSheet("QLabel {  color : orange; }");
    ui->label2->setStyleSheet("QLabel {  color : orange; }");
    ui->label3->setStyleSheet("QLabel {  color : orange; }");
    ui->label5->setStyleSheet("QLabel {  color : orange; }");
    ui->label4->setStyleSheet("QLabel {  color : orange; }");
    ui->radioButton->setStyleSheet("QRadioButton {  color : orange; }");
    ui->radioButton_3->setStyleSheet("QRadioButton {  color : orange; }");
    ui->radioButton_4->setStyleSheet("QRadioButton {  color : orange; }");
    //ui->radioButton_5->setStyleSheet("QRadioButton {  color : orange; }");
    ui->radioButton_6->setStyleSheet("QRadioButton {  color : orange; }");
    ui->pushButton->setStyleSheet("background-color:orange;");
    ui->pushButton_2->setStyleSheet("background-color:orange;");
    ui->pushButton_3->setStyleSheet("background-color:orange;");

    QPixmap bkgnd("F:/6th Sem/Linux Project/Security_Project/darkbg.jpeg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
}

Encrption::~Encrption()
{
    delete ui;
}

void Encrption::on_pushButton_clicked()
{
    QString dd;
    QMessageBox errorBox;
    errorBox.setText("Enter");
    if(ui->radioButton->isChecked()){
        //cout << "\nENTER FIRST PRIME NUMBER\n";
         //   cin >> p;
       p=(ui->key1->toPlainText()).toLong();
      //  p=47;
            flag = prime(p);
            if (flag == 0)
            {
              errorBox.setText("Public key is not a prime number.");
              errorBox.exec();
            }
            //cout << "\nENTER ANOTHER PRIME NUMBER\n";
            //cin >> q;
            q=(ui->key2->toPlainText()).toLong();
            flag = prime(q);
            if (flag == 0 || p == q)
            {
                errorBox.setText("Private key is not a prime number.");
                errorBox.exec();
            }
           // cout << "\nENTER MESSAGE\n";
            //fflush(stdin);
            //cin >> msg;
            QString str=ui->text1->toPlainText();

             strcpy(msg, str.toStdString().c_str());
            for (i = 0; msg[i] != '\0'; i++)
                m[i] = msg[i];
            n = p * q;
            t = (p - 1) * (q - 1);
            ce();
           /* cout << "\nPOSSIBLE VALUES OF e AND d ARE\n";
            for (i = 0; i < j - 1; i++)
                cout << e[i] << "\t" << d[i] << "\n";*/
           // decrypt();
          encryptRSA();
            string qe="";
            for(int i=0;en[i]!='\0';i++){
                qe=qe+(char)en[i];
            }
            QString qw = QString::fromStdString(qe);
            ui->text2->setText(qw);
          //  decrypt();



    }
    else if(ui->radioButton_3->isChecked()){

        blowfish.calcSubKey( ui->key1->toPlainText() );
        QByteArray encyptedData;

        QString dataString =  ui->text1->toPlainText();


            encyptedData = blowfish.encrypt(  QByteArray(dataString.toUtf8()) );



        ui->text2->setHtml( encyptedData.toBase64() );

    }
    else if(ui->radioButton_4->isChecked()){
        QMessageBox errorBox;
        errorBox.setText("Please Enter a value less than 26");



        QString dd;
        dd=ui->text1->toPlainText();
        std::string ct = dd.toLocal8Bit().constData();
        long int s=p=(ui->key2->toPlainText()).toLong();
        if(s>26)errorBox.exec();
        else{
        string result=encryptCeaser(ct, s);

        QString qw = QString::fromStdString(result);
        ui->text2->setText(qw);}
    }

    else if(ui->radioButton_6->isChecked()){
        Des d9;
            char *str=new char[1000];

            //strcpy(str,"PHOENIX it & ece solutions.");
            //cout<<"Enter a string : ";
            //cin >> str;
            QString st=ui->text1->toPlainText();
            strcpy(str, st.toStdString().c_str());


        ui->text2->setText(d9.Encrypt(str));
    }


}




//****ONClick event for Ceaser Cypher***********************************//////
void Encrption::on_radioButton_4_clicked()
{

}






//////**************Onclick event of RSA algo***************************///////
void Encrption::on_radioButton_clicked()
{

}

void Encrption::on_radioButton_6_clicked()
{

}



void Encrption::on_radioButton_3_clicked()
{

}

void Encrption::on_pushButton_2_clicked()
{
    if(ui->radioButton->isChecked()){
        decrypt();
        string qe="";
        for(int i=0;m[i]!=-1;i++){
           qe=qe+(char)m[i];
        }
        QString qw = QString::fromStdString(qe);
        ui->text1->setText(qw);
    }
    else if(ui->radioButton_6->isChecked()){

        Des d2;
        char *str=new char[10000];

        QString st=ui->text2->toPlainText();
        strcpy(str, st.toStdString().c_str());

        ui->text1->setText(d2.Decrypt(str));

    }
    else if(ui->radioButton_4->isChecked()){
        QString dd;
        QMessageBox errorBox;
        errorBox.setText("Please Enter a value less than 26");
        dd=ui->text2->toPlainText();
        std::string ct = dd.toLocal8Bit().constData();
        long int s=p=(ui->key2->toPlainText()).toLong();
        if(s>26) errorBox.exec();
        else{
        string result=decryptCeaser(ct, s);

        QString qw = QString::fromStdString(result);
        ui->text1->setText(qw);}
    }
    else if(ui->radioButton_3->isChecked()){

        QByteArray decryptedData;


            decryptedData = blowfish.decrypt( QByteArray::fromBase64( QByteArray( ui->text2->toPlainText().toUtf8() ) ) );


        ui->text1->setHtml( decryptedData );
    }

}

void Encrption::on_pushButton_3_clicked()
{
    FileEncrypt *enc=new FileEncrypt();
    this->hide();
    enc->show();


}

