#include <stdio.h>
#include <string.h>
#include <math.h>

// Định nghĩa cấu trúc LienLac
struct LienLac {
    char ten[50];
    char sdt[20];
};

typedef struct LienLac LL;

// Hàm tìm kiếm theo phương pháp Jump Search
int jumpSearch(LL danhsach[], int n, char k[]) {
    int step = sqrt(n);
    int prev = 0;
    int jump = step;

    // Vòng lặp chính, tìm vùng chứa phần tử cần tìm
    while (strcmp(danhsach[jump - 1].ten, k) < 0) {
        prev = jump;
        jump += step;

        // Nếu vượt quá kích thước mảng, đặt jump bằng n
        if (jump > n) {
            jump = n;
        }

        // Nếu prev vượt quá kích thước mảng, không tìm thấy
        if (prev >= n) {
            return -1;
        }
    }

    // Tìm tuyến tính trong vùng được xác định
    while (prev < jump && strcmp(danhsach[prev].ten, k) <= 0) {
        if (strcmp(danhsach[prev].ten, k) == 0) {
            return prev;
        }
        prev++;
    }

    return -1;  // Không tìm thấy
}

int main() {
    FILE* file;
    LL Ds[50];
    int solienlac = 0;

    // Mở tệp danh bạ
    file = fopen("DanhBa.txt", "r");
    if (file == NULL) {
        printf("Khong the mo tep DanhBa.txt\n");
        return 1;
    }

    // Đọc dữ liệu từ tệp và lưu vào mảng
    while (fscanf(file, "%49s %19s", Ds[solienlac].ten, Ds[solienlac].sdt) == 2) {
        solienlac++;
        if (solienlac >= 50) { 
            printf("Danh ba qua lon, khong the doc them.\n");
            break;
        }
    }
    fclose(file);

    // Sắp xếp danh sách bằng Bubble Sort
    for (int i = 0; i < solienlac - 1; i++) {
        for (int j = i + 1; j < solienlac; j++) {
            if (strcmp(Ds[i].ten, Ds[j].ten) > 0) {
                LL temp = Ds[i];
                Ds[i] = Ds[j];
                Ds[j] = temp;
            }
        }
    }

    // Nhập tên liên lạc cần tìm
    char k[50];
    printf("Nhap ten lien lac can tim: ");
    fgets(k, sizeof(k), stdin);
    k[strcspn(k, "\n")] = '\0';  // Xóa ký tự newline

    // Gọi hàm tìm kiếm Jump Search
    int vitri = jumpSearch(Ds, solienlac, k);

    // Hiển thị kết quả tìm kiếm
    if (vitri != -1) {
        printf("Lien lac '%s' co so dien thoai: %s\n", Ds[vitri].ten, Ds[vitri].sdt);
    } else {
        printf("Khong tim thay lien lac '%s' trong danh ba.\n", k);
    }

    return 0;
}
