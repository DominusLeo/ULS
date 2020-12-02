#include "libmx.h"

void mx_push_front(t_list **list, void *data) {
    t_list *new_element = mx_create_node(data);/*створюємо поінтер на новий
                                                 елемент листа і одразу в ньому
                                                 новий елемент з новими даними*/

    if (*list == NULL) {
        *list = new_element;
        return;
    }
    if(!data)
        return;
    new_element->next = *list;/*поінтер на лист є першим елементом -
                                тому присвоїв його в некст ми поставили
                                вказівник на новий елемент на початок*/
    *list = new_element;//вписали відповідно в цей поінтер дані нового елементу
}
