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
#include "lexcompiler.h"
#include "opcodes.h"
#include "gvar.h"
#include "platform.h"
#include <stdio.h>
#include <string.h>
void raz(char *s) {
    char *p=strchr(s,';');
    if(p){
     *p='\0';raz(p+1);
    }
    char *cm=strstr(s,"//");
    if(cm){
     *cm='\0';
    }
    arg2[0] = 0; arg3[0] = 0; arg4[0] = 0; arg5[0] = 0;
    if (sscanf(s, "%89s %89s %89s %89s %89s", arg1,arg2,arg3,arg4,arg5) < 1) return;
    int num = -1;
    if (strcmp(arg1,"set")==0) { num = OP_MOV;}
    else if(strcasecmp(arg1,"add")==0){ num = OP_ADD; }
    else if(strcasecmp(arg1,"sub")==0){ num = OP_SUB; }
    else if(strcasecmp(arg1,"int_print")==0){ num = OP_INT_PRINT;}
    else if(strcasecmp(arg1,"print_c")==0){ num = OP_PRINT_C; }
    else if(strcasecmp(arg1,"add_num")==0){ num = OP_ADD_NUM;}
    else if(strcasecmp(arg1,"subt_num")==0){ num = OP_SUBT_NUM; }
    else if(strcasecmp(arg1,"clear")==0){ num = OP_CLEAR;}
    else if(strcasecmp(arg1,"mul_num")==0){ num = OP_MUL_NUM; }
    else if(strcasecmp(arg1,"div_num")==0){ num = OP_DIV_NUM;}
    else if(strcasecmp(arg1,"str")==0){ num = OP_STR; }
    else if(strcasecmp(arg1,"print_str")==0){ num = OP_PRINT_STR;}
    else if(strcasecmp(arg1,"fmov")==0){ num = OP_FMOV; }
    else if(strcasecmp(arg1,"printfl")==0){ num = OP_PRINTFL;}
    else if(strcasecmp(arg1,"movC")==0){ num = OP_MOVC; }
    else if(strcasecmp(arg1,"printc")==0){ num = OP_PRINTC;}
    else if(strcasecmp(arg1,"strlen")==0){ num = OP_STRLEN; }
    else if(strcasecmp(arg1,"fadd")==0){ num = OP_FADD;}
    else if(strcasecmp(arg1,"input_int")==0){ num = OP_INPUT_INT; }
    else if(strcasecmp(arg1,"input_str")==0){ num = OP_INPUT_STR;}
    else if(strcasecmp(arg1,"dec")==0){ num = OP_DEC;}
    else if(strcasecmp(arg1,"inc")==0){ num = OP_INC;}
    else if(strcasecmp(arg1,"copy")==0){ num = OP_COPY;}
    else if(strcasecmp(arg1,"savev")==0){ num = OP_SAVEV;}
    else if(strcasecmp(arg1,"loadv")==0){ num = OP_LOADV; }
    else if(strcasecmp(arg1,"inputf")==0){ num = OP_INPUTF;}
    else if(strcasecmp(arg1,"inputc")==0){ num = OP_INPUTC; }
    else if(strcasecmp(arg1,"if")==0){ num = OP_IF;}
    else if(strcasecmp(arg1,"repeat")==0){ num = OP_REPEAT;}
    else if(strcasecmp(arg1,"N")==0){num = OP_N;}
    else if(strcasecmp(arg1,"ac_int")==0){num = OP_AC_INT;}
    else if(strcasecmp(arg1,"setb")==0){num = OP_SETB;}
    else if(strcasecmp(arg1,"printb")==0){num = OP_PRINTB;}
    else if(strcasecmp(arg1,"while")==0){num = OP_WHILE;}
    else if(strcasecmp(arg1,"sleep")==0){num = OP_SLEEP;}
    else if(strcasecmp(arg1,"print")==0){num = OP_PRINT;}
    else if(strcasecmp(arg1,"prints")==0){num = OP_PRINTS;}
    else if(strcasecmp(arg1,"exit")==0){num = OP_EXIT;}
    else if(strcasecmp(arg1,"clear_screen")==0){num=OP_CLEAR_SCREEN;}
    else if(strcasecmp(arg1,"print_os")==0){num =OP_PRINT_OS;}
    else if(strcasecmp(arg1,"bits")==0){num=OPBITS;}
    else{PLATFORM_COLOR_RED();printf("[ERR]: Unknown argument: %s\n",arg1);PLATFORM_COLOR_RESET();}
    code[cs++] = num;
    code[cs++] = 0;
    code[cs++] = 0;
    strcpy(sa[arg_i],arg2);strcpy(sb[arg_i],arg3);
    strcpy(sc[arg_i],arg4);strcpy(sd[arg_i],arg5);arg_i++;
}
