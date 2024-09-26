#include <stdio.h>
#include <string.h>
#include <math.h>

// Định nghĩa cấu trúc HangHoa
struct HangHoa {
    char ma[10];   // Mã đơn hàng
    char ten[20];  // Tên hàng hóa
    int soluong;   // Số lượng
};

typedef struct HangHoa HH;

// Hàm Jump Search tìm kiếm mã đơn hàng
int jumpSearch(HH Ds[], int n, char k[]) {
    int step = sqrt(n);  // Kích thước bước nhảy
    int prev = 0;
    int jump = step;

    // Vòng lặp nhảy qua các bước
    while (strcmp(Ds[prev].ma, k) < 0) {
        prev = jump;
        jump += step;

        // Nếu jump vượt quá kích thước mảng, đặt lại bằng n
        if (jump > n) {
            jump = n;
        }

        // Nếu prev vượt quá kích thước mảng, không tìm thấy
        if (prev >= n) {
            return -1;
        }
    }

    // Tìm tuyến tính trong vùng đã nhảy qua
    while (prev < jump && strcmp(Ds[prev].ma, k) <= 0) {
        if (strcmp(Ds[prev].ma, k) == 0) {
            return prev;
        }
        prev++;
    }

    return -1;  // Không tìm thấy
}

int main() {
    FILE* file;
    HH Ds[50];
    int soluonghanghoa = 0;

    // Mở tệp "KhoHang.txt"
    file = fopen("KhoHang.txt", "r");
    if (file == NULL) {
        printf("Khong the mo tep KhoHang.txt\n");
        return 1;
    }

    // Đọc dữ liệu từ tệp và lưu vào mảng Ds
    while (fscanf(file, "%s %s %d", Ds[soluonghanghoa].ma, Ds[soluonghanghoa].ten, &Ds[soluonghanghoa].soluong) == 3) {
        soluonghanghoa++;
        if (soluonghanghoa >= 50) {
            printf("Kho hang qua lon, khong the doc them.\n");
            break;
        }
    }
    fclose(file);

    // Sắp xếp mảng theo mã đơn hàng sử dụng Bubble Sort
    for (int i = 0; i < soluonghanghoa - 1; i++) {
        for (int j = i + 1; j < soluonghanghoa; j++) {
            if (strcmp(Ds[i].ma, Ds[j].ma) > 0) {
                HH temp = Ds[i];
                Ds[i] = Ds[j];
                Ds[j] = temp;
            }
        }
    }

    // Nhập mã đơn hàng cần tìm
    char k[10];
    printf("Nhap ma don hang can tim: ");
    fgets(k, sizeof(k), stdin);
    k[strcspn(k, "\n")] = '\0';  // Xóa ký tự newline

    // Tìm kiếm mã đơn hàng bằng Jump Search
    int vitri = jumpSearch(Ds, soluonghanghoa, k);

    // Hiển thị kết quả tìm kiếm
    if (vitri != -1) {
        printf("Hang hoa '%s' ton tai trong kho\n", k);
        printf("Ten: %s\n", Ds[vitri].ten);
        printf("So luong: %d\n", Ds[vitri].soluong);
    } else {
        printf("Hang hoa '%s' khong ton tai trong kho.\n", k);
    }

    return 0;
}
