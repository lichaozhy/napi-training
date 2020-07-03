#define NAPI_VERSION 3

#include <node_api.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// 实际暴露的方法，这里只是简单返回一个字符串
napi_value HelloMethod (napi_env env, napi_callback_info info) {
    napi_value world;
    napi_create_string_utf8(env, "world", 5, &world);
    return world;
}

char *genericWords() {
    char *value = "abcedfg";

    return value;
}

// 扩展的初始化方法，其中 
// env：环境变量
// exports、module：node模块中对外暴露的对象
void Init (napi_env env, napi_value exports, napi_value module, void* priv) {
    napi_status status;

    // napi_property_descriptor 为结构体，作用是描述扩展暴露的 属性/方法 的描述
    napi_property_descriptor desc = { "hello", 0, HelloMethod, 0, 0, 0, napi_default, 0 };
    napi_property_descriptor alias = { "fuck", 0, HelloMethod, 0, 0, 0, napi_default, 0 };

    napi_value es_word;

    status = napi_create_string_utf8(env, genericWords(), NAPI_AUTO_LENGTH, &es_word);

    napi_property_descriptor word = {
        "word",
        NULL,
        NULL,
        NULL,
        NULL,
        es_word,
        napi_default,
        NULL
    };

    printf("hello");


    napi_define_properties(env, exports, 1, &desc);  // 定义暴露的方法
    napi_define_properties(env, exports, 1, &alias);
    napi_define_properties(env, exports, 1, &word);
}

NAPI_MODULE(lc, Init);  // 注册扩展，扩展名叫做hello，Init为扩展的初始化方法