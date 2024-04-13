#ifndef SORTS_H
#define SORTS_H

template <typename T>
QList <T> qSort(QList <T> list, int size, int compare(T, T), int i = 0){
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

#endif // SORTS_H
