# Tugas Proyek Struktur Data Semester 4

**Kelompok:** 4. 6  
**Anggota:**  
- Adillah Ridwan [M0403241072]
- Tesalonika Natalie Sofi Siregar [M0403241185]  
- Nadya Shafwah Rizalti	[M0403241007]  
- Muhammad Rezonaldo Yunus [M0403241122]

---
# Topik 6: Sistem Rekomendasi Produk Berbasis Riwayat Transaksi

**Konteks industri:** e-commerce

Kasus ini menggambarkan sistem rekomendasi sederhana pada platform e-commerce yang memanfaatkan riwayat transaksi pelanggan. Pada tahap awal, rekomendasi produk dapat dilakukan secara manual atau berbasis aturan sederhana, seperti menampilkan produk terlaris atau produk yang sering dibeli secara bersamaan.

Seiring bertambahnya jumlah transaksi, produk, dan pengguna, pencarian pola pembelian dan penyajian rekomendasi menjadi semakin lambat jika data dikelola secara sederhana. Oleh karena itu, diperlukan pemilihan struktur data yang tepat agar pengelolaan riwayat transaksi dan penyusunan rekomendasi tetap efisien meskipun volume data meningkat.

> Sistem rekomendasi ini **tidak berbasis machine learning**. Rekomendasi dibangun menggunakan aturan sederhana (rule-based) yang dapat dijelaskan secara eksplisit melalui perhitungan frekuensi dan pencarian data.

Bentuk rekomendasi yang dikembangkan dibatasi pada:
- Rekomendasi produk paling sering dibeli (Top-N produk)
- Rekomendasi produk yang sering dibeli bersama dalam transaksi yang sama (frequently bought together)
- Rekomendasi berbasis riwayat pelanggan, yaitu menyarankan produk yang sering muncul pada transaksi pelanggan lain dengan pola pembelian serupa

Seluruh rekomendasi harus dapat dijelaskan secara logis menggunakan data transaksi yang tersedia, tanpa melibatkan model prediktif atau proses pembelajaran otomatis.

---

## Permasalahan di Lapangan
- Riwayat transaksi semakin besar dan sulit dicari secara cepat
- Penyusunan rekomendasi produk menjadi lambat jika data tidak terstruktur dengan baik
- Update data transaksi dan produk memengaruhi performa sistem
- Sistem sederhana tidak mampu menangani pertumbuhan data transaksi

---

## Tujuan Proyek
Membangun sistem rekomendasi produk sederhana berbasis riwayat transaksi, serta membandingkan performa struktur data yang digunakan untuk pengelolaan data transaksi dan penyusunan rekomendasi.

---

## Domain Data (Minimal)
- ID transaksi
- ID pelanggan
- ID produk
- Nama produk
- Kategori produk
- Jumlah pembelian
- Tanggal transaksi

---

## Aktivitas Sistem Wajib
- Insert data transaksi
- Search riwayat transaksi berdasarkan pelanggan atau produk
- Analisis sederhana pola pembelian (misalnya: produk paling sering dibeli, atau produk yang sering muncul dalam transaksi yang sama)
- Generate rekomendasi produk sederhana
- Delete atau update data transaksi

---

## Fokus Analisis
Analisis perbandingan struktur data terhadap:
- Kecepatan pencarian riwayat transaksi
- Efisiensi penyusunan rekomendasi produk berbasis frekuensi
- Kemudahan insert, update, dan delete data transaksi
- Dampak pertumbuhan jumlah transaksi terhadap performa sistem

---

## Target Minggu ke-7 (Progress)
- Spesifikasi sistem & skenario transaksi e-commerce
- Implementasi minimal 1 struktur data
- Dataset awal transaksi (dummy / simulasi)
- Pengujian awal insert dan search transaksi

---

## Target Minggu ke-14 (Final)
- Implementasi lengkap ≥ 2 struktur data
- Grafik perbandingan waktu eksekusi & penggunaan memori
- Demo aplikasi sistem rekomendasi produk sederhana
- Laporan analisis performa & rekomendasi struktur data

---

## Catatan
Mahasiswa **tidak diwajibkan dan tidak dinilai** berdasarkan implementasi:
- Machine learning
- Collaborative filtering
- Content-based filtering
- Similarity matrix atau model prediktif lainnya

Fokus penilaian adalah pada penggunaan **struktur data**, pengelolaan data transaksi, dan analisis performa sistem dalam menghasilkan rekomendasi sederhana berbasis riwayat transaksi. Analisis pola pembelian bersifat sederhana dan berbasis **hitungan frekuensi (counting)**, bukan berbasis prediksi, pembelajaran model, atau perhitungan similarity.