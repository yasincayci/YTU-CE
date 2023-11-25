#include <stdio.h>
#include <string.h>
#include <ctype.h>  //JIM_SAW_ME_IN_A_BARBERSHOP
#define SIZE 1000
#define totalAsciiNumber 256 // ASCII de toplamda 256 karakter var
//int max (int a, int b) { return (a > b)? a: b; }
 void badCharacterRule(char pattern[SIZE], int patlen, int badCharacterTable[totalAsciiNumber]){
 	int i;
     for (i = 0; i < totalAsciiNumber; i++) // T�m ascii karakterleri i�in atlama say�s� patlen oldu
         badCharacterTable[i] = patlen;

     for (i = 0; i < patlen-1; i++){ // bad character rule a g�re tablonun form�l� length-i-1
         badCharacterTable[(int)pattern[i]] = patlen-i-1;
 	}
 }
 
 // Boyer Moore Arama Algoritmas�
 void search(char text[SIZE], char pattern[SIZE]){
     int patlen = strlen(pattern);
     int textlen = strlen(text);
     int badCharacterTable[totalAsciiNumber];
     
     badCharacterRule(pattern, patlen, badCharacterTable); // �n i�lem yap�l�r
     
	 int shift = 0,i,found = 0,counter = 0; 
     while (shift <= (textlen - patlen)){ // Text in sonuna kadar kayd�rma i�lemi yap�l�r
		 int j = patlen - 1;
         while (j >= 0 && pattern[j] == text[shift + j]) // Text ve pattern tamamen e�le�ene kadar j yi azalt�r 
             j--; // Tamamen e�le�me olursa j -1 e kadar azal�r
         
		 if (j == -1) {
         	found++;
         	counter += patlen; // kar��la�t�rma say�s� patlen kadar artm�� olur
            shift += patlen; // e�le�me durumunda birer birer ilerlemek yerine tek seferde pattern in uzunlu�u kadar ilerlemek gerekir
            if(shift <= textlen){
            	printf("%s\n",text);
				for(i = 0; i < shift; i++)
					printf(" ");
			printf("%s\n",pattern);
			}
         }
         
		 else{ // e�le�meme durumu ger�ekle�mi�, text in pattern ile e�le�meyen harfinin bad character tablosundaki de�eri kadar kayd�rma yapmal�y�z
             counter += patlen - j; // kar��la�t�rma say�s� yanl�� kar��la�t�rma ��kana kadar artm�� olur
             shift += badCharacterTable[(int)text[shift + patlen - 1]];
			 //shift += badCharacterTable[text[shift + j]];
			 //shift += max(1, j-badCharacterTable[text[shift + j]]);
             if(shift <= textlen){
             	printf("%s\n",text);
				for(i = 0; i < shift; i++)
					printf(" ");
			printf("%s\n",pattern);
			}
		}
		
		if(shift > (textlen - patlen)){ // arama k�sm� biterse ekrana karma��kl��� bast�rmak i�in
			printf("Bulunan kelime sayisi: %d\n",found);
			printf("Sayac = %d\nZaman karmasikligi:",counter);
			for(i = 0; i < counter; i++)
			printf("*");
		}
     }
 }
 
 char upper(char ch[SIZE], int number){ // arama esnas�ndaki k���k b�y�k harf hassasiyeti i�in
	int i;
	for(i = 0; i < number; i++){
		if(ch[i] >= 'a' && ch[i] <= 'z')
			ch[i] -= 32;
	}
	return *ch;
 }
 
 void printBadChTable(char pattern[SIZE], int patlen, int badCharacterTable[SIZE]){
 	int i;
 	badCharacterRule(pattern, patlen, badCharacterTable);
 	printf("\n-----------------------------------------\n");
	printf("Bad Character Table\n");
 	for(i = 0; i < patlen; i++)
 		printf("  %c  ",pattern[i]);
 	printf("  *  ");
	printf("\n");
	for(i = 0; i < patlen; i++)
 		printf("  %d  ", badCharacterTable[pattern[i]]);
 	printf("  %d  ",patlen);	
 	printf("\n-----------------------------------------\n");	
 }
	
 int main(){
 	
 	int badCharacterTable[SIZE];
	char text[SIZE],pattern[SIZE];
    
	printf("Text i giriniz: ");
	gets(text); 
	int textlen = strlen(text);
	upper(text,textlen);
	
	printf("Pattern i giriniz: ");
	gets(pattern);
	int patlen = strlen(pattern);
	upper(pattern,patlen);
	
	printBadChTable(pattern,patlen,badCharacterTable);
	printf("%s\n%s\n",text,pattern);
    search(text, pattern);
    
	return 0;
 }
 
 /*
 #include <stdio.h>
#include <string.h> //JIM_SAW_ME_IN_A_BARBERSHOP
#include <ctype.h>
#define SIZE 1000
#define totalAsciiNumber 256 // ASCII de toplamda 256 karakter var
//int max (int a, int b) { return (a > b)? a: b; }
 void badCharacterRule(char pattern[SIZE], int patlen, int badCharacterTable[totalAsciiNumber]){
 	int i;
     for (i = 0; i < totalAsciiNumber; i++) // T�m ascii karakterleri i�in atlama say�s� patlen oldu
         badCharacterTable[i] = patlen;

     for (i = 0; i < patlen-1; i++){ // bad character rule a g�re tablonun form�l� length-i-1
         badCharacterTable[(int)pattern[i]] = patlen - i - 1;
 	}
 }
 
 // Boyer Moore Arama Algoritmas�
 void search(char text[SIZE], char pattern[SIZE]){
     int patlen = strlen(pattern);
     int textlen = strlen(text);
     int badCharacterTable[totalAsciiNumber];
     
     badCharacterRule(pattern, patlen, badCharacterTable); // �n i�lem yap�l�r
     
	 int shift = 0,i,found = 0,counter = 0; 
     while (shift <= (textlen - patlen)){ // Text in sonuna kadar kayd�rma i�lemi yap�l�r
		 int j = patlen - 1;
         while (j >= 0 && pattern[j] == text[shift + j]) // Text ve pattern tamamen e�le�ene kadar j yi azalt�r 
             j--; // Tamamen e�le�me olursa j -1 e kadar azal�r
         
		 if (j == -1) {
         	found++;
         	counter += patlen; // kar��la�t�rma say�s� patlen kadar artm�� olur
            shift += patlen; // e�le�me durumunda birer birer ilerlemek yerine tek seferde pattern in uzunlu�u kadar ilerlemek gerekir
            if(shift <= textlen){
            	printf("%s\n",text);
				for(i = 0; i < shift; i++)
					printf(" ");
			printf("%s\n",pattern);
			}
         }
         
		 else{ // e�le�meme durumu ger�ekle�mi�, text in pattern ile e�le�meyen harfinin bad character tablosundaki de�eri kadar kayd�rma yapmal�y�z
             counter += patlen - j; // kar��la�t�rma say�s� yanl�� kar��la�t�rma ��kana kadar artm�� olur
             shift += badCharacterTable[(int)text[shift + patlen - 1]];
			 //shift += max(1, j-badCharacterTable[text[shift + j]]);
             if(shift <= textlen){
             	printf("%s\n",text);
				for(i = 0; i < shift; i++)
					printf(" ");
			printf("%s\n",pattern);
			}
		}
		
		if(shift > (textlen - patlen)){ // arama k�sm� biterse ekrana karma��kl��� bast�rmak i�in
			printf("Bulunan kelime sayisi: %d\n",found);
			printf("sayac = %d\nZaman karmasikligi:",counter);
			for(i = 0; i < counter; i++)
			printf("*");
		}
     }
 }
 
 char upper(char ch[SIZE], int number){ // arama esnas�ndaki k���k b�y�k harf hassasiyeti i�in
	int i;
	for(i = 0; i < number; i++){
		if(ch[i] >= 'a' && ch[i] <= 'z')
			ch[i] -= 32;
	}
	return *ch;
 }
 
 void printBadChTable(char pattern[SIZE], int patlen, int badCharacterTable[SIZE]){
 	int i;
 	badCharacterRule(pattern, patlen, badCharacterTable);
 	printf("\n-----------------------------------------\n");
	printf("Bad Character Table\n");
 	for(i = 0; i < patlen; i++)
 		printf("  %c  ",pattern[i]);
 	printf("  *  ");
	printf("\n");
	for(i = 0; i < patlen; i++)
 		printf("  %d  ", badCharacterTable[pattern[i]]);
 	printf("  %d  ",patlen);	
 	printf("\n-----------------------------------------\n");	
 }
	
 int main(){
 	
 	int badCharacterTable[SIZE];
	char text[SIZE],pattern[SIZE];
    
	printf("Text i giriniz: ");
	gets(text); 
	int textlen = strlen(text);
	upper(text,textlen);
	
	printf("Pattern i giriniz: ");
	gets(pattern);
	int patlen = strlen(pattern);
	upper(pattern,patlen);
	
	printBadChTable(pattern,patlen,badCharacterTable);
	printf("%s\n%s\n",text,pattern);
    search(text, pattern);
    
	return 0;
 }
*/

