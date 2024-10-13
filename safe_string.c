#include "safe_string.h"

void zero_out(u8 *s, u8 n)
{
    u8 x = n;
    u8 *p;
    for (p = s; x; p++, x--)
        *p = 0;
}

void copy_str(char *dest, const char *src, u32 n)
{
    const char *s;
    char *d;
    u32 x;
    for (x = n, d = dest, s = src; x; d++, s++, x--)
        *d = *s;
    return;
}

u32 length(const char *str)
{
    u32 n = 0;
    const char *p = str;
    for (; *p; p++, n++)
        ;
    return n;
}

String *init(const char *str)
{
    u32 size, l;
    l = length(str);
    size = l + 1 + sizeof(String);

    String *ret;
    ret = calloc(1, size);
    if (ret == NULL)
        assert_perror(errno);
    ret->count = l;
    copy_str(ret->data, str, l);
    ret->data[l] = '\0';
    return ret;
}

String *concat(String *orig, char *add)
{
    u32 temp_count = orig->count;
    u32 add_size = length(add);
    u32 new_count = temp_count + add_size;
    u32 size = new_count + 1 + sizeof(String);

    // String *temp = orig;

    char temp_data[temp_count + 1];
    // for (u32 n = 0; n <= temp_count; n++)
    //     temp_data[n] = orig->data[n];
    copy_str(temp_data, orig->data, temp_count);

    orig = realloc(orig, size);
    if (orig == NULL)
        assert_perror(errno);

    zero_out((u8 *)orig, size);

    copy_str(orig->data, temp_data, temp_count);
    // printf("after first copy; '%s'\n", orig->data);
    copy_str(&(orig->data[temp_count]), add, add_size);
    // printf("after second copy; '%s'\n", orig->data);

    orig->count = new_count;
    orig->data[new_count] = '\0';
    return orig;
}

int main()
{
    String *s;
    s = init("Hello");
    printf("String:'%s' length?:%d\n", s->data, length(s->data));
    s = concat(s, " THERE");
    printf("String after:'%s' length?:%d\n", s->data, length(s->data));
    s = concat(s, " MY FRIEND");
    printf("String after 2:'%s' length?:%d\n", s->data, length(s->data));

    String *s2 = init("Wrk please lol");
    printf("String:'%s' length?:%d\n", s2->data, length(s2->data));
    s2 = concat(s2, " THANKS YAAAAY!");
    printf("String:'%s' length?:%d\n", s2->data, length(s2->data));

    free(s);
    return 0;
}