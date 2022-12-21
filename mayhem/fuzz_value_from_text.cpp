#include <stdint.h>
#include <stdio.h>
#include <climits>

#include <fuzzer/FuzzedDataProvider.h>

typedef struct value_t
{
    int type;
    union
    {
        float f;
        double d;
        unsigned char b;
        signed char c;
        uint16_t u;
        int16_t s;
        uint32_t U;
        int32_t S;
        char *z;
        char C[4];
        struct
        {
            size_t length;
            unsigned char *data;
        } m;
    } val;
} value_t;

extern "C" int value_from_text(const char *text, value_t *value, char type);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    FuzzedDataProvider provider(data, size);
    std::string str = provider.ConsumeRandomLengthString();
    char type = provider.ConsumeIntegral<char>();
    value_t vt;

    value_from_text(str.c_str(), &vt, type);

    return 0;
}