/*
 * ADT programme of Array dynami
 * 
 * Author: Yann Chicheportiche
 */

#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct AdptArray_
{
    int size;
    PElement* array;
    DEL_FUNC DeleteFunction;
    COPY_FUNC CopyFunction;
    PRINT_FUNC PrintFunction;

}AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC Copy,DEL_FUNC Delete,PRINT_FUNC Print){
    PAdptArray Parray = (PAdptArray)malloc(sizeof(AdptArray));
    if(Parray == NULL) return NULL;
    Parray->size = 0;
    Parray->array = NULL;
    Parray->CopyFunction = Copy;
    Parray->DeleteFunction = Delete;
    Parray->PrintFunction = Print;

    return Parray;
    }

Result SetAdptArrayAt(PAdptArray PArray, int index , PElement element){
    if(PArray == NULL){
        return FAIL;
    }
    if(index >= PArray->size){
        PElement* NewPtr = (PElement*)realloc(PArray->array,(index+1) * sizeof(PElement));
        if(NewPtr == NULL){
            return FAIL;
        }
        PArray->size = index+1;
        PArray->array = NewPtr;

    }
    if(PArray->array[index] != NULL){
        PArray->DeleteFunction(PArray->array[index]);
    }
    PArray->array[index] = PArray->CopyFunction(element);
    return SUCCESS;
}

void DeleteAdptArray(PAdptArray Arr){
    if(Arr == NULL){
        return;
    }
    for (size_t i = 0; i < Arr->size; i++)
    {
        if(Arr->array[i] != NULL){
            Arr->DeleteFunction(Arr->array[i]);
        }
    }
    free(Arr->array);
    free(Arr);

}

PElement GetAdptArrayAt(PAdptArray Array, int index){
    if(Array == NULL){
        return NULL;
    }
    if(Array->array[index] == NULL){
        return NULL;
    }
    return Array->CopyFunction(Array->array[index]);
}

int GetAdptArraySize(PAdptArray Array){
    if(Array == NULL){
        return -1;
    }
    return Array->size;
}

void PrintDB(PAdptArray Array){
    if(Array == NULL){
        printf("The Struct is Null\n");
        return;
    }
    for (size_t i = 0; i < Array->size; i++)
    {
        if(Array->array[i]!= NULL){
            Array->PrintFunction(Array->array[i]);
        }
    }
    
}
