#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a job
struct Job {
    int id;       // Job ID
    int deadline; // Deadline of the job
    int profit;   // Profit if the job is completed on or before the deadline
};

class Scheduler {
public:
    // Comparison function to sort jobs in decreasing order of profit
    static bool compareByProfit(Job a, Job b) {
        return a.profit > b.profit;
    }

    // Function to schedule jobs to maximize profit
    pair<vector<int>, int> scheduleJobs(Job jobs[], int numJobs) {
        // Sort jobs by profit in descending order
        sort(jobs, jobs + numJobs, compareByProfit); //jobs ->startindex, jobs_numof jobs->lastindex

        // Find the maximum deadline
        int maxDeadline = 0;
        for (int i = 0; i < numJobs; i++) {
            maxDeadline = max(maxDeadline, jobs[i].deadline);
        }

        // Time slots, initialized to -1
        vector<int> jobSlots(maxDeadline + 1, -1); // index 0 unused since deadlines start at 1 (deadline, initialization)
        vector<int> scheduledJobs;
        int totalProfit = 0;

        // Schedule jobs greedily
        for (int i = 0; i < numJobs; i++) {
            for (int slot = jobs[i].deadline; slot > 0; slot--) {
                if (jobSlots[slot] == -1) {
                    jobSlots[slot] = jobs[i].id;
                    scheduledJobs.push_back(jobs[i].id);
                    totalProfit += jobs[i].profit;
                    break;
                }
            }
        }

        return {scheduledJobs, totalProfit};
    }
};

int main() {
    int testCases;
    cout << "Enter number of test cases: ";
    cin >> testCases;

    while (testCases--) {
        int numJobs;
        cout << "\nEnter number of jobs: ";
        cin >> numJobs;

        Job jobList[numJobs];
        cout << "Enter Job ID, Deadline, and Profit for each job:\n";
        for (int i = 0; i < numJobs; i++) {
            cin >> jobList[i].id >> jobList[i].deadline >> jobList[i].profit;
        }

        Scheduler scheduler;
        pair<vector<int>, int> result = scheduler.scheduleJobs(jobList, numJobs);

        cout << "\nNumber of jobs done: " << result.first.size() << endl;
        cout << "Total profit earned: " << result.second << endl;
        cout << "Jobs scheduled (by ID): ";
        for (int jobId : result.first) {
            cout << jobId << " ";
        }
        cout << endl;
    }

    return 0;
}
