/*
 * Copyright 2010 sakamoto.gsyc.3s@gmail.com
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

/**
 * expdef : dll1 caller main program
 *
 * $Id$
 */

#include <stdio.h>

int __declspec(dllimport) func1(int a, int b);
int __declspec(dllimport) func2(int a, int b);

int main(int argc, char *argv[])
{
    printf("func1(2, 3) = %d\n", func1(2, 3));
    printf("func2(2, 3) = %d\n", func2(2, 3));
    return 0;
}
