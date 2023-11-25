#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<MMsystem.h>

int main(){
	
	int difficulty, random, i = 0, j = 0, flag, gcontrol = 0, gscore = 0, musicControl = 1;
	int gsatir, gsutun, gsatir2, gsutun2, remembering, globnum, randcontrol;
	int board[8][8], numberList[32] ={0}, csatir, csatir2, csutun, csutun2, cscore = 0, scorecontrol1;
	int gsum = 0, csum = 0, lremember[8] = {0}, lremember2[8] = {0}, cremember[8] = {0}, cremember2[8] = {0};
	
	while(musicControl == 1){
	
	// m�zik eklemek i�in, m�zik dosyas� sadece kod dosyas�yla ayn� klas�rdeyse �al���yor
	 PlaySound(TEXT("Tsubasa.wav"),NULL,SND_ASYNC); 
	
	srand(time(NULL)); //her �al��mada farkl� bir tahta olu�turmak i�in
	
	printf("Lutfen oyunun kolay olmasi icin 1,\n orta zorlukta olmasi icin 2,\n zor olmasi icin 3 giriniz: ");
	scanf("%d",&difficulty);
	
	//zorlu�a g�re oyunu kurmak i�in
	
	if(difficulty == 1){
		globnum = 4;
		remembering = 1;
	}
	
	else if(difficulty == 2){
		globnum = 6;
		remembering = 3;
	}
	
	else if(difficulty == 3){
		globnum = 8;
		remembering = 8;
	}
	
	else{
		printf("Yanlis sayiyi girdiniz!\n");
	}
	
	scorecontrol1 = (globnum * globnum) / 4;
	randcontrol = (globnum * globnum) / 2;
		
		//y�ld�zlarla kapl� tahtay� olu�turmak i�in
		
		for(i = 0; i < globnum; i++){
			for(j = 0; j < globnum; j++){
				printf("  %2c  ",'*');
			}
				printf("\n");
			}
		printf("\n\n");
		
	//matrise random say� atamak i�in
	
		for(i=0; i<globnum; i++){
			for(j=0; j<globnum; j++){
				flag = 0;
				while(flag == 0){
					random = rand() % randcontrol;
					if(numberList[random] != 2){
						flag = 1;
					}
					else{
						flag = 0;
					}
				}
				board[i][j] = random;
				numberList[random]++;			
			}	
				printf("\n");
		}
		
		//oyuncu ve bilgisayar�n kod blo�u
		
		while(gcontrol == 0 && gscore < scorecontrol1 + 1){ //gcontrol ile s�ran�n oyuncuda olmas�n�, gscore ile de oyuncunun kazanaca�� kesinle�irse oyunun bitmesini ayarlad�m
			printf("\nOyun Sirasi: Oyuncu\n");
			
			printf("Tahmininizdeki satiri giriniz: ");
			scanf("%d",&gsatir);
			printf("Tahmininizdeki sutunu giriniz: ");
			scanf("%d",&gsutun);
			printf("\nBu koordinattaki kart: %d\n",board[gsatir-1][gsutun-1]);
			
			printf("Tahmininizdeki satiri giriniz: ");
			scanf("%d",&gsatir2);
			printf("Tahmininizdeki sutunu giriniz: ");
			scanf("%d",&gsutun2);
			
			while((gsatir == gsatir2) && (gsutun == gsutun2)){ //yap�lan iki tahminde de ayn� noktadaki kartlar� se�memek i�in
				printf("Tahmininizdeki satiri giriniz: ");
				scanf("%d",&gsatir2);
				printf("Tahmininizdeki sutunu giriniz: ");
				scanf("%d",&gsutun2);
			}
			
			printf("\nBu koordinattaki kart: %d\n",board[gsatir2-1][gsutun2-1]);
			
			////girilen tahminleri diziye atay�p son 2 kart� bilgisayar�n hat�rlamas� i�in
			
			int a = 0;
			while(a < remembering && lremember[a] == 0){
				lremember[a] = gsatir;
				a++;
			}
		
			int b = 0;
			while(b < remembering && lremember2[b] == 0){
				lremember[b] = gsatir2;
				b++;
			}
			
			int c = 0;
			while(c < remembering && cremember[c] == 0){
				cremember[c] = gsutun;
				c++;
			}
		
			int d = 0;
			while(d < remembering && cremember2[d] == 0){
				cremember2[d] = gsutun2;
				d++;
			}
			
			//yap�lan tahminlerdeki kartlar� a�mak ve kalan k�s�mlar� y�ld�zlarla doldurmak i�in
			
				if((gsatir >= 1 && gsatir <= globnum) && (gsutun >= 1 && gsutun <= globnum) && (gsatir2 >= 1 && gsatir2 <= globnum) && (gsutun2 >= 1 && gsutun2 <= globnum)) {
				for(i = 0; i < globnum; i++){
					for(j = 0; j < globnum; j++){
						
						if((i == gsatir-1) && (j == gsutun-1) ){
							printf("  %2d  ",board[gsatir-1][gsutun-1]);
						}
						
						else if((i == gsatir2-1) && (j == gsutun2-1) ){
							printf("  %2d  ",board[gsatir2-1][gsutun2-1]);
							}	
					
						else{
							printf("  %2c  ",'*');
						}
					}
					printf("\n");
				}		
					printf("\n\n");
				
				//do�ru tahmin yap�ld���nda skoru artt�rmak, mevcut skoru ekrana bast�rmak i�in
					
				if(board[gsatir-1][gsutun-1] == board[gsatir2-1][gsutun2-1]){
					if((board[gsatir-1][gsutun-1] != -1) && (board[gsatir2-1][gsutun2-1] != -1)) {// e� kartlar tekrar a��l�rsa skor artmas�n diye
						gscore++;
					}
					
					board[gsatir-1][gsutun-1] = -1;
					board[gsatir2-1][gsutun2-1] = -1;
					gcontrol = 0;
					
					if(gscore == scorecontrol1 && cscore == scorecontrol1){
						gcontrol = 2;
					}
					
					printf("\nTebrikler!\n\n");
					printf("Oyuncu %d-%d Bilgisayar\n",gscore,cscore);
				}
				
				//e�le�mi� kartlar� - ile kalan k�sm� * ile bast�rmak i�in
					
				for(i = 0; i < globnum; i++){
					for(j = 0; j < globnum; j++){
						if(board[i][j] == -1){
							printf("  %2c  ",'-');
						}
						else{
								printf("  %2c  ",'*');
							}
				}
				printf("\n");
			}
			
			//yanl�� tahminde s�ran�n bilgisayara ge�mesi i�in
			
				if(board[gsatir-1][gsutun-1] != board[gsatir2-1][gsutun2-1]){
					gcontrol = 1;
					printf("\nOyuncunun dogru tahmin sayisi: %d\n\n",gscore);
				}
				
		 	gsum++; //oyuncunun toplamda ka� tahminde sonuca ula�t���n� bulmak i�in
		}

		while(gcontrol == 1 && cscore < scorecontrol1 + 1){
			
			printf("\nOyun Sirasi: Bilgisayar\n");
			
			csum++; //bilgisayar�n toplamda ka� tahminde sonuca ula�t���n� bulmak i�in
			
			//ilk tahmini alma
			csatir = 1 + rand() % globnum;
			csutun = 1 + rand() % globnum;
			
			//geriye d�n�k kartlar� hat�rlamak ve onlar� se�memek i�in;
			while(i == 0){
				while( (csatir == lremember[i]) && (csutun == cremember[i])) {
					csatir = 1 + rand() % globnum;
					csutun = 1 + rand() % globnum;
				}
				i++;
			}
			
			// - ile g�sterilen kart� se�memek i�in
			while(board[csatir-1][csutun-1] == -1){
				csatir = 1 + rand() % globnum;
				csutun = 1 + rand() % globnum;				
			}
						
			printf("Bilgisayarin tahminindeki satir: %d\n",csatir);
			printf("Bilgisayarin tahminindeki sutun: %d\n",csutun);
			printf("\nBu koordinattaki kart: %d\n\n",board[csatir-1][csutun-1]);
			
			//ikinci tahmini alma
			csatir2 = 1 + rand() % globnum;
			csutun2 = 1 + rand() % globnum;
			
			//geriye d�n�k kartlar� hat�rlamak ve onlar� se�memek i�in
			i = 0;
			while(i == 0){
				while( (csatir2 == lremember2[i]) && (csutun2 == cremember2[i]) ){
					csatir2 = 1 + rand() % globnum;
					csutun2 = 1 + rand() % globnum;
				}
				i++;
			}
			
			//ilk tahmin ile ikinci tahminin ayn� olmamas� ve yap�lan tahminin - ile g�sterilen kart olmamas� i�in
			
			while( ((csatir == csatir2) && (csutun == csutun2)) || (board[csatir2-1][csutun2-1] == -1) ){
				csatir2 = 1 + rand() % globnum;
				csutun2 = 1 + rand() % globnum;
			}
		
			printf("Bilgisayarin tahminindeki satir: %d\n",csatir2);
			printf("Bilgisayarin tahminindeki sutun: %d\n",csutun2);
			printf("\nBu koordinattaki kart: %d\n\n",board[csatir2-1][csutun2-1]);
			
			//yap�lan tahminlerdeki kartlar� a�mak ve kalan k�s�mlar� y�ld�zlarla doldurmak i�in
			
				for(i = 0; i < globnum; i++){
					for(j = 0; j < globnum; j++){			
						if((i == csatir-1) && (j == csutun-1)){
							printf("  %2d  ",board[csatir-1][csutun-1]);
						}
						
						else if((i == csatir2-1) && (j == csutun2-1)){
							printf("  %2d  ",board[csatir2-1][csutun2-1]);
							}	
					
						else{
							printf("  %2c  ",'*');
						}
					}
					printf("\n");
				}
				
				printf("\n\n");
				
				//yap�lan do�ru tahminde skoru artt�rmak, e�le�en kartlar�n yerine - koyabilmek i�in
				
				if(board[csatir-1][csutun-1] == board[csatir2-1][csutun2-1]){
					if((board[csatir-1][csutun-1] != -1) && (board[csatir2-1][csutun2-1] != -1)) {
						cscore++;
					}
				
					board[csatir-1][csutun-1] = -1;
					board[csatir2-1][csutun2-1] = -1;
					gcontrol = 1;
					
					printf("\nTebrikler!\n\n");
					printf("Oyuncu %d-%d Bilgisayar\n",gscore,cscore);
					
					if(gscore == scorecontrol1 && cscore == scorecontrol1){ // beraberlik durumu i�in
						gcontrol = 2;
					}
				}
					// e�le�en kartlar�n yerine - bast�rmak i�in
					
					for(i = 0; i < globnum; i++){
						for(j = 0; j < globnum; j++){
							if(board[i][j] == -1){
							printf("  %2c  ",'-');
						}	
					
						else{
							printf("  %2c  ",'*');
						}
					}
						printf("\n");
					}
				
				// yanl�� tahmin sonucunda s�ran�n oyuncuya ge�mesi ve mevcut skoru bast�rmak i�in
				
				if(board[csatir-1][csutun-1] != board[csatir2-1][csutun2-1]){
					gcontrol = 0;
					printf("\nBilgisayarin dogru tahmin sayisi: %d\n\n",cscore);
					printf("Oyuncu %d-%d Bilgisayar\n",gscore,cscore);
				}
				
				// bilgisayar tahmini yapt�ktan sonra mevcut durumun 2 saniyeli�ine g�sterilip sonra silinmesi i�in
				sleep(2);
				system("cls");
		}
	}
	
	//Oyunun sonucunun ekrana bast�r�lmas� i�in
	
	if(gscore > cscore){
		printf("\nOyuncu %d-%d Bilgisayar\n",gscore,cscore);
		printf("\nOyuncu oyunu kazandi\nToplam tahmin sayisi : %d\n",gsum);
	}
	
	else if(cscore > gscore){
		printf("\nOyuncu %d-%d Bilgisayar\n",gscore,cscore);
		printf("\nBilgisayar oyunu kazandi\nToplam tahmin sayisi : %d\n",csum);
	}
	
	else{
		printf("\nOyuncu %d-%d Bilgisayar\n",gscore,cscore);
		printf("\nBeraberlik\nOyuncunun Toplam tahmin sayisi : %d\nBilgisayarin toplam tahmin sayisi : %d\n",gsum,csum);
	}
	musicControl = 0;
	return 0;
}}
