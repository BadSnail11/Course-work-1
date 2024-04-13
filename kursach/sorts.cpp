#include "sorts.h"
#include "classes.h"

sorts::sorts() {}


template <typename T>
QList <T> sorts::qSort(QList <T> list, int size, int compare(T, T), int i){
    int j =  i + size - 1;
    T mid = list.value(i + size / 2);
    do {
        while (compare(list.value(i), mid) == 1){
            i++;
        }
        while (compare(list.value(j), mid) == 0){
            j--;
        }
        if (i <= j){
            list.swapItemsAt(i, j);
            i++;
            j--;
        }
    } while (i <= j);
    if (j > 0){
        list = qSort(list, j + 1, compare);
    }
    if (i < size){
        list = qSort(list, size - i, compare, i);
    }
    return list;
}
