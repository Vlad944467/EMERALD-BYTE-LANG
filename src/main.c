/*
 * Copyright 2026 Vlad944467
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "gvar.h"
#include "platform.h"
#include "opcodes.h"
#include "lexcompiler.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
char names_r[100][64];
char values_r[100][64];
int count_r = 0;
int err_count=0;
int mov(){
    int idx = arg2[0] - 'a';
    values[idx] = atoi(arg3);
}
int add(){
    int idx = arg2[0] - 'a';
    values[idx] = values[idx] + atoi(arg3);
}
int INT_print(){
    int idx = arg2[0] - 'a';
    printf("%d\n",values[idx]);
}
int sub(){
    int idx = arg2[0] - 'a';
    values[idx] = values[idx] - atoi(arg3);
}
int add_num() {
    int result = atoi(arg2) + atoi(arg3);
    printf("%d\n", result);
}
int subt_num(){
    int result = atoi(arg2) - atoi(arg3);
    printf("%d\n", result);
}
int clear() {
    int idx = arg2[0] - 'a';
    values[idx] = 0;
}
int mul_num() {
    int result = atoi(arg2) * atoi(arg3);
    printf("%d\n", result);
}
int div_num() {
    int result = atoi(arg2) / atoi(arg3);
    printf("%d\n", result);
}
void load_sbc(const char *name) {
    FILE *f = fopen(name, "r");
    if (!f) { puts("Файл не найден"); return; }
    cs = 0;
    int n;
    fscanf(f, "%d", &cs);
    for (int i = 0; i < cs; i++) fscanf(f, "%d", &code[i]);
    fscanf(f,"%d",&arg_i);
    for(int i=0;i<arg_i;i++) {
        fscanf(f,"%s",sa[i]);
        fgetc(f);
        fgets(sb[i],100,f);
        sb[i][strcspn(sb[i],"\n")]=0;
        if(sb[i][0]==' ')memmove(sb[i],sb[i]+1,strlen(sb[i]));
    }
    fclose(f);
}

void save_sbc(const char *name) {
    FILE *f = fopen(name, "w");
    if (!f) { puts("Не удалось создать файл"); return; }
    fprintf(f, "%d\n", cs);
    for (int i = 0; i < cs; i++) {
        fprintf(f, "%d\n", code[i]);
    }
    fprintf(f,"%d\n",arg_i);
    for(int i=0;i<arg_i;i++) fprintf(f,"%s %s\n",sa[i],sb[i]);
    fclose(f);
    printf("Байт-код записан в %s\n", name);
}
int run(){
    pc = 0;
    while (pc < cs) {
        int o = code[pc];
        pc += 3;
        strcpy(arg2, sa[pc/3-1]);
        strcpy(arg3,sb[pc/3-1]);
        strcpy(arg4, sc[pc/3-1]);
        strcpy(arg5,sd[pc/3-1]);
        if(o == OP_MOV){mov();
        }else if(o == OP_ADD){ add();
        }else if(o == OP_SUB){ sub();
        }else if(o == OP_INT_PRINT){ INT_print();
        }else if(o == OP_PRINT_C){ printf("%s\n",arg2);
        }else if(o == OP_ADD_NUM) { add_num();
        }else if(o == OP_SUBT_NUM) { subt_num();
        }else if(o == OP_CLEAR) { clear();
        }else if(o == OP_MUL_NUM) { mul_num();
        }else if(o == OP_DIV_NUM) { div_num();
        }else if(o == OP_STR) {
            int idx = arg2[0] - 'a';
            strcpy(strings[idx], arg3);
        }else if(o == OP_PRINT_STR) {
            int idx = arg2[0] - 'a';
            printf("%s\n", strings[idx]);
        }else if(o == OP_FMOV) {
            int idx = arg2[0] - 'a';
            fval[idx] = atof(arg3);
        }else if(o == OP_PRINTFL) {
            int idx = arg2[0] - 'a';
            printf("%f\n",fval[idx]);
        }else if(o == OP_MOVC) {
            int idx = arg2[0] - 'a';
            fval[idx] = fval[idx] - atof(arg3);
        }else if(o == OP_PRINTC) {
            int idx = arg2[0] - 'a';
            cval[idx] = arg3[0];
        }else if(o == OP_STRLEN) {
            int idx = arg2[0] - 'a';
            printf("%c\n",cval[idx]);
        }else if(o == OP_FADD) {
            int idx = arg2[0] - 'a';
            printf("%zu\n",strlen(strings[idx]));
        }else if(o == OP_INPUT_INT) {
            int idx = arg2[0] - 'a';
            scanf("%d", &values[idx]);
            getchar();
        }else if(o == OP_INPUT_STR) {
            int idx = arg2[0] - 'a';
            scanf("%s", strings[idx]);
            getchar();
        }else if(o == OP_DEC) {
            int idx = arg2[0] - 'a';
            values[idx] = values[idx] - 1;
        }else if(o == OP_INC) {
            int idx = arg2[0] - 'a';
            values[idx] = values[idx] + 1;
        }else if(o == OP_COPY) {
            int idx1 = arg2[0] - 'a';
            int idx2 = arg3[0] - 'a';
            values[idx2] = values[idx1];
        }else if(o == OP_SAVEV) {
            int idx = arg2[0] - 'a';
            FILE *f = fopen("data.txt", "w");
            fprintf(f, "%d", values[idx]);
            fclose(f);
        }else if(o == OP_LOADV) {
            int idx = arg2[0] - 'a';
            FILE *f = fopen("data.txt", "r");
            if (f) {
                fscanf(f, "%d", &values[idx]);
                fclose(f);
            }
        }else if(o == OP_INPUTF) {
            int idx = arg2[0] - 'a';
            scanf("%f", &fval[idx]);
            getchar();
        }else if(o == OP_INPUTC) {
            int idx = arg2[0] - 'a';
            scanf("%c", &cval[idx]);
            getchar();
        }else if(o == OP_IF) {
            int a=0, b = atoi(arg4),istrue = 0;
            if(!strcmp(arg2,"x")) a = values[0];
            if(!strcmp(arg2,"y")) a = values[1];
            if(!strcmp(arg3,">")) istrue=(a > b);
            if(!strcmp(arg3,"<")) istrue=(a < b);
            if(!strcmp(arg3,"==")) istrue=(a==b);
            if(istrue){printf("%s\n",arg5);}
            else{PLATFORM_COLOR_RED();printf("--VM: [ERR]: if: Unknown argument--\n\n");PLATFORM_COLOR_RESET();
                PLATFORM_COLOR_GREEN();printf("--STR:\n %s %s %s %s %s--\n\n", arg1,arg2,arg3,arg4,arg5);PLATFORM_COLOR_RESET();return 1;
            }
        }
        else if(o == OP_REPEAT){
            int count = atoi(arg2);
            if(count <= 0){PLATFORM_COLOR_YELLOW();printf("\n--VM: [WARN]: repeat: bad count: %s--\n\n",arg2);PLATFORM_COLOR_RESET();}
            else if(!strcasecmp(arg3,"print_c")){
                for(int i=0;i < count;i++){ printf("%s\n",arg4); }
            }
            else if(!strcasecmp(arg3,"int_print")){
                int idx = arg4[0] - 'a';
                for(int i=0;i < count;i++){ printf("%d\n",values[idx]); }
            }
            else if(!strcasecmp(arg3,"print_str")){
                int idx = arg4[0] - 'a';
                for(int i = 0;i < count; i+=1){ printf("%s\n", strings[idx]); }
            }
            else{PLATFORM_COLOR_RED();printf("\n--VM: [ERR]: repeat: Unknown argument: %s--\n\n",arg3);PLATFORM_COLOR_RESET();return 1;}
        }
        else if(o == OP_N){puts("\n");}
        else if(o == OP_AC_INT){
            int inn = arg2[0] - 'a';
            int inn2 = arg4[0] - 'a';
            if(arg3[0]=='+'){ values[inn] = values[inn] + values[inn2]; }
            else if(arg3[0]=='-'){ values[inn] = values[inn] - values[inn2]; }
            else if(arg3[0]=='*'){values[inn] = values[inn] * values[inn2];}
            else if(arg3[0]=='/'){
                if(values[inn2]==0){PLATFORM_COLOR_YELLOW();printf("[WARN]: ac_int: Division by zero");PLATFORM_COLOR_RESET();}
                values[inn] = values[inn] / values[inn2];
            }else{PLATFORM_COLOR_RED();printf("\n--VM: [ERR]: ac_int: Unknown op: %s--\n",arg3);PLATFORM_COLOR_RESET();
                PLATFORM_COLOR_GREEN();printf("--STR:\n  %s %s %s %s--\n\n",arg1,arg2,arg3,arg4);PLATFORM_COLOR_RESET();return 1;
            }
        }else if(o == OP_SETB){
            int idx = arg2[0] - 'a';
            bval[idx] = atoi(arg3);
            if(bval[idx] != 0 && bval[idx] != 1){PLATFORM_COLOR_RED();printf("\n--VM: [ERR]: setb: bad value: %s. Use 0 or 1--\n\n", arg3);
                PLATFORM_COLOR_RESET();
            return 1;
            }
        }else if(o == OP_PRINTB){
            int idx = arg2[0] - 'a';
            printf("%d\n",bval[idx]);
        }else if (o == OP_WHILE){
            int idx = arg2[0] - 'a';
            while(1) {
                if(arg3[0] == '<' && !(values[idx] < atoi(arg4))){break;}
                if(arg3[0] == '>' && !(values[idx] > atoi(arg4))){break;}
                if(arg3[0] == '=' && !(values[idx] == atoi(arg4))){break;}

                if(!strcasecmp(arg5,"int_print")){printf("%d\n",values[idx]);}
                else{
                    PLATFORM_COLOR_RED();
                    printf("\n--VM: [ERR]: while: Unknown op: %s--\n",arg3);PLATFORM_COLOR_RESET();
                    PLATFORM_COLOR_GREEN();printf("--STR:\n  %s %s %s %s %s--\n\n",arg1,arg2,arg3,arg4,arg5);
                    PLATFORM_COLOR_RESET();return 1;
                }
            }
        }else if (o==OP_SLEEP){
            if(arg2[0]==0){
                PLATFORM_COLOR_RED();
                printf("\n--VM: [ERR]: sleep: need an argument: %s--\n",arg3);PLATFORM_COLOR_RESET();
                PLATFORM_COLOR_GREEN();printf("--STR:\n  %s %s %s %s %s--\n\n",arg1,arg2,arg3,arg4,arg5);
                PLATFORM_COLOR_RESET();return 1;
            }
            PLATFORM_SLEEP(atoi(arg2));
        }else if(o==OP_PRINT){
            if(!strcmp(arg3,"**")){
                int count1 = atoi(arg4);
                if(!strcmp(arg5,"nn")){
                    for(int i=0;i<count1;i+=1){ printf("%s\n",arg2);
                    }
                }
                else{
                    for(int i=0;i<count1;i+=1){ printf("%s",arg2);
                    }
                }
            }else if(!strcmp(arg3,"+")){printf("%d\n",atoi(arg2) + atoi(arg4));}
            else if(!strcmp(arg3,"-")){printf("%d\n",atoi(arg2) - atoi(arg4));}
            else if(!strcmp(arg3,"*")){printf("%d\n",atoi(arg2) * atoi(arg4));}
            else if(!strcmp(arg3,"nn")){printf("%s\n",arg2);}
            else if(!strcmp(arg3,"red")){
                if(!strcmp(arg4,"nn")){PLATFORM_COLOR_RED();printf("%s\n",arg2);PLATFORM_COLOR_RESET();}
                else{PLATFORM_COLOR_RED();printf("%s",arg2);PLATFORM_COLOR_RESET();}
            }
            else if(!strcmp(arg3,"green")){
                if(!strcmp(arg4,"nn")){PLATFORM_COLOR_GREEN();printf("%s\n",arg2);PLATFORM_COLOR_RESET();}
                else{PLATFORM_COLOR_GREEN();printf("%s",arg2);PLATFORM_COLOR_RESET();}
            }else if(!strcmp(arg3,"yellow")){
                if(!strcmp(arg4,"nn")){PLATFORM_COLOR_YELLOW();printf("%s\n",arg2);PLATFORM_COLOR_RESET();}
                else{PLATFORM_COLOR_YELLOW();printf("%s",arg2);PLATFORM_COLOR_RESET();}
            }
            else{printf("%s",arg2);}
        }else if(o ==OP_PRINTS){printf("%s %s %s %s ",arg2,arg3,arg4,arg5);}
        else if(o==OP_EXIT){
            if(!strcasecmp(arg2,"true")){exit(1);}
            else if(!strcasecmp(arg2,"false")){exit(0);}
            else if(arg2[0]=='\0'){exit(0);}
            else{PLATFORM_COLOR_RED();
                printf("--VM: [ERR]: exit: Unknown argument: %s--\n",arg2);PLATFORM_COLOR_RESET();
                PLATFORM_COLOR_GREEN();("--STR:\n  %s %s %s %s %s--\n\n",arg1,arg2,arg3,arg4,arg5);
                PLATFORM_COLOR_RESET();return 1;
            }
        }else if(o==OP_CLEAR_SCREEN){PLATFORM_CLEAR_SCREEN();}
        else if(o==OP_PRINT_OS){printf(OS_NAME);}
        else if(o==OPBITS){printf(ARCH_BITS);}
        else{PLATFORM_COLOR_RED();printf("\n\n--VM: [ERR]: Unknown opcode--\n");PLATFORM_COLOR_RESET();
            PLATFORM_COLOR_YELLOW();printf("--The opcode was not found in the VM instruction table--\n\n");PLATFORM_COLOR_RESET();
            printf("Execution stopped\n");printf("----------------------\n\n");return 0;
        }
     }

}
void main() {
    int ch;
    puts("Напишите цифру 3 и увидите информацию");
    puts("о использования приложения.");
    puts("\n1 - REPL interpretator");
    puts("2 - to run code");
    puts("3 - help");
    puts("4 - compile");
    puts("5 - run\n");
    while (1) {
        scanf("%d",&ch);
        getchar();
        switch (ch) {
            case 1:
                puts("———————————————————");
                puts("\nSF interpretator");
                while (1) {
                    printf("> ");
                    fgets(s, sizeof(s), stdin);
                    s[strcspn(s, "\n")] = 0;
                    if (strcmp(s, "exit") == 0) break;
                    cs=0;arg_i=0;raz(s);run();
                }
                break;
            case 2:
                int fi;
                puts("Файл должен называтся programm.sf\n");
                scanf("%d",&fi);
                if(fi==1){
                    system("clear");
                    printf("------output-------\n\n");
    			    FILE *f = fopen("programm.sf","r");
                    printf("\n-------------------\n");
                    if(!f){
                    puts("Файл пустой или не найден");
                    puts("Нужен файл с названием programm.sf");
                    break;
                    }
                    cs = 0;
                    arg_i = 0;
    			    while (fgets(s, sizeof(s), f)) { 
        		    s[strcspn(s, "\n")] = 0;
        		    raz(s);
                    }
                    printf("\n-------------------\n");
                    run();
                    fclose(f);
                    break;
                }
                return;
            case 3:
                printf("\nЕсли выбираете два, то нужен файл с нужным\n");
                printf("кодом и с названием programm.sf\n\n");
                break;
            case 4:
                cs = 0;
                arg_i = 0;
                FILE *f4 = fopen("programm.sf", "r");
                if (!f4) { puts("Файл не найден"); break; }
                while (fgets(s, sizeof(s), f4)) {
                    s[strcspn(s, "\n")] = 0;
                    raz(s);
                }
                fclose(f4);
                save_sbc("programm.fx");
                break;
            case 5:
                load_sbc("programm.fx");
                puts("OUTPUT----------------\n");
                run();
                break;
            default:puts("Неизвестная команда");   
        }    
    }    
    return;
}
