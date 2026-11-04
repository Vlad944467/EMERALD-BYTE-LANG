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
#ifndef PLATFORM_H
#define PLATFORM_H
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h
    #define OS_NAME "Windows"
    #if defined(_WIN64) || defined(_M_X64) || defined(_M_ARM64)
        #define ARCH_BITS "64-bit\n"
    #elif defined(_WIN32) || defined(_M_IX86) || defined(_M_ARM)
        #define ARCH_BITS "32-bit\n"
    #else
        #define ARCH_BITS "  --Unknown--  "
    #endif
    #define PLATFORM_SLEEP(ms) Sleep((DWORD)(ms))
    #define PLATFORM_COLOR_RESET() do { \
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,7); \
    } while(0)
    #define PLATFORM_COLOR_RED() do { \
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,12); \
    } while(0)
    #define PLATFORM_COLOR_GREEN() do { \
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,10); \
    } while(0)
    #define PLATFORM_COLOR_YELLOW() do { \
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h,14); \
    } while(0)
    #define PLATFORM_CLEAR_SCREEN() system("cls")
#elif defined(__linux__)
    #define OS_NAME "Linux\n"
    #include <unistd.h>
    #if defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__) || defined(__arm64__) || defined(__ppc64__)
        #define ARCH_BITS "64-bit\n"
    #elif defined(__i386__) || defined(__i686__) || defined(__arm__) || defined(__thumb__) || defined(__ppc__)
        #define ARCH_BITS "32-bit\n"
    #else
        #define ARCH_BITS "  --Unknown--  "
    #endif
    #define PLATFORM_SLEEP(ms) usleep
    #define PLATFORM_COLOR_RESET() printf("\033[0m")
    #define PLATFORM_COLOR_RED() printf("\033[31m")
    #define PLATFORM_COLOR_GREEN() printf("\033[32m")
    #define PLATFORM_COLOR_YELLOW() printf("\033[33m")
    #define PLATFORM_CLEAR_SCREEN() printf("\x1b[2J\x1b[H")
#elif defined(__APPLE__) && defined(__MACH__)
    #define OS_NAME "macOS"
    #if defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__) || defined(__arm64__) || defined(__ppc64__)
        #define ARCH_BITS "64-bit\n"
    #elif defined(__i386__) || defined(__i686__) || defined(__arm__) || defined(__thumb__) || defined(__ppc__)
        #define ARCH_BITS "32-bit\n"
    #else
        #define ARCH_BITS "  --Unknown--  "
    #endif
    #define PLATFORM_SLEEP(ms) fprintf(stderr,"\n[PLATFORM_ERR]\n\n")
    #define PLATFORM_COLOR_RESET() printf("\x1b[0m")
    #define PLATFORM_COLOR_RED() printf("\x1b[31m")
    #define PLATFORM_COLOR_GREEN() printf("\x1b[32m")
    #define PLATFORM_COLOR_YELLOW() printf("\x1b[33m")
    #define PLATFORM_CLEAR_SCREEN() printf("\x1b[2J\x1b[H")
#elif defined(__Fuchsia__)
    #define OS_NAME "Fuchsia"
    #if defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__) || defined(__arm64__) || defined(__ppc64__)
    #define ARCH_BITS "64-bit\n"
    #elif defined(__i386__) || defined(__i686__) || defined(__arm__) || defined(__thumb__) || defined(__ppc__)
    #define ARCH_BITS "32-bit\n"
    #else
    #define ARCH_BITS "  --Unknown--  "
    #endif
    #define PLATFORM_SLEEP(ms) fprintf(stderr,"\n[PLATFORM_ERR]\n\n")
    #define PLATFORM_CLEAR_SCREEN() printf("\x1b[2J\x1b[H")
    #define PLATFORM_COLOR_RESET() printf("\x1b[0m")
    #define PLATFORM_COLOR_RED() printf("\x1b[31m")
    #define PLATFORM_COLOR_GREEN() printf("\x1b[32m")
    #define PLATFORM_COLOR_YELLOW() printf("\x1b[33m")
#elif defined(__QNX__)
    #define OS_NAME "qnx"
    #if defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__) || defined(__arm64__) || defined(__ppc64__)
    #define ARCH_BITS "64-bit\n"
    #elif defined(__i386__) || defined(__i686__) || defined(__arm__) || defined(__thumb__) || defined(__ppc__)
    #define ARCH_BITS "32-bit\n"
    #else
    #define ARCH_BITS "  --Unknown--  "
    #endif
    #define PLATFORM_SLEEP(ms) nap((unsigned int)(ms))
    #define PLATFORM_CLEAR_SCREEN() printf("\x1b[2J\x1b[H");
    #define PLATFORM_COLOR_RESET() printf("\x1b[0m")
    #define PLATFORM_COLOR_RED() printf("\x1b[31m")
    #define PLATFORM_COLOR_GREEN() printf("\x1b[32m")
    #define PLATFORM_COLOR_YELLOW() printf("\x1b[33m")
#elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
    #include <unistd.h>
        #if defined(__FreeBSD__)
            #define OS_NAME "FreeBSD"
        #elif defined(__OpenBSD__)
            #define OS_NAME "OpenBSD"
        #elif defined(__NetBSD__)
            #define OS_NAME "NetBSD"
        #elif defined(__DragonFly__)
            #define OS_NAME "DragonFly"
        #endif
    #if defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__) || defined(__arm64__) || defined(__ppc64__)
        #define ARCH_BITS "64-bit\n"
    #elif defined(__i386__) || defined(__i686__) || defined(__arm__) || defined(__thumb__) || defined(__ppc__)
        #define ARCH_BITS "32-bit\n"
    #else
        #define ARCH_BITS "  --Unknown--  "
    #endif
    #define PLATFORM_SLEEP(ms) usleep
    #define PLATFORM_COLOR_RESET() printf("\033[0m")
    #define PLATFORM_COLOR_RED() printf("\033[31m")
    #define PLATFORM_COLOR_GREEN() printf("\033[32m")
    #define PLATFORM_COLOR_YELLOW() printf("\033[33m")
    #define PLATFORM_CLEAR_SCREEN() printf("\x1b[2J\x1b[H");
#else
    #pragma message("\n[PLATFORM_ERR]: Unsupported OS\n\n")
    #define OS_NAME "  --Unknown--  "
#endif
#endif
