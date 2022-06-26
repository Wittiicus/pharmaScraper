#include <stdio.h> 

#include <stdlib.h> 

#include <unistd.h> 

#include <string.h> 

#include <errno.h> 

#include <fcntl.h> 

#include <pthread.h> 

#include <sys/types.h> 

#include <sys/stat.h> 

#include "log.h" 

 

int logindex = 0; 

int* logi = &logindex; 

// mutex for log, required by logging functions for  

// thread-safe code 

pthread_mutex_t tlock = PTHREAD_MUTEX_INITIALIZER; 

 

 

 

//#1  

//TODO define and initialize a mutex for person_counter 

pthread_mutex_t dlock = PTHREAD_MUTEX_INITIALIZER; 

 

 

void* conversation(void*); // this is signature for the  

                           // threads starting routine 

 

//#2 

//TODO define a record for person 

//TODO with fields: person index, tid, name, line counter, 

//TODO and done indicating when the person is done with 

//TODO the conversation 

 

typedef struct{
    int Person_Index ; 
    char name[10] ; 
    pthread_t tid ; 
    int line_count ; 
    int done ; 
}PERSON ; 

 

 

//#3 

//TODO define an array of 8 person records 

//TODO define a global variable person_counter indication  

//TODO when all threads are done 

 


PERSON person[8] ; 



int done = 0  ;



FILE* flog = NULL; 

 

 

 

//#4 

//TODO function main 

//TODO check the value of _level being 1 .. 8, if not 

//TODO display an error message using msg() and terminate 

//TODO based on the value of _level display how many 

//TODO personalities are involved. Use msg() for displaying 

//TODO it. 

 

int main() { 

  int* res ;

 

  if ( _level <  1 || _level > 8) { 
      msg("warning");
      return 0 ; 

  } 

 

  else{ 

  int j ; 
for ( j = 0 ; j < _level ; j++) { 

person[j].Person_Index = j ; 

int k ;

k =   snprintf(person[j].name , 10, "Person%d", j)  ; 

person[j].line_count = 0 ;

person[j].tid = -1 ; 

person[j].done = -1 ; 
//msg("person : %d",i );

}

     msg("There are %d Personalities", _level) ; 
     int i ;
     for (i = 0 ; i < _level ; i++){
         printf("%s \n", person[i].name);
     }

  } 

 

//For example if _level is 0, it will display: 

//’the program was compiled with a wrong level’ 
//’permitted levels are 1 .. 8’ 

 

//if _level is 3, it will display: 

//’There are 3 personalities:’ 

//’Person0’ 

//’Person1’ 

//’Person2’ 

 

 

 

 

 

 

 

 

  create_log("assgn2.log"); 

//#5 

//TODO inititalize your table of personalities 



//TODO set the value of done for each person to -1 

 


 

//For example Person2 initialization: 

 

//index = 2; 

//name = Person2; 

//line_count = 0; 

//tid = -1; 

//done = -1; 


//#6 

//TODO set person_counter to 0 

//TODO in a do-while loop while person_counter != 0 

//TODO   in a for loop i = 0 .. _level-1 

//TODO      if i-th person is done, continue 

//TODO      create a thread for 1 line of i-th person  

//TODO      modify the info in the i-the person record 

//TODO   end of for loop 

//TODO   in a for loop i = 0 .. _level-1 

//TODO      if i-th person is done, continue 

//TODO      join thread for i-th person 

//TODO   end of for loop 

//TODO end of do-while loop 

 

 //global variable done as person_counter indication   

 

do { 
int i; 
for(i=0 ; i <  _level; i++ )  

{ 

      if (person[i].done == 1) continue; 
 

       pthread_create( &person[i].tid , NULL,
       &conversation , &person[i]); 

} 

 

     for(i=0 ; i < _level; i++) { 

     if (person[i].done==1) continue; 

     pthread_join(person[i].tid , (void**)&res) ; 


    } 

  } 

while(done != 0); 



 

 

 

 

 

 

 

 

 

 

 

 

 

//#7 

//TODO in a for loop i = 1 .. _level-1 

//TODO    display how many lines i-th person processed 

//TODO end of for loop 

//TODO end of main 

int f = 0 ; 
for( f = 0 ; f < _level ; f++){ 

   msg("%s processed %d lines", person[f].name , person[f].line_count ) ;
   
    

} 

 

return 0; 

 

}// end function main 

 

//for example, it will display: 

//Person Person0 processed 3 lines 

//Person Person1 processed 4 lines 

//Person Person2 processed 5 lines 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

//#8 

//TODO function conversation 

//TODO define void* variable ret and set it to NULL 

//TODO lock mutex dlock   

//TODO get the argument (it is a pointer to person record) 

//TODO if done for this person is -1 (first run) 

//TODO    set done for this person to not done (i.e. 0) 

//TODO    increment the global person_counter 

//TODO prompt the user using msg() for the message 

//TODO read the response using fgets() 

//TODO unlock mutex dlock 

 

void* conversation(void* arg) { 

   
  void* ret = NULL ;

  char line[100]; 

  PERSON* p ; 

  pthread_mutex_lock(&dlock);


  p = (PERSON*) arg; 

 
   if ( p->done == -1) { 

     p->done = 0 ; 

     done++; 

   } 

   

   msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message:", 

       getpid(),pthread_self(),p->Person_Index,p->name); 


   fgets(line, 100 , stdin);

   pthread_mutex_unlock(&dlock);



//#9 

//TODO if the response was "quit" 

//TODO    lock mutex dlock 

//TODO    update done for this person to done (i.e. 1) 

//TODO    decrement the global person_counter 

//TODO    unlock mutex dlock 

//TODO    log a message that this person quit using Msg() 

//TODO    exit the thread with return value ret 

//TODO if the response was not "quit" 

//TODO    log the response using Msg() 

//TODO    update done for this person to not done (i.e. 0)  

//TODO    increment line count for this person 

//TODO    exit the thread with return value ret 

//TODO end of function conversation 

char str1[] = "quit"  ;


if (strcmp(line,str1) == 10) { 

     pthread_mutex_lock(&dlock);

     p->done = 1 ;  

    

     done = done - 1 ;//global variable 
    

     pthread_mutex_unlock(&dlock);

 

     Msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message:\n user quit", 

        getpid,pthread_self(),p->Person_Index,p->name,line); 

    pthread_exit(&ret);


   } 

  

else { 

   Msg("[pid=%u,tid=%u,index=%u,name=%s] Enter Message:\n %s", 

        getpid,pthread_self(),p->Person_Index,p->name,line); 

 

     p->done = 0 ; 

     p->line_count++ ;
    

    

     pthread_exit(&ret) ;

} 

 

}// end function conversation 