#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "osqueue.h"
#include "threadPool.h"


/******************************************************************************/
/**************************[TASKS FUNCTIONS START]*****************************/
/******************************************************************************/

typedef struct awesomeContainer
{
   int awesomeNum;
   char* awesomeString;
}AwesomeContainer;

void printStart()
{
   char* start = " _______ _______ _______ ______ _______ \n|       |       |   _   |    _ |       |\n|  _____|_     _|  |_|  |   | ||_     _|\n| |_____  |   | |       |   |_||_|   |  \n|_____  | |   | |       |    __  |   |  \n _____| | |   | |   _   |   |  | |   |  \n|_______| |___| |__| |__|___|  |_|___|  ";
   char* test = " _______ _______ _______ _______ \n|       |       |       |       |\n|_     _|    ___|  _____|_     _|\n  |   | |   |___| |_____  |   |  \n  |   | |    ___|_____  | |   |  \n  |   | |   |___ _____| | |   |  \n  |___| |_______|_______| |___|  ";
   printf("%s\n", test);
   printf("%s\n", start);
}


void printEnd()
{
   char* end = " _______ __    _ ______  \n|       |  |  | |      | \n|    ___|   |_| |  _    |\n|   |___|       | | |   |\n|    ___|  _    | |_|   |\n|   |___| | |   |       |\n|_______|_|  |__|______| ";
   char* test = " _______ _______ _______ _______ \n|       |       |       |       |\n|_     _|    ___|  _____|_     _|\n  |   | |   |___| |_____  |   |  \n  |   | |    ___|_____  | |   |  \n  |   | |   |___ _____| | |   |  \n  |___| |_______|_______| |___|  ";
   printf("%s\n", test);
   printf("%s\n", end);
}

void hello(void* a)
{
   printf("hello\n");
}

void doMediumTask()
{
   int j;
   for(j=0; j<1000; j++)
   {
      short i;
      for (i=1; i != 0; i++)
      {
         ;
      }
   }
}

void doLongTask(void* a)
{
   long i;
   for (i=0; i < 60; i++)
   {
      sleep(1);
   }
   if (a==NULL)
   {
      return;
   }
   AwesomeContainer* con = (AwesomeContainer*)(a);
   con->awesomeNum = 1; // for success
}

void halt()
{
   int i;
   for (i = 0; i < 10; i++) doMediumTask();
}

void printingProgressBar()
{
   printf("\n");
   char* line1 = "||||| 20%% *___*";
   char* line2 = "|||||||||| 40%% *___*";
   char* line3 = "||||||||||||||| 60%% *___*";
   char* line4 = "|||||||||||||||||||| 80%% *___*";
   char* line5 = "||||||||||||||||||||||||| 100%% *___*";

   char* text[5] = {line1,line2,line3,line4,line5};
   //print text
   int i;
   for (i = 0; i < 5; ++i)
   {
      doMediumTask();
      doMediumTask();
      doMediumTask();
      doMediumTask();
      printf("\033[1A");
      printf("\r");
      printf("%s\n",text[i]);
   }
      doMediumTask();
      doMediumTask();
      doMediumTask();
      doMediumTask();
}

void doLongTaskWithPrint(void* a)
{
   printf("Doing a long task.. give me a break\n");
   long i;
   doLongTask(NULL);
   printingProgressBar();
   if (a==NULL)
   {
      printf("Finished long task.. carry on\n");
      printf("\n");
      return;
   }
   AwesomeContainer* con = (AwesomeContainer*)(a);
   con->awesomeNum = 1; // for success
   printf("Finished long task.. carry on\n");
   printf("\n");
}

void doMediumTaskWithPrint(void* a)
{
   printf("Doing a medium task\n");
   doMediumTask();
   if (a==NULL)
   {
      return;
   }
   AwesomeContainer* con = (AwesomeContainer*)(a);
   con->awesomeNum = 1; // for success
}

void awesomePrint(void* a)
{
   printf("\n");
   printf("\n");
   AwesomeContainer* con = (AwesomeContainer*)(a);
   int i;
   char* stars = "****************************";
   for(i=0 ; i<con->awesomeNum ; ++i)
   {
      printf("%s\n",stars);
      doMediumTask();
   }
   printf("\n");
   printf("%s\n",con->awesomeString);
   printf("\n");
   for(i=0 ; i<con->awesomeNum ; ++i)
   {
      printf("%s\n",stars);
      doMediumTask();
   }
   printf("\n");
   printf("\n");
}

int fibonaciAux(int n)
{
   if (n < 2)
   {
      return n;
   }
   return fibonaciAux(n-1) + fibonaciAux(n-2);
}

void fibonaci(void* n)
{
   int num = *((int*)(n));
   printf("Calculating Fibonaci of %d\n",num);
   int res = fibonaciAux(num);

   int i;
   for (i = 0; i < 20; i++) doMediumTask();
   printf("Fibonaci of %d is %d ... apparently\n\n",num,res);
}

void printingCannabisText(void* a)
{
   int i;
   char* line0 = "A bit of reading while your at it...";
   char* cannabisDraw[17] = {"                 0","                00","               0000","   0          000000           0","   00         000000           0","    0000      000000          00","    000000    0000000     00000"," 0     0000000 000000 00000000   0","00      000000 00000 0000000    00","0000     000000 000 000000    0000"," 000000000  0000 0 000 0 000000000","    000000000  0 0 0 00000000000","        000000000000000000000","              000 0 0000","            00000 0  00000","          00       0       00","                    0"};
   char* line1 = "Cannabis is an annual, dioecious, flowering herb.";
   char* line2 = "The leaves are palmately compound or digitate, with serrate leaflets.";
   char* line3 = "The first pair of leaves usually have a single leaflet, the number gradually increasing up to a";
   char* line4 = "maximum of about thirteen leaflets per leaf (usually seven or nine), depending on variety and growing conditions.";
   char* text[5] = {line1,line2,line3,line4};

   printf("\n\n%s\n\n\n",line0);
   for (i = 0; i < 20; i++) doMediumTask();

   //print leaf
   for (i = 0; i < 17; i++){
      printf("%s\n", cannabisDraw[i]);
      doMediumTask();
   }

   //print text
   for (i = 0; i < 4; ++i)
   {
      doMediumTask();
      doMediumTask();
      doMediumTask();
      doMediumTask();
      printf("%s\n",text[i]);
   }
   printf("\n");
   printf("\n");
}

void badfunction(void *a)
{
   //this is a function that should not run,
   //i will only insert it after a destroy was called
   assert(0==1);
}

void printOK()
{
   printf("\n");
   char* line1 = " ___                        ____  _  __                      ___";
   char* line2 = "|  _|                      / __ \\| |/ /                     |_  |";
   char* line3 = "| |                       | |  | | ' /                        | |";
   char* line4 = "| |          TEST         | |  | |  <           PASSED        | |";
   char* line5 = "| |                       | |__| | . \\                        | |";
   char* line6 = "| |_                       \\____/|_|\\_\\                      _| |";
   char* line7 = "|___|                                                       |___|";

   char* text[7] = {line1,line2,line3,line4,line5,line6,line7};

   int i;
   //print text
   for (i = 0; i < 7; ++i)
   {
      printf("%s\n",text[i]);
   }
   printf("\n");
}


/******************************************************************************/
/***************************[TASKS FUNCTIONS END]******************************/
/******************************************************************************/


void test_create_and_destroy()
{
   halt(); //ignore
   ThreadPool* tp1 = tpCreate(3);
   tpDestroy(tp1,1);

   ThreadPool* tp2 = tpCreate(3);
   tpDestroy(tp2,0);

   printOK();
   printf(" \n");
}

void test_thread_pool_sanity()
{
   halt(); //ignore
   int i;

   ThreadPool* tp = tpCreate(3);
   for(i=0; i<5; ++i)
   {
      tpInsertTask(tp,hello,NULL);
   }

   tpDestroy(tp,1);
   printOK();
   printf(" \n");
}

void test_single_thread_many_tasks()
{
   halt(); //ignore
   ThreadPool* tp = tpCreate(1);

   tpInsertTask(tp,doMediumTaskWithPrint,NULL);
   tpInsertTask(tp,doMediumTaskWithPrint,NULL);
   AwesomeContainer con;
   con.awesomeNum = 3;
   con.awesomeString = "betty bought a bit of butter but the butter betty bought was bitter";
   tpInsertTask(tp,awesomePrint,&con);
   tpInsertTask(tp,doMediumTaskWithPrint,NULL);
   tpInsertTask(tp,doMediumTaskWithPrint,NULL);
   int num1 = 10;
   tpInsertTask(tp,fibonaci,&num1);
   int num2 = 20;
   tpInsertTask(tp,fibonaci,&num2);
   int a=0;
   AwesomeContainer con2;
   con2.awesomeNum = 3;
   con2.awesomeString = "Whats your name? my name is Arnio";
   tpInsertTask(tp,awesomePrint,&con2);
   tpInsertTask(tp,printingCannabisText,NULL);
   tpInsertTask(tp,doLongTaskWithPrint,&a);

   tpDestroy(tp,1);
   printOK();
   printf(" \n");
}

void test_many_threads_single_task()
{
   halt(); //ignore
   ThreadPool* tp = tpCreate(50);
   tpInsertTask(tp,doMediumTask,NULL);

   tpDestroy(tp,1);

   printOK();
   printf(" \n");
}

void test_destroy_should_wait_for_tasks_1()
{
   halt(); //ignore
   ThreadPool* tp = tpCreate(10);

   AwesomeContainer con;
   con.awesomeNum = 0;
   con.awesomeString = "DontCare"; // we use only the awesomeNum
   tpInsertTask(tp,doLongTask,&con);

   tpDestroy(tp,1);

   assert(con.awesomeNum==1);
   printOK();
   printf(" \n");
}

void test_destroy_should_wait_for_tasks_2()
{
   halt(); //ignore
   ThreadPool* tp = tpCreate(5);

   AwesomeContainer con;
   con.awesomeNum = 0;
   con.awesomeString = "DontCare"; // we use only the awesomeNum
   tpInsertTask(tp,doLongTask,NULL);
   tpInsertTask(tp,doLongTask,NULL);
   tpInsertTask(tp,doLongTask,NULL);
   tpInsertTask(tp,doLongTask,NULL);
   tpInsertTask(tp,doMediumTask,NULL);
   tpInsertTask(tp,doMediumTask,NULL);
   tpInsertTask(tp,doMediumTask,NULL);
   tpInsertTask(tp,doMediumTask,NULL);
   tpInsertTask(tp,doMediumTask,NULL);
   tpInsertTask(tp,doMediumTask,NULL);
   tpInsertTask(tp,doMediumTask,NULL);
   tpInsertTask(tp,doMediumTask,NULL);
   tpInsertTask(tp,doLongTask,&con);

   tpDestroy(tp,1);

   assert(con.awesomeNum==1);
   printOK();
   printf(" \n");
}

void test_destroy_should_not_wait_for_tasks()
{
   halt(); //ignore
   ThreadPool* tp = tpCreate(4);

      tpInsertTask(tp,doMediumTask,NULL);
      tpInsertTask(tp,doMediumTask,NULL);
      tpInsertTask(tp,doMediumTask,NULL);
      tpInsertTask(tp,doMediumTask,NULL);

   tpDestroy(tp,0);
   printOK();
   printf(" \n");
}

// Once this operation is still taking place no concurrent tpDestroy() are allowed on the same threadPool (PDF)
void test_destroy_twice()
{
   halt(); //ignore
   ThreadPool* tp = tpCreate(5);
   tpInsertTask(tp,doLongTask,NULL);
   tpInsertTask(tp,doLongTask,NULL);

   tpDestroy(tp,1);
   tpDestroy(tp,1);

   printOK();
   printf(" \n");
}

void aux_test_for_agressive(int num)
{
   int i;

   ThreadPool* tp = tpCreate(num);
   for(i=0; i<num; ++i)
   {
      tpInsertTask(tp,doMediumTask,NULL);
   }
   tpDestroy(tp,1);
   int precent = num*5;
   char bar[43];
   int j;
   for (j = 0; j < 42; j++)
   {
      if (j==0) {
         bar[j] = '[';
      } else if (j>=1 && j<=num*2){
         bar[j] = '=';
      } else if (j>num*2 && j<=40){
         bar[j] = ' ';
      } else {
         bar[j] = ']';
      }
   }
   bar[42] = '\0';
   printf("%d%% %s\n",precent, bar);
   printf("\033[1A");
   printf("\r");
}

void test_agressive()
{
   halt(); //ignore
   //repeat the same test many times to check for rare cases
   int i;
   for (i = 1; i <= 20; ++i)
   {
      aux_test_for_agressive(i);
   }
   printOK();
   printf(" \n");
}

void test_insert_task_after_destroy_1()
{
   halt(); //ignore
   ThreadPool* tp = tpCreate(5);
   tpInsertTask(tp,doMediumTask,NULL);
   tpInsertTask(tp,doMediumTask,NULL);

   tpDestroy(tp,1);

   tpInsertTask(tp,badfunction,NULL);

   printOK();
   printf(" \n");
}

void test_insert_task_after_destroy_2()
{
   halt(); //ignore
   ThreadPool* tp = tpCreate(5);
   tpInsertTask(tp,doMediumTask,NULL);
   tpInsertTask(tp,doLongTask,NULL);

   tpDestroy(tp,0);

   tpInsertTask(tp,badfunction,NULL);

   printOK();
   printf(" \n");
}

void aux_test_thread_pool_inside_thread_pool(void *a)
{
   halt();
   printf("\033[15A%s\n",((AwesomeContainer*)(a))->awesomeString);
   ThreadPool* tp = tpCreate(3);
   int i;
   for(i=0; i<5; ++i)
   {
      tpInsertTask(tp,doMediumTask,NULL);
   }
   tpInsertTask(tp,doLongTask,(AwesomeContainer*)(a));
   tpDestroy(tp,1);
}
void test_thread_pool_inside_thread_pool_1()
{
   //more threads then tasks
   printf("were gonna make a tree of thread pools! oh yeah\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
   halt();//ignore

   char* tree1 = "                            A\n                           d$b\n                         .d\\$$b.\n                       .d$i$$\\$$b.\n                          d$$@b\n                         d\\$$$ib\n                       .d$$$\\$$$b\n                     .d$$@$$$$\\$$ib.\n                         d$$i$$b\n                        d\\$$$$@$b\n                     .d$@$$\\$$$$$@b.\n                   .d$$$$i$$$\\$$$$$$b.\n                           ###\n                           ###\n                           ###";
   char* tree2 = "                            A\n                           d$b\n                         .d\\$$b.\n                       .d$i$$\\$$b.\n                          d$$@b\n                         d\\$$$ib\n      |                .d$$$\\$$$b\n    \\|/|/            .d$$@$$$$\\$$ib.\n  \\|\\\\|//|/              d$$i$$b\n   \\|\\|/|/              d\\$$$$@$b\n    \\\\|//            .d$@$$\\$$$$$@b.\n     \\|/           .d$$$$i$$$\\$$$$$$b.\n     \\|/                   ###\n      |                    ###\n_\\|/__|_\\|/____\\|/_        ###";
   char* tree3 = "                            A\n                           d$b\n                         .d\\$$b.\n                       .d$i$$\\$$b.\n                          d$$@b\n                         d\\$$$ib\n      |                .d$$$\\$$$b               |\n    \\|/|/            .d$$@$$$$\\$$ib.          \\|/|/\n  \\|\\\\|//|/              d$$i$$b            \\|\\\\|//|/\n   \\|\\|/|/              d\\$$$$@$b            \\|\\|/|/\n    \\\\|//            .d$@$$\\$$$$$@b.          \\\\|//\n     \\|/           .d$$$$i$$$\\$$$$$$b.         \\|/\n     \\|/                   ###                 \\|/\n      |                    ###                  |\n_\\|/__|_\\|/____\\|/_        ###            _\\|/__|_\\|/____\\|/_";

   ThreadPool* tp = tpCreate(8);
   AwesomeContainer con1;
   con1.awesomeNum = 0;
   con1.awesomeString = tree1; // we use only the awesomeNum
   tpInsertTask(tp,aux_test_thread_pool_inside_thread_pool,&con1);


   AwesomeContainer con2;
   con2.awesomeNum = 0;
   con2.awesomeString = tree2; // we use only the awesomeNum
   tpInsertTask(tp,aux_test_thread_pool_inside_thread_pool,&con2);


   AwesomeContainer con3;
   con3.awesomeNum = 0;
   con3.awesomeString = tree3; // we use only the awesomeNum
   tpInsertTask(tp,aux_test_thread_pool_inside_thread_pool,&con3);


   tpDestroy(tp,1);
   assert(con1.awesomeNum==1);
   assert(con2.awesomeNum==1);
   assert(con3.awesomeNum==1);
   printOK();
   printf(" \n");
}
void test_thread_pool_inside_thread_pool_2()
{
   printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
   halt(); //ignore

   char* tree1 = "                            A\n                           d$b\n                         .d\\$$b.\n                       .d$i$$\\$$b.\n                          d$$@b\n                         d\\$$$ib\n                       .d$$$\\$$$b\n                     .d$$@$$$$\\$$ib.\n                         d$$i$$b\n                        d\\$$$$@$b\n                     .d$@$$\\$$$$$@b.\n                   .d$$$$i$$$\\$$$$$$b.\n                           ###\n                           ###\n                           ###";
   char* tree2 = "                            A\n                           d$b\n                         .d\\$$b.\n                       .d$i$$\\$$b.\n                          d$$@b\n                         d\\$$$ib\n      |                .d$$$\\$$$b\n    \\|/|/            .d$$@$$$$\\$$ib.\n  \\|\\\\|//|/              d$$i$$b\n   \\|\\|/|/              d\\$$$$@$b\n    \\\\|//            .d$@$$\\$$$$$@b.\n     \\|/           .d$$$$i$$$\\$$$$$$b.\n     \\|/                   ###\n      |                    ###\n_\\|/__|_\\|/____\\|/_        ###";
   char* tree3 = "                            A\n                           d$b\n                         .d\\$$b.\n                       .d$i$$\\$$b.\n                          d$$@b\n                         d\\$$$ib\n      |                .d$$$\\$$$b               |\n    \\|/|/            .d$$@$$$$\\$$ib.          \\|/|/\n  \\|\\\\|//|/              d$$i$$b            \\|\\\\|//|/\n   \\|\\|/|/              d\\$$$$@$b            \\|\\|/|/\n    \\\\|//            .d$@$$\\$$$$$@b.          \\\\|//\n     \\|/           .d$$$$i$$$\\$$$$$$b.         \\|/\n     \\|/                   ###                 \\|/\n      |                    ###                  |\n_\\|/__|_\\|/____\\|/_        ###            _\\|/__|_\\|/____\\|/_";

   ThreadPool* tp = tpCreate(3);

   AwesomeContainer con1;
   con1.awesomeNum = 0;
   con1.awesomeString = tree1; // we use only the awesomeNum
   tpInsertTask(tp,aux_test_thread_pool_inside_thread_pool,&con1);


   AwesomeContainer con2;
   con2.awesomeNum = 0;
   con2.awesomeString = tree2; // we use only the awesomeNum
   tpInsertTask(tp,aux_test_thread_pool_inside_thread_pool,&con2);


   AwesomeContainer con3;
   con3.awesomeNum = 0;
   con3.awesomeString = tree3; // we use only the awesomeNum
   tpInsertTask(tp,aux_test_thread_pool_inside_thread_pool,&con3);
   tpInsertTask(tp,aux_test_thread_pool_inside_thread_pool,&con3);
   tpInsertTask(tp,aux_test_thread_pool_inside_thread_pool,&con3);
   tpInsertTask(tp,aux_test_thread_pool_inside_thread_pool,&con3);
   tpInsertTask(tp,aux_test_thread_pool_inside_thread_pool,&con3);

   tpDestroy(tp,1);
   assert(con1.awesomeNum==1);
   assert(con2.awesomeNum==1);
   assert(con3.awesomeNum==1);
   printOK();
   printf(" \n");
}


int main()
{
   printStart();
   printf("\n");


   printf("test_create_and_destroy...\n");
   test_create_and_destroy();


   printf("test_thread_pool_sanity...\n");
   test_thread_pool_sanity();


   printf("test_agressive, this might take a while...\n");
   test_agressive();


   printf("test_single_thread_many_tasks...\n");
   test_single_thread_many_tasks();


   printf("test_many_threads_single_task...\n");
   test_many_threads_single_task();


   printf("test_destroy_should_wait_for_tasks #1 (more threads then tasks)...\n");
   test_destroy_should_wait_for_tasks_1();


   printf("test_destroy_should_wait_for_tasks #2 (more tasks then threads)...\n");
   test_destroy_should_wait_for_tasks_2();


   printf("test_destroy_should_not_wait_for_tasks...\n");
   test_destroy_should_not_wait_for_tasks();


   printf("test_destroy_twice...\n");
   test_destroy_twice();


   printf("test_insert_task_after_destroy #1...\n");
   test_insert_task_after_destroy_1();


   printf("test_insert_task_after_destroy #2...\n");
   test_insert_task_after_destroy_2();


   printf("test_thread_pool_inside_thread_pool #1 (more threads then tasks)...\n");
   test_thread_pool_inside_thread_pool_1();


   printf("test_thread_pool_inside_thread_pool #2 (more tasks then threads)...\n");
   test_thread_pool_inside_thread_pool_2();


   printEnd();
   return 0;
}
