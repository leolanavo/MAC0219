#include "../include/my_thread.hpp"

void *combineUnit(void *prm) {
    params p = (params) prm;

    p->target.data[p->x][p->y] = p->ai;
    p->target.data[p->x][p->y + 1] = p->bj;
}
