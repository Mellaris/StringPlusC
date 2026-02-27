#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "s21_string.h"

START_TEST(test_memcpy) {
  char src[] = "Hello world";
  char d1[50];
  char d2[50];

  s21_memcpy(d1, src, 11);
  memcpy(d2, src, 11);

  ck_assert_mem_eq(d1, d2, 11);
}
END_TEST

START_TEST(test_memset) {
  char b1[10];
  char b2[10];

  s21_memset(b1, 'A', 10);
  memset(b2, 'A', 10);

  ck_assert_mem_eq(b1, b2, 10);
}
END_TEST

START_TEST(test_memcmp) {
  char str1[] = "Hello";
  char str2[] = "Hello";
  ck_assert_int_eq(s21_memcmp(str1, str2, 5), memcmp(str1, str2, 5));
  char str3[] = "abc";
  char str4[] = "abd";
  ck_assert_int_eq(s21_memcmp(str3, str4, 3), memcmp(str3, str4, 3));
  char str5[] = "xyz";
  char str6[] = "abc";
  ck_assert_int_eq(s21_memcmp(str5, str6, 3), memcmp(str5, str6, 3));
  ck_assert_int_eq(s21_memcmp(str3, str4, 2), memcmp(str3, str4, 2));
  ck_assert_int_eq(s21_memcmp("anything", "different", 0),
                   memcmp("anything", "different", 0));
  int nums1[] = {1, 2, 3, 4, 5};
  int nums2[] = {1, 2, 3, 4, 6};
  ck_assert_int_eq(s21_memcmp(nums1, nums2, sizeof(nums1)),
                   memcmp(nums1, nums2, sizeof(nums1)));
  char a = 'a';
  char b = 'b';
  ck_assert_int_eq(s21_memcmp(&a, &b, 1), memcmp(&a, &b, 1));
  char sp1[] = "  test";
  char sp2[] = " test";
  ck_assert_int_eq(s21_memcmp(sp1, sp2, 6), memcmp(sp1, sp2, 6));
}
END_TEST

START_TEST(test_memchr_normal) {
  char *str = "Hello";
  ck_assert_ptr_eq(s21_memchr(str, 'l', 4), memchr(str, 'l', 4));
}
END_TEST

START_TEST(test_memchr_empty) {
  char *str = "";
  ck_assert_ptr_eq(s21_memchr(str, 'l', 0), memchr(str, 'l', 0));
}
END_TEST

START_TEST(test_memchr_null) {
  char *str = "Hello";
  ck_assert_ptr_eq(s21_memchr(str, '\0', 6), memchr(str, '\0', 6));
}
END_TEST

START_TEST(test_strlen) {
  ck_assert_int_eq(s21_strlen(""), strlen(""));
  ck_assert_int_eq(s21_strlen("a"), strlen("a"));
  ck_assert_int_eq(s21_strlen("hello"), strlen("hello"));
  ck_assert_int_eq(s21_strlen("hello world"), strlen("hello world"));
  ck_assert_int_eq(s21_strlen("test"), strlen("test"));
  ck_assert_int_eq(s21_strlen(""), strlen(""));
  ck_assert_int_eq(s21_strlen("1234567890"), strlen("1234567890"));
  ck_assert_int_eq(s21_strlen("  spaces  "), strlen("  spaces  "));
  ck_assert_int_eq(s21_strlen("\n\t\r"), strlen("\n\t\r"));
  ck_assert_int_eq(s21_strlen("привет"), strlen("привет"));
}
END_TEST

START_TEST(test_strncmp) {
  ck_assert_int_eq(s21_strncmp("abc", "abc", 3), strncmp("abc", "abc", 3));
  ck_assert_int_eq(s21_strncmp("abc", "abd", 3), strncmp("abc", "abd", 3));
  ck_assert_int_eq(s21_strncmp("abc", "abd", 2), strncmp("abc", "abd", 2));
  ck_assert_int_eq(s21_strncmp("", "", 5), strncmp("", "", 5));
}
END_TEST

START_TEST(test_strncpy) {
  char d1[20], d2[20];
  s21_strncpy(d1, "Hello", 10);
  strncpy(d2, "Hello", 10);
  ck_assert_str_eq(d1, d2);
  char buf[10];
  ck_assert_ptr_eq(s21_strncpy(buf, "test", 5), buf);
}
END_TEST

START_TEST(test_strncat) {
  char d1[50] = "Hello";
  char d2[50] = "Hello";

  s21_strncat(d1, " world", 3);
  strncat(d2, " world", 3);

  ck_assert_str_eq(d1, d2);
}
END_TEST

START_TEST(test_strchr_normal) {
  char *str = "Hello";
  ck_assert_ptr_eq(s21_strchr(str, 'l'), strchr(str, 'l'));
}
END_TEST

START_TEST(test_strchr_empty) {
  char *str = "";
  ck_assert_ptr_eq(s21_strchr(str, 'l'), strchr(str, 'l'));
}
END_TEST

START_TEST(test_strchr_null) {
  char *str = "Hello";
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

START_TEST(test_strrchr_normal) {
  char *str = "Hello";
  ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
}
END_TEST

START_TEST(test_strrchr_empty) {
  char *str = "";
  ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
}
END_TEST

START_TEST(test_strrchr_null) {
  char *str = "Hello";
  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

START_TEST(test_strcspn) {
  ck_assert_int_eq(s21_strcspn("hello123", "0123456789"),
                   strcspn("hello123", "0123456789"));
  ck_assert_int_eq(s21_strcspn("123hello", "0123456789"),
                   strcspn("123hello", "0123456789"));
  ck_assert_int_eq(s21_strcspn("hello", "0123456789"),
                   strcspn("hello", "0123456789"));
  ck_assert_int_eq(s21_strcspn("", "0123456789"), strcspn("", "0123456789"));
  ck_assert_int_eq(s21_strcspn("hello", ""), strcspn("hello", ""));
  ck_assert_int_eq(s21_strcspn("abcxyz", "x"), strcspn("abcxyz", "x"));
  ck_assert_int_eq(s21_strcspn("hello world", "aeiou"),
                   strcspn("hello world", "aeiou"));
  ck_assert_int_eq(s21_strcspn("hello, world!", " ,!"),
                   strcspn("hello, world!", " ,!"));
  ck_assert_int_eq(s21_strcspn("abc", "abc"), strcspn("abc", "abc"));
  ck_assert_int_eq(s21_strcspn("a", "xyz"), strcspn("a", "xyz"));
  ck_assert_int_eq(s21_strcspn("a", "a"), strcspn("a", "a"));
  ck_assert_int_eq(s21_strcspn("abcdef", "f"), strcspn("abcdef", "f"));
  ck_assert_int_eq(s21_strcspn("abacadae", "cde"), strcspn("abacadae", "cde"));
  ck_assert_int_eq(s21_strcspn("\n\t\r test", "\n\t\r"),
                   strcspn("\n\t\r test", "\n\t\r"));
}
END_TEST

START_TEST(test_strpbrk) {
  ck_assert_str_eq(s21_strpbrk("hello", "aeiou"), strpbrk("hello", "aeiou"));
  ck_assert_str_eq(s21_strpbrk("hello123", "0123456789"),
                   strpbrk("hello123", "0123456789"));
  ck_assert_ptr_eq(s21_strpbrk("hello", "xyz"), strpbrk("hello", "xyz"));
  ck_assert_ptr_eq(s21_strpbrk("", "aeiou"), strpbrk("", "aeiou"));
  ck_assert_ptr_eq(s21_strpbrk("hello", ""), strpbrk("hello", ""));
  ck_assert_str_eq(s21_strpbrk("apple", "aeiou"), strpbrk("apple", "aeiou"));
  ck_assert_str_eq(s21_strpbrk("test!", "!?"), strpbrk("test!", "!?"));
  ck_assert_str_eq(s21_strpbrk("abcxyz", "xyz"), strpbrk("abcxyz", "xyz"));
  ck_assert_str_eq(s21_strpbrk("hello, world!", " ,!"),
                   strpbrk("hello, world!", " ,!"));
  ck_assert_str_eq(s21_strpbrk("abc", "abc"), strpbrk("abc", "abc"));
  ck_assert_ptr_eq(s21_strpbrk("a", "xyz"), strpbrk("a", "xyz"));
  ck_assert_str_eq(s21_strpbrk("a", "a"), strpbrk("a", "a"));
  ck_assert_str_eq(s21_strpbrk("\n\t\r test", "est"),
                   strpbrk("\n\t\r test", "est"));
  ck_assert_str_eq(s21_strpbrk("abacadae", "cde"), strpbrk("abacadae", "cde"));
  ck_assert_ptr_eq(s21_strpbrk("Hello", "AEIOU"), strpbrk("Hello", "AEIOU"));
  ck_assert_str_eq(s21_strpbrk("Hello", "aeiou"), strpbrk("Hello", "aeiou"));
  ck_assert_str_eq(s21_strpbrk("test123test", "123"),
                   strpbrk("test123test", "123"));
}
END_TEST

START_TEST(test_strstr) {
  ck_assert_str_eq(s21_strstr("Hello World", "World"),
                   strstr("Hello World", "World"));
  ck_assert_str_eq(s21_strstr("Hello World", "Hello"),
                   strstr("Hello World", "Hello"));
  ck_assert_ptr_eq(s21_strstr("Hello World", "XYZ"),
                   strstr("Hello World", "XYZ"));
  ck_assert_str_eq(s21_strstr("Hello World", ""), strstr("Hello World", ""));
  ck_assert_str_eq(s21_strstr("test", "test"), strstr("test", "test"));
  ck_assert_ptr_eq(s21_strstr("hi", "hello"), strstr("hi", "hello"));
  ck_assert_ptr_eq(s21_strstr("abcxxxabc", "abcd"),
                   strstr("abcxxxabc", "abcd"));
  ck_assert_str_eq(s21_strstr("abababc", "abc"), strstr("abababc", "abc"));
  ck_assert_str_eq(s21_strstr("abc", "b"), strstr("abc", "b"));
  ck_assert_str_eq(s21_strstr("startend", "end"), strstr("startend", "end"));
  ck_assert_str_eq(s21_strstr("aaaaab", "aab"), strstr("aaaaab", "aab"));
  ck_assert_ptr_eq(s21_strstr("Hello", "hello"), strstr("Hello", "hello"));
  ck_assert_str_eq(s21_strstr("Hello", "Hello"), strstr("Hello", "Hello"));
  ck_assert_str_eq(s21_strstr("test\nnewline", "\nnew"),
                   strstr("test\nnewline", "\nnew"));
  ck_assert_str_eq(s21_strstr("Hello beautiful World", "beautiful World"),
                   strstr("Hello beautiful World", "beautiful World"));
  ck_assert_ptr_eq(s21_strstr("mississippi", "issip"),
                   strstr("mississippi", "issip"));
  ck_assert_str_eq(s21_strstr("mississippi", "issi"),
                   strstr("mississippi", "issi"));
  ck_assert_ptr_eq(s21_strstr("", "test"), strstr("", "test"));
  ck_assert_str_eq(s21_strstr("", ""), strstr("", ""));
}
END_TEST

START_TEST(test_strstr_normal) {
  char *str = "Hello dllol";
  char *str2 = "llo";
  ck_assert_ptr_eq(s21_strstr(str, str2), strstr(str, str2));
}
END_TEST

START_TEST(test_strstr_empty1) {
  char *str = "";
  char *str2 = "llo";
  ck_assert_ptr_eq(s21_strstr(str, str2), strstr(str, str2));
}
END_TEST

START_TEST(test_strstr_empty2) {
  char *str = "Hello";
  char *str2 = "";
  ck_assert_ptr_eq(s21_strstr(str, str2), strstr(str, str2));
}
END_TEST

START_TEST(test_strerror_known) {
  ck_assert_str_eq(s21_strerror(0), strerror(0));
  ck_assert_str_eq(s21_strerror(1), strerror(1));
  ck_assert_str_eq(s21_strerror(2), strerror(2));
}
END_TEST

START_TEST(test_strerror_unknown) {
  ck_assert_str_eq(s21_strerror(999), strerror(999));
  ck_assert_str_eq(s21_strerror(-5), strerror(-5));
}
END_TEST

START_TEST(test_strtok) {
  char s1[] = "one,two,three";
  char s2[] = "one,two,three";

  char *t1 = s21_strtok(s1, ",");
  char *t2 = strtok(s2, ",");

  while (t1 || t2) {
    ck_assert_ptr_nonnull(t1);
    ck_assert_ptr_nonnull(t2);
    ck_assert_str_eq(t1, t2);

    t1 = s21_strtok(NULL, ",");
    t2 = strtok(NULL, ",");
  }
}
END_TEST

START_TEST(test_sprintf_char) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Char: %c", 'A');
  sprintf(buf2, "Char: %c", 'A');
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_char_special) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Newline: %c", '\n');
  sprintf(buf2, "Newline: %c", '\n');
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_int_positive) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Number: %d", 123);
  sprintf(buf2, "Number: %d", 123);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_int_negative) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Negative: %d", -456);
  sprintf(buf2, "Negative: %d", -456);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_int_zero) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Zero: %d", 0);
  sprintf(buf2, "Zero: %d", 0);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_uint) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Unsigned: %u", 999);
  sprintf(buf2, "Unsigned: %u", 999);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_uint_zero) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Zero: %u", 0);
  sprintf(buf2, "Zero: %u", 0);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_float_positive) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Float: %f", 3.14);
  sprintf(buf2, "Float: %f", 3.14);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_float_negative) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Negative: %f", -2.5);
  sprintf(buf2, "Negative: %f", -2.5);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_float_zero) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Zero: %f", 0.0);
  sprintf(buf2, "Zero: %f", 0.0);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_string) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Hello %s!", "world");
  sprintf(buf2, "Hello %s!", "world");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_string_empty) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Empty: %s", "");
  sprintf(buf2, "Empty: %s", "");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_percent) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "Percent: %%");
  sprintf(buf2, "Percent: %%");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_mixed) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%s: %d, %c, %f%%", "Result", 42, 'X', 99.5);
  sprintf(buf2, "%s: %d, %c, %f%%", "Result", 42, 'X', 99.5);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_unknown) {
  char buf[100];
  int len = s21_sprintf(buf, "A%xB");
  ck_assert_str_eq(buf, "A%xB");
  ck_assert_int_eq(len, 4);
}
END_TEST

START_TEST(test_sprintf_width_int) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%5d", 42);
  sprintf(buf2, "%5d", 42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_width_string) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%10s", "hello");
  sprintf(buf2, "%10s", "hello");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_width_char) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%5c", 'A');
  sprintf(buf2, "%5c", 'A');
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_width_float) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%15f", 3.14);
  sprintf(buf2, "%15f", 3.14);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_minus_int) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%-5d", 42);
  sprintf(buf2, "%-5d", 42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_minus_string) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%-10s", "hello");
  sprintf(buf2, "%-10s", "hello");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_minus_float) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%-15f", 3.14);
  sprintf(buf2, "%-15f", 3.14);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_plus_positive) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%+d", 42);
  sprintf(buf2, "%+d", 42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_plus_negative) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%+d", -42);
  sprintf(buf2, "%+d", -42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_plus_float) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%+f", 3.14);
  sprintf(buf2, "%+f", 3.14);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_space_positive) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "% d", 42);
  sprintf(buf2, "% d", 42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_space_negative) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "% d", -42);
  sprintf(buf2, "% d", -42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_space_float) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "% f", 3.14);
  sprintf(buf2, "% f", 3.14);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_plus_width) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%+5d", 42);
  sprintf(buf2, "%+5d", 42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_minus_plus_width) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%-+5d", 42);
  sprintf(buf2, "%-+5d", 42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_space_width) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "% 5d", 42);
  sprintf(buf2, "% 5d", 42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_minus_space_width) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%- 5d", 42);
  sprintf(buf2, "%- 5d", 42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_precision_float_2) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%.2f", 3.14159);
  sprintf(buf2, "%.2f", 3.14159);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_precision_float_0) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%.0f", 3.14);
  sprintf(buf2, "%.0f", 3.14);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_precision_float_4) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%.4f", 2.5);
  sprintf(buf2, "%.4f", 2.5);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_precision_string) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%.3s", "hello");
  sprintf(buf2, "%.3s", "hello");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_precision_string_width) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%10.3s", "hello");
  sprintf(buf2, "%10.3s", "hello");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_precision_int) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%.5d", 42);
  sprintf(buf2, "%.5d", 42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_precision_int_negative) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%.5d", -42);
  sprintf(buf2, "%.5d", -42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_precision_int_plus) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%+.5d", 42);
  sprintf(buf2, "%+.5d", 42);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_length_h_int) {
  char buf1[100], buf2[100];
  short num = 32000;
  s21_sprintf(buf1, "%hd", num);
  sprintf(buf2, "%hd", num);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_length_h_uint) {
  char buf1[100], buf2[100];
  unsigned short num = 65000;
  s21_sprintf(buf1, "%hu", num);
  sprintf(buf2, "%hu", num);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_length_l_int) {
  char buf1[100], buf2[100];
  long num = 1234567890L;
  s21_sprintf(buf1, "%ld", num);
  sprintf(buf2, "%ld", num);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_length_l_uint) {
  char buf1[100], buf2[100];
  unsigned long num = 4000000000UL;
  s21_sprintf(buf1, "%lu", num);
  sprintf(buf2, "%lu", num);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_width_precision_float) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%10.2f", 3.14);
  sprintf(buf2, "%10.2f", 3.14);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_minus_width_precision_float) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%-10.2f", 3.14);
  sprintf(buf2, "%-10.2f", 3.14);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_sprintf_plus_precision_long) {
  char buf1[100], buf2[100];
  s21_sprintf(buf1, "%+.8ld", 12345L);
  sprintf(buf2, "%+.8ld", 12345L);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_to_upper_basic) {
  char *res = s21_to_upper("Hello World");
  ck_assert_str_eq(res, "HELLO WORLD");
  free(res);
}
END_TEST

START_TEST(test_to_upper_empty) {
  char *res = s21_to_upper("");
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_to_upper_numbers_symbols) {
  char *res = s21_to_upper("123!@#abcXYZ");
  ck_assert_str_eq(res, "123!@#ABCXYZ");
  free(res);
}
END_TEST

START_TEST(test_to_upper_null) { ck_assert_ptr_eq(s21_to_upper(NULL), NULL); }
END_TEST

START_TEST(test_to_lower_basic) {
  char *res = s21_to_lower("Hello World");
  ck_assert_str_eq(res, "hello world");
  free(res);
}
END_TEST

START_TEST(test_to_lower_empty) {
  char *res = s21_to_lower("");
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_to_lower_numbers_symbols) {
  char *res = s21_to_lower("123!@#AbCxYz");
  ck_assert_str_eq(res, "123!@#abcxyz");
  free(res);
}
END_TEST

START_TEST(test_to_lower_null) { ck_assert_ptr_eq(s21_to_lower(NULL), NULL); }
END_TEST

START_TEST(test_insert_middle) {
  char *res = s21_insert("Hello World", "Beautiful ", 6);
  ck_assert_str_eq(res, "Hello Beautiful World");
  free(res);
}
END_TEST

START_TEST(test_insert_start) {
  char *res = s21_insert("World", "Hello ", 0);
  ck_assert_str_eq(res, "Hello World");
  free(res);
}
END_TEST

START_TEST(test_insert_end) {
  char *res = s21_insert("Hello", " World", 5);
  ck_assert_str_eq(res, "Hello World");
  free(res);
}
END_TEST

START_TEST(test_insert_index_too_large) {
  ck_assert_ptr_eq(s21_insert("Hello", "World", 10), NULL);
}
END_TEST

START_TEST(test_insert_null_src) {
  ck_assert_ptr_eq(s21_insert(NULL, "abc", 0), NULL);
}
END_TEST

START_TEST(test_insert_null_str) {
  ck_assert_ptr_eq(s21_insert("abc", NULL, 0), NULL);
}
END_TEST

START_TEST(test_trim_spaces) {
  char *res = s21_trim("   Hello World   ", NULL);
  ck_assert_str_eq(res, "Hello World");
  free(res);
}
END_TEST

START_TEST(test_trim_custom_chars) {
  char *res = s21_trim("xxabcxx", "x");
  ck_assert_str_eq(res, "abc");
  free(res);
}
END_TEST

START_TEST(test_trim_no_chars_to_trim) {
  char *res = s21_trim("Hello", NULL);
  ck_assert_str_eq(res, "Hello");
  free(res);
}
END_TEST

START_TEST(test_trim_only_trim_chars) {
  char *res = s21_trim("     ", NULL);
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_trim_empty_string) {
  char *res = s21_trim("", NULL);
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_trim_null_src) { ck_assert_ptr_eq(s21_trim(NULL, NULL), NULL); }
END_TEST

Suite *s21_string_suite(void) {
  Suite *s = suite_create("s21_string");

  TCase *tc_memcpy = tcase_create("memcpy");
  tcase_add_test(tc_memcpy, test_memcpy);
  suite_add_tcase(s, tc_memcpy);

  TCase *tc_memset = tcase_create("memset");
  tcase_add_test(tc_memset, test_memset);
  suite_add_tcase(s, tc_memset);

  TCase *tc_memcmp = tcase_create("memcmp");
  tcase_add_test(tc_memcmp, test_memcmp);
  suite_add_tcase(s, tc_memcmp);

  TCase *tc_memchr = tcase_create("memchr");
  tcase_add_test(tc_memchr, test_memchr_normal);
  tcase_add_test(tc_memchr, test_memchr_empty);
  tcase_add_test(tc_memchr, test_memchr_null);
  suite_add_tcase(s, tc_memchr);

  TCase *tc_strlen = tcase_create("strlen");
  tcase_add_test(tc_strlen, test_strlen);
  suite_add_tcase(s, tc_strlen);

  TCase *tc_strncmp = tcase_create("strncmp");
  tcase_add_test(tc_strncmp, test_strncmp);
  suite_add_tcase(s, tc_strncmp);

  TCase *tc_strncpy = tcase_create("strncpy");
  tcase_add_test(tc_strncpy, test_strncpy);
  suite_add_tcase(s, tc_strncpy);

  TCase *tc_strncat = tcase_create("strncat");
  tcase_add_test(tc_strncat, test_strncat);
  suite_add_tcase(s, tc_strncat);

  TCase *tc_strchr = tcase_create("strchr");
  tcase_add_test(tc_strchr, test_strchr_normal);
  tcase_add_test(tc_strchr, test_strchr_empty);
  tcase_add_test(tc_strchr, test_strchr_null);
  suite_add_tcase(s, tc_strchr);

  TCase *tc_strrchr = tcase_create("strrchr");
  tcase_add_test(tc_strrchr, test_strrchr_normal);
  tcase_add_test(tc_strrchr, test_strrchr_empty);
  tcase_add_test(tc_strrchr, test_strrchr_null);
  suite_add_tcase(s, tc_strrchr);

  TCase *tc_strcspn = tcase_create("strcspn");
  tcase_add_test(tc_strcspn, test_strcspn);
  suite_add_tcase(s, tc_strcspn);

  TCase *tc_strpbrk = tcase_create("strpbrk");
  tcase_add_test(tc_strpbrk, test_strpbrk);
  suite_add_tcase(s, tc_strpbrk);

  TCase *tc_strstr = tcase_create("strstr");
  tcase_add_test(tc_strstr, test_strstr);
  tcase_add_test(tc_strstr, test_strstr_normal);
  tcase_add_test(tc_strstr, test_strstr_empty1);
  tcase_add_test(tc_strstr, test_strstr_empty2);
  suite_add_tcase(s, tc_strstr);

  TCase *tc_strerror = tcase_create("strerror");
  tcase_add_test(tc_strerror, test_strerror_known);
  tcase_add_test(tc_strerror, test_strerror_unknown);
  suite_add_tcase(s, tc_strerror);

  TCase *tc_strtok = tcase_create("strtok");
  tcase_add_test(tc_strtok, test_strtok);
  suite_add_tcase(s, tc_strtok);

  TCase *tc_to_upper = tcase_create("to_upper");
  tcase_add_test(tc_to_upper, test_to_upper_basic);
  tcase_add_test(tc_to_upper, test_to_upper_empty);
  tcase_add_test(tc_to_upper, test_to_upper_numbers_symbols);
  tcase_add_test(tc_to_upper, test_to_upper_null);
  suite_add_tcase(s, tc_to_upper);

  TCase *tc_to_lower = tcase_create("to_lower");
  tcase_add_test(tc_to_lower, test_to_lower_basic);
  tcase_add_test(tc_to_lower, test_to_lower_empty);
  tcase_add_test(tc_to_lower, test_to_lower_numbers_symbols);
  tcase_add_test(tc_to_lower, test_to_lower_null);
  suite_add_tcase(s, tc_to_lower);

  TCase *tc_insert = tcase_create("insert");
  tcase_add_test(tc_insert, test_insert_middle);
  tcase_add_test(tc_insert, test_insert_start);
  tcase_add_test(tc_insert, test_insert_end);
  tcase_add_test(tc_insert, test_insert_index_too_large);
  tcase_add_test(tc_insert, test_insert_null_src);
  tcase_add_test(tc_insert, test_insert_null_str);
  suite_add_tcase(s, tc_insert);

  TCase *tc_trim = tcase_create("trim");
  tcase_add_test(tc_trim, test_trim_spaces);
  tcase_add_test(tc_trim, test_trim_custom_chars);
  tcase_add_test(tc_trim, test_trim_no_chars_to_trim);
  tcase_add_test(tc_trim, test_trim_only_trim_chars);
  tcase_add_test(tc_trim, test_trim_empty_string);
  tcase_add_test(tc_trim, test_trim_null_src);
  suite_add_tcase(s, tc_trim);

  TCase *tc_sprintf = tcase_create("sprintf");
  tcase_add_test(tc_sprintf, test_sprintf_char);
  tcase_add_test(tc_sprintf, test_sprintf_char_special);
  tcase_add_test(tc_sprintf, test_sprintf_int_positive);
  tcase_add_test(tc_sprintf, test_sprintf_int_negative);
  tcase_add_test(tc_sprintf, test_sprintf_int_zero);
  tcase_add_test(tc_sprintf, test_sprintf_uint);
  tcase_add_test(tc_sprintf, test_sprintf_uint_zero);
  tcase_add_test(tc_sprintf, test_sprintf_float_positive);
  tcase_add_test(tc_sprintf, test_sprintf_float_negative);
  tcase_add_test(tc_sprintf, test_sprintf_float_zero);
  tcase_add_test(tc_sprintf, test_sprintf_string);
  tcase_add_test(tc_sprintf, test_sprintf_string_empty);
  tcase_add_test(tc_sprintf, test_sprintf_percent);
  tcase_add_test(tc_sprintf, test_sprintf_mixed);
  tcase_add_test(tc_sprintf, test_sprintf_unknown);
  tcase_add_test(tc_sprintf, test_sprintf_width_int);
  tcase_add_test(tc_sprintf, test_sprintf_width_string);
  tcase_add_test(tc_sprintf, test_sprintf_width_char);
  tcase_add_test(tc_sprintf, test_sprintf_width_float);
  tcase_add_test(tc_sprintf, test_sprintf_minus_int);
  tcase_add_test(tc_sprintf, test_sprintf_minus_string);
  tcase_add_test(tc_sprintf, test_sprintf_minus_float);
  tcase_add_test(tc_sprintf, test_sprintf_plus_positive);
  tcase_add_test(tc_sprintf, test_sprintf_plus_negative);
  tcase_add_test(tc_sprintf, test_sprintf_plus_float);
  tcase_add_test(tc_sprintf, test_sprintf_space_positive);
  tcase_add_test(tc_sprintf, test_sprintf_space_negative);
  tcase_add_test(tc_sprintf, test_sprintf_space_float);
  tcase_add_test(tc_sprintf, test_sprintf_plus_width);
  tcase_add_test(tc_sprintf, test_sprintf_minus_plus_width);
  tcase_add_test(tc_sprintf, test_sprintf_space_width);
  tcase_add_test(tc_sprintf, test_sprintf_minus_space_width);
  tcase_add_test(tc_sprintf, test_sprintf_precision_float_2);
  tcase_add_test(tc_sprintf, test_sprintf_precision_float_0);
  tcase_add_test(tc_sprintf, test_sprintf_precision_float_4);
  tcase_add_test(tc_sprintf, test_sprintf_precision_string);
  tcase_add_test(tc_sprintf, test_sprintf_precision_string_width);
  tcase_add_test(tc_sprintf, test_sprintf_precision_int);
  tcase_add_test(tc_sprintf, test_sprintf_precision_int_negative);
  tcase_add_test(tc_sprintf, test_sprintf_precision_int_plus);
  tcase_add_test(tc_sprintf, test_sprintf_length_h_int);
  tcase_add_test(tc_sprintf, test_sprintf_length_h_uint);
  tcase_add_test(tc_sprintf, test_sprintf_length_l_int);
  tcase_add_test(tc_sprintf, test_sprintf_length_l_uint);
  tcase_add_test(tc_sprintf, test_sprintf_width_precision_float);
  tcase_add_test(tc_sprintf, test_sprintf_minus_width_precision_float);
  tcase_add_test(tc_sprintf, test_sprintf_plus_precision_long);
  suite_add_tcase(s, tc_sprintf);

  return s;
}

int main(void) {
  SRunner *sr = srunner_create(s21_string_suite());
  // CK_VERBOSE or CK_NORMAL
  srunner_run_all(sr, CK_NORMAL);

  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? 0 : 1;
}