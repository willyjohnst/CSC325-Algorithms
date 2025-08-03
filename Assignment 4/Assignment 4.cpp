#include <iostream>
#include <vector>
#include <iomanip>

using namespace::std;

struct item {
    string obj; 
    int value, weight;
    item(string o, int v, int w) : obj(o), value(v), weight(w) {}
};


class priority_queue {
private:
    void binary_insert(item x, int high, int low) {
        int x_weighted_value = x.value / x.weight;
        while (low <= high) {
            const int mid = low + (high - low) / 2;
            if (x_weighted_value == pq.at(mid).value / pq.at(mid).weight) {
                pq.insert(pq.begin() + mid, x);
                return;
            }
            else if (x_weighted_value > pq.at(mid).value / pq.at(mid).weight) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        pq.insert(pq.begin() + low, x);
    }
public:
    vector<item> pq;
    void additem(item x) {
        binary_insert(x, pq.size() - 1, 0);
    }
    const item get_highest() {
        item x = pq.back();
        pq.pop_back();
        return x;
    }
};

void print_fp_solution(const vector<item>& bagged_items) {
    cout << left << setw(20) << "Item Name"
        << right << setw(10) << "Weight"
        << right << setw(10) << "Value" << endl;
    cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;

    int total_weight = 0;
    int total_value = 0;

    for (const auto& item : bagged_items) {
        cout << left << setw(20) << item.obj
            << right << setw(10) << item.weight
            << right << setw(10) << item.value << endl;
        total_weight += item.weight;
        total_value += item.value;
    }

    cout << setfill('-') << setw(40) << "" << setfill(' ') << endl;
    cout << left << setw(20) << "Totals:"
        << right << setw(10) << total_weight
        << right << setw(10) << total_value << endl;
}


void farmer_problem(const vector<item>& cave_items, int max_weight) {
    priority_queue cave_items_sort;
    vector<item> bagged_items;
    int bag_weight = 0;

    for (item x : cave_items) {
        cave_items_sort.additem(x);
    }
    for (item curr : cave_items_sort.pq) {
        item curr = cave_items_sort.get_highest();
        if (max_weight > bag_weight + curr.weight) {
            bag_weight += curr.weight;
            bagged_items.push_back(curr);
        }
    }
    print_fp_solution(bagged_items);
}



int main()
{
    vector<item> items;
    items.push_back(item("Elephant horn 1", 4000, 2));
    items.push_back(item("Elephant horn 2", 4500, 3));
    items.push_back(item("Hammer", 4500, 3));
    items.push_back(item("Scissors", 500, 1));
    items.push_back(item("Vase 1", 5000, 2));
    items.push_back(item("Vase 2", 7000, 3));
    items.push_back(item("Vase 3", 8000, 7));
    items.push_back(item("Stone neck chain", 1000, 1));

    farmer_problem(items, 13);
}

