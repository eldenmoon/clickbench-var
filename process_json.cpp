#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cerr << "Error: Cannot open input file." << std::endl;
        return 1;
    }

    std::string line;
    std::ofstream outputFile("output.json");
    size_t i = 0;
    while (std::getline(input_file, line)) {
        rapidjson::Document document;
        document.Parse(line.c_str());

        if (!document.HasParseError() && document.IsObject()) {
            rapidjson::Value& EventDate = document["EventDate"];
            rapidjson::Value& EventTime = document["EventTime"];
            rapidjson::Value& ClientEventTime = document["ClientEventTime"];
            rapidjson::Value& LocalEventTime = document["LocalEventTime"];
            rapidjson::Value& UserID = document["UserID"];
            rapidjson::Value& WatchID = document["WatchID"];
            rapidjson::Value& FUniqID = document["FUniqID"];
            rapidjson::Value& ParamPrice = document["ParamPrice"];
            rapidjson::Value& RefererHash = document["RefererHash"];
            rapidjson::Value& URLHash = document["URLHash"];

            rapidjson::Document new_document;
            new_document.SetObject();

            rapidjson::Document var;
            var.CopyFrom(document, var.GetAllocator()); 
            var.EraseMember("EventDate");
            var.EraseMember("EventTime");
            var.EraseMember("ClientEventTime");
            var.EraseMember("LocalEventTime");
            var.EraseMember("UserID");
            var.EraseMember("WatchID");
            var.EraseMember("FUniqID");
            var.EraseMember("ParamPrice");
            var.EraseMember("RefererHash");
            var.EraseMember("URLHash");
            new_document.AddMember("EventTime", EventTime, new_document.GetAllocator());
            new_document.AddMember("EventDate", EventDate, new_document.GetAllocator());
            new_document.AddMember("ClientEventTime", ClientEventTime, new_document.GetAllocator());
            new_document.AddMember("LocalEventTime", LocalEventTime, new_document.GetAllocator());
            new_document.AddMember("UserID", UserID, new_document.GetAllocator());
            new_document.AddMember("WatchID", WatchID, new_document.GetAllocator());
            new_document.AddMember("FUniqID", FUniqID, new_document.GetAllocator());
            new_document.AddMember("ParamPrice", ParamPrice, new_document.GetAllocator());
            new_document.AddMember("RefererHash", RefererHash, new_document.GetAllocator());
            new_document.AddMember("URLHash", URLHash, new_document.GetAllocator());

            new_document.AddMember("var", var, new_document.GetAllocator());

            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
            new_document.Accept(writer);

            if (i % 100000 == 0) {
                std::cout << "procceed " << i  << " lines" << std::endl;
            }

             // 将处理后的 JSON 数据写入目标文件
            if (outputFile.is_open()) {
                outputFile << buffer.GetString() << std::endl;
                ++i;
            } else {
                std::cout << "fuck!" << std::endl;
            }
        }
    }
    outputFile.close();

    return 0;
}

