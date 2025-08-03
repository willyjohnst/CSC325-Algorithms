#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct job {
    char name;
    int deadline;
    int profit;
    job(char n, int d, int p) : name(n), deadline(d), profit(p) {}
    job() {
        name = '?';
        deadline = -1;
        profit = -1;
    }
};

vector<job>* sort(vector<job>& jobs) {
    for (int i = 0; i < jobs.size(); i++) {
        for (int j = 0; j < jobs.size(); j++) {
            if (jobs.at(j).profit > jobs.at(i).profit) {
                job temp = jobs.at(i);
                jobs.at(i) = jobs.at(j);
                jobs.at(j) = temp;
            }
        }
    }
    return &jobs;
}

int main()
{
    vector<job> jobs;
    jobs.push_back({ 'A', 2, 100 });
    jobs.push_back({ 'B', 1, 19 });
    jobs.push_back({ 'C', 2, 27 });
    jobs.push_back({ 'D', 1, 25 });
    jobs.push_back({ 'E', 3, 15 });
    sort(jobs);

    int max_time = 0;
    for (int i = 0; i < jobs.size(); i++) {
        if (jobs.at(i).deadline > max_time) {
            max_time = jobs.at(i).deadline;
        }
    }

    vector<job> time_slots(max_time);

    for (int i = 0; i < 5; i++) {
        job top = jobs.back();
        jobs.pop_back();
        for (int j = time_slots.size() - 1; j >= 0; j--) {
            if (time_slots.at(j).profit == -1 and j < top.deadline) {
                time_slots.at(j) = top;
                break;
            }
        }
    }

    cout << "Max number of jobs that can be completed within deadlines: " << max_time << endl;

    cout << "Jobs list in order: " << endl;
    for (int i = 0; i < time_slots.size(); i++) {
        cout << "Position " << i + 1 << ": " << time_slots.at(i).name << " profit: " << time_slots.at(i).profit << " deadline: " << time_slots.at(i).deadline << endl;
    }

    cout << "Total profit: " << time_slots.at(0).profit + time_slots.at(1).profit + time_slots.at(2).profit << endl;

    return 0;
}
