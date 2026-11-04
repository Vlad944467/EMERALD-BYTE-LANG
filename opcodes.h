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
#ifndef OPCODES_H
#define OPCODES_H
enum opcode {
    OP_MOV=200,
    OP_ADD,
    OP_SUB,
    OP_INT_PRINT,
    OP_PRINT_C,
    OP_ADD_NUM,
    OP_SUBT_NUM,
    OP_CLEAR,
    OP_MUL_NUM,
    OP_DIV_NUM,
    OP_STR,
    OP_PRINT_STR,
    OP_FMOV,
    OP_PRINTFL,
    OP_MOVC,
    OP_PRINTC,
    OP_STRLEN,
    OP_FADD,
    OP_INPUT_INT,
    OP_INPUT_STR,
    OP_DEC,
    OP_INC,
    OP_COPY,
    OP_SAVEV,
    OP_LOADV,
    OP_INPUTF,
    OP_INPUTC,
    OP_IF,
    OP_REPEAT,
    OP_N,
    OP_AC_INT,
    OP_SETB,
    OP_PRINTB,
    OP_WHILE,
    OP_SLEEP,
    OP_PRINT,
    OP_PRINTS,
    OP_EXIT,
    OP_CLEAR_SCREEN,
    OP_PRINT_OS,
    OPBITS
};
#endif
