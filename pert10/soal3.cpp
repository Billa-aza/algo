#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
using namespace std;

struct Process {
    string name;
    int at, bt, qclass;
    int remaining;
    int ct = 0, tat = 0, wt = 0, rt = -1;
};

int main() {
    int n;
    cout << "Masukkan jumlah proses: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        cout << "\nProses " << i+1 << endl;
        cout << "Nama proses : "; cin >> p[i].name;
        cout << "Arrival Time: "; cin >> p[i].at;
        cout << "Burst Time  : "; cin >> p[i].bt;
        cout << "Queue (1=RR, 2=FCFS): "; cin >> p[i].qclass;
        p[i].remaining = p[i].bt;
    }

    queue<int> q1, q2; 
    int time = 0, completed = 0;
    vector<pair<int,string>> gantt;
    vector<string> ganttLevel;

    while (completed < n) {

        for (int i = 0; i < n; i++) {
            if (p[i].at == time) {
                if (p[i].qclass == 1) q1.push(i);
                else q2.push(i);
            }
        }

        int idx = -1;
        int levelUsed = 0;

        if (!q1.empty()) {
            idx = q1.front();
            q1.pop();
            levelUsed = 1;

            if (p[idx].rt == -1)
                p[idx].rt = time - p[idx].at;

            gantt.push_back({time, p[idx].name});
            ganttLevel.push_back("Q1");

            int quantum = 2;

            while (quantum-- && p[idx].remaining > 0) {
                p[idx].remaining--;
                time++;

                for (int i = 0; i < n; i++) {
                    if (p[i].at == time) {
                        if (p[i].qclass == 1) q1.push(i);
                        else q2.push(i);
                    }
                }

                if (p[idx].remaining == 0) break;

                if (!q1.empty()) break;
            }

            if (p[idx].remaining > 0)
                q1.push(idx);    
            else
                p[idx].ct = time; 

            if (p[idx].remaining == 0) completed++;
            continue;
        }

        else if (!q2.empty()) {
            idx = q2.front();
            q2.pop();
            levelUsed = 2;

            if (p[idx].rt == -1)
                p[idx].rt = time - p[idx].at;

            gantt.push_back({time, p[idx].name});
            ganttLevel.push_back("Q2");

            while (p[idx].remaining > 0) {
                p[idx].remaining--;
                time++;

            
                for (int i = 0; i < n; i++) {
                    if (p[i].at == time) {
                        if (p[i].qclass == 1) q1.push(i);
                        else q2.push(i);
                    }
                }

                if (!q1.empty()) break;
            }

            if (p[idx].remaining == 0) {
                p[idx].ct = time;
                completed++;
            } else {
                q2.push(idx);
            }

            continue;
        }

        time++;
    }

    for (auto &x : p) {
        x.tat = x.ct - x.at;
        x.wt  = x.tat - x.bt;
    }

    cout << "\n=== GANTT CHART (MLQ) ===\n";
    for (int i=0;i<gantt.size();i++)
        cout << "| " << gantt[i].second << "(" << ganttLevel[i] << ") ";
    cout << "|\n0 ";

    for (auto &g : gantt) cout << g.first << " ";
    cout << time << endl;

    cout << "\n=== TABEL HASIL ===\n";
    cout << left << setw(8) << "Proses"
         << setw(6) << "AT"
         << setw(6) << "BT"
         << setw(6) << "Q"
         << setw(6) << "CT"
         << setw(6) << "TAT"
         << setw(6) << "WT"
         << setw(6) << "RT"
         << endl;

    double sumWT1=0, sumWT2=0, sumTAT1=0, sumTAT2=0;
    int c1=0, c2=0;

    for (auto &x : p) {
        cout << left << setw(8) << x.name
             << setw(6) << x.at
             << setw(6) << x.bt
             << setw(6) << x.qclass
             << setw(6) << x.ct
             << setw(6) << x.tat
             << setw(6) << x.wt
             << setw(6) << x.rt
             << endl;

        if (x.qclass == 1) {
            sumWT1 += x.wt; sumTAT1 += x.tat; c1++;
        } else {
            sumWT2 += x.wt; sumTAT2 += x.tat; c2++;
        }
    }

    cout << "\n=== PERBANDINGAN KINERJA ===\n";
    cout << "Queue 1 (RR):\n";
    cout << "  Rata-rata WT  : " << sumWT1/c1 << endl;
    cout << "  Rata-rata TAT : " << sumTAT1/c1 << endl;

    cout << "Queue 2 (FCFS):\n";
    cout << "  Rata-rata WT  : " << sumWT2/c2 << endl;
    cout << "  Rata-rata TAT : " << sumTAT2/c2 << endl;

    cout << "\n=== ANALISIS MLQ ===\n";
    cout << "Kelebihan:\n"
         << "- Proses prioritas tinggi (Q1) selalu didahulukan.\n"
         << "- RR di Q1 memberi fairness antar proses interaktif.\n"
         << "- FCFS di Q2 ideal untuk batch/long jobs.\n\n"
         << "Kekurangan:\n"
         << "- Proses di Q2 dapat mengalami starvation jika Q1 sangat sibuk.\n"
         << "- Tidak fleksibel: proses TIDAK bisa pindah queue.\n"
         << "- Jika tingkat kedatangan Q1 tinggi, performa Q2 sangat buruk.\n";

    return 0;
}
