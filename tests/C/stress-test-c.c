#include <stdbool.h>
#include <stdio.h>

void print(int myInt) {
    printf("%d\n", myInt);
}
int globalA;
int globalB;
int results[64];

struct Node {
    int value;
    int pad1;
    int pad2;
    int pad3;
};

struct Node node0;
struct Node node1;
struct Node node2;
struct Node node3;
struct Node node4;
struct Node node5;
struct Node node6;
struct Node node7;
struct Node localNode0;
struct Node localNode1;
struct Node localNode2;
struct Node localNode3;

int factorial(int n) {
    int i;
    int acc;
    int temp[20];
    int mirror[20];
    acc = 1;
    i = 1;
    while (i <= n) {
        temp[i] = i;
        mirror[19 - i] = temp[i];
        acc = acc * i;
        i = i + 1;
    }
    return acc;
}

int fib_helper(int n, int a, int b) {
    if (n == 0) {
        return a;
    } else {
        return fib_helper(n - 1, b, a + b);
    }
}

int fib(int n) {
    return fib_helper(n, 0, 1);
}

int set_node_fields(int idx, int base) {
    int sum;
    sum = 0;
    if (idx == 0) {
        node0.value = base;
        node0.pad1 = base + 1;
        node0.pad2 = base + 2;
        node0.pad3 = base + 3;
        sum = node0.value + node0.pad1 + node0.pad2 + node0.pad3;
    } else if (idx == 1) {
        node1.value = base;
        node1.pad1 = base + 1;
        node1.pad2 = base + 2;
        node1.pad3 = base + 3;
        sum = node1.value + node1.pad1 + node1.pad2 + node1.pad3;
    } else if (idx == 2) {
        node2.value = base;
        node2.pad1 = base + 1;
        node2.pad2 = base + 2;
        node2.pad3 = base + 3;
        sum = node2.value + node2.pad1 + node2.pad2 + node2.pad3;
    } else if (idx == 3) {
        node3.value = base;
        node3.pad1 = base + 1;
        node3.pad2 = base + 2;
        node3.pad3 = base + 3;
        sum = node3.value + node3.pad1 + node3.pad2 + node3.pad3;
    } else if (idx == 4) {
        node4.value = base;
        node4.pad1 = base + 1;
        node4.pad2 = base + 2;
        node4.pad3 = base + 3;
        sum = node4.value + node4.pad1 + node4.pad2 + node4.pad3;
    } else if (idx == 5) {
        node5.value = base;
        node5.pad1 = base + 1;
        node5.pad2 = base + 2;
        node5.pad3 = base + 3;
        sum = node5.value + node5.pad1 + node5.pad2 + node5.pad3;
    } else if (idx == 6) {
        node6.value = base;
        node6.pad1 = base + 1;
        node6.pad2 = base + 2;
        node6.pad3 = base + 3;
        sum = node6.value + node6.pad1 + node6.pad2 + node6.pad3;
    } else {
        node7.value = base;
        node7.pad1 = base + 1;
        node7.pad2 = base + 2;
        node7.pad3 = base + 3;
        sum = node7.value + node7.pad1 + node7.pad2 + node7.pad3;
    }
    return sum;
}

int update_local_node(int idx, int base) {
    int result;
    result = 0;
    if (idx == 0) {
        localNode0.value = base;
        localNode0.pad1 = base + 100;
        localNode0.pad2 = localNode0.pad1 + 10;
        localNode0.pad3 = localNode0.pad2 + 10;
        result = localNode0.pad3;
    } else if (idx == 1) {
        localNode1.value = base;
        localNode1.pad1 = base + 100;
        localNode1.pad2 = localNode1.pad1 + 10;
        localNode1.pad3 = localNode1.pad2 + 10;
        result = localNode1.pad3;
    } else if (idx == 2) {
        localNode2.value = base;
        localNode2.pad1 = base + 100;
        localNode2.pad2 = localNode2.pad1 + 10;
        localNode2.pad3 = localNode2.pad2 + 10;
        result = localNode2.pad3;
    } else {
        localNode3.value = base;
        localNode3.pad1 = base + 100;
        localNode3.pad2 = localNode3.pad1 + 10;
        localNode3.pad3 = localNode3.pad2 + 10;
        result = localNode3.pad3;
    }
    return result;
}

int sum_structs(int count) {
    int i;
    int total;
    i = 0;
    total = 0;
    while (i < count) {
        total = total + set_node_fields(i, i * 7);
        i = i + 1;
    }
    return total;
}

int heavy_loop(int limit) {
    int acc;
    int i;
    int j;
    int table[50];
    int scratch[50];
    acc = 0;
    i = 0;
    while (i < limit) {
        j = 0;
        while (j < 50) {
            table[j] = (i + j) * (i - j + 7);
            scratch[j] = table[j] / (j / 5 + 1);
            acc = acc + scratch[j];
            j = j + 1;
        }
        i = i + 1;
    }
    return acc;
}

int switch_magic(int x) {
    int crazy;
    crazy = 0;
    switch (x) {
        case 0:
            crazy = crazy + 1;
            break;
        case 1:
            crazy = crazy + 3;
            break;
        case 2:
            crazy = crazy + 6;
            break;
        case 3:
            crazy = crazy + 10;
            break;
        default:
            crazy = crazy + 15;
            break;
    }
    return crazy;
}

int ternary_test(int x) {
    int y;
    y = (x > 10) ? (x * 2) : (x + 100);
    return y;
}

int bool_mix(int x, int y) {
    bool flag;
    flag = false;
    if (x > y) {
        flag = true;
    }
    if (flag && x > 0) {
        return 1;
    }
    if (x < 0 || y < 0) {
        return 2;
    }
    return 3;
}

int nested_arrays() {
    int outer[10];
    int inner[10];
    int guard;
    int i;
    guard = 0;
    i = 0;
    while (i < 10) {
        outer[i] = i * i;
        inner[i] = outer[i] - i;
        guard = guard + inner[i];
        i = i + 1;
    }
    return guard;
}

int cascade(int seed) {
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
    a = seed + 1;
    b = a * 2;
    c = b + 3;
    d = c * 4;
    e = d + 5;
    f = e * 6;
    g = f + 7;
    h = g * 8;
    return h;
}

int mod3(int value) {
    int div;
    int mod;
    div = value / 3;
    mod = value - div * 3;
    return mod;
}

int stress_branch(int count) {
    int i;
    int sum;
    int mod;
    i = 0;
    sum = 0;
    while (i < count) {
        mod = mod3(i);
        if (mod == 0) {
            sum = sum + i * 2;
        } else if (mod == 1) {
            sum = sum + i * 3;
        } else {
            sum = sum + i * 4;
        }
        i = i + 1;
    }
    return sum;
}

int mega_stack() {
    int block1[60];
    int block2[60];
    int block3[60];
    int block4[60];
    int block5[60];
    int block6[60];
    int block7[60];
    int block8[60];
    int i;
    int total;
    total = 0;
    i = 0;
    while (i < 60) {
        block1[i] = i;
        block2[i] = block1[i] + 1;
        block3[i] = block2[i] + 2;
        block4[i] = block3[i] + 3;
        block5[i] = block4[i] + 4;
        block6[i] = block5[i] + 5;
        block7[i] = block6[i] + 6;
        block8[i] = block7[i] + 7;
        total = total + block8[i];
        i = i + 1;
    }
    return total;
}

int main() {
    int i;
    int total;
    int arr[100];
    int mirror[100];
    int evenSum;
    int oddSum;
    int bools[10];
    bool toggles[10];
    int idx;

    i = 0;
    total = 0;
    evenSum = 0;
    oddSum = 0;
    while (i < 100) {
        arr[i] = i * 11 - 7;
        mirror[99 - i] = arr[i];
        if ((i / 2) * 2 == i) {
            evenSum = evenSum + arr[i];
        } else {
            oddSum = oddSum + arr[i];
        }
        idx = i - (i / 10) * 10;
        if (arr[i] > 0) {
            toggles[idx] = true;
        } else {
            toggles[idx] = false;
        }
        i = i + 1;
    }

    globalA = factorial(6);
    globalB = fib(12);
    results[0] = heavy_loop(5);
    results[1] = sum_structs(8);
    results[2] = switch_magic(3);
    results[3] = ternary_test(5);
    results[4] = bool_mix(-1, 2);
    results[5] = nested_arrays();
    results[6] = cascade(9);
    results[7] = stress_branch(20);
    results[8] = mega_stack();

    i = 0;
    while (i < 4) {
        total = total + update_local_node(i, cascade(i));
        i = i + 1;
    }

    i = 0;
    while (i < 10) {
        int a;
        int b;
        int c;
        int d;
        int e;
        int f;
        int g;
        int h;
        int k;
        int l;
        a = i + 1;
        b = a * 2;
        c = b + 3;
        d = c * 4;
        e = d + 5;
        f = e * 6;
        g = f + 7;
        h = g * 8;
        k = h + 9;
        l = k * 10;
        bools[i] = l;
        total = total + l;
        i = i + 1;
    }

    i = 0;
    while (i < 9) {
        print(i);
        print(results[i]);
        i = i + 1;
    }

    print(globalA);
    print(globalB);
    print(evenSum);
    print(oddSum);
    print(total);
    print(arr[0]);
    print(arr[99]);
    print(mirror[0]);
    print(mirror[99]);
    print(sum_structs(3));
    print(heavy_loop(3));

    i = 0;
    while (i < 5) {
        if (toggles[i]) {
            print(1);
        } else {
            print(0);
        }
        i = i + 1;
    }

    return 0;
}

