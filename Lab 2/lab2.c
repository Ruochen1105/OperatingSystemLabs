#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int main(void) {
  char input[100], array[100];
  int i, head, tail,j, time = 0, sum = 0;
  bool flag = true;
  
  fgets(array, 100, stdin);
  int n = atoi(&array[0]);//number of processes
  
  int r1[n], b1[n], r2[n], b2[n], r3[n], blocked[n], ready[1000], to_add[n];

  head = 0;
  tail = atoi(&array[0]) - 1;
  
  if (atoi(&array[2]) == 1) {
    
    printf("FIFO Scheduling\n");
    
    for (i = 0; i < atoi(&array[0]); i++){
      r1[i] = atoi(&array[4 + 8 * i]);
      b1[i] = atoi(&array[6 + 8 * i]);
      r2[i] = atoi(&array[8 + 8 * i]);
      b2[i] = atoi(&array[10 + 8 * i]);
      r3[i] = 1;
      ready[i] = i;
      blocked[i] = 0;
      to_add[i] = 0;
    }  

    while (flag){
    //for (j = 0; j < 20; j++){
      printf("\nCycle %d:\n", time+1);

      for (i = 0;i < n; i++){//every blocked process proceeds 1
        if (blocked[i] != 0){
          blocked[i] -= 1;
          printf("Process%d is blocked.\n", i+1);
          if (blocked[i] == 0){
            to_add[i] = 1;
            if (b1[i] == 0){
              b2[i] = 0;
            } else {
              b1[i] = 0;
            }
          }
        }
      }

      if (head <= tail){//first ready process runs 1
        if (r1[ready[head]] != 0 && r2[ready[head]] != 0 && r3[ready[head]] != 0){
          printf("Process%d runs.\n", ready[head]+1);
          r1[ready[head]] -= 1;
        } else if (b2[ready[head]] == 0 && r3[ready[head]] == 1){
          printf("Process%d terminates.\n", ready[head]+1);
          r3[ready[head]] = 0;
        } else if (b1[ready[head]] == 0 && r2[ready[head]] != 0 && r3[ready[head]] != 0){
          printf("Process%d runs.\n", ready[head]+1);
          r2[ready[head]] -= 1;
        } 
        for (i = head + 1; i <= tail; i++){//other processes wait
          printf("Process%d is ready.\n", ready[i]+1);
        }
        if (b1[ready[head]] != 0){//check if a "block" is issued
          if (r1[ready[head]] == 0){
            blocked[ready[head]] = b1[ready[head]];
            head += 1;
          }
        } else if (b2[ready[head]] != 0){
          if (r2[ready[head]] == 0){
            blocked[ready[head]] = b2[ready[head]];
            head += 1;
          }
        } else if (r3[ready[head]] == 0){
          head += 1;
        }
      }

      for (i = 0; i < n; i++){//add processes to ready
        if (to_add[i] == 1){
          tail += 1;
          ready[tail] = i;
          to_add[i] = 0;
        }
      }
  
      for (i = 0; i < n; i++){//check if all processes finish
        sum += r3[i];
      }
      if (sum == 0){
        flag = false;
      } else {
        sum = 0;
      }
      time = time + 1;
    }
    
  } else if (atoi(&array[2]) == 2){
    
    printf("Round Robin Scheduling\n");
    
    int q = atoi(&array[4]), last = -1, timer[n];
    printf("Round Robin quantum is %d.\n", q);
    
    for (i = 0; i < atoi(&array[0]); i++){
      r1[i] = atoi(&array[6 + 8 * i]);
      b1[i] = atoi(&array[8 + 8 * i]);
      r2[i] = atoi(&array[10 + 8 * i]);
      b2[i] = atoi(&array[12 + 8 * i]);
      r3[i] = 1;
      ready[i] = i;
      blocked[i] = 0;
      to_add[i] = 0;
      timer[i] = 0;
    }

    while (flag){

      printf("\nCycle %d:\n", time+1);

      for (i = 0;i < n; i++){//every blocked process proceeds 1
        if (blocked[i] != 0){
          blocked[i] -= 1;
          printf("Process%d is blocked.\n", i+1);
          if (blocked[i] == 0){
            to_add[i] = 1;
            if (b1[i] == 0){
              b2[i] = 0;
            } else {
              b1[i] = 0;
            }
          }
        }
      }

      if (head <= tail){//first ready process runs 1
        
        if (r1[ready[head]] != 0 && r2[ready[head]] != 0 && r3[ready[head]] != 0){
          printf("Process%d runs.\n", ready[head]+1);
          timer[ready[head]] += 1;
          r1[ready[head]] -= 1;
        } else if (b2[ready[head]] == 0 && r3[ready[head]] == 1){
          printf("Process%d terminates.\n", ready[head]+1);
          timer[ready[head]] += 1;
          r3[ready[head]] = 0;
        } else if (b1[ready[head]] == 0 && r2[ready[head]] != 0 && r3[ready[head]] != 0){
          printf("Process%d runs.\n", ready[head]+1);
          timer[ready[head]] += 1;
          r2[ready[head]] -= 1;
        }
        
        for (i = head + 1; i <= tail; i++){//other processes wait
          printf("Process%d is ready.\n", ready[i]+1);
        }
        
        if (b1[ready[head]] != 0){//check if a "block" is issued
          if (r1[ready[head]] == 0){
            blocked[ready[head]] = b1[ready[head]];
            timer[ready[head]] = 0;
            head += 1;
          }
        } else if (b2[ready[head]] != 0){
          if (r2[ready[head]] == 0){
            blocked[ready[head]] = b2[ready[head]];
            timer[ready[head]] = 0;
            head += 1;
          }
        } else if (r3[ready[head]] == 0){
          timer[ready[head]] = 0;
          head += 1;
        }
      }

      for (i = 0; i < n; i++){
        if (timer[i] >= q){
          to_add[i] = 1;
          head += 1;
          timer[i] = 0;
        }
      }

      for (i = 0; i < n; i++){//add processes to ready
        if (to_add[i] == 1){
          tail += 1;
          ready[tail] = i;
          to_add[i] = 0;
        }
      }
  
      for (i = 0; i < n; i++){//check if all processes finish
        sum += r3[i];
      }
      if (sum == 0){
        flag = false;
      } else {
        sum = 0;
      }
      time = time + 1;
    }
    
  } else {
    printf("Unrecognizable input.\n");
  }

}