#include <stdio.h>
#include <string.h>
#include <math.h>

struct LienLac {
    char ten[50];
    char sdt[20];
};

typedef struct LienLac LL;

int min(int a, int b) {
    return (a < b) ? a : b;
}

int jumpSearch(LL danhsach[], int n, char k[]) {
    int step = sqrt(n);
    int prev = 0;

    while (strcmp(danhsach[min(prev + step, n) - 1].ten, k) <= 0) {
        if (strcmp(danhsach[min(prev + step, n) - 1].ten, k) == 0) {
            return min(prev + step, n) - 1;
        }
        prev = min(prev + step, n);
        if (prev >= n) {
            return -1;
        }
    }

    while (prev < n && strcmp(danhsach[prev].ten, k) <= 0) {
        if (strcmp(danhsach[prev].ten, k) == 0) {
            return prev;
        }
        prev++;
    }

    return -1;
}

int main() {
    FILE* file;
    LL Ds[50];
    int solienlac = 0;

    file = fopen("DanhBa.txt", "r");
    if (file == NULL) {
        printf("Khong the mo tep DanhBa.txt\n");
        return 1;
    }

    while (fscanf(file, "%49s %19s", Ds[solienlac].ten, Ds[solienlac].sdt) == 2) {
        solienlac++;
        if (solienlac >= 50) { 
            printf("Danh ba qua lon, khong the doc them.\n");
            break;
        }
    }
    fclose(file);

    // Sap xep BUBBLE SORT
    for (int i = 0; i < solienlac - 1; i++) {
        for (int j = i + 1; j < solienlac; j++) {
            if (strcmp(Ds[i].ten, Ds[j].ten) > 0) {
                LL temp = Ds[i];
                Ds[i] = Ds[j];
                Ds[j] = temp;
            }
        }
    }

    char k[50];
    printf("Nhap ten lien lac can tim: ");
    fgets(k, sizeof(k), stdin);
    k[strcspn(k, "\n")] = '\0';

    int vitri = jumpSearch(Ds, solienlac, k);

    if (vitri != -1) {
        printf("Lien lac '%s' co so dien thoai: %s\n", Ds[vitri].ten, Ds[vitri].sdt);
    } else {
        printf("Khong tim thay lien lac '%s' trong danh ba.\n", k);
    }

    return 0;
}