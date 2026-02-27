#include "s21_string.h"

#include <stdlib.h>

//////////////////////////////////////////////////O

void *s21_memchr(const void *str, int c, s21_size n) {
  const unsigned char *cur = (const unsigned char *)str;
  unsigned char target = (unsigned char)c;
  void *res = NULL;
  for (s21_size i = 0; i < n && res == NULL; i++) {
    if (cur[i] == target) {
      res = (void *)(cur + i);
    }
  }
  return res;
}
char *s21_strchr(const char *str, int c) {
  const char *cur = str;
  char target = (char)c;
  char *res = NULL;
  while (*cur != target && *cur != '\0') cur++;
  if (*cur != '\0' || target == '\0') res = (char *)cur;
  return res;
}
char *s21_strrchr(const char *str, int c) {
  const char *cur = str + s21_strlen(str);
  char target = (char)c;
  char *res = NULL;
  while (*cur != target && cur != str) cur--;
  if (*cur == target) res = (char *)cur;
  return res;
}

///////sprintf

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int written = 0;
  const char *p = format;

  while (*p != '\0') {
    if (*p == '%') {
      p++;

      FormatFlags flags;
      p = parse_flags(p, &flags);

      if (*p == 'c') {
        written += format_char_with_flags(str + written, &args, &flags);
      } else if (*p == 'd') {
        written += format_int_with_flags(str + written, &args, &flags);
      } else if (*p == 'u') {
        written += format_uint_with_flags(str + written, &args, &flags);
      } else if (*p == 'f') {
        written += format_float_with_flags(str + written, &args, &flags);
      } else if (*p == 's') {
        written += format_string_with_flags(str + written, &args, &flags);
      } else if (*p == '%') {
        str[written++] = '%';
      } else {
        str[written++] = '%';
        str[written++] = *p;
      }
    } else {
      str[written++] = *p;
    }
    p++;
  }

  str[written] = '\0';
  va_end(args);
  return written;
}
// reads flags and width, return specificator
const char *parse_flags(const char *p, FormatFlags *flags) {
  flags->minus = 0;
  flags->plus = 0;
  flags->space = 0;
  flags->width = 0;
  flags->precision = 0;
  flags->has_precision = 0;
  flags->length = 0;

  while (*p == '-' || *p == '+' || *p == ' ') {
    if (*p == '-')
      flags->minus = 1;
    else if (*p == '+')
      flags->plus = 1;
    else if (*p == ' ')
      flags->space = 1;
    p++;
  }

  while (*p >= '0' && *p <= '9') {
    flags->width = flags->width * 10 + (*p - '0');
    p++;
  }

  if (*p == '.') {
    p++;
    flags->has_precision = 1;
    while (*p >= '0' && *p <= '9') {
      flags->precision = flags->precision * 10 + (*p - '0');
      p++;
    }
  }

  if (*p == 'h' || *p == 'l') {
    flags->length = *p;
    p++;
  }

  return p;
}
int add_padding(char *str, int len, const FormatFlags *flags) {
  int padding = 0;

  if (flags->width > len) {
    padding = flags->width - len;
  }

  if (padding == 0) {
    return len;
  }

  if (!flags->minus) {
    for (int i = len - 1; i >= 0; i--) {
      str[i + padding] = str[i];
    }
    for (int i = 0; i < padding; i++) {
      str[i] = ' ';
    }
  } else {
    for (int i = 0; i < padding; i++) {
      str[len + i] = ' ';
    }
  }

  return len + padding;
}
// %c
int format_char_with_flags(char *str, va_list *args, const FormatFlags *flags) {
  char c = (char)va_arg(*args, int);
  str[0] = c;
  return add_padding(str, 1, flags);
}
// %s
int format_string_with_flags(char *str, va_list *args,
                             const FormatFlags *flags) {
  const char *s = va_arg(*args, char *);
  int len = 0;

  while (s[len] != '\0' && (!flags->has_precision || len < flags->precision)) {
    str[len] = s[len];
    len++;
  }

  return add_padding(str, len, flags);
}
void reverse_string(char *str, int len) {
  int start = 0;
  int end = len - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}
int int_to_string(int num, char *str) {
  int i = 0;
  int is_negative = 0;

  if (num == 0) {
    str[i++] = '0';
  } else {
    if (num < 0) {
      is_negative = 1;
      num = -num;
    }

    while (num != 0) {
      str[i++] = (num % 10) + '0';
      num = num / 10;
    }

    if (is_negative) {
      str[i++] = '-';
    }

    reverse_string(str, i);
  }

  return i;
}

// %d
int format_int_with_flags(char *str, va_list *args, const FormatFlags *flags) {
  long num;

  if (flags->length == 'h') {
    num = (short)va_arg(*args, int);
  } else if (flags->length == 'l') {
    num = va_arg(*args, long);
  } else {
    num = va_arg(*args, int);
  }

  int len = 0;
  char temp[50];

  int temp_len = long_to_string(num, temp);

  if (num >= 0) {
    if (flags->plus) {
      str[len++] = '+';
    } else if (flags->space) {
      str[len++] = ' ';
    }
  }

  if (flags->has_precision) {
    len += apply_int_precision(str + len, temp, temp_len, flags->precision);
  } else {
    for (int i = 0; i < temp_len; i++) {
      str[len++] = temp[i];
    }
  }

  return add_padding(str, len, flags);
}
int long_to_string(long num, char *str) {
  int i = 0;
  int is_negative = 0;

  if (num == 0) {
    str[i++] = '0';
  } else {
    if (num < 0) {
      is_negative = 1;
      num = -num;
    }

    while (num != 0) {
      str[i++] = (num % 10) + '0';
      num = num / 10;
    }

    if (is_negative) {
      str[i++] = '-';
    }

    reverse_string(str, i);
  }

  return i;
}
int apply_int_precision(char *dest, const char *src, int src_len,
                        int precision) {
  int len = 0;
  int num_digits = src_len;

  if (src[0] == '-') {
    num_digits--;
  }

  int zeros = precision - num_digits;

  if (zeros > 0) {
    if (src[0] == '-') {
      dest[len++] = '-';
      for (int i = 0; i < zeros; i++) {
        dest[len++] = '0';
      }
      for (int i = 1; i < src_len; i++) {
        dest[len++] = src[i];
      }
    } else {
      for (int i = 0; i < zeros; i++) {
        dest[len++] = '0';
      }
      for (int i = 0; i < src_len; i++) {
        dest[len++] = src[i];
      }
    }
  } else {
    for (int i = 0; i < src_len; i++) {
      dest[len++] = src[i];
    }
  }

  return len;
}

int uint_to_string(unsigned int num, char *str) {
  int i = 0;

  if (num == 0) {
    str[i++] = '0';
  } else {
    while (num != 0) {
      str[i++] = (num % 10) + '0';
      num = num / 10;
    }

    reverse_string(str, i);
  }

  return i;
}

// %u
int format_uint_with_flags(char *str, va_list *args, const FormatFlags *flags) {
  unsigned long num;

  if (flags->length == 'h') {
    num = (unsigned short)va_arg(*args, unsigned int);
  } else if (flags->length == 'l') {
    num = va_arg(*args, unsigned long);
  } else {
    num = va_arg(*args, unsigned int);
  }

  char temp[50];
  int temp_len = 0;

  if (num == 0) {
    temp[temp_len++] = '0';
  } else {
    while (num != 0) {
      temp[temp_len++] = (num % 10) + '0';
      num = num / 10;
    }
    reverse_string(temp, temp_len);
  }

  int len = 0;
  for (int i = 0; i < temp_len; i++) {
    str[len++] = temp[i];
  }

  return add_padding(str, len, flags);
}

int float_to_string_with_precision(double num, char *str, int precision) {
  int int_part = (int)num;
  double frac_part = num - int_part;

  if (num < 0) {
    frac_part = -frac_part;
  }

  int len = int_to_string(int_part, str);

  if (precision > 0) {
    str[len++] = '.';

    for (int i = 0; i < precision; i++) {
      frac_part *= 10;
      int digit = (int)frac_part;
      str[len++] = digit + '0';
      frac_part -= digit;
    }
  }

  return len;
}

// %f
int format_float_with_flags(char *str, va_list *args, FormatFlags *flags) {
  double num = va_arg(*args, double);
  int len = 0;

  if (num >= 0) {
    if (flags->plus) {
      str[len++] = '+';
    } else if (flags->space) {
      str[len++] = ' ';
    }
  }

  int precision = flags->has_precision ? flags->precision : 6;
  len += float_to_string_with_precision(num, str + len, precision);

  return add_padding(str, len, flags);
}

////////////////////////////////////////////////N

char *s21_strstr(const char *haystack, const char *needle) {
  if (haystack == S21_NULL || needle == S21_NULL) {
    return S21_NULL;
  }
  if (needle[0] == '\0') {
    return (char *)haystack;
  }
  for (s21_size i = 0; haystack[i] != '\0'; i++) {
    s21_size j = 0;
    while (needle[j] != '\0' && haystack[i + j] == needle[j]) {
      j++;
    }
    if (needle[j] == '\0') {
      return (char *)(haystack + i);
    }
  }
  return S21_NULL;
}

s21_size s21_strlen(const char *str) {
  s21_size size = 0;
  while (str[size] != '\0') {
    size++;
  }
  return size;
}

int s21_memcmp(const void *str1, const void *str2, s21_size n) {
  if (n == 0) {
    return 0;
  }
  const unsigned char *first = (unsigned char *)str1;
  const unsigned char *second = (unsigned char *)str2;
  for (s21_size i = 0; i < n; i++) {
    if (first[i] != second[i]) {
      int final = (int)(first[i] - second[i]);
      return final;
    }
  }
  return 0;
}

char *s21_strncpy(char *dest, const char *src, s21_size n) {
  s21_size i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  if (n > i) {
    for (s21_size c = i; c < n; c++) {
      dest[c] = '\0';
    }
  }
  return dest;
}

s21_size s21_strcspn(const char *str1, const char *str2) {
  s21_size i, j;
  for (i = 0; str1[i] != '\0'; i++) {
    for (j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        return i;
      }
    }
  }
  return i;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size i, j;
  for (i = 0; str1[i] != '\0'; i++) {
    for (j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        return (char *)(str1 + i);
      }
    }
  }
  return S21_NULL;
}

////////////////////////////////////////D

char *s21_strncat(char *dest, const char *src, s21_size n) {
  s21_size dlen = s21_strlen(dest);
  s21_size i = 0;

  for (; i < n && src[i]; i++) {
    dest[dlen + i] = src[i];
  }
  dest[dlen + i] = '\0';
  return dest;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last = S21_NULL;

  if (str) last = str;
  if (!last) return S21_NULL;

  while (*last && s21_strchr(delim, *last)) {
    last++;
  }

  if (!*last) return S21_NULL;

  char *token_start = last;

  while (*last && !s21_strchr(delim, *last)) {
    last++;
  }

  if (*last) {
    *last = '\0';
    last++;
  }

  return token_start;
}

void *s21_memcpy(void *dest, const void *src, s21_size n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  for (s21_size i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size n) {
  unsigned char *s = (unsigned char *)str;
  unsigned char ch = (unsigned char)c;

  for (s21_size i = 0; i < n; i++) {
    s[i] = ch;
  }
  return str;
}

int s21_strncmp(const char *str1, const char *str2, s21_size n) {
  for (s21_size i = 0; i < n; i++) {
    if (str1[i] != str2[i] || str1[i] == '\0')
      return (unsigned char)str1[i] - (unsigned char)str2[i];
  }
  return 0;
}

#ifdef __linux__
static const char *linux_errors[] = {
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
};
#define ERRORS_COUNT (sizeof(linux_errors) / sizeof(linux_errors[0]))
#elif __APPLE__
static const char *mac_errors[] = {
    "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
};
#define ERRORS_COUNT (sizeof(mac_errors) / sizeof(mac_errors[0]))
#endif

char *s21_strerror(int errnum) {
  static char buffer[128];

  if (errnum >= 0 && errnum < (int)ERRORS_COUNT) {
#ifdef __linux__
    return (char *)linux_errors[errnum];
#elif __APPLE__
    return (char *)mac_errors[errnum];
#endif
  }

  int i = 0;
#ifdef __linux__
  const char *prefix = "Unknown error ";
#elif __APPLE__
  const char *prefix = "Unknown error: ";
#endif

  while (prefix[i]) {
    buffer[i] = prefix[i];
    i++;
  }

  int num = errnum;
  if (num < 0) {
    buffer[i++] = '-';
    num = -num;
  }

  char tmp[20];
  int j = 0;
  do {
    tmp[j++] = (char)('0' + num % 10);
    num /= 10;
  } while (num);

  while (j--) buffer[i++] = tmp[j];
  buffer[i] = '\0';

  return buffer;
}
static int s21_is_upper(char c) { return (c >= 'A' && c <= 'Z'); }

static int s21_is_lower(char c) { return (c >= 'a' && c <= 'z'); }

static int s21_is_trim_char(char c, const char *trim_chars) {
  int found = 0;
  for (s21_size i = 0; trim_chars[i] != '\0'; i++) {
    if (c == trim_chars[i]) {
      found = 1;
      break;
    }
  }
  return found;
}
void *s21_to_upper(const char *str) {
  if (!str) return NULL;

  s21_size len = s21_strlen(str);
  char *res = (char *)malloc(len + 1);
  if (!res) return NULL;

  for (s21_size i = 0; i < len; i++) {
    if (s21_is_lower(str[i]))
      res[i] = str[i] - ('a' - 'A');
    else
      res[i] = str[i];
  }
  res[len] = '\0';

  return res;
}
void *s21_to_lower(const char *str) {
  if (!str) return NULL;

  s21_size len = s21_strlen(str);
  char *res = (char *)malloc(len + 1);
  if (!res) return NULL;

  for (s21_size i = 0; i < len; i++) {
    if (s21_is_upper(str[i]))
      res[i] = str[i] + ('a' - 'A');
    else
      res[i] = str[i];
  }
  res[len] = '\0';

  return res;
}
void *s21_insert(const char *src, const char *str, size_t start_index) {
  if (!src || !str) return NULL;

  s21_size src_len = s21_strlen(src);
  s21_size str_len = s21_strlen(str);

  if (start_index > src_len) return NULL;

  char *res = (char *)malloc(src_len + str_len + 1);
  if (!res) return NULL;

  s21_size i = 0;

  for (; i < start_index; i++) res[i] = src[i];

  for (s21_size j = 0; j < str_len; j++) res[i++] = str[j];

  for (s21_size k = start_index; k < src_len; k++) res[i++] = src[k];

  res[i] = '\0';

  return res;
}
void *s21_trim(const char *src, const char *trim_chars) {
  if (!src) return NULL;
  if (!trim_chars) trim_chars = " ";

  s21_size start = 0;
  s21_size end = s21_strlen(src);

  while (src[start] && s21_is_trim_char(src[start], trim_chars)) start++;

  if (start == end) {
    char *empty = (char *)malloc(1);
    if (empty) empty[0] = '\0';
    return empty;
  }

  end--;
  while (end > start && s21_is_trim_char(src[end], trim_chars)) end--;

  s21_size len = end - start + 1;
  char *res = (char *)malloc(len + 1);
  if (!res) return NULL;

  for (s21_size i = 0; i < len; i++) res[i] = src[start + i];

  res[len] = '\0';

  return res;
}
