#include <jni.h>
#include <string>
#include <android/log.h>
#include "util.h"
#include "calculator.h"
#include "sha3.h"


void Ramdom(uint8 *a, int len) {
    srand(time(0));
    for (int i = 0; i < len; i++) {
        a[i] = rand() % 256;
    }
}

char nibbleToChar(unsigned nibble) {
    return (char) ((nibble >= 10 ? 'a' - 10 : '0') + nibble);
}

std::string bytesToHexString(uint8_t const *bytes, unsigned size) {
    std::string str;
    for (unsigned i = 0; i != size; ++i) {
        str += nibbleToChar(bytes[i] >> 4);
        str += nibbleToChar(bytes[i] & 0xf);
    }
    return str;
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_appfloweb_keccak_MainActivity_keccakTest(
        JNIEnv *env,
        jobject /* this */) {

    const char *TAG = "Keccak Test";

    setenv("ADSP_LIBRARY_PATH", "/data/local/tmp/dsp", 1);
    //Activate Unsigned PD
    if (remote_session_control) {
        struct remote_rpc_control_unsigned_module data;
        data.enable = 1;
        data.domain = CDSP_DOMAIN_ID;
        remote_session_control(DSPRPC_CONTROL_UNSIGNED_MODULE, (void *) &data, sizeof(data));
    }

    int in_bytes_len = 64 * 16 * 400;
    int out_bytes_len = 64 * 16 * 400;
    int in_step = in_bytes_len / (16 * 400);
    int out_step = out_bytes_len / (16 * 400);
    int nErr = 0;
    remote_handle64 handle;
    char *uri = (char *) calculator_URI "&_dom=cdsp";
    clock_t t1, t2;
    uint8_t ret[64];

    std::string info = "Keccak Test:\n\n";

    rpcmem_init();
    uint8_t *in_bytes = (uint8_t *) aligned_malloc(RPCMEM_HEAP_ID_CONTIG, in_bytes_len, 128);
    uint8_t *out_bytes = (uint8_t *) (aligned_malloc(RPCMEM_HEAP_ID_SYSTEM, out_bytes_len, 128));
    assert(in_bytes);
    assert(out_bytes);

    nErr = calculator_open(uri, &handle);
    if (nErr != 0) {
        info.append("Handle open failed.\n");
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Handle open failed, returned 0x%x", nErr);
        goto bail;
    }

    Ramdom(in_bytes,in_bytes_len);

    //dsp
    t1 = clock();
    calculator_keccak512_64_64(handle, in_bytes, in_bytes_len, out_bytes, out_bytes_len);
    t2 = clock();

    SHA3_512(ret, out_bytes, out_bytes_len);
    info.append("dsp:\n");
    info.append("hash:").append(bytesToHexString(ret,64)).append("\n");
    info.append("time:").append(std::to_string(t2 - t1)).append("\n\n");

    //cpu
    memset(out_bytes, 0, out_bytes_len);
    t1 = clock();
    for (int i = 0; i < in_bytes_len / in_step; i++) {
        SHA3_512(out_bytes + out_step * i, in_bytes + in_step*i, in_step);
    }
    t2 = clock();

    SHA3_512(ret, out_bytes, out_bytes_len);
    info.append("cpu:\n");
    info.append("hash:").append(bytesToHexString(ret,64)).append("\n");
    info.append("time:").append(std::to_string(t2 - t1)).append("\n\n");


    bail:
    if (handle) {
        nErr = calculator_close(handle);
        if (nErr != 0) {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "Handle close failed, returned 0x%x", nErr);
        }
    }
    aligned_free(in_bytes);
    aligned_free(out_bytes);
    rpcmem_deinit();

    return env->NewStringUTF(info.c_str());
}
