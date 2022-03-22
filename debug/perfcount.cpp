#include "perfcount.hpp"

#include <cstdlib>
#include <map>
#include <vector>
#include <thread>

#include "3rdparty/pugi/pugixml.hpp"

#define accuracy microseconds

static std::map<std::thread::id, std::map<std::string, std::vector<std::chrono::accuracy>>> perfData;
static std::map<std::thread::id, std::chrono::high_resolution_clock::time_point> startTimes;

static bool perfcountInitialized = false;

static void writePerfData() {
    pugi::xml_document doc;
    
    auto root = doc.append_child("perfData");

    #define _stringify(name) #name
    #define stringify(name) _stringify(name)

    root.append_attribute("accuracy").set_value(stringify(accuracy));
    
    #undef _stringify
    #undef stringify

    int id = 0;
    for (auto threadData : perfData) {
        auto thread = root.append_child("thread");
        thread.append_attribute("id").set_value(id++);
        for (auto funcData : threadData.second) {
            auto func = thread.append_child("func");
            func.append_attribute("name").set_value(funcData.first.c_str());
            for (auto run : funcData.second) {
                func.append_child("run").append_attribute("time").set_value(run.count());
            }
        }
    }

    doc.save_file(BEANS_DBG_PERFCOUNT_FILE, "    ", pugi::format_indent | pugi::format_no_declaration);
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
    perfData[std::this_thread::get_id()][funcName].push_back(std::chrono::duration_cast<std::chrono::accuracy>(end - start));
}