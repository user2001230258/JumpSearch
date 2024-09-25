#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_PRODUCTS 1000
#define MAX_CODE_LENGTH 10
#define MAX_NAME_LENGTH 50

struct Product {
    char code[MAX_CODE_LENGTH];
    char name[MAX_NAME_LENGTH];
    int quantity;
};

int min(int a, int b) {
    return (a < b) ? a : b;
}

int jumpSearch(struct Product inventory[], int n, const char* targetCode) {
    int step = (int)sqrt(n);
    int prev = 0;

    while (prev < n && strcmp(inventory[min(step, n) - 1].code, targetCode) < 0) {
        prev = step;
        step += (int)sqrt(n);
        if (prev >= n)
            return -1;
    }

    while (prev < n && strcmp(inventory[prev].code, targetCode) < 0) {
        prev++;
        if (prev == min(step, n))
            return -1;
    }

    if (prev < n && strcmp(inventory[prev].code, targetCode) == 0)
        return prev;

    return -1;
}

void saveToFile(struct Product inventory[], int n, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s,%s,%d\n", inventory[i].code, inventory[i].name, inventory[i].quantity);
    }

    fclose(file);
    printf("Da luu kho hang vao file %s\n", filename);
}

int loadFromFile(struct Product inventory[], const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file de doc.\n");
        return 0;
    }

    int n = 0;
    while (n < MAX_PRODUCTS && fscanf(file, "%[^,],%[^,],%d\n", inventory[n].code, inventory[n].name, &inventory[n].quantity) == 3) {
        n++;
    }

    fclose(file);
    printf("Da doc %d san pham tu file %s\n", n, filename);
    return n;
}

int main() {
    struct Product inventory[MAX_PRODUCTS];
    int n = 0;
    char filename[] = "inventory.txt";

    // Đọc kho hàng từ file
    n = loadFromFile(inventory, filename);

    // Thêm một số sản phẩm mới (nếu file trống hoặc không tồn tại)
    if (n == 0) {
        strcpy(inventory[n].code, "A001"); strcpy(inventory[n].name, "Ao thun"); inventory[n].quantity = 100; n++;
        strcpy(inventory[n].code, "B002"); strcpy(inventory[n].name, "Quan jean"); inventory[n].quantity = 75; n++;
        strcpy(inventory[n].code, "C003"); strcpy(inventory[n].name, "Giay Nike"); inventory[n].quantity = 50; n++;
        strcpy(inventory[n].code, "D004"); strcpy(inventory[n].name, "Tui xach"); inventory[n].quantity = 30; n++;
        strcpy(inventory[n].code, "E005"); strcpy(inventory[n].name, "Mu luoi trai"); inventory[n].quantity = 60; n++;
    }

    // Lưu kho hàng vào file
    saveToFile(inventory, n, filename);

    // Nhập mã đơn hàng để tìm kiếm
    char searchCode[MAX_CODE_LENGTH];
    printf("Nhap ma don hang: ");
    scanf("%s", searchCode);

    // Tìm kiếm một sản phẩm
    int result = jumpSearch(inventory, n, searchCode);

    if (result != -1) {
        printf("Tim thay: %s - %s (So luong: %d)\n", 
               inventory[result].code, 
               inventory[result].name, 
               inventory[result].quantity);
    } else {
        printf("Khong tim thay san pham.\n");
    }

    return 0;
}