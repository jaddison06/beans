#include "perfcount.hpp"

#include <cstdlib>
#include <map>
#include <vector>
#include <thread>

#include <stdio.h>

using accuracy = std::chrono::microseconds;

static std::map<std::thread::id, std::map<std::string, std::vector<accuracy>>> perfData;
static std::map<std::thread::id, std::chrono::high_resolution_clock::time_point> startTimes;

static bool perfcountInitialized = false;

static void writePerfData() {
    int thread = 0;
    for (auto threadData : perfData) {
        printf("thread %i\n", thread++);
        for (auto funcData : threadData.second) {
            printf("  function %s\n", funcData.first.c_str());
            for (auto run : funcData.second) {
                printf("    %i microseconds\n", run.count());
            }
        }
    }
}

static void initialize() {
    std::atexit(writePerfData);

    perfcountInitialized = true;
}

void beans::perfcountStart() {
    if (!perfcountInitialized) initialize();

    startTimes[std::this_thread::get_id()] = std::chrono::high_resolution_clock::now();
}

void beans::perfcountEnd(std::string funcName) {
    auto end = std::chrono::high_resolution_clock::now();
    auto start = startTimes[std::this_thread::get_id()];
    perfData[std::this_thread::get_id()][funcName].push_back(std::chrono::duration_cast<accuracy>(end - start));
}