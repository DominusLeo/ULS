#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *new_element = mx_create_node(data);/*створюємо поінтер на новий
                                                 елемент листа і одразу в ньому
                                                 новий елемент з новими даними*/
    t_list *temp = *list;/*створюємо новий поінтер який
                           буде відсилати на кінець листа*/
    if (list == NULL || *list == NULL) {
        *list = new_element;
        return;
    }
    if(!data)
        return;
    for (; temp->next; temp = temp->next);/*переставляємо поінтер на кінець,
                                            прирівнюючи його до нексту,
                                            доки той не буде НУЛЛем*/
    temp->next = new_element;
//    new_element->next = *list;
//    *list = new_element;
}
