/*
#include <stdio.h>

int add_one(int *a);

struct TEST {
    int c;
};

int main() {
    struct TEST t;
    struct TEST *pt = &t;

    //pt �� ����Ű�� ����ü ������ c ����� ���� 0 ���� �Ѵ�
    pt->c = 0;

    //    add_one �Լ��� ���ڿ� t ����ü ������ ��� c �� �ּҰ��� �����ϰ� �ִ�.

    add_one(&t.c);    // ������ �켱���� ����

    printf("t.c : %d \n", t.c);
    */
    /*
    add_one �Լ��� ���ڿ� pt �� ����Ű�� ����ü ������ ��� c
    �� �ּҰ��� �����ϰ� �ִ�.
    */
/*
    add_one(&pt->c);

    printf("t.c : %d \n", t.c);

    return 0;
}

int add_one(int *a) {
    *a += 1;    //a = *a + 1
    return 0;
}
*/