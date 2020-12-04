#ifndef HEADER_H
#define HEADER_H

#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <malloc/malloc.h>
#include <stdlib.h>
#include <stdio.h>
# include <stdarg.h>
# include <wchar.h>
# include <wctype.h>
# include <stdint.h>

typedef struct s_list {
    void *data;
    struct s_list *next;
}               t_list;

//for ft_printf
# define FLSIZ(x) x == 'j' || x == 'z' || x == '#' || x == 'l' || x == 'h'
# define FL2(x) x == ' ' || (x != 44 && x != 47 && x > 41 && x < 58) || x == 'L'
# define DEVAL(x) x == 'D' || x == 'd' || x == 'x' || x == 'O' || x == 'b'
# define DEVA2(x) x == 'i' || x == 'o' || x == 'X' || x == 'u' || x == 'U'
# define OPER(x) (x < 96 || x > 103) && x != 105 && x != 120 && x != 114
# define OPE2(x) x != 115 && (x < 110 || x > 112) && x != 117  && x != 83
# define OPE3(x) (x < 65 || x > 71) && x != 85 && x != 88 && x != 79

//int					mx_atoi(const char *str);
int					ft_nbrlen(intmax_t c, int a);
int					ft_printf(const char *format, ...);
void				ft_prfoper(char *s, va_list *ar, int *i);
void				ft_prfnbr(char c, int *i, va_list *ar, char *ito);
char				*ft_itoabase(uintmax_t c, int l, int y);
size_t				ft_strlen(const char *s);
char				*unistr(wchar_t *s, int *j);
char				*unicd(wint_t c);
void				ft_prfdbl(char c, int *i, va_list *ar);
//char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
uintmax_t			ft_basetoint(char *s, int base);
char				*ft_joinfree(char *s1, char *s2, int j);
void				ft_dblhex(long double c, int *i, int y);
size_t				ft_wcharlen(const wchar_t *s);
void				ft_precforp(char *s, int *i);
void				ft_outun(char *s, int *i, int j, int c);
char				*ft_qstr(char *s, int *i);
void				strendf(char s, int *i);
char				*ft_rotnb(char *s, int i);
//______

//Utils pack
void mx_printchar(char c);
void mx_print_unicode(wchar_t c);//_________________________________________70+!
void mx_printstr(const char *s);
void mx_print_strarr(char **arr, const char *delim);
void mx_printint(int n);
double mx_pow(double n, unsigned int pow);
int mx_sqrt(int x);
char *mx_nbr_to_hex(unsigned long nbr);
unsigned long mx_hex_to_nbr(const char *hex);
char *mx_itoa(int number);
void mx_foreach(int *arr, int size, void (*f)(int));
int mx_binary_search(char **arr, int size, const char *s, int *count);
int mx_bubble_sort(char **arr, int size);
int mx_quicksort(char **arr, int left, int right);//________________________60-?

//String pack
int mx_strlen(const char *s);
void mx_swap_char(char *s1, char *s2);
void mx_str_reverse(char *s);
void mx_strdel(char **str);
void mx_del_strarr(char ***arr);
int mx_get_char_index(const char *str, char c);
char *mx_strdup(const char *s1);
char *mx_strndup(const char *s1, size_t n);//_______________________________90+!
char *mx_strcpy(char *dst, const char *src);
char *mx_strncpy(char *dst, const char *src, int len);
int mx_strcmp(const char *s1, const char *s2);
char *mx_strcat(char *restrict s1, const char *restrict s2);
char *mx_strstr(const char *haystack, const char *needle);
int mx_get_substr_index(const char *str, const char *sub);
int mx_count_substr(const char *str, const char *sub);//____________________70+?
int mx_count_words(const char *str, char c);//______________________________95+!
char *mx_strnew(const int size);
char *mx_strtrim(const char *str);
char *mx_del_extra_spaces(const char *str);
char **mx_strsplit(const char *s, char c);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_file_to_str(const char *file);
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd);//10-?
char *mx_replace_substr(const char *str, const char *sub, const char *replace);

//Memory pack
void *mx_memset(void *b, int c, size_t len);
void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
int mx_memcmp(const void *s1, const void *s2, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memmem(const void *big, size_t big_len, const void *little,
                size_t little_len);
void *mx_memmove(void *dst, const void *src, size_t len);
void *mx_realloc(void *ptr, size_t size);

//List pack
t_list *mx_create_node(void *data);
void mx_push_front(t_list **list, void *data);
void mx_push_back(t_list **list, void *data);
void mx_pop_front(t_list **head);
void mx_pop_back(t_list **head);
int mx_list_size(t_list *list);
t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *));



//helpfull
int mx_strncmp(const char *s1, const char *s2, int n);//some bugs or no
char *mx_strchr(const char *s, int c);
bool mx_isdigit(int c);
bool mx_islower(int c);
bool mx_isupper(int c);
bool mx_isspace(char c);
bool mx_isalpha(int c);
int my_sort_arr_int(int *arr, int size);
int mx_atoi(const char *str);
void mx_printerr(const char *s);
void mx_arr_rotate(int *arr, int size, int shift);
void mx_str_rotate(char **arr, int size, int shift);
void mx_sort_arr_char(char *arr[], int size);//my own
int mx_quicksort_int(int *arr, int left, int right);//my own
void mx_print_unicode_str(char *str);//my own
char **mx_unique_elements(char **src, int count);//my own

#endif
