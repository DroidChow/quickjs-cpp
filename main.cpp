#include <iostream>
extern "C" {
#include "quickjs/quickjs-libc.h"
}

static int eval_buf(JSContext *ctx, const void *buf, int buf_len,
                    const char *filename, int eval_flags)
{
    JSValue val;
    int ret;

    val = JS_Eval(ctx, (const char*)buf, buf_len, filename, eval_flags);
    if (JS_IsException(val)) {
        js_std_dump_error(ctx);
        ret = -1;
    } else {
        ret = 0;
    }
    JS_FreeValue(ctx, val);
    return ret;
}
int main() {

    JSRuntime *rt;
    JSContext *ctx;

    rt = JS_NewRuntime();
    if (!rt) {
        fprintf(stderr, "qjs: cannot allocate JS runtime\n");
        exit(2);
    }

    ctx = JS_NewContext(rt);
    if (!ctx) {
        fprintf(stderr, "qjs: cannot allocate JS context\n");
        exit(2);
    }
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);

    js_std_add_helpers(ctx, 0, NULL);

    /* system modules */
    js_init_module_std(ctx, "std");
    js_init_module_os(ctx, "os");


    /* make 'std' and 'os' visible to non module code */
    const char *str = "import * as std from 'std';\n"
                      "import * as os from 'os';\n"
                      "std.global.std = std;\n"
                      "std.global.os = os;\n"
                      "console.log('hello');\n"
                      ;
    eval_buf(ctx, str, strlen(str), "<input>", JS_EVAL_TYPE_MODULE);

    return 0;
}