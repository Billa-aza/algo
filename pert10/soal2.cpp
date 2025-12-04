#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    string name;
    int at, bt, priority;
    int remaining;
    int ct = 0, tat = 0, wt = 0, rt = -1;
    int waiting = 0;
};

int main() {
    int n;
    cout << "Masukkan jumlah proses: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        cout << "\nProses " << i + 1 << endl;
        cout << "Nama proses : ";
        cin >> p[i].name;
        cout << "Arrival Time: ";
        cin >> p[i].at;
        cout << "Burst Time  : ";
        cin >> p[i].bt;
        cout << "Priority    : ";
        cin >> p[i].priority;

        p[i].remaining = p[i].bt;
    }

    int time = 0, completed = 0, prev = -1;
    vector<pair<int,string>> gantt;
    int aging_count = 0;

    while (completed != n) {

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining > 0) {
                if (i != prev) p[i].waiting++; 
                if (p[i].waiting > 5) {
                    p[i].priority--;
                    p[i].waiting = 0;
                    aging_count++;
                }
            }
        }

        int idx = -1;
        int best = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining > 0) {
                if (p[i].priority < best) {
                    best = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (p[idx].rt == -1) 
                p[idx].rt = time - p[idx].at;

            if (prev != idx)
                gantt.push_back({time, p[idx].name});

            p[idx].remaining--;
            p[idx].waiting = 0;
            time++;
            prev = idx;

            if (p[idx].remaining == 0) {
                p[idx].ct = time;
                completed++;
            }

        } else {
            time++;
        }
    }

    cout << "\n\n=== GANTT CHART (Priority + Aging + Preemption) ===\n";
    for (auto &g : gantt) cout << "| " << g.second << " ";
    cout << "|\n0 ";

    for (auto &g : gantt) cout << g.first << " ";
    cout << time << endl;

    for (auto &x : p) {
        x.tat = x.ct - x.at;
        x.wt  = x.tat - x.bt;
    }

    cout << "\n=== TABEL HASIL ===\n";
    cout << left << setw(8) << "Proses"
         << setw(8) << "AT"
         << setw(8) << "BT"
         << setw(10) << "Prior"
         << setw(8) << "CT"
         << setw(8) << "TAT"
         << setw(8) << "WT"
         << setw(8) << "RT"
         << endl;

    for (auto &x : p) {
        cout << left << setw(8) << x.name
             << setw(8) << x.at
             << setw(8) << x.bt
             << setw(10) << x.priority
             << setw(8) << x.ct
             << setw(8) << x.tat
             << setw(8) << x.wt
             << setw(8) << x.rt
             << endl;
    }

    cout << "\nJumlah perubahan priority karena aging: " << aging_count << endl;

    cout << "\nPenjelasan Starvation:\n";
    cout << "Pada Priority Scheduling preemptive, proses dengan prioritas rendah dapat terus ditunda\n"
            "jika selalu ada proses prioritas lebih tinggi yang datang. Aging mencegah hal ini dengan\n"
            "menaikkan prioritas proses yang sudah menunggu terlalu lama.\n";

    return 0;
}
