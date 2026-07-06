#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctype.h>
#include <windows.h>
#include <cstring>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

// Variabel global
int iterasi, i, p, k, pelanggan, depot, total, kapasitas_max, kapasitas_kendaraan, pilih;
int dim_new[1000][1000], target_new, indextarget;
int pop, maxiter;
int permintaan[500][500], jarakkoor[500][500], pickup[500], delivery[500];
int dim[1000][1000], dup_dim[1000][1000], fx[1000], fx_baru[1000];
int sisabarang_skrg, isiskrg, kapasitaskosongskrg, nrute, ruteskrg, rute[500];
double jarak_skrg,  jaraktotal;
double temp, gaya_sosial[500][500], subPow, kapasitas, s_i, s_i_total[500][500];
double r_ip_vect[200][200][200], s_ip[200][200][200], x_new[1000][1000];
double jarak[500][500], jarak1[500][500];
int temp1, target, simpan1, simpan, simpantarget;
double posisi[1000][1000], dup_posisi[1000][1000];
double lbd, ubd, posisi_baru[1000][1000], d[500][500], simpanbelalang[1000][1000];
// Parameter CGOA
double c1, c2, cmax, cmin, f, l, P_chaotic;

// Untuk menyimpan best global
int best_index = -1;
int best_value_global = 1e9;
int best_dim_saved[1000];

ofstream vrpspd, output;
ifstream call1, call2;

void judul() {
    cout << setfill('=') << setw(70) << "=" << endl;
    cout << setfill(' ') << setw(62)
         << "Program Penerapan Chaotic Grasshopper Optimization Algorithm (CGOA)" << endl;
    cout << setw(58)
         << "Untuk Menyelesaikan Vehicle Routing Problem with" << endl;
    cout << setw(60)
         << "Simultaneous Pickup and Delivery (VRPSPD)" << endl;
    cout << setfill('-') << setw(70) << "-" << endl;
    cout << setfill(' ') << setw(40) << "Fauziah Qhurrotu Aini" << endl;
    cout << setw(36) << "181221002" << endl;
    cout << setfill('=') << setw(70) << "=" << endl << endl;
}

void inisialisasiparameter() {
    cout << "\nParameter Chaotic Grasshopper Optimization Algorithm\n";
    cout << "Jumlah populasi belalang (>=2): ";
    while (true) {
        if (!(cin >> pop) || pop <= 1 ) {
            cout << "Error: Masukkan bilangan bulat lebih dari 1\n";
        }
        else if (cin.peek() != '\n') {
            cout << "Error: Input harus bilangan bulat saja\n";
        }
        else {
            break;
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Jumlah populasi belalang: ";
    }

    
    cout << "Maksimum Iterasi (>=1): ";
    while (true) {
        if (!(cin >> maxiter) || maxiter < 1) {
            cout << "Error: Masukkan bilangan bulat minimal 1\n";
        } 
        else if (cin.peek() != '\n') {
            cout << "Error: Masukkan bilangan bulat minimal 1\n";
        }
        else {
            break;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Maksimum Iterasi: ";
    }

    
    cout << "Persen muatan awal kendaraan (50-100): ";
    while (true) {
        if (!(cin >> kapasitas) || kapasitas < 50 || kapasitas > 100) {
            cout << "Error: Masukkan persentase antara 50-100\n";
        }
        else if (cin.peek() != '\n') {
            cout << "Error: Masukkan persentase antara 50-100\n";
        }
        else {
            break;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Persen muatan awal kendaraan: ";
    }

    
    cout << "Batas bawah dimensi (lbd): ";
    while (true) {
        if (!(cin >> lbd)) {
            cout << "Error: Input tidak valid\n";
        }
        else if (cin.peek() != '\n') {
            cout << "Error: Input tidak valid\n";
        }
        else {
            break;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Batas bawah dimensi (lbd): ";
    }

    
    cout << "Batas atas dimensi (ubd): ";
    while (true) {
        if (!(cin >> ubd)) {
            cout << "Error: Input tidak valid\n";
        }
        else if (cin.peek() != '\n') {
            cout << "Error: Input tidak valid\n";
        }
        else if (ubd == lbd) {   
        cout << "Error: Batas atas tidak boleh sama dengan batas bawah\n";
        }
        else {
            break;
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Batas atas dimensi (ubd): ";
    }

    
    cout << "Masukkan nilai f [0-1]: ";
    while (true) {
        if (!(cin >> f) || f < 0 || f > 1) {
            cout << "Error: Masukkan nilai antara 0-1\n";
        }
        else if (cin.peek() != '\n') {
            cout << "Error: Masukkan nilai antara 0-1\n";
        }
        else {
            break;
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Masukkan nilai f [0-1]: ";
    }

   
    // Parameter CGOA default
    l = 1.5;
    P_chaotic = 4.0;
    
    vrpspd << endl;
}

void ambildata() {
    cout << "\nParameter Vehicle Routing Problem with Simultaneous Pickup and Delivery \n";
    cout << " Pilih data: \n 1. Data Kecil (13 Pelanggan) \n 2. Data Sedang (22 Pelanggan) \n 3. Data Besar (100 Pelanggan) \n";
    cout << " Pilihan: ";
    while (true) {
        if (!(cin >> pilih) || pilih < 1 || pilih > 3) {
            cout << "Error: Pilihan data salah!\n";
        }
        else if (cin.peek() != '\n') {
            cout << "Error: Input harus berupa angka 1-3 saja\n";
        }
        else {
            break;
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Pilihan: ";
    }

    
    if (pilih == 1) {
        output.open("outputkecil.txt", ios::app);
        call1.open("jarakkecil.txt");
        call2.open("permintaankecil.txt");
        pelanggan = 13;
        depot = 1;
        total = pelanggan + depot;
        kapasitas_max = 180;
        kapasitas_kendaraan = (int)((kapasitas / 100.0) * kapasitas_max);
        
        for (int i = 0; i < total; i++) {
            for (int p = 0; p < total; p++) {
                call1 >> jarak[i][p];
            }
        }
        
        int nomor;
        for (int i = 0; i < pelanggan; i++) {
            call2 >> nomor >> delivery[nomor] >> pickup[nomor];
        }
        
    } else if (pilih == 2) {
        output.open("outputsedang.txt", ios::app);
        call1.open("jaraksedang.txt");
        call2.open("permintaansedang.txt");
        pelanggan = 22;
        depot = 1;
        total = pelanggan + depot;
        kapasitas_max = 10500;
        kapasitas_kendaraan = (int)((kapasitas / 100.0) * kapasitas_max);
        
        for (int i = 0; i < total; i++) {
            for (int p = 0; p < total; p++) {
                call1 >> jarak[i][p];
            }
        }   
        
        int nomor;
        for (int i = 0; i < pelanggan; i++) {
            call2 >> nomor >> delivery[nomor] >> pickup[nomor];
        }
        
    } else if (pilih == 3) {
        output.open("outputbesar.txt", ios::app);
        call1.open("jarakbesar.txt");
        call2.open("permintaanbesar.txt");
        pelanggan = 100;
        depot = 1;
        total = pelanggan + depot;
        kapasitas_max = 200;
        kapasitas_kendaraan = (int)((kapasitas / 100.0) * kapasitas_max);
        
        for (int i = 0; i < total; i++) {
            for (int p = 0; p < total; p++) {
                call1 >> jarak[i][p];
            }
        }
        
        int nomor;
        for (int i = 0; i < pelanggan; i++) {
            call2 >> nomor >> delivery[nomor] >> pickup[nomor];
        }
    }
}

void gen_popawal() {
    const int w = 16;   
    output << "\n\nPOSISI AWAL BELALANG\n\n";
    output << fixed << setprecision(4);

    output << setw(w) << "Belalang";
    for (p = 0; p < pelanggan; p++) {
        output << setw(w) << p + 1;
    }
    output << endl;

    
    output << setfill('-');
    output << setw(w) << "";
    for (p = 0; p < pelanggan; p++) {
        output << setw(w) << "";
    }
    output << endl;
    output << setfill(' ');

    // Data
    for (i = 0; i < pop; i++) {
        output << setw(w) << i + 1;
        for (p = 0; p < pelanggan; p++) {
            posisi[i][p] = (double)rand() / RAND_MAX;
            output << setw(w) << posisi[i][p];
        }
        output << endl;
    }
}

void urutan_pop(double posisi[1000][1000], int dim[1000][1000]) {
     for (i = 0; i < pop; i++) {
        for (p = 0; p < pelanggan; p++) {

            int label = 1; // label awal

            for (k = 0; k < pelanggan; k++) {
                if (posisi[i][k] < posisi[i][p]) {
                    label++;
                }
            }

            dim[i][p] = label;
        }
    }

    // Output
    output << "\nUrutan Belalang \t\t Calon Rute \n";
    for (i = 0; i < pop; i++) {
        output << "\t" << i + 1 << "\t\t";
        for (p = 0; p < pelanggan; p++) {
            output << dim[i][p] << "\t";
        }
        output << endl;
    }
}

void tampilkan_rute_belalang(int belalang_index, int dim_data[1000][1000]) {
    output << "{ ";
    for (int z = 0; z < pelanggan; z++) {
        output << dim_data[belalang_index][z];
        if (z < pelanggan - 1) output << "-";
    }
    output << " }";
}

void fungsitujuan(int fx[1000], int dim[1000][1000]) {
    output << "\n\n NILAI FUNGSI TUJUAN \n========================\n";
    
    for (i = 0; i < pop; i++) {
        output << "\n ===== Belalang " << i + 1 << " ===== \n";
        sisabarang_skrg = kapasitas_kendaraan;
        isiskrg = kapasitas_kendaraan;
        jarak_skrg = jarak[0][dim[i][0]];
        sisabarang_skrg = sisabarang_skrg - delivery[dim[i][0]];
        isiskrg = isiskrg - delivery[dim[i][0]] + pickup[dim[i][0]];
        kapasitaskosongskrg = kapasitas_max - isiskrg;
        nrute = 1;
        ruteskrg = 0;
        rute[ruteskrg] = dim[i][0];
        ruteskrg += 1;
        jaraktotal = 0;
        
        for (p = 0; p < pelanggan - 1; p++) {
            sisabarang_skrg = sisabarang_skrg - delivery[dim[i][p + 1]];
            if (sisabarang_skrg >= 0 && (isiskrg - delivery[dim[i][p + 1]] + pickup[dim[i][p + 1]]) <= kapasitas_max) {
                isiskrg = isiskrg - delivery[dim[i][p + 1]] + pickup[dim[i][p + 1]];
                kapasitaskosongskrg = kapasitas_max - isiskrg;
                jarak_skrg = jarak_skrg + jarak[dim[i][p]][dim[i][p + 1]];
                rute[ruteskrg] = dim[i][p + 1];
                ruteskrg += 1;
            } else {
                jarak_skrg = jarak_skrg + jarak[dim[i][p]][0];
                jaraktotal = jaraktotal + jarak_skrg;
                output << "Rute " << nrute << ": 0-";
                for (k = 0; k < ruteskrg; k++) {
                    output << rute[k] << "-";
                }
                output << "0\n";
                output << "Dengan Total Jarak : " << jarak_skrg << "\n";
                nrute += 1;
                ruteskrg = 0;
                rute[ruteskrg] = dim[i][p + 1];
                ruteskrg += 1;
                jarak_skrg = jarak[0][dim[i][p + 1]];
                sisabarang_skrg = kapasitas_kendaraan;
                isiskrg = kapasitas_kendaraan;
                sisabarang_skrg = sisabarang_skrg - delivery[dim[i][p + 1]];
                isiskrg = isiskrg - delivery[dim[i][p + 1]] + pickup[dim[i][p + 1]];
                kapasitaskosongskrg = kapasitas_max - isiskrg;
            }
            
            if (p == pelanggan - 2) {
                jarak_skrg = jarak_skrg + jarak[dim[i][p + 1]][0];
                jaraktotal = jaraktotal + jarak_skrg;
                output << "Rute " << nrute << ": 0-";
                for (k = 0; k < ruteskrg; k++) {
                    output << rute[k] << "-";
                }
                output << "0\n";
                output << "Dengan Total Jarak : " << jarak_skrg << "\n";
            }
        }
        fx[i] = jaraktotal;
        output << "\n\n Total jarak belalang " << i + 1 << ": " << jaraktotal << "\n";
    }
}

void tampilkan_belalang(int fx_data[1000]) {
    output << "\n --- Belalang --- \n";
    output << "\n Belalang \t\t Calon Rute \n";

    int lokal_best = fx_data[0];
    int lokal_index = 0;

    for (i = 1; i < pop; i++) {
        if (fx_data[i] < lokal_best) {
            lokal_best = fx_data[i];
            lokal_index = i;
        }
    }

    output << "\n " << lokal_index + 1 << "\t\t";
    for (p = 0; p < pelanggan; p++) {
        output << dim[lokal_index][p] << "\t";
    }
    output << endl;
}

void generate_chaotic_parameters() {
    // Inisialisasi parameter chaotic dengan random (0,1)
    if (iterasi == 0) {
        c1 = ((double)rand() / (RAND_MAX));
        c2 = ((double)rand() / (RAND_MAX));
        output << "\n ----- Parameter Chaotic Awal ----- \n";
        output << "\n c1 = " << c1 << "\n c2 = " << c2 << "\n";
    } else {
        // Update parameter chaotic dengan Logistic Map
        c1 = P_chaotic * c1 * (1 - c1);
        c2 = P_chaotic * c2 * (1 - c2);
        
        // Pastikan nilai tetap dalam range (0,1)
        if (c1 <= 0 || c1 >= 1) c1 = ((double)rand() / (RAND_MAX));
        if (c2 <= 0 || c2 >= 1) c2 = ((double)rand() / (RAND_MAX));
        
        output << "\n ----- Update Parameter Chaotic ----- \n";
        output << "\n c1 = " << c1 << "\n c2 = " << c2 << "\n";
    }
}

void hitungjarak(double posisi[1000][1000]) {
    output << "\n ----- Menghitung jarak antar belalang ----- \n";
    output << fixed << setprecision(6);
    
    for (i = 0; i < pop; i++) {
        for (int p = 0; p < pop; p++) {
            if (i == p) continue;
            else {
                subPow = 0;
                for (k = 0; k < pelanggan; k++) {
                    subPow = subPow + pow((posisi[i][k] - posisi[p][k]), 2);
                }
                d[i][p] = sqrt(subPow);
                output << "Jarak antara Belalang " << i+1 << " dan " << p+1 << ": " << d[i][p] << "\n";
            }
        }
    }
    output << "\n";
}

void updateposisi(double posisi[1000][1000]) {
    // Hitung gaya sosial
    for (i = 0; i < pop; i++) {
        for (p = 0; p < pop; p++) {
            if (i == p) continue;
            else {
                gaya_sosial[i][p] = f * exp(-d[i][p] / l) - exp(-d[i][p]);
            }
        }
    }
    
    // cetak gaya sosial
    output << "\n ----- Menghitung gaya sosial antar belalang ----- \n";
    output << fixed << setprecision(7);
    for (i = 0; i < pop; i++) {
        for (p = 0; p < pop; p++) {
            if (i == p) continue;
            output << "Gaya sosial antara Belalang " << i+1 << " dan " << p+1 << ": " << gaya_sosial[i][p] << "\n";
        }
    }
    output << "\n";

    // Hitung vektor satuan
    for (i = 0; i < pop; i++) {
        for (p = 0; p < pop; p++) {
            for (k = 0; k < pelanggan; k++) {
                if (i != p && d[i][p] != 0) {
                    r_ip_vect[i][p][k] = (posisi[p][k] - posisi[i][k]) / d[i][p];
                } else {
                    r_ip_vect[i][p][k] = 0;
                }
            }
        }
    }
    
    // Hitung interaksi sosial dengan parameter chaotic c2
    for (k = 0; k < pelanggan; k++) {
        for (p = 0; p < pop; p++) {
            s_i = 0;
            for (i = 0; i < pop; i++) {
                if (i != p) {
                    s_ip[p][i][k] = c2 * ((ubd - lbd) / 2) * gaya_sosial[i][p] * r_ip_vect[p][i][k] ;
                    s_i = s_i + s_ip[p][i][k];
                } else {
                    s_ip[p][i][k] = 0;
                }
            }
            s_i_total[p][k] = s_i;
        }
    }
    
    // Update posisi dengan parameter chaotic c1
    for (i = 0; i < pop; i++) {
        for (p = 0; p < pelanggan; p++) {
            simpanbelalang[i][p] = posisi[i][p];
            x_new[i][p] = c1 * s_i_total[i][p] + posisi[indextarget][p];
        }
    }
    
    // Cek batas
    for (i = 0; i < pop; i++) {
        for (p = 0; p < pelanggan; p++) {
            if (x_new[i][p] > ubd || x_new[i][p] < lbd) {
                for (k = 0; k < pelanggan; k++) {
                    if (iterasi == 0) {
                        x_new[i][k] = posisi[i][k];
                    } else {
                        x_new[i][k] = simpanbelalang[i][k];
                    }
                }
                break;
            }
        }
    }
    
    output << "\n\n---- UPDATE POSISI BELALANG ----\n\n";
    const int w = 16;   
    output << fixed << setprecision(4);

    output << setw(w) << "Belalang";
    for (i = 0; i < pelanggan; i++) {
        output << setw(w) << i + 1;
    }
    output << endl;

    output << setfill('-');
    output << setw(w) << "";
    for (i = 0; i < pelanggan; i++) {
        output << setw(w) << "";
    }
    output << endl;
    output << setfill(' ');

    // Data
    for (i = 0; i < pop; i++) {
        output << setw(w) << i + 1;
        for (p = 0; p < pelanggan; p++) {
            output << setw(w) << x_new[i][p];
        }
        output << endl;
    }
}

void proses_target_iterasi(int fx_data[1000], int dim_data[1000][1000], int iter)
{
    // Cari nilai terbaik pada iterasi ini (calon target)
    int lokal_best = fx_data[0];
    int lokal_index = 0;

    for (int a = 1; a < pop; a++) {
        if (fx_data[a] < lokal_best) {
            lokal_best = fx_data[a];
            lokal_index = a;
        }
    }

    output << "\n===================================================\n";
    output << " UPDATE TARGET BELALANG ITERASI " << iter+1 << "\n";
    output << "=====================================================\n";

    output << "Calon belalang target iterasi " << iter+1 << " : Belalang " << lokal_index + 1 << "  -> ";
    tampilkan_rute_belalang(lokal_index, dim_data);

    output << "\nNilai calon belalang target iterasi = " << lokal_best << "\n\n";

    if (lokal_best < simpan) {
        // Update target
        output << "Karena " << lokal_best << " < " << simpan << " -> UPDATE TARGET\n";
        output << "Belalang target baru = \nBelalang "<< lokal_index + 1 << " -> ";
        tampilkan_rute_belalang(lokal_index, dim_data);
        output << "\nNilai fungsi tujuan = " << lokal_best << "\n";

        // update global best
        simpan = lokal_best;
        indextarget = lokal_index;
        best_value_global = simpan;
        best_index = indextarget;

        // simpan rute terbaik
        for (int b = 0; b < pelanggan; b++) {
            best_dim_saved[b] = dim_data[lokal_index][b];
            dim[indextarget][b] = dim_data[lokal_index][b]; // update dim populasi
        }
    }
    else {
        // Tidak ada perbaikan
        output << "Karena " << lokal_best << " >= " << simpan << " -> TIDAK UPDATE TARGET\n";
        output << "Belalang target tetap = \nBelalang "<< indextarget + 1 << " -> ";
        tampilkan_rute_belalang(indextarget, dim);
        output << "\nNilai fungsi tujuan = " << simpan << "\n";
    }

    output << "\n";
}

void fungsitujuanhasil(int fx[1000], int dim[1000][1000]) {
    output << "\n\n ====== HASIL TERBAIK ======\n\n";
    
    int indeks_terbaik = indextarget;
    sisabarang_skrg = kapasitas_kendaraan;
    isiskrg = kapasitas_kendaraan;
    jarak_skrg = jarak[0][dim[indeks_terbaik][0]];
    sisabarang_skrg = sisabarang_skrg - delivery[dim[indeks_terbaik][0]];
    isiskrg = isiskrg - delivery[dim[indeks_terbaik][0]] + pickup[dim[indeks_terbaik][0]];
    kapasitaskosongskrg = kapasitas_max - isiskrg;
    nrute = 1;
    ruteskrg = 0;
    rute[ruteskrg] = dim[indeks_terbaik][0];
    ruteskrg += 1;
    jaraktotal = 0;
    
    cout << "\nRUTE TERBAIK:\n";
    output << "\nRUTE TERBAIK:\n";
    
    for (p = 0; p < pelanggan - 1; p++) {
        sisabarang_skrg = sisabarang_skrg - delivery[dim[indeks_terbaik][p + 1]];
        if (sisabarang_skrg >= 0 && (isiskrg - delivery[dim[indeks_terbaik][p + 1]] + pickup[dim[indeks_terbaik][p + 1]]) <= kapasitas_max) {
            isiskrg = isiskrg - delivery[dim[indeks_terbaik][p + 1]] + pickup[dim[indeks_terbaik][p + 1]];
            kapasitaskosongskrg = kapasitas_max - isiskrg;
            jarak_skrg = jarak_skrg + jarak[dim[indeks_terbaik][p]][dim[indeks_terbaik][p + 1]];
            rute[ruteskrg] = dim[indeks_terbaik][p + 1];
            ruteskrg += 1;
        } else {
            jarak_skrg = jarak_skrg + jarak[dim[indeks_terbaik][p]][0];
            jaraktotal = jaraktotal + jarak_skrg;
            
            cout << "Rute " << nrute << ": Depot(0)-";
            output << "Rute " << nrute << ": Depot(0)-";
            for (k = 0; k < ruteskrg; k++) {
                cout << rute[k] << "-";
                output << rute[k] << "-";
            }
            cout << "Depot(0)  Jarak: " << jarak_skrg << "\n";
            output << "Depot(0)  Jarak: " << jarak_skrg << "\n";
            
            nrute += 1;
            ruteskrg = 0;
            rute[ruteskrg] = dim[indeks_terbaik][p + 1];
            ruteskrg += 1;
            jarak_skrg = jarak[0][dim[indeks_terbaik][p + 1]];
            sisabarang_skrg = kapasitas_kendaraan;
            isiskrg = kapasitas_kendaraan;
            sisabarang_skrg = sisabarang_skrg - delivery[dim[indeks_terbaik][p + 1]];
            isiskrg = isiskrg - delivery[dim[indeks_terbaik][p + 1]] + pickup[dim[indeks_terbaik][p + 1]];
            kapasitaskosongskrg = kapasitas_max - isiskrg;
        }
        
        if (p == pelanggan - 2) {
            jarak_skrg = jarak_skrg + jarak[dim[indeks_terbaik][p + 1]][0];
            jaraktotal = jaraktotal + jarak_skrg;
            
            cout << "Rute " << nrute << ": Depot(0)-";
            output << "Rute " << nrute << ": Depot(0)-";
            for (k = 0; k < ruteskrg; k++) {
                cout << rute[k] << "-";
                output << rute[k] << "-";
            }
            cout << "Depot(0)  Jarak: " << jarak_skrg << "\n";
            output << "Depot(0)  Jarak: " << jarak_skrg << "\n";
        }
    }
    
    fx[indeks_terbaik] = jaraktotal;
    cout << "\nTotal Jarak Tempuh: " << jaraktotal << "\n";
    output << "\nTotal Jarak Tempuh: " << jaraktotal << "\n";
}

void tentukan_target_awal() {
    int best0 = fx[0];
    indextarget = 0;

    for (int z = 1; z < pop; z++) {
        if (fx[z] < best0) {
            best0 = fx[z];
            indextarget = z;
        }
    }

    simpan = best0;
    best_value_global = best0;
    best_index = indextarget;
    for (p = 0; p < pelanggan; p++) best_dim_saved[p] = dim[indextarget][p];

    output << "\n===========================================\n";
    output << "              SOLUSI AWAL \n";
    output << "===========================================\n";
    output << "Belalang target awal : Belalang " << indextarget + 1 << "  -> ";
    tampilkan_rute_belalang(indextarget, dim);
    output << "\nNilai fungsi tujuan = " << simpan << "\n\n";
}

int main() {
    srand((unsigned)time(NULL));
    judul();
    inisialisasiparameter();
    ambildata();
    
    // Buka file output
    vrpspd.open("proses_cgoa.txt", ios::app);
    
    cout << "\n==========================================\n";
    cout << "   PROSES CGOA UNTUK VRPSPD DIMULAI\n";
    cout << "==========================================\n";
    
    gen_popawal();
    urutan_pop(posisi, dim);
    fungsitujuan(fx, dim);

    // tentukan target awal dan simpan
    tentukan_target_awal();
    
    for (iterasi = 0; iterasi < maxiter; iterasi++) {
        cout << "\nIterasi " << iterasi + 1 << " dari " << maxiter << endl;

        // --- Output ke File Proses CGOA ---
        output << "\n\n==============================================\n";
        output << "               ITERASI KE-" << iterasi + 1 << "\n";
        output << "==============================================\n";
        
        // Generate atau update parameter chaotic
        generate_chaotic_parameters();
        
        if (iterasi == 0) {
            hitungjarak(posisi);
            updateposisi(posisi);
        } else {
            hitungjarak(x_new);
            updateposisi(x_new);
        }
        
        urutan_pop(x_new, dim_new);
        fungsitujuan(fx_baru, dim_new);

        // proses kandidat target iterasi dan bandingkan dengan best global
        proses_target_iterasi(fx_baru, dim_new, iterasi);
        
        // update fx array pada index target supaya consistent
        fx[indextarget] = simpan;

        cout << "Hasil terbaik Iterasi " << iterasi + 1 << ": ";
        for (p = 0; p < pelanggan; p++) {
            cout << dim[indextarget][p] << " ";
        }
        cout << " | Total Jarak: " << fx[indextarget] << "\n";
    }

    // ================================
    //    HITUNG ULANG CHAOTIC TERAKHIR
    // ================================
    generate_chaotic_parameters();  // <--- ini yang kamu minta

    output << "\n===========================================\n";
    output << "      UPDATE NILAI CHAOTIC TERBARU        \n";
    output << "===========================================\n";
    output << "c1 TERBARU = " << c1 << "\n";
    output << "c2 TERBARU = " << c2 << "\n\n";

    
    cout << "\n\n==========================================\n";
    cout << "   SOLUSI TERBAIK CGOA UNTUK VRPSPD\n";
    cout << "==========================================\n";
    
    for (p = 0; p < pelanggan; p++) {
        cout << dim[indextarget][p] << "\t";
    }
    cout << endl;
    
    fungsitujuanhasil(fx, dim);
    
    // Simpan parameter ke file
    output << "\n\nPARAMETER CGOA YANG DIGUNAKAN:\n";
    output << "Populasi: " << pop << endl;
    output << "Maksimum Iterasi: " << maxiter << endl;
    output << "Persen Muatan Awal: " << kapasitas << "%" << endl;
    output << "Batas Bawah (lbd): " << lbd << endl;
    output << "Batas Atas (ubd): " << ubd << endl;
    output << "Nilai f: " << f << endl;
    output << "Nilai l: " << l << endl;
    output << "Kapasitas Maksimum: " << kapasitas_max << endl;
    output << "Kapasitas Kendaraan: " << kapasitas_kendaraan << endl;
    
    vrpspd.close();
    output.close();
    
    cout << "\n\nProses selesai! Hasil disimpan dalam file output." << endl;
    cout << "Tekan tombol apa saja untuk keluar...";
    getch();
    
    return 0;
}
