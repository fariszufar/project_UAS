#ifndef MANAJEMEN_BUKU_DAN_LOGIN_H
#define MANAJEMEN_BUKU_DAN_LOGIN_H

// =========================================
// STRUCT DATA BUKU 
// =========================================
typedef struct {
    char id[20];
    char judul[100];
    char penulis[100];
    char kategori[50];
    char status[20];      // "Tersedia" / "Dipinjam"
    int jumlahDipinjam;   // utk tracking dipinjam
} Buku;

// =========================================
// DEKLARASI FUNGSI LOGIN
// =========================================
int LOGIN();

// =========================================
// DEKLARASI FUNGSI MANAJEMEN BUKU
// =========================================
void TAMBAH_BUKU_BARU();
void EDIT_INFO_BUKU();
void HAPUS_BUKU();

// DEKLARASI LIST GLOBAL
extern Buku globalListBuku[500];
extern int totalBuku;

// FILE HANDLING
void MUAT_DATA_BUKU();
void SIMPAN_DATA_BUKU();

#endif
