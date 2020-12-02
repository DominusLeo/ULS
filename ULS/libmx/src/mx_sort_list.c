#include "libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    t_list *buf;
    void *temp;

    for (int i = 0; i < mx_list_size(lst); i++) {
        buf = lst;
        for (int j = 0; j < mx_list_size(lst) - 1; j++) {
            if (cmp(buf->data, buf->next->data)) {
                temp = buf->data;
                buf->data = buf->next->data;
                buf->next->data = temp;
            }
        buf = buf->next;
        }
    }
    return lst;
}
