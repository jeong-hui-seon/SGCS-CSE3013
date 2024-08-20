#include "str.h"
#include <string>
#include <cstring>
using namespace std;

Str::Str(int leng){
    len=leng;
} // leng 은 string의 길이.

Str::Str(const char *neyong){
    string s(neyong); //neyong을 string으로 변환한다.
    len = s.length(); //string의 길이를 계산한다.
    str = new char[len+1]; // '\0'자리까지 계산해서 동적으로 메모리를 할당한다.
    for (int i=0; i<len; i++){ //문자열의 문자을 하나씩 저장한다.
        str[i]=neyong[i];
    }
    str[len]='\0';
} // neyong은 초기화할 내용이 들어감.

Str::~Str(){
    delete[] str; // 동적으로 할당한 메모리를 해제한다.
} // 소멸자.

int Str::length(void){
    return len;
} // string의 길이를 리턴하는 함수.

char * Str::contents(void){
    return str;
} // string의 내용을 리턴하는 함수.

int Str::compare(class Str& a){
    return strcmp(str,a.str); //문자열이 동일하면 0, 다르면 1을 반환한다.
} // a의 내용과 strcmp.

int Str::compare(const char *a){
    return strcmp(str, a);
} // a의 내용과 strcmp.

void Str::operator=(const char *a){
    string s(a);
    len = s.length();
    str = new char[len+1];
    for (int i=0; i<len; i++){
        str[i]=a[i];
    }
    str[len]='\0';
} // string의 값을 대입.

void Str::operator=(class Str& a){
    string s(a.str);
    len = s.length();
    str = new char[len+1];
    for (int i=0; i<len; i++){
        str[i]=a.str[i];
    }
    str[len]='\0';
} // Str의 내용을 대입.