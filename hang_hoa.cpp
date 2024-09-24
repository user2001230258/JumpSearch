#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CONTACTS 1000

typedef struct {
    int nameCode;       // Mã hóa tên dưới dạng số nguyên
    long long phoneNumber; // Số điện thoại dưới dạng số nguyên
} Contact;

// Hàm mã hóa tên thành một số nguyên
int encodeName(const char* name) {
    int code = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        char c = name[i];
        if (c == ' ' || c == '\t') continue; // ignore whitespace characters
        c = tolower(c); // convert to lowercase
        code += (int)c;  // calculate the ASCII code
    }
    return code;
}

// Hàm sắp xếp danh bạ theo mã hóa tên
void sortPhoneBook(Contact phoneBook[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (phoneBook[i].nameCode > phoneBook[j].nameCode) {
                Contact temp = phoneBook[i];
                phoneBook[i] = phoneBook[j];
                phoneBook[j] = temp;
            }
        }
    }
}

// Hàm tìm kiếm nhảy (jump search) theo mã hóa tên
int jumpSearch(Contact phoneBook[], int n, int targetCode) {
    int step = (int)sqrt(n);
    int prev = 0;

    while (prev < n && phoneBook[prev].nameCode <= targetCode) {
        if (phoneBook[prev].nameCode == targetCode) {
            return prev;
        }
        prev += step;
        if (prev >= n) {
            prev = n - 1;
        }
    }

    while (prev >= 0 && phoneBook[prev].nameCode > targetCode) {
        prev--;
    }

    if (prev >= 0 && phoneBook[prev].nameCode == targetCode)
        return prev;

    return -1;
}

int main() {
    Contact phoneBook[MAX_CONTACTS];
    int n = 0;
    char filename[] = "namecode.txt";

    // Đọc danh bạ từ file (tên và số điện thoại dưới dạng số nguyên)
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char name[50];
        long long phone;
        while (n < MAX_CONTACTS && fscanf(file, "%49s %lld", name, &phone) == 2) {
            phoneBook[n].nameCode = encodeName(name);
            phoneBook[n].phoneNumber = phone;
            n++;
        }
        fclose(file);
    }

    // Sắp xếp danh bạ theo mã hóa tên
    sortPhoneBook(phoneBook, n);

    // Nhập tên cần tìm
    char searchName[50];
    printf("Nhap ten can tim: ");
    scanf("%49s", searchName);

    // trim whitespace characters from the search name
    int len = strlen(searchName);
    while (len > 0 && isspace(searchName[len-1])) {
        searchName[--len] = '\0';
    }
    while (len > 0 && isspace(searchName[0])) {
        memmove(searchName, searchName + 1, len);
        len--;
    }

    // Mã hóa tên cần tìm
    int searchCode = encodeName(searchName);

    // Tìm kiếm
    int result = jumpSearch(phoneBook, n, searchCode);

    if (result != -1) {
        printf("Tim thay: %d: %lld\n", phoneBook[result].nameCode, phoneBook[result].phoneNumber);
    } else {
        printf("Khong tim thay ten trong file.\n");
    }

    return 0;
}