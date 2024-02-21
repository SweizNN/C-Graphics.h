#include <iostream>
#include <graphics.h>
#include <math.h>
//İnan Yiğit Oğuz 220202014 Mustafa Efe Tamer 220202084
using namespace std;

void ekranibol()
{
    //x koordinati boyunca 10br karelik karelere boluyoruz
    for(int v=0; v<=getmaxx(); v=v+10)
    {
        setcolor(8);
        line(v,0,v,getmaxx());

    }
    //ykoordinati boyunca 10br karelik karelere boluyoruz
    for(int b=0; b<=getmaxy(); b=b+10)
    {
        setcolor(8);
        line(0,b,getmaxy(),b);
    }
    setlinestyle(SOLID_LINE,1,2);

}


int main()
{
    system("COLOR 5");
    system("curl http://bilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt > koordinatlar.txt");//link buraya girilcek konsola yazdýrma
    printf("\n\nKoordinatlar sisteme yuklendi\n\n");

    // koordinatlar.txt metin belgesinin içindeki verileri çekiyoruz
    int i=0;
    char karakterler[1000];
    FILE *hedefDosya;
    char karakter;
    if((hedefDosya=fopen("koordinatlar.txt","r"))!=NULL)//dosyayi okuma modunda aciyoruz

    {
        //tum karakterleri tek tek diziye atar
        karakter=fgetc(hedefDosya);
        while(karakter!=EOF)
        {
            karakterler[i]=karakter;
            printf("%c",karakter);
            karakter=fgetc(hedefDosya);
            i++;
        }
    }
    else
    {
        printf("Dosya bulunamadi");
    }
    int j=0;
    char str1[1000];
    int bsayac=0;

    int satir;
    printf("\n\nSatir giriniz: ");
    scanf("%d",&satir);

    while(true)//karakterler dizisindeki B sayısını bulur
    {
        if(karakterler[j]=='B')
        {
            bsayac++;
        }
        if(satir==bsayac)
        {
            break;
        }
        j++;
    }

    if(bsayac==satir)
    {
        initwindow(800,800,"pencere");
        //1 satirin tamamini str1 dizisien atar
        int i=0;
        while(karakterler[j]!='F')
        {
            str1[i]=karakterler[j];
            j++;
            i++;
        }

        // str1[] dizisini konsola yazdiriyoruz
        for(int k=1; k<i; k++)
        {
            printf("%c",str1[k]);
        }
        // str1[] dizisini atoi fonksiyonu ile x koordinatlarini ve y koordinatlarini ayri ayri tutuyoruz
        int xkoor[300];
        int ykoor[300];
        int t=0;
        int p=0;
        int sekilKoord[20];
        int sekilKoordSayac=0;
        for(int h=0; h<=strlen(str1); h++)
        {
            if(str1[h]=='(')
            {
                xkoor[t]=atoi(&str1[h+1]);//acma parantezi gorunce bir sonraki indeksteki elemani x dizisine atar
                t++;
            }
            if(str1[h]==')')
            {
                if(str1[h-2]==',')//kapama parantezinden 2 indeks sonra virgul varsa tek basamakli sayi oldugunu bulur
                {
                    ykoor[p]=atoi(&str1[h-1]);
                    p++;
                }
                else//virgul yoksa 2 basamakli sayi vardir
                {
                    ykoor[p]=atoi(&str1[h-2]);
                    p++;
                }
            }
        }
        printf("\n\n");
        // xkoor ve ykoor dizilerini okuyoruz
        int topnoktasayisi=0;//kac tane x koordinati varsa o kadar nokta vardir
        for(int y=0; y<t; y++)
        {
            printf("%d,",xkoor[y]);
            topnoktasayisi++;
            printf("%d\t",ykoor[y]);

        }

        printf("\n\n");

        ekranibol();

        int sekilsay=0;
        int j=3;//bunun sebebi ucgen olmasi icin min 3. indeksten aramaya baslamasi gerekir
        int k=0;
        int u=0;
        double alan;
        while(k<topnoktasayisi)
        {
            while(j<=topnoktasayisi)
            {
                if(xkoor[k]==xkoor[j] && ykoor[k]==ykoor[j])//sekil sayisini ve sekillerin hangi koor baslayip sonlandigini bulur
                {
                    int q=k;
                    setcolor(13);
                    sekilKoordSayac=0;
                    while(q<=j)
                    {
                        //x ve y yi tek bir diziye attik sekilKoord dizisi
                        sekilKoord[sekilKoordSayac]=xkoor[q]*10;//seklin koordinatlarini 10 katini alip diziye atar drawpoly icin
                        sekilKoord[sekilKoordSayac+1]=ykoor[q]*10;
                        sekilKoordSayac+=2;//koordinatlarin indeksini arttirir
                        q++;
                    }
                    drawpoly(sekilKoordSayac,sekilKoord);
                    setfillstyle(SOLID_FILL,sekilsay+1);
                    fillpoly(sekilKoordSayac/2,sekilKoord);//icini boyama
                    sekilsay++;

                    //alan
                    alan=0;//her seferinde alani 0 lamasi icin if icinde
                    while(u<j)
                    {
                        alan+=((xkoor[u]*ykoor[u+1])-(ykoor[u]*xkoor[u+1]));//matrislerde determinant bulma mantigi
                        u++;
                    }
                    alan=alan/2.0;
                    printf("\nalan: %lf\n",alan);
                    printf("\nKaynak rezerv alani: %lf\n",alan*10);
                    break;
                }
                j++;
            }

            k=j+1;//bir sonraki seklin indeksi burda baslar
            j=j+3;//bir sonraki sekil en kucuk ucgen olabilicegi icin 3 nokta sonradan aramaya baslar
            u=k;//seklin baslangic indeksinden itibaren alanini hesaplamasi icin
        }
        printf("Sekil sayisi: %d",sekilsay);
    }

//klavyeden bir karakter alinca grafik penceresi kapanir
    getch();
    closegraph();

    return 0;
}
