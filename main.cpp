#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

#define JSON_HAS_CPP_14 1
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void actorsList(const json& source) {
    std::cout << "The actors in file\n---------------" << std::endl;

    ///итерации по каждому фильму в базе
    for (auto it = source.begin(); it != source.end(); it++) {

        ///ссылка на актерский состав в конкретном фильме
        auto cast = it->find("cast&crew");
        for (auto j = cast->begin(); j != cast->end(); j++) {
            std::cout << setiosflags(std::ios::left) << std::setw(23) << j.key() << "\t";
        }
    }
    std::cout << std::endl;
}
///fill list by founded actors
void findActor(const json &source, const std::string &target, std::vector<json::const_iterator> &list) {
    for (auto it = source.begin(); it != source.end(); it++) {
        auto cast = it->find("cast&crew");
        for (auto j = cast->begin(); j != cast->end(); j++) {
            if (target == j.key()) {
                ///сохраняю указатель на фильм
                list.push_back(it);
            }
        }
    }
}

int main() {

    json films;
    std::ifstream file("filmoteka.json");
    if (file.is_open()) {
        file >> films;
        file.close();
    } else {
        std::cout << "Can`t open the data file" << std::endl;
        return 0;
    }

    std::string request;
    do {
        std::cout << "\nInput actor name (-? listing / -1 exit): ";
        std::getline(std::cin, request);

        if (request == "-?") {
            actorsList(films);
        } else if (request == "-1") {
            break;
        } else {
            std::vector<json::const_iterator> records;
            findActor(films, request, records);

            if (!records.empty()) {
                std::cout << "Actor " << request;
                for (int i = 0; i < records.size(); i++) {
                   std::cout << " as " << (*records[i])["cast&crew"][request] << " is in movie by "
                             << (*records[i])["director"] << " " << records[i].key() << "." << std::endl;
                   if (i < records.size() - 1) std::cout << "And ";
                }
            } else {
                std::cout << "Cant`t find the actor " << request << "." << std::endl;
            }
        }
    } while (request != "-1");

    return 0;
}
