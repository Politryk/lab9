//---------------------------------------------------------------------------
#include "windows.h"
#include "stdio.h"
#include "conio.h"
#pragma hdrstop

#define SIGN "signature"
//---------------------------------------------------------------------------
     // ВОЛЕЮ ХАОСА ЭТОМУ КОДУ ДОНА НЕ ОДНОЗНАЧНОСТЬ!!!
bool CopyFile(char* filename, FILE* input_file);
bool OpenFile(FILE* bin_file);

#pragma argsused
int main(int argc, char* argv[])
{
   if(argc!=2){
    printf("not read!!!");                //Проверка на введенные данные
    getch();
    return 0;
   }

   FILE* input_file;
   input_file = fopen(argv[1],"rt");     //открытие файла для чтения


   if(input_file == NULL){
   printf("file not found!!!");             //Проверка существует ли файл
   getch();
   return 0;
   }

   int len_file = strlen(argv[1]);
   char *file_name = new char[len_file];
   strcpy(file_name,argv[1]);

   bool k = CopyFile(file_name,input_file);

   if(!k){
   getch();
   return 0;
   }

   FILE* bin_file;
   bin_file = fopen(file_name,"rb");     //открытие бинарного файла

   delete file_name;


   if(bin_file == NULL){
   fclose(bin_file);                     //Проверка открыт ли файл
   printf("failed!!!");
   getch();
   return 0;
   }
                                          //Конец проверки

   bool error_list = OpenFile(bin_file);

   if(!error_list){
   getch();
   return 0;
   }

   system("pause");

}


                                                //Функция копирования файла
bool CopyFile(char* file_name, FILE* input_file){

                                               //Формирование пути нового файла
char* pch = strtok(file_name,".");
   strcat(file_name,".bin");

                                                //создание выходного файла
   FILE* output_file;
   output_file = fopen(file_name,"wb");

                                                //Првоерка создан ли файл
   if(output_file == NULL){
   fclose(input_file);
   printf("file not criet");
   return false;
   }

                                                    //Запись сигнатуры
   fwrite(SIGN, sizeof(char),10,output_file);

   char str[256];

   while(1){
   if(fgets(str,256,input_file)==NULL)              //получить строчку из txt
   break;
   int len_str = strlen(str);                      //Узнаем длину строки
   len_str++;
   fwrite(&len_str,sizeof(int),1,output_file);      //записать длину строки
   fwrite(str, sizeof(char),len_str,output_file);    //записать строку в  bin
   }

   fclose(input_file);                            //pзавершение работы с файлами
   fclose(output_file);

   return true;
}


                                                 //Функция открытия файла
bool OpenFile(FILE* bin_file){

                                                 //Считывание сигнатуры
   char sign_this[10];
   fread(sign_this, sizeof(char), 10, bin_file);

                                                  //Проверка сигнатуры файла
   if(strcmp(sign_this,SIGN)!=0){
   fclose(bin_file);
   printf("not my file");
   return false;
   }
                                                   //Конец проверки


                                                 //Считывание бинарного файла
   int n;
   char str_new[4];                          // 4 т.к. 4 байта в типе int
   while(1){

   fread(&n, sizeof(int), 1, bin_file);

   char *scan = new char[n];
   fread(scan,n,1,bin_file);                    //получаем строку

   if(int feof(bin_file)!=0)
   break;

   printf("%s",scan);                          //выводим на экран
   delete scan;
   }

   fclose(bin_file);

   return true;

}
//---------------------------------------------------------------------------
