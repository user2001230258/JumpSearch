#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CONTACTS 1000
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15

typedef struct {
    char name[MAX_NAME_LENGTH];
    char phoneNumber[MAX_PHONE_LENGTH];
} Contact;

// Hàm loại bỏ ký tự xuống dòng 
void removeNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Hàm sắp xếp mảng phoneBook theo thứ tự abc
// Sử dụng sắp xếp bubble sort
void sortPhoneBook(Contact phoneBook[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(phoneBook[i].name, phoneBook[j].name) > 0) {
                // Đổi chỗ 2 phần tử
                Contact temp = phoneBook[i];
                phoneBook[i] = phoneBook[j];
                phoneBook[j] = temp;
            }
        }
    }
}

int jumpSearch(Contact phoneBook[], int n, const char* targetName) {
    int step = (int)sqrt(n);  // Tinh kich thuoc buoc nhay
    int prev = 0;

    // Find the block where the target name is likely to be
    while (prev < n && strcmp(phoneBook[prev].name, targetName) <= 0) {
        if (strcmp(phoneBook[prev].name, targetName) == 0) {
        	return prev;
		}
		prev += step;
		if (prev >= n) {
			prev = n - 1;
		}
    }

    // Perform a linear search within the block
    while (prev >= 0 && strcmp(phoneBook[prev].name, targetName) > 0) {
        prev--;
    }

    // Check if the target name is found
    if (prev >= 0 && strcmp(phoneBook[prev].name, targetName) == 0)
        return prev;

    return -1;
}

int main() {
    Contact phoneBook[MAX_CONTACTS];
    int n = 0;
    char filename[] = "phonebook.txt";

    // Load contacts from file
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char line[100];
        while (n < MAX_CONTACTS && fgets(line, sizeof(line), file)) {
            removeNewline(line);  // Loại bỏ ký tự xuống dòng nếu có
            sscanf(line, "%49[^,],%14s", phoneBook[n].name, phoneBook[n].phoneNumber);
            n++;
        }
        fclose(file);
    }

    // Sắp xếp mảng phoneBook theo thứ tự abc
    sortPhoneBook(phoneBook, n);

    // Nhap ten can tim
    char searchName[MAX_NAME_LENGTH];
    printf("Nhap ten can tim: ");
    fgets(searchName, sizeof(searchName), stdin);
    removeNewline(searchName);  // Loại bỏ ký tự xuống dòng từ đầu vào

    // Tim kiem 1 lien he
    int result = jumpSearch(phoneBook, n, searchName);

    if (result != -1) {
        printf("Tim thay: %s: %s\n", phoneBook[result].name, phoneBook[result].phoneNumber);
    } else {
        printf("Khong tim thay ten trong file.\n");
    }

    return 0;
}