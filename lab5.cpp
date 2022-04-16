#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <math.h>
using namespace std;

struct memory {
    int free;   //объем свободной памяти
    int largest = 1;    //размер наибольшего свобожного блока 
    int satisfied; //количество удовлетворённых запросов (%)
} M;

struct process {
    int number;
    char name[10]; //имя процесса
    int size; //размер блока
} P[20], P_buff[20], SP[20];

int main(){

    int tick, tick_1, tick_2, block_number; //выбор
    int number = 0, i, tmp, tmp_buff, queue = 0, size_buff, n, sp, min_proc, min_size, min_kol, min_kol_summ, min_index;  //хранилище
    int memory_free, memory_occupied = 0, volume;  //работа с памятью
    char block_name[10];

    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    
    puts("Введите размер памяти (цифрой до 32): ");
    scanf("%d", &volume);
    if(volume != 0)
    {
    	if(volume >0 && volume <= 32)
    	{
    			for(i=0; i<volume; i++)
				{
					strcpy(P_buff[i].name, "");
					P_buff[i].size = 0;
		        }
	    		memory_free = volume;
		        while(tick!=5)
		        {
		        	printf("\n");
		            puts("------------------");
		            puts("       МЕНЮ       ");
		            puts("------------------");
		            puts(" 1) Выделить память для процесса");
		            puts(" 2) Вывести процессы (состояние памяти)");
		            puts(" 3) Удалить процесс");
		            puts(" 4) Выход");
		            puts("------------------");
		            puts("Введите пункт меню: ");
		            scanf("%d",&tick);
					printf("\n");
		            if(tick == 1)
		            {
		                number++;
		                getchar();
		                puts("Введите имя и размер блока процесса:");
		                gets(P[number].name);
		                scanf("%d", &P[number].size);
		                getchar();
		                if(P[number].size > 0)
		                {
		                	min_kol = 0;
		                    if(P[number].size > memory_free)
		                    {
		                    	min_size = P[1].size;
		                    	min_proc = 1;
								for(i=1;i<number-queue;i++)
								{
									if(P[i].size < min_size)
									{
										min_proc = i;
									}
								}
								
								for(i=0; i<volume; i++)
								{
									if(strcmp(P_buff[i].name, P[min_proc].name) == 0 || P_buff[i].size == 0)
									{
										min_kol++;
									}
									else
									if(strcmp(P_buff[i].name, P[min_proc].name) != 0 && P_buff[i].size != 0)
									{
										min_kol = 0;
									}

									
									if(min_kol_summ < min_kol)
									{
										min_kol_summ = min_kol;
										min_index = i;
									}
								}
								printf("%d\n", min_proc);
								printf("%d\n",min_kol_summ);
						
								{
						
									printf(" Свопинг процесса %s %d на процесс %s %d\n",P[min_proc].name, P[min_proc].size, P[number].name, P[number].size);
									puts(" Выберите пункт \"2\" в меню, для просмотра процессов");
									min_size = P[number].size;
									for(i=0;i<volume;i++)
									{
										if(strcmp(P_buff[i].name, P[min_proc].name) == 0 && min_size != 0)
										{
											strcpy(P_buff[i].name, P[number].name);
											P[min_proc].size--;
											min_size--;
										}
										else
										if(min_size != 0 && P_buff[i].size == 0)
										{
											strcpy(P_buff[i-1].name, P[number].name);
											P_buff[i].size = 1;
											P[min_proc].size--;
											min_size--;
											memory_occupied++;
											memory_free--;
										}
										else
										if(strcmp(P_buff[i].name, P[min_proc].name) == 0 && min_size == 0 && P[min_proc].size != 0)
										{
											strcpy(P_buff[i].name, "");
											P_buff[i+1].size = 0;
											P[min_proc].size--;
											memory_occupied--;
											memory_free++;
										}
									}
									
									strcpy(P[min_proc].name, P[number].name);
									P[min_proc].size = P[number].size;
									queue++;
									number--;
								}
								else
								{
									puts(" Размер процесса слишком велик, свопинг минимального процесса невозможен!");
									number--;
								}
		                    	
		                    }
		                    else
		                    {
		                        printf("Добавить процесс %s %d? [1 - YES | 2 - NO]\n", P[number].name, P[number].size);
		                        scanf("%d", &tick_1);
		                        if(tick_1== 1)
		                        {
		                            printf("Добавлен процесс: %s %d\n", P[number].name, P[number].size);
		                            
		                            tmp_buff = 0;
		                            size_buff = 0;
		                            for(i=0; i<volume; i++)
		                            {
		                                size_buff += P[i].size;
		                                for(tmp=tmp_buff; tmp<=size_buff; tmp++)
		                                {
		                                    P_buff[tmp] = P[i];
		                                    P_buff[tmp].size = 1;
		                                    tmp_buff = tmp; 
		                                }
		                            }
		
		                            memory_occupied += P[number].size;
		                            memory_free = volume - memory_occupied;
		                        }
		                        else
		                        if(tick_1 == 2)
		                        {
		                            puts(" Запрос отклонен");
		                            number--;
		                        }
		                        else
		                        {
		                            puts(" ERROR! Введена неверная команда. Запрос отклонен");
		                            number--;
		                        }
		                    }
		                }
		                else
		                if(volume == 0)
		                {
		                    puts(" ERROR! Вы ввели символ, букву или 0! Попробуйте ещё раз");
		                    number--;
		                }
		                else
		                {
		                	printf(" ERROR! Размер блока процесса не может быть отрицательным или нулем: %d. Попробуйте ещё раз\n", P[number].size);
		                	number--;
						}
		            }
		            else
		            if(tick == 2)
		            {
		                n=0;
		                M.free = memory_free;
		                if(number == 0)
		                {
		                    M.satisfied = 100;
		                }
		                else
		                {
		                    M.satisfied = (((number - queue) * 100) / (number));
		                }
		
		                for(i=0; i<=volume; i++){
		                    if(P_buff[i].size < 1)
		                    {
		                        M.largest = 0;
		                        n++;
		                    }
		                }
		
		                puts(" №     name    size");
		                for(i=0; i<volume; i++){
		                    if((i+1)/10 == 0)
		                    {
		                    	printf(" %d  %6s  %6d\n", i+1, P_buff[i].name, P_buff[i+1].size);
							}
							else
							{
								printf(" %d  %5s  %6d\n", i+1, P_buff[i].name, P_buff[i+1].size);
							}
		                }
		
		                if(n > 0)
		                {
		                    printf(" Объем памяти: %d\n Объем свободной памяти: %d\n Размер наибольшего свободного блока: %d\n Количество запросов на выделение памяти: %d\n Количество удовлетворенных запросов (%%): %d%%\n", volume, M.free, M.largest, number+queue, M.satisfied);
		                }
		                else
		                {
		                     printf(" Объем памяти: %d\n Объем свободной памяти: %d\n Размер наибольшего свободного блока: Нет свободных блоков\n Количество запросов на выделение памяти: %d\n Количество удовлетворенных запросов (%%): %d%%\n", volume, M.free, number+queue, M.satisfied);
		                }
		            }
		            else
		            if(tick == 3)
		            {
		                puts("1) Освободить 1 блок");
		                puts("2) Удалить весь процесс");
		                puts("3) Очистить всю память");
		                scanf("%d", &tick_2);
		                switch(tick_2){
		                    case 1: getchar();
		                            printf("Введите номер блока (всего блоков: %d):", volume);
		                            scanf("%d", &block_number);
		                            if(block_number <= volume && block_number > 0)
		                            {
			                            strcpy(P_buff[block_number-1].name, " ");
			                            P_buff[block_number].size = 0;
			                            memory_occupied --;
			                            memory_free = volume - memory_occupied;
			                                
			                            for(i=1;i<number; i++)
			                            {
			                                if(strcmp(P[i].name, P_buff[block_number].name) == 0)
			                                {
			                                	P[i].size--;
			                                	break;
											}
										}
			                        }
			                        else
			                        if(block_number == 0)
			                        {
			                        	printf(" ERROR! Введен символ, буква или 0. Попробуйте ещё раз");
									}
									else
			                        {
			                        	
		                                printf(" ERROR! Введено неверное значение блока: %d. Попробуйте ещё раз", block_number);
		                            }
		                            break;
		                    case 2: getchar();
		                            puts("Введите название процесса: ");
		                            gets(block_name);
		                            for(i=0; i<volume; i++)
		                            {
		                                if(strcmp(P_buff[i].name, block_name) == 0)
		                                {
		                                    strcpy(P_buff[i].name, " ");
		                                    memory_occupied --;
		                                    P_buff[i+1].size = 0;
		                                    n++;
		                                }
		                            }
		                             
		                            if(n > 0)
		                            {
			                            memory_free = volume - memory_occupied;
			                            for(i=1;i<=number;i++)
			                            {
			                            	if(strcmp(P[i].name, block_name) == 0)
			                                {
			                                    strcpy(P[i].name, " ");
			                                    P[i].size = 0;
			                                    {
			                                    	strcpy(P[i].name, P[i+1].name);
			                                    	P[i].size = P[i+1].size;
												}
												
												number--;
			                                }
										}
									}
									else
									{
										puts(" ERROR! Введено неверное значение или такого процесса нет. Попробуйте ещё раз\n");
									}
		                            break;
		                    case 3: for(i=0; i<volume; i++)
		                            {
		                                strcpy(P_buff[i].name, " ");
		                                P_buff[i+1].size = 0;
		                            }
		                            memory_occupied = 0;
		                            number = 0;
		                            queue = 0;
		                            memory_free = volume;
		                            break;
		                    default: puts(" ERROR! Введено неверное значение. Попробуйте ещё раз");
		                }
		            }
		            else
		            if(tick == 4)
		            {
		                puts(" Выход из программы");
		                break;
		            }
		            else
		            if(tick == 0)
		            {
		            	puts(" ERROR! Вы ввели букву, символ или 0! Проверьте значение размера памяти и попробуйте ещё раз");
					}
		            else
		            {
		                puts(" ERROR! Введено неверное значение");
		            }
		        }
		    }
		    else
		    {
		    	puts(" ERROR! Введено неверное значение (отрицательные или больше заданного размера памяти). Проверьте значение размера памяти и попробуйте ещё раз");
			}
		  	    	
	}
	else
	{
		puts(" ERROR! Вы ввели букву, символ или 0! Проверьте значение размера памяти и попробуйте ещё раз");
	}
    getchar();
    return(0);
}
