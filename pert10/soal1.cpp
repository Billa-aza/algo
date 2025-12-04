#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    string name;
    int at, bt;
    int remaining;
    int ct = 0;
    int tat = 0;
    int wt = 0;
    int rt = -1;
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
        p[i].remaining = p[i].bt;
    }

    int time = 0, completed = 0, prev = -1;
    vector<pair<int,string>> gantt; // time , process_name
    int preemption_count = 0;

    while (completed != n) {
        int idx = -1;
        int mn = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining > 0) {
                if (p[i].remaining < mn) {
                    mn = p[i].remaining;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (p[idx].rt == -1) {
                p[idx].rt = time - p[idx].at;
            }

            if (prev != idx && prev != -1) 
                preemption_count++;

            if (prev != idx)
                gantt.push_back({time, p[idx].name});

            p[idx].remaining--;
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

    cout << "\n\n=== GANTT CHART (Dynamic with Preemption) ===\n";
    for (int i = 0; i < gantt.size(); i++) {
        cout << "| " << gantt[i].second << " ";
    }
    cout << "|\n";

    cout << "0 ";
    for (int i = 0; i < gantt.size(); i++) {
        cout << gantt[i].first << " ";
    }
    cout << time << endl;

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
    }

    cout << "\n\n=== TABEL HASIL ===\n";
    cout << left << setw(8) << "Proses" 
         << setw(8) << "AT"
         << setw(8) << "BT"
         << setw(8) << "CT"
         << setw(8) << "TAT"
         << setw(8) << "WT"
         << setw(8) << "RT"
         << endl;

    for (auto &x : p) {
        cout << left << setw(8) << x.name
             << setw(8) << x.at
             << setw(8) << x.bt
             << setw(8) << x.ct
             << setw(8) << x.tat
             << setw(8) << x.wt
             << setw(8) << x.rt
             << endl;
    }

    cout << "\nJumlah Preemption: " << preemption_count << endl;

    cout << "\nPenjelasan Starvation:\n";
    cout << "Pada algoritma SRTF, proses dengan burst time besar dapat tertunda terus-menerus\n"
            "jika selalu datang proses baru dengan burst time lebih kecil. Ini menyebabkan\n"
            "proses tersebut mengalami *starvation* atau menunggu terlalu lama.\n";

    return 0;
}
