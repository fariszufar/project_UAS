#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "manajemen_buku_dan_login.h"

// =========================================
// LIST GLOBAL
// =========================================
Buku globalListBuku[500];
int totalBuku = 0;

// =========================================
// MUAT DATA BUKU DARI FILE TXT
// =========================================
void MUAT_DATA_BUKU() {
    FILE *file = fopen("database_buku.txt", "r");
    if (file == NULL) return;

    totalBuku = 0;
    while (!feof(file)) {
        Buku b;
        fscanf(file, "%[^;];%[^;];%[^;];%[^;];%[^;];%d\n",
               b.id, b.judul, b.penulis, b.kategori, b.status, &b.jumlahDipinjam);
        globalListBuku[totalBuku++] = b;
    }
    fclose(file);
}

// =========================================
// SIMPAN DATA KE FILE TXT
// =========================================
void SIMPAN_DATA_BUKU() {
    FILE *file = fopen("database_buku.txt", "w");
    for (int i = 0; i < totalBuku; i++) {
        fprintf(file, "%s;%s;%s;%s;%s;%d\n",
                globalListBuku[i].id,
                globalListBuku[i].judul,
                globalListBuku[i].penulis,
                globalListBuku[i].kategori,
                globalListBuku[i].status,
                globalListBuku[i].jumlahDipinjam);
    }
    fclose(file);
}

// =========================================
// LOGIN (SESUAI PSEUDOCODE)
// =========================================
int LOGIN() {
    char username[50], password[50];

    printf("Masukkan Username: ");
    scanf("%s", username);
    printf("Masukkan Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        printf("Login Berhasil!\n");
        return 1;
    } else {
        printf("Login Gagal!\n");
        return 0;
    }
}

// =========================================
// FUNGSI MENCARI BUKU BY ID
// =========================================
int CARI_INDEX_BUKU(char *id) {
    for (int i = 0; i < totalBuku; i++) {
        if (strcmp(globalListBuku[i].id, id) == 0)
            return i;
    }
    return -1;
}

// =========================================
// TAMBAH BUKU BARU
// =========================================
void TAMBAH_BUKU_BARU() {
    char id[20], judul[100], penulis[100], kategori[50];

    printf("Masukkan ID Buku: ");
    scanf("%s", id);

    if (CARI_INDEX_BUKU(id) != -1) {
        printf("ID buku sudah ada!\n");
        return;
    }

    printf("Masukkan Judul Buku: ");
    scanf(" %[^\n]", judul);

    printf("Masukkan Penulis: ");
    scanf(" %[^\n]", penulis);

    printf("Masukkan Kategori: ");
    scanf(" %[^\n]", kategori);

    // Masukkan ke struct
    strcpy(globalListBuku[totalBuku].id, id);
    strcpy(globalListBuku[totalBuku].judul, judul);
    strcpy(globalListBuku[totalBuku].penulis, penulis);
    strcpy(globalListBuku[totalBuku].kategori, kategori);
    strcpy(globalListBuku[totalBuku].status, "Tersedia");
    globalListBuku[totalBuku].jumlahDipinjam = 0;

    totalBuku++;
    SIMPAN_DATA_BUKU();

    printf("Buku baru berhasil ditambahkan!\n");
}

// =========================================
// EDIT INFO BUKU
// =========================================
void EDIT_INFO_BUKU() {
    char id[20];
    printf("Masukkan ID Buku yang ingin diedit: ");
    scanf("%s", id);

    int idx = CARI_INDEX_BUKU(id);
    if (idx == -1) {
        printf("Buku tidak ditemukan!\n");
        return;
    }

    printf("Judul baru (lama: %s): ", globalListBuku[idx].judul);
    scanf(" %[^\n]", globalListBuku[idx].judul);

    printf("Penulis baru (lama: %s): ", globalListBuku[idx].penulis);
    scanf(" %[^\n]", globalListBuku[idx].penulis);

    printf("Kategori baru (lama: %s): ", globalListBuku[idx].kategori);
    scanf(" %[^\n]", globalListBuku[idx].kategori);

    SIMPAN_DATA_BUKU();
    printf("Data buku berhasil diperbarui!\n");
}

// =========================================
// HAPUS BUKU
// =========================================
void HAPUS_BUKU() {
    char id[20];
    printf("Masukkan ID Buku yang ingin dihapus: ");
    scanf("%s", id);

    int idx = CARI_INDEX_BUKU(id);
    if (idx == -1) {
        printf("Buku tidak ditemukan!\n");
        return;
    }

    if (strcmp(globalListBuku[idx].status, "Dipinjam") == 0) {
        printf("Buku sedang dipinjam, tidak bisa dihapus!\n");
        return;
    }

    // geser array
    for (int i = idx; i < totalBuku - 1; i++) {
        globalListBuku[i] = globalListBuku[i + 1];
    }

    totalBuku--;
    SIMPAN_DATA_BUKU();
    printf("Buku berhasil dihapus!\n");
}
