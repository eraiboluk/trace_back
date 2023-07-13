#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func2();

#define SW(i) case i: return __builtin_extract_return_addr(__builtin_return_address(i))
int main();
void * get_address(int i) {
    switch (i) {
        SW(0);
        SW(1);
        SW(2);
        SW(3);
        SW(4);
        SW(5);
        SW(6);
        SW(7);
        SW(8);
        SW(9);
        SW(10);
        SW(11);
        SW(12);
        SW(13);
        SW(14);
        SW(15);
        SW(16);
        SW(17);
        SW(18);
        SW(19);
        SW(20);
        
    }
}

char* find_function_name(int* address,char name[20]) {
    
    char hex_address[20], command[100];
    sprintf(hex_address, "%x", address);

    const char *last_three = &hex_address[strlen(hex_address)-3];

    strcpy(command, "nm -C ");
    strcat(command, name);
    strcat(command, " | grep ");
    strcat(command, last_three);

    
    FILE* pipe = popen(command, "r");
    if (pipe == NULL) {
        perror("popen");
        return NULL;
    }
    char output[100];
    if (fgets(output, sizeof(output), pipe) == NULL) {
        pclose(pipe);
        return NULL;
    }
    pclose(pipe);

    
    char* function_name = strrchr(output, ' ');
    if (function_name == NULL) {
        return NULL;
    }
    function_name++; 

    
    char* result = strdup(function_name);
    if (result == NULL) {
        perror("strdup");
        return NULL;
    }
    return result;
}

int offset_address(void* return_address) {

    int *offset_address_ptr = (int*)(return_address - 4);
    int offset = *offset_address_ptr; 
    return offset;

}

int function_address(void* return_address) {

    int *offset_address_ptr = (int*)(return_address - 4);
    int offset = *offset_address_ptr;   
    int func_address = return_address + offset;
    return func_address;

}    

void trace_return_values() {
    int i=0;
    char name[20];

    printf("What is the name of the executable?\n");
    scanf("%s", name);

    while(get_address(i) <= main )
    {
        printf("(retrn= %p, addr=%p, offset=%d) In Function: %s\n",get_address(i), function_address(get_address(i)), offset_address(get_address(i)), find_function_name(function_address(get_address(i)), name));
        
        i++;
    } 
}
void foo() {
    trace_return_values();
}
void bar() {
    foo();
}
void func3(){
    func2();
}
void func2(){
    bar();
}
void func1(){
    func3();
}
int main(void) {
    func1();
    return 0;
}