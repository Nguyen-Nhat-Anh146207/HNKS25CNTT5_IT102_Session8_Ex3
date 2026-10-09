
#include <stdio.h>

struct UserAccount {
    int account_id;
    int plan_type;
    int monthly_fee;
    int remaining_days;
    int active_devices;
};

int main() {
    struct UserAccount account_list[100];
    struct UserAccount temp;

    int N;
    int i, j;
    int limit_devices;
    int downgraded_count = 0;

    long long mrr_before = 0;
    long long mrr_after = 0;
    long long mrr_difference;

    // 1. Nhap so luong tai khoan
    do {
        printf("Nhap so tai khoan (1-100): ");
        scanf("%d", &N);

        if (N < 1 || N > 100) {
            printf("So luong khong hop le. Nhap lai!\n");
        }
    } while (N < 1 || N > 100);

    // 2. Nhap du lieu va tinh MRR truoc kiem toan
    for (i = 0; i < N; i++) {
        printf("\n--- Tai khoan thu %d ---\n", i + 1);

        printf("Nhap ma tai khoan: ");
        scanf("%d", &account_list[i].account_id);

        do {
            printf("Nhap goi (0-Free, 1-Standard, 2-Premium): ");
            scanf("%d", &account_list[i].plan_type);

            if (account_list[i].plan_type < 0 ||
                account_list[i].plan_type > 2) {
                printf("Ma goi khong hop le. Nhap lai!\n");
            }
        } while (account_list[i].plan_type < 0 ||
                 account_list[i].plan_type > 2);

        printf("Nhap phi thang ban dau: ");
        scanf("%d", &account_list[i].monthly_fee);

        printf("Nhap so ngay con lai: ");
        scanf("%d", &account_list[i].remaining_days);

        printf("Nhap so thiet bi dang ket noi: ");
        scanf("%d", &account_list[i].active_devices);

        mrr_before += account_list[i].monthly_fee;
    }

    for (i = 0; i < N; i++) {
        if (account_list[i].remaining_days <= 0) {
            if (account_list[i].plan_type != 0) {
                downgraded_count++;
            }
            account_list[i].plan_type = 0;
            account_list[i].monthly_fee = 0;
        }

        if (account_list[i].plan_type == 0) {
            account_list[i].monthly_fee = 0;
            limit_devices = 1;
        } else if (account_list[i].plan_type == 1) {
            account_list[i].monthly_fee = 120000;
            limit_devices = 2;
        } else {
            account_list[i].monthly_fee = 300000;
            limit_devices = 5;
        }

        if (account_list[i].active_devices <= 0) {
            account_list[i].active_devices = 1;
        }

        if (account_list[i].active_devices > limit_devices) {
            account_list[i].active_devices = limit_devices;
        }
        mrr_after += account_list[i].monthly_fee;
    }

    for (i = 1; i < N; i++) {
        temp = account_list[i];
        j = i - 1;

        while (j >= 0 && ((temp.plan_type > 0 && account_list[j].plan_type == 0) || (temp.plan_type > 0 && account_list[j].plan_type > 0 && account_list[j].monthly_fee < temp.monthly_fee))) {
            account_list[j + 1] = account_list[j];
            j--;
        }
        account_list[j + 1] = temp;
    }

    printf("\n================ BAO CAO KIEM TOAN ================\n");

    printf("%-12s %-10s %-14s %-14s %-12s\n", "Ma TK", "Ma goi", "Phi thang", "Ngay con lai", "Thiet bi");

    printf("---------------------------------------------------------------\n");
    for (i = 0; i < N; i++) {
        printf("%-12d %-10d %-14d %-14d %-12d\n", account_list[i].account_id, account_list[i].plan_type, account_list[i].monthly_fee, account_list[i].remaining_days, account_list[i].active_devices);
    }

    mrr_difference = mrr_after - mrr_before;
    printf("---------------------------------------------------------------\n");
    printf("MRR truoc kiem toan: %lld VND\n", mrr_before);
    printf("MRR sau kiem toan:   %lld VND\n", mrr_after);
    printf("Chenh lech MRR:      %lld VND\n", mrr_difference);
    printf("So tai khoan ha cap: %d\n", downgraded_count);

    return 0;
}