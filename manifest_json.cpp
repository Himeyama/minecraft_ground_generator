#include <uuid/uuid.h>

char* manifest(char *name){
    uuid_t u1, u2;
    char uuid1[37], uuid2[37];
    uuid_generate(u1);
    uuid_unparse(u1, uuid1);
    uuid_generate(u2);
    uuid_unparse(u2, uuid2);

    char* tmp = (char*)malloc(sizeof(char) * 1024);
    char str[1024] = \
    "{\
    \n  \"format_version\" : 1,\
    \n  \"header\" : {\
    \n      \"description\" : \"ground\",\
    \n      \"name\" : \"%s\",\
    \n      \"platform_locked\" : false,\
    \n      \"uuid\" : \"%s\",\
    \n      \"version\" : [ 0, 0, 1 ],\
    \n      \"min_engine_version\":[1,8,0]\
    \n},\
    \n  \"min_engine_version\" : [ 0, 0, 1, 1, 2, 5 ],\
    \n  \"modules\" : [\
    \n      {\
    \n          \"description\" : \"Not Used\",\
    \n          \"type\" : \"data\",\
    \n          \"uuid\" : \"%s\",\
    \n          \"version\" : [ 0, 0, 1 ]\
    \n      }\
    \n  ]\
    \n}";
    sprintf(tmp, str, name, uuid1, uuid2);
    return tmp;
}