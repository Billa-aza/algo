import math

# ===============================
# Membership Functions
# ===============================

def s_curve(x, a, b):
    if x <= a: return 0.0
    if x >= b: return 1.0
    mid = (a + b) / 2
    if x <= mid:
        return 2 * ((x - a) / (b - a)) ** 2
    return 1 - 2 * ((x - b) / (b - a)) ** 2


def turun_power(x, a, b, mu_at_mid=0.08, x_mid=60):
    if x <= a: return 1.0
    if x >= b: return 0.0
    base = (b - x_mid) / (b - a)
    p = math.log(mu_at_mid) / math.log(base)
    return ((b - x) / (b - a)) ** p


def lin_down(x, a, b):
    if x <= a: return 1.0
    if x >= b: return 0.0
    return (b - x) / (b - a)


def lin_up(x, a, b):
    if x <= a: return 0.0
    if x >= b: return 1.0
    return (x - a) / (b - a)


# ===============================
# Tsukamoto Core
# ===============================

def z_berkurang(alpha):
    return 75 - 68 * alpha


def z_bertambah(alpha):
    return 25 + 75 * alpha


def hitung_tsukamoto(demand_k, stock_k):
    mu_naik = s_curve(demand_k, 45, 75)
    mu_turun = turun_power(demand_k, 45, 75)
    mu_sedikit = lin_down(stock_k, 2, 10)
    mu_banyak = lin_up(stock_k, 5, 11)

    a1 = min(mu_turun, mu_banyak)
    a2 = min(mu_naik, mu_sedikit)
    a3 = min(mu_naik, mu_banyak)
    a4 = min(mu_turun, mu_sedikit)

    z1 = z_berkurang(a1)
    z2 = z_bertambah(a2)
    z3 = z_bertambah(a3)
    z4 = z_berkurang(a4)

    z_star = (a1*z1 + a2*z2 + a3*z3 + a4*z4) / (a1 + a2 + a3 + a4)

    return {
        'z_star': z_star,
        'rekomendasi': round(z_star * 1000)
    }


# ===============================
# MAIN PROGRAM
# ===============================

demand = None
stock = None
hasil = None
produksi_user = None

while True:
    print("\n=== MENU PERENCANAAN PRODUKSI ===")
    print("1. Input demand")
    print("2. Input stock")
    print("3. Hitung rekomendasi produksi (sistem)")
    print("4. Tentukan jumlah produksi (user)")
    print("5. Evaluasi keputusan produksi")
    print("6. Keluar")

    menu = input("Pilih menu (1-6): ")

    if menu == "1":
        demand = float(input("Masukkan demand (ribuan): "))
        print("Demand disimpan.")

    elif menu == "2":
        stock = float(input("Masukkan stock (ribuan): "))
        print("Stock disimpan.")

    elif menu == "3":
        if demand is None or stock is None:
            print("Input demand dan stock terlebih dahulu!")
        else:
            hasil = hitung_tsukamoto(demand, stock)
            print("Rekomendasi produksi telah dihitung.")

    elif menu == "4":
        if hasil is None:
            print("Hitung rekomendasi terlebih dahulu!")
        else:
            produksi_user = int(input("Masukkan jumlah produksi yang diinginkan (kaleng): "))
            print("Jumlah produksi user disimpan.")

    elif menu == "5":
        if hasil is None or produksi_user is None:
            print("Data belum lengkap!")
        else:
            print("\n=== EVALUASI PRODUKSI ===")
            print("Rekomendasi sistem :", hasil['rekomendasi'], "kaleng")
            print("Produksi user      :", produksi_user, "kaleng")

            selisih = produksi_user - hasil['rekomendasi']
            print("Selisih            :", selisih, "kaleng")

            if abs(selisih) <= 1000:
                print("Keputusan produksi: OPTIMAL")
            elif selisih > 0:
                print("Keputusan produksi: OVER PRODUKSI")
            else:
                print("Keputusan produksi: UNDER PRODUKSI")

    elif menu == "6":
        print("Program selesai.")
        break

    else:
        print("Menu tidak valid!")