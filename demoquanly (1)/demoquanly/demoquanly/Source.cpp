#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include<Windows.h>
#include<iomanip>
#include<fstream>
using namespace std;
#define dau 40
#define cuoi 3
#define MAX 10
 
typedef char xau[300];
xau mnu[10] = { ">>. Nhap danh sach San Pham ",
                ">>. Liet ke danh sach San Pham  ",
                ">>. Tim kiem San Pham theo ma Hang  ",
                ">>. Liet ke San Pham co Tong Tien lon nhat  ",
                ">>. Liet ke San pham co Tong Tien nho Nhat ",
				">>. Liet ke danh sach San Pham co so luong lon nhat",
                ">>. Tong So Pham da Xuat Het Kho",
				">>. Liet ke cac San Pham Theo Kho",
				">>. Xoa San Pham theo Ma ",
				">>. Thoat",};
 
 //ifstream fi;   // mo file de doc
 //ofstream fo;  // mo file de ghi 
typedef struct tagKho{
    int Ma;
    char TenSanPham[35];
    int ngay, thang, nam;
    float DonGia;
    float SoLuong;
    float TK;
	int Kho;
}Kho,*PKho;
 
typedef struct tagNODE {
	Kho Data;
    tagNODE* Next;
}NODE, *PNODE;
 
typedef struct tagLIST {
    NODE* Dau;
    NODE* Cuoi;
}LISTKho, *PLIST;
 
//Khoi tao NODE
NODE* KhoitaoNode()
{
    NODE* x = (NODE*)malloc(sizeof(NODE));
    if(x == NULL)
    {
        printf("\n Bo nho khong du ");
        return 0;
    }
    x->Next = NULL;
    return x;
}
 
//Khoi tao danh sach LIST Kho
void KhoitaoList(LISTKho* x)
{
    x->Dau = NULL;
    x->Cuoi=NULL;
}
void gotoxy(int x,int y)
{
	COORD cur ={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cur);
}
int textcolor(int color)
{
	HANDLE h;
	h=GetStdHandle(STD_OUTPUT_HANDLE);
	return SetConsoleTextAttribute(h,color);
} 
//Nhap thong tin San Pham
void Nhap (NODE* x)
{	
    char tg[25];
    int a, d, m, y,b;
    float t, c;
	printf("\nNhap Kho: ");		
	scanf_s("%d",&a);
	x->Data.Kho=a;
	fflush(stdin);
    printf("\nNhap ma SanPham: ");
    scanf_s("%d", &b);
    x->Data.Ma = b;
    fflush(stdin);
    printf("Nhap ten SanPham: ");
    gets_s(tg);
	strcpy_s(x->Data.TenSanPham,tg);
    fflush(stdin);
    do
    {
        printf("Nhap Ngay Nhap: ");
        scanf_s("%d", &d);
        fflush(stdin);
    }while(d > 31 || d < 1);
    x->Data.ngay = d;
    do
    {
        printf("Nhap Thang Nhap: ");
        scanf_s("%d", &m);
		/*fi>>m;*/
        fflush(stdin);
    }while(m > 12 || m < 1);
    x->Data.thang = m;
    do
    {
        printf("Nhap Nam Nhap: ");
        scanf_s("%d", &y);
	/*	fi>>y;*/
        fflush(stdin);
    }while(y > 9999 || y < 1000);
    x->Data.nam = y;
    fflush(stdin);
    do
    {
        printf("Nhap Don Gia: ");
        scanf_s("%f", &c);
	/*	fi>>c;*/
    }while(c < 0 );
	x->Data.DonGia = c;
    fflush(stdin);
    do
    {
        printf("Nhap SoLuong: ");
        scanf_s("%f", &t);
	/*	fi>>t;*/
    }while(c < 0 );
	x->Data.SoLuong = t;
	x->Data.TK = (x->Data.DonGia * x->Data.SoLuong);
    fflush(stdin);
    x->Next = NULL;
}
 
//in san pham
void InSP(NODE* p)
{
    cout<<"  _________________________________________________________________________________________________"<<endl;
    cout<<" |        Ten San Pham      |    Ngay Nhap          |    Ma SanPham     |     Tong Tien |   Kho    |"<<endl;
    cout<<" |__________________________|_______________________|___________________|_______________|__________|"<<endl;
    
	cout<<" |"<<setw(5)<<p->Data.TenSanPham<<"                     |"<<setw(10)<<p->Data.ngay<<"/"<<p->Data.thang<<"/"<<p->Data.nam
		<<"      |"<<setw(10)<<p->Data.Ma<<"         |"<<setw(12)<<p->Data.TK<<"   |"<<setw(5)<<p->Data.Kho<<"     |" ; 
		

    cout<<" \n |__________________________|_______________________|___________________|_______________|__________|\n";

}

    
 
// in danh sach San Pham
void InDanhSach(LISTKho x)
{
	
    NODE *p;
    p = x.Dau;
    while(p != NULL)
    {
        InSP(p);
        p = p->Next;
    }
	
}
 
//Them mot NODE vao Cuoi danh sach
void ThemCuoi(LISTKho* x, NODE* t)
{
    if(x->Dau == NULL)
    {
        x->Dau = t;
    }
   else
   {
       x->Cuoi->Next = t;
   }
   x->Cuoi = t;
}
 
// Them mot san pham vao cuoi danh sach
int NhapSP(LISTKho* x)
{
    NODE* a = KhoitaoNode();
    Nhap(a);
    ThemCuoi(x,a);
    return 0;
}
 
//Tim kiem theo Ma San Pham
void TimKiem(LISTKho x , int n)
{
    NODE *p;
    p = x.Dau;
    while(p != NULL)
    {
        if(p->Data.Ma == n)
        {
            InSP(p);
        }else   printf("\n Khong co San Pham dat tieu chuan can tim\n");
        p = p->Next;
    }
}
 
//Xoa 1 Ma San Pham bat ki Theo ma San Pham
int XoaSP(LISTKho *x , int n)
{
    NODE *p = x->Dau;
    NODE *q = NULL;
    while(p != NULL)
    {
        if(p->Data.Ma == n)
            break;
        q = p;
        p = p->Next;
    }
    if(p == NULL) 
		return 0;
    if(q != NULL)
    {
			x->Cuoi = q;
            q->Next = p->Next;
			free(p);
        
    }
    else
    {
        x->Dau = p->Next;
        if(x->Dau == NULL)
        {
            x->Cuoi = NULL;
        }
    }
    return 1;
}
 
//Giai phong bo nho
void giaiphong(LISTKho *x)
{
    NODE *p = x->Dau;
    NODE *a;
   while( p->Next != NULL)
    {
        a = p;
        p = p->Next;
        free(a);
    }
}
 
//In cac San Pham co Tong Tien max
void inSPMax(LISTKho x)
{
    NODE *p; NODE *f;
	f=x.Dau;
    p = x.Dau;
	float max=0;
	while(p!=NULL)
	{
		if(p->Data.TK > max)
		{
			max=p->Data.TK;
			f=p;			
		}	
		p=p->Next;		
	}
	InSP(f);
	
}
 
//In cac San Pham co tong tien min
void inSPMin(LISTKho x)
{
    NODE *p;
	NODE *f;
	f=x.Dau;
    p = x.Dau;
	float min=0;
    while(p != NULL)
    {
        if(p->Data.TK < min)
        {
			min=p->Data.TK;
			f=p;
        }
        p = p->Next;
    }
	InSP(f);
}
 
//Liet ke so Sp co so luong nhap vao kho nhieu nhat
 
void inSPSLLonNhat(LISTKho x)
{
    NODE *p;
	NODE *f;
	f=x.Dau;
    p = x.Dau;
	float max=0;
    while(p != NULL)
    {
		if(p->Data.SoLuong>max)
        {
			max=p->Data.SoLuong;
			f=p;
        } 
        p = p->Next;
    }
	InSP(f);
}
 
//Dem so San Pham Xuat Kho het
void SPHet(LISTKho x)
{
    NODE *p;
    int n = 0;
    p = x.Dau;
    while(p != NULL)
    {
		if(p->Data.DonGia > 0 && p->Data.SoLuong ==0)
        {
            n++;
			InSP(p);
        }
        p = p->Next;
    }
    printf("\n So San Pham Da Xuat Kho het : %d\n", n);
}
 
// Liet ke San pham theo kho
void inSPKho(LISTKho x)
{
    NODE *p;
	int t=0;
    p = x.Dau;
	printf("Nhap kho can Tim ");
	scanf_s("%d",&t);
    while(p != NULL)
    {
		if(p->Data.Kho == t)
        {
            
            InSP(p);
        }else printf("\n Khong co San Pham dat tieu chuan can tim\n");
        p = p->Next;
    }
}

//Ham Tao Danh Sach Tuy chon
int Menu()
{
    int a;
    int Ma;
    LISTKho x;
    KhoitaoList(&x);
    do
    {
        printf("\n Ban chon 1,2,3,4,5");
        printf("\n\nNhap so can chon roi bam enter");
        printf("\n\n\n 1 - Nhap danh sach San Pham");
        printf("\n 2 - Liet ke danh sach San Pham ");
        printf("\n 3 - Tim kiem San Pham theo ma Hang");
        printf("\n 4 - Liet ke San Pham co Tong Tien lon nhat ");
        printf("\n 5 - Liet ke San pham co Tong Tien nho Nhat");
        printf("\n 6 - Liet ke danh sach San Pham co so luong lon nhat");
        printf("\n 7 - Tong So Pham da Xuat Het Kho");
        printf("\n 8 - Liet ke cac San Pham Theo Kho");
        printf("\n 9 - Xoa San Pham theo Ma ");
        printf("\n 0 - Thoat\n");
        scanf_s("%d",&a);
        switch(a)
        {
            case 1:
                {
                    int n;
                    printf("\nNhap so luong SanPham : ");
                    scanf_s("%d",&n);
					//fi>>n;
                    for(int i = 1; i <= n ;i++)
                    {
                        printf("\nNhap San Pham Thu : %d \n",i);
                        NhapSP(&x);
                    }
						/*fi.close();
						fo.close();*/
                    break;
                }
            case 2:
                {
                    InDanhSach(x);
                    break;
                }
            case 3:
                {
                    fflush(stdin);
                    printf("\nNhap Ma San Pham can tim:");
                    scanf_s("%d",&Ma);
                    TimKiem(x ,Ma);
                    break;
                }  
            case 4:
                {
                    inSPMax(x);
                    break;
                }
            case 5:
                {
                    inSPMin(x);
                    break;
                }
            case 6:
                {
                    inSPSLLonNhat(x);
                    break;
                }
            case 7:
                {
                    SPHet(x);
                    break;
                }
            case 8:
                {
                    inSPKho(x);
                    break;
                }
            case 9:
                {
                    fflush(stdin);
                    printf("\nNhap Ma San Pham can xoa:");
                    scanf_s("%d",&Ma);
                    fflush(stdin);
                    XoaSP(&x ,Ma);
					InDanhSach(x);
                    break;
                }
            case 0:
                {
                    break;
                }
            default: printf("\nBan chon sai vui long chon lai!");
        }
    }while(a != 0);
    giaiphong(&x);
    return 1;
}
void inmenu(int vt)
{
    int i;
	system("cls");
    gotoxy(dau,cuoi); textcolor(12);
    _cprintf(" Chuong trinh menu \n  ");
    gotoxy(dau-4,cuoi+1); textcolor(6);
    _cprintf("=======================================");
    for (i=1; i<=MAX; i++)
        {
            if (i==vt) textcolor(2);
            else textcolor(7);
            gotoxy(dau-1,cuoi+1+i); _cprintf(mnu[i-1]);
        }
	gotoxy(dau-5,cuoi+12); textcolor(6);
	   _cprintf("=======================================");
	gotoxy(dau-5,cuoi+12); textcolor(6);
	 _cprintf("  \n   - Nguyen Hoang Duy - \n  ");
	 _cprintf("  \n   - Dang Thanh The - \n  ");
}
 
void menu(int vt,LISTKho x)
{
   int Ma;
	
    
    char c;
    do
    {
        inmenu(vt);
        gotoxy(80,25);
        c=_getch();
        switch (c)
        {
            case 72: vt--; if (vt==0) vt=10; break;
            case 80: vt++; if (vt==11) vt=1; break;
            case 27: exit(0);
        }
    } while (c!=13);
    switch (vt)
        {
			
			case 1: system("cls"); 
				{
                    int n;      
					printf("nhap so san pham: ");
					scanf_s("%d",&n);
					printf_s("so luong san pham: %d ", n);
                    for(int i = 1; i <= n ;i++)
                    {
                        printf("\nNhap San Pham Thu : %d \n",i);
                        NhapSP(&x);
                    }
					_getch();
                }
				menu(vt,x); break;
            case 2: system("cls"); 
				{
					InDanhSach(x);
					_getch();
				}
				menu(vt,x); break;
            case 3: system("cls"); 
                    fflush(stdin);
                    printf("\nNhap Ma San Pham can tim:");
                    scanf_s("%d",&Ma);
					TimKiem(x ,Ma); _getch();menu(vt,x); break;
			case 4: system("cls");inSPMax(x);_getch(); menu(vt,x); break;
			case 5: system("cls"); inSPMin(x); _getch();menu(vt,x); break;
			case 6: system("cls"); inSPSLLonNhat(x);_getch(); menu(vt,x); break;
			case 7: system("cls"); SPHet(x); _getch();menu(vt,x); break;
			case 8: system("cls"); inSPKho(x); _getch();menu(vt,x); break;
			case 9: system("cls"); 
                    fflush(stdin);
                    printf("\nNhap Ma San Pham can xoa:");
                    scanf_s("%d",&Ma);
                    fflush(stdin);
                    XoaSP(&x,Ma);
					InDanhSach(x);_getch(); menu(vt,x); break;
            case 10: exit(0);
        }
}


void main()
{
	LISTKho x;
	KhoitaoList(&x);
	menu(1,x);
	
   // Menu();
	
	system("PAUSE");
}