#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_SISWA 149 // Jumlah siswa yang diberikan

// Struktur untuk menyimpan data siswa
typedef struct {
    char nama[100];
    int hadir; // 1 jika hadir, 0 jika tidak hadir
    char kelas[2]; // Kelas A, B, C, atau D
    char waktuAbsen[6]; // Waktu absen dalam format HH:MM
} Siswa;

// Fungsi untuk mendapatkan waktu saat ini dalam format HH:MM
void dapatkanWaktuSekarang(char *waktu) {
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    strftime(waktu, 6, "%H:%M", tm_info);
}

// Fungsi untuk menentukan kelas berdasarkan NIM
void tentukanKelas(Siswa *siswa, int index) {
    // Menentukan kelas berdasarkan NIM ganjil/genap dan rentang 1-75 atau 76-150
    if (index >= 1 && index <= 75) {
        if (index % 2 != 0) {
            strcpy(siswa->kelas, "A"); // NIM ganjil, kelas A
        } else {
            strcpy(siswa->kelas, "B"); // NIM genap, kelas B
        }
    } else if (index >= 76 && index <= 149) {
        if (index % 2 != 0) {
            strcpy(siswa->kelas, "C"); // NIM ganjil, kelas C
        } else {
            strcpy(siswa->kelas, "D"); // NIM genap, kelas D
        }
    }
}

// Fungsi untuk menampilkan absensi
void tampilkanAbsensi(Siswa absensi[], int jumlahSiswa) {
    printf("\n%-4s %-40s %-6s %-12s %-6s\n", "NIM", "Nama", "Kelas", "Status", "Waktu");
    printf("%s\n", "-------------------------------------------------------------------------------");
    for (int i = 0; i < jumlahSiswa; i++) {
        printf("%-4d %-40s %-6s %-12s %-6s\n", i + 1, absensi[i].nama, absensi[i].kelas, absensi[i].hadir ? "Hadir" : "Tidak Hadir", absensi[i].hadir ? absensi[i].waktuAbsen : "-");
    }
}

// Fungsi untuk menyimpan absensi ke file CSV
void simpanKeCSV(Siswa absensi[], int jumlahSiswa) {
    FILE *file = fopen("absensi.csv", "w");
    if (file == NULL) {
        printf("Gagal membuat file absensi.csv\n");
        return;
    }

    // Tulis header
    fprintf(file, "NIM,Nama,Kelas,Status,Waktu\n");

    // Tulis data siswa
    for (int i = 0; i < jumlahSiswa; i++) {
        fprintf(file, "%d,%s,%s,%s,%s\n", i + 1, absensi[i].nama, absensi[i].kelas, absensi[i].hadir ? "Hadir" : "Tidak Hadir", absensi[i].hadir ? absensi[i].waktuAbsen : "-");
    }

    fclose(file);
    printf("Data absensi berhasil disimpan ke absensi.csv\n");
}

int main() {
    // Daftar nama siswa
    Siswa absensi[MAX_SISWA] = {
        {"NURZAHRA ALYA NABILA"}, {"DEWI NURISMA"}, {"ALIM NAFI ROBANI"}, {"DESTA MUHAMMAD EDI KURNIAWAN"},
        {"AISYAH NURUL NATASYA"}, {"ABDUL HOFUR"}, {"KHANSA NISRINA"}, {"HOSEA PRAMURDIANTO PASKAH"},
        {"DIWANGGA NARENDRA DANISWARA WIPUTRA"}, {"FAHRAN ICHLASUL ZIKRI"}, {"ABILKHASAN ALMUZAKKI"},
        {"CITRA SALSABILA"}, {"IMAM HIBATULLAH"}, {"CHANDRA SALIM"}, {"ABISYAH ANANTA AMRU"},
        {"FAISHAL RAMADHAN"}, {"DILA PUSPITA CAHYARANI"}, {"PRATIWI RAHMADIANA"}, {"HILMY TSAQIF FIRDAUS"},
        {"DWIMA AGUNG PANGESTU"}, {"PROBO DWI YULASTONO"}, {"ALANGIR AL MUHTADA"}, {"MAYCHA TANAYA"},
        {"ALIF WIDIA RACHMAT ROSYADI"}, {"AKHDAN LUTHFI NAJMUDIN"}, {"ANDRIAN AMMAR MAULANA"},
        {"MOLASKY SEPTAMAHARDIKA POETRA"}, {"HARI CAHYADI"}, {"FADHLAN MAULANA ILMAN"}, {"RYAN DESTRIANSYAH"},
        {"ERHAN MADARAIHAN"}, {"MOHAMAD RISQIY AL-AMIN"}, {"FAIZ KHOIRUL FUADI"}, {"ZAKY SINDUNG KUMARA"},
        {"ZAIM ULIL HIKAM"}, {"DIMAS PANDU PRASETYO"}, {"RIQZA ZIDAN AKHMAD FAHRIZAL"}, {"NAUFAL FENOKHOLIS"},
        {"TEUKU MUHAMMAD RIZKI MAULANA"}, {"DINA SEVINA FAJRI AQMARINA"}, {"FANY AMANDA KURNIATY"},
        {"RAFFI IQBAL FADLURRAHMAN"}, {"SILVIANA SALSABILA MUSAKINAH"}, {"NABIL AIMAN FADHLURROHMAN"},
        {"APRILIA TRI HAPSARI"}, {"MUHAMMAD QAMARUN HATMA"}, {"NABILLA PUTRI ANDINI"}, {"TRIAS ANGEL WIDYAWARDANI"},
        {"ILHAM PUTRA PRADANA"}, {"GALINDRA FEORAS UGARY"}, {"ALWAN JULIANTO"}, {"PATU MUHAMMAD HARITS"},
        {"DIMAS HASBY ALLAVI"}, {"SHIDQI ABIYYU GHAZY"}, {"IMAM MAJID MAULANA"}, {"MUHAMMAD IRFAN GHANI"},
        {"RAYHAN GALANG PERSADA"}, {"TRIA RAHMA PUTRI"}, {"FAUZI MALIK NASHRULLAH"}, {"MUHAMMAD NOUFAL"},
        {"DHIYA ULHAQ RAMADHANI"}, {"BAGUS RAGAKUSUMA"}, {"ILHAM GANI KUSWANDI"}, {"KRISNA DZAKI BRILLIANTO"},
        {"MUHAMMAD SATRIO WIBOWO"}, {"SALSABILA ARVANI HASIBUAN"}, {"MUHAMMAD RIAN HIDAYAT"}, {"RAYHAN KUMAISA AL FAUZI"},
        {"XAFIO AERO DERAFA"}, {"MUHAMMAD FAKHRUL ARIFIN"}, {"FEBRIYAN ADHI NUGROHO"}, {"FARREL ARDAN TURINO"},
        {"MUFTI KAMAL FAADHILAH"}, {"FAIZ WEKA SURYA ZEIN"}, {"IRVAN AGUSTINUS SILALAHI"}, {"FADHILAH SETYO WIBOWO"},
        {"NAJLA TSABITAH"}, {"MOHAMMAD FANAN ADI KUSUMA"}, {"TALITHA AYUNDA MARITSA"}, {"ILHAM PRATAMA"},
        {"AULIA FIRMANSYAH"}, {"RENATA REVANANDRA AULIA"}, {"SHAFIRA ARINTIA ZEN"}, {"DANI SETIAWAN"},
        {"HARTARTO"}, {"MUHAMMAD ZAHFRAN NAUFALDI"}, {"NASHR ARDY WAHYONO"}, {"DANENDRA ADHYAKSA EMIKO WIDODO"},
        {"TATAG YUDO PRAKOSO"}, {"FHALAH ARINDA PUTRA"}, {"MUHAMMAD MUNHANIF ILHAM"}, {"SABIQ KHAIRY MUFID"},
        {"IRFANDI HENDRA FAIZZA"}, {"ALFIN YUSRIL HUSNA"}, {"MATTHEW JASON YOEWONO"}, {"DHIKA HERVIAN SABDA SETYA RAHMAN"},
        {"FAJAR RIZKY NUGROHA"}, {"ZENDIKA AKHDAN MAULANA"}, {"RYAN MARTA PRAYOGA"}, {"FAIZ YUDISTIRA SAMOSIR"},
        {"SHAFWAN NABIH MUHADZDZIB"}, {"JOUVAN FIRGIE PAMUNGKAS"}, {"MUHAMMAD ZULVA RIATMA"}, {"RIDWAN BEKTI SUWITO"},
        {"YUSUF ANDRIAN"}, {"NABILATUL WAHIDAH"}, {"OKY RINALDI SAPUTRA"}, {"MUHAMMAD LATHIF AL HASANI"},
        {"DAFFA NOVANDRA SAPUTRA"}, {"NATASYA AISYA PUTRI"}, {"MUHAMMAD AKBAR FIRMANSYAH"}, {"MUAMMAR ROFI ZUNURAIN"},
        {"ZIDAN MAULANA ASH SHIDDIQ"}, {"FRANZ GERALD AUDRICHO MANURUNG"}, {"RAFA AMADA BAYU HABIB"}, {"HENRY FERDINAND FIRDAUS"},
        {"RAFAEL PAEAN GERALDO SIMANJUNTAK"}, {"RAHESTA DITYA PERDANA"}, {"AHMAD RIDWAN FAHREZI"}, {"LAISTS SYAFIATUN NESSA"},
        {"HENKEL RADITYA"}, {"NELSON JESAYA NAPITUPULU"}, {"MEISYA KUSUMA WARDHANI"}, {"JULIUS ALFADI MORDRIGO"},
        {"ADAM"}, {"FATHIN ABDUL MAJID"}, {"KIA SHADRA AFIQA BUSONO"}, {"FUAD NUR SYAMSI"}, {"SATRIA NUGRAHA SURYA PUTRA"},
        {"MELODY SALMAN BILLAAHI"}, {"MEIDYA RAIHAN ALIFIYANTO"}, {"RAGIL SAPUTRO NUGROHO"}, {"AHMAD FAISAL FALAH"},
        {"PRADIPTA MAHARANI WIDHARRY"}, {"AMANAH HAFIDA RAHMA"}, {"HAFIYYUN DIMAS MOLANA"}, {"HARIRI FEBRIANTO ARKANSYAH"},
        {"NAJMI SANJIRO AMIN"}, {"GHOZI ALFALAH HIDAYAT"}, {"MUHAMMAD ADHITYA NAFHI SUTOPO"}, {"SEPTI AISYA"},
        {"RAZAN MUHAMMAD IHSAN M"}, {"DAMAR MUAZIZ LATIF"}, {"HIFAYATUN ANIN"}, {"AZKA AZKIYA ELHAQ"},
        {"ZHAFIF AGIS RIZQULLAH"}, {"IQLIMA AFIFAH"}, {"RIYAN"}, {"ARYA SAMANDIKA"}
    };

    int jumlahSiswa = MAX_SISWA;
    int pilihan;

    // Menentukan kelas untuk setiap siswa berdasarkan NIM
    for (int i = 0; i < jumlahSiswa; i++) {
        tentukanKelas(&absensi[i], i + 1); // Indeks array dimulai dari 0, sedangkan NIM dimulai dari 1
        absensi[i].hadir = 0; // Status kehadiran awalnya adalah tidak hadir
        strcpy(absensi[i].waktuAbsen, "-"); // Waktu absen awalnya kosong
    }

    do {
        // Menu pilihan
        printf("\nMenu:\n");
        printf("1. Absen\n");
        printf("2. Tampilkan Absensi\n");
        printf("3. Keluar\n");
        printf("4. Simpan ke Excel (CSV)\n");
        printf("Pilihan: ");
        if (scanf("%d", &pilihan) != 1) {
            printf("Pilihan tidak valid!\n");
            while(getchar() != '\n'); // Membersihkan input buffer
            continue;
        }

        switch (pilihan) {
            case 1: {
                int nim;
                printf("Masukkan NIM: ");
                if (scanf("%d", &nim) != 1) {
                    printf("NIM tidak valid!\n");
                    while(getchar() != '\n'); // Membersihkan input buffer
                    break;
                }

                if (nim >= 1 && nim <= jumlahSiswa) {
                    // NIM langsung dianggap hadir
                    absensi[nim - 1].hadir = 1;
                    dapatkanWaktuSekarang(absensi[nim - 1].waktuAbsen);
                    printf("Siswa dengan NIM %d sudah hadir pada waktu %s.\n", nim, absensi[nim - 1].waktuAbsen);
                } else {
                    printf("NIM tidak valid.\n");
                }
                break;
            }
            case 2:
                tampilkanAbsensi(absensi, jumlahSiswa);
                break;
            case 3:
                printf("Terima kasih!\n");
                break;
            case 4:
                simpanKeCSV(absensi, jumlahSiswa);
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 3);

    return 0;
}
