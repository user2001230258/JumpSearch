#include <stdio.h>
#include <string.h>
#include <math.h>

struct HangHoa {
    char ma[10]; // Mã đơn hàng
    char ten[20]; // Tên hàng hóa
    int soluong; // Số lượng
};

typedef struct HangHoa HH;

int jumpSearch(HH Ds[], int n, char k[]) {
    int step = sqrt(n);
    int prev = 0;

    while (strcmp(Ds[prev].ma, k) != 0 && prev < n) {
        if (strcmp(Ds[prev].ma, k) > 0) {
            return -1;
        }
        prev += step;
    }

    if (prev >= n) {
        prev -= step;
    }

    while (prev < n) {
        if (strcmp(Ds[prev].ma, k) == 0) {
            return prev;
        }
        prev++;
    }

    return -1;
}

int main() {
    FILE* file;
    HH Ds[50];
    int soluonghanghoa = 0;
    file = fopen("KhoHang.txt", "r");
    if (file == NULL) {
        printf("Khong the mo tep KhoHang.txt\n");
        return 1;
    }

    while (fscanf(file, "%s %s %d", Ds[soluonghanghoa].ma, Ds[soluonghanghoa].ten, &Ds[soluonghanghoa].soluong) == 3) {
        soluonghanghoa++;
        if (soluonghanghoa >= 49) {
            printf("Kho hang qua lon, khong the doc them.\n");
            break;
        }
    }
    fclose(file);

    // Sort the array before using jump search
    for (int i = 0; i < soluonghanghoa - 1; i++) {
        for (int j = i + 1; j < soluonghanghoa; j++) {
            if (strcmp(Ds[i].ma, Ds[j].ma) > 0) {
                HH temp = Ds[i];
                Ds[i] = Ds[j];
                Ds[j] = temp;
            }
        }
    }

    char k[10];
    printf("Nhap ma don hang can tim: ");
    fgets(k, sizeof(k), stdin);   //sizeof(hangcantim) có thể thay = 99
    k[strcspn(k, "\n")] = '\0';//gets

    int vitri = jumpSearch(Ds, soluonghanghoa, k);
    if (vitri != -1) {
        printf("Hang hoa '%s' ton tai trong kho\n", k);
        printf("Ten: %s\n", Ds[vitri].ten);
        printf("So luong: %d\n", Ds[vitri].soluong);
    }
    else {
        printf("Hang hoa '%s' khong ton tai trong kho.\n", k);
    }

    return 0;
}