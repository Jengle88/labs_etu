#include "SaveDataReader.h"
#include "../Characters/MainHero.h"
#include "Grid.h"
#include "../UI/Models/Field.h"

const std::string SaveDataReader::START_TAG = "<start>";
const std::string SaveDataReader::END_TAG = "<end>";

std::vector<std::string> SaveDataReader::splitLine(const std::string &line) {
    std::vector<std::string> res;
    std::vector<int> separatePos;
    for (int i = 1; i < line.size(); ++i) {
        if (line[i] == ' ')
            separatePos.push_back(i);
    }
    int separateArrIndex = 0;
    res.emplace_back("");
    if (separateArrIndex + 1 < separatePos.size()) {
        res.back().reserve(separatePos[separateArrIndex + 1] - separatePos[separateArrIndex]);
    }
    for (int i = 0; i < line.size(); ++i) {
        if (separateArrIndex != separatePos.size() && separatePos[separateArrIndex] == i) {
            res.emplace_back("");
            if (separateArrIndex + 1 < separatePos.size()) {
                res.back().reserve(separatePos[separateArrIndex + 1] - separatePos[separateArrIndex]);
            }
            separateArrIndex++;
        } else
            res.back().push_back(line[i]);
    }
    if (res.back().empty())
        return {};
    else
        return res;
}

bool SaveDataReader::tagValidator(std::fstream &in) {
    int cntLayer = 0;
    std::string str;
    bool checkFlag = true;
    while (getline(in, str)) {
        if (str == START_TAG)
            cntLayer++;
        else if (str == END_TAG)
            cntLayer--;
        if (cntLayer < 0 || cntLayer > 1) {
            checkFlag = false;
            break;
        }
    }
    in.clear();
    in.seekg(0); // перемещаем курсор считывания файла в начало
    return checkFlag;
}

std::vector<std::string> SaveDataReader::extractUsefulInformation(std::fstream &in) {
    std::vector<std::string> usefulInformation;
    std::string str;
    while (getline(in, str)) {
        if (str.size() >= 2 && str[0] != '/' && str[1] != '/') // убираем пустые строки и комментарии
            usefulInformation.push_back(str);
    }
    in.clear();
    in.seekg(0); // перемещаем курсор считывания файла в начало
    return usefulInformation;
}

void SaveDataReader::nextPosition(const std::vector<std::string> &info, int &posInInfo) {
    if (posInInfo + 1 > info.size())
        throw std::length_error("Не вся информация считана или неправильный порядок данных в файле");
    else
        posInInfo++;
}

void
SaveDataReader::readWallsPos(SaveDataAdapter &saveDataAdapter, const std::vector<std::string> &info, int &posInInfo,
                             std::vector<std::string> &tokens) {
    std::vector<CellPoint> posOfWalls;
    nextPosition(info, posInInfo);
    tokens = splitLine(info[posInInfo]);
    if (tokens[0] == START_TAG) {
        nextPosition(info, posInInfo);
        tokens = splitLine(info[posInInfo]);
        while (tokens[0] != END_TAG) {
            size_t pos1, pos2;
            posOfWalls.emplace_back(CellPoint(std::stoi(tokens[0], &pos1), std::stoi(tokens[1], &pos2)));
            if (pos1 != tokens[0].size() || pos2 != tokens[1].size())
                throw std::invalid_argument("Неверное значение позиции непроходимой точки\n");
            nextPosition(info, posInInfo);
            tokens = splitLine(info[posInInfo]);
        }
    } else
        throw std::invalid_argument("Не удалось считать позиции непроходимых клеток\n");
    saveDataAdapter.setWalls(posOfWalls);
}

void SaveDataReader::readEnemiesPosHealth(SaveDataAdapter &saveDataAdapter, const std::vector<std::string> &info,
                                          int &posInInfo, std::vector<std::string> &tokens) {
    std::vector<std::pair<std::string, std::pair<double, CellPoint>>> enemiesPos;
    nextPosition(info, posInInfo);
    tokens = splitLine(info[posInInfo]);
    if (tokens[0] == START_TAG) {
        nextPosition(info, posInInfo);
        tokens = splitLine(info[posInInfo]);
        while (tokens[0] != END_TAG) {
            size_t pos1, pos2, pos3;
            enemiesPos.push_back({tokens[0],
                                  {std::stof(tokens[1], &pos1),
                                   CellPoint(std::stoi(tokens[2], &pos2), std::stoi(tokens[3], &pos3))
                                  }
                                 });
            if (pos1 != tokens[1].size() || pos2 != tokens[2].size() || pos3 != tokens[3].size())
                throw std::invalid_argument("Неверное значение информации о позициях и здоровье врагов\n");
            nextPosition(info, posInInfo);
            tokens = splitLine(info[posInInfo]);
        }
    } else
        throw std::invalid_argument("Не удалось считать позиции и здоровье врагов\n");
    saveDataAdapter.setEnemiesPos(enemiesPos);
}

void SaveDataReader::readThingsPosLevel(SaveDataAdapter &saveDataAdapter, const std::vector<std::string> &info,
                                        int &posInInfo, std::vector<std::string> &tokens) {
    std::vector<std::pair<std::string, std::pair<int, CellPoint>>> thingsPos;
    nextPosition(info, posInInfo);
    tokens = splitLine(info[posInInfo]);
    if (tokens[0] == START_TAG) {
        nextPosition(info, posInInfo);
        tokens = splitLine(info[posInInfo]);
        while (tokens[0] != END_TAG) {
            size_t pos1, pos2, pos3;
            thingsPos.push_back({tokens[0], {std::stoi(tokens[1], &pos1),
                                             CellPoint(std::stoi(tokens[2], &pos2), std::stoi(tokens[3], &pos3))}});
            if (pos1 != tokens[1].size() || pos2 != tokens[2].size() || pos3 != tokens[3].size())
                throw std::invalid_argument("Неверное значение информации о позициях и уровне вещей\n");
            nextPosition(info, posInInfo);
            tokens = splitLine(info[posInInfo]);
        }
    } else
        throw std::invalid_argument("Не удалось считать позиции вещей\n");
    saveDataAdapter.setThingsPos(thingsPos);
}

void
SaveDataReader::readHeroThings(SaveDataAdapter &saveDataAdapter, const std::vector<std::string> &info, int &posInInfo,
                               std::vector<std::string> &tokens) {
    std::vector<std::pair<std::string, int>> heroThings;
    nextPosition(info, posInInfo);
    tokens = splitLine(info[posInInfo]);
    if (tokens[0] == START_TAG) {
        nextPosition(info, posInInfo);
        tokens = splitLine(info[posInInfo]);
        while (tokens[0] != END_TAG) {
            size_t pos1;
            heroThings.emplace_back(tokens[0], std::stoi(tokens[1], &pos1));
            if (pos1 != tokens[1].size())
                throw std::invalid_argument("Неверное значение информации о вещах героя\n");
            nextPosition(info, posInInfo);
            tokens = splitLine(info[posInInfo]);
        }
    } else
        throw std::invalid_argument("Не удалось считать вещи игрока\n");
    saveDataAdapter.setHeroThings(heroThings);
}

void SaveDataReader::readHeroAchievement(SaveDataAdapter &saveDataAdapter, const std::vector<std::string> &info,
                                         int &posInInfo, std::vector<std::string> &tokens) {
    std::vector<std::pair<std::string, int>> heroAchievement;
    nextPosition(info, posInInfo);
    tokens = splitLine(info[posInInfo]);
    if (tokens[0] == START_TAG) {
        nextPosition(info, posInInfo);
        tokens = splitLine(info[posInInfo]);
        while (tokens[0] != END_TAG) {
            size_t pos1;
            heroAchievement.emplace_back(tokens[0], std::stoi(tokens[1], &pos1));
            if (pos1 != tokens[1].size())
                throw std::invalid_argument("Неверное значение информации о достижениях герое\n");
            nextPosition(info, posInInfo);
            tokens = splitLine(info[posInInfo]);
        }
    } else
        throw std::invalid_argument("Не удалось считать достижения игрока\n");
    saveDataAdapter.setHeroAchievements(heroAchievement);
}

bool SaveDataReader::readInfo(SaveDataAdapter &saveDataAdapter, const std::vector<std::string> &info,
                              int &posInInfo) {
    std::vector<std::string> tokens;
    while (posInInfo < info.size()) {
        tokens = splitLine(info[posInInfo]);
        if (tokens[0] == "height") {
            size_t pos;
            saveDataAdapter.setHeightField(std::stoi(tokens[1], &pos));
            if (pos != tokens[1].size())
                throw std::invalid_argument("Неверное значение высоты\n");
        } else if (tokens[0] == "width") {
            size_t pos;
            saveDataAdapter.setWidthField(std::stoi(tokens[1], &pos));
            if (pos != tokens[1].size())
                throw std::invalid_argument("Неверное значение ширины\n");
        } else if (tokens[0] == "start") {
            size_t pos1, pos2;
            saveDataAdapter.setStart(CellPoint(std::stoi(tokens[1], &pos1), std::stoi(tokens[2], &pos2)));
            if (pos1 != tokens[1].size() || pos2 != tokens[2].size())
                throw std::invalid_argument("Неверное значение стартовой точки\n");
        } else if (tokens[0] == "finish") {
            size_t pos1, pos2;
            saveDataAdapter.setFinish(CellPoint(std::stoi(tokens[1], &pos1), std::stoi(tokens[2], &pos2)));
            if (pos1 != tokens[1].size() || pos2 != tokens[2].size())
                throw std::invalid_argument("Неверное значение финишной точки\n");
        } else if (tokens[0] == "wallsPos") {
            readWallsPos(saveDataAdapter, info, posInInfo, tokens);
        } else if (tokens[0] == "MainHero") {
            size_t pos1, pos2, pos3;
            saveDataAdapter.setHeroHealth(std::stof(tokens[1], &pos1));
            saveDataAdapter.setHeroPos(CellPoint(std::stoi(tokens[2], &pos2), std::stoi(tokens[3], &pos3)));
            if (pos1 != tokens[1].size() || pos2 != tokens[2].size() || pos3 != tokens[3].size())
                throw std::invalid_argument("Неверное значение информации о герое\n");
        } else if (tokens[0] == "enemiesPosHealth") {
            readEnemiesPosHealth(saveDataAdapter, info, posInInfo, tokens);
        } else if (tokens[0] == "cntSteps") {
            size_t pos;
            saveDataAdapter.setCntSteps(std::stoi(tokens[1], &pos));
            if (pos != tokens[1].size())
                throw std::invalid_argument("Неверное значение количества шагов\n");
        } else if (tokens[0] == "thingsPosLevel") {
            readThingsPosLevel(saveDataAdapter, info, posInInfo, tokens);
        } else if (tokens[0] == "heroLevel") {
            saveDataAdapter.setHeroLevel(std::stoi(tokens[1]));
        } else if (tokens[0] == "heroThings") {
            readHeroThings(saveDataAdapter, info, posInInfo, tokens);
        } else if (tokens[0] == "heroAchievement") {
            readHeroAchievement(saveDataAdapter, info, posInInfo, tokens);
        }
        nextPosition(info, posInInfo);
    }
    return true;
}

void SaveDataReader::readSaveFile(const std::string &pathToFile, SaveDataAdapter &saveDataAdapter) {
    std::fstream in(pathToFile, std::ios_base::in);
    if (!tagValidator(in))
        throw std::invalid_argument("Структура данных в файле не подходит под игровое сохранение\n");
    std::vector<std::string> usefulInfo = extractUsefulInformation(in);
    in.close();
    int pos = 0;
    readInfo(saveDataAdapter, usefulInfo, pos);
    dataValidator(saveDataAdapter);
}

void SaveDataReader::dataValidator(const SaveDataAdapter &dataAdapter) {
    // проверка размеров и кол-ва непроходимых вершин
    if (!Grid::isValidHeight(dataAdapter.getHeightField()) ||
        !Grid::isValidWidth(dataAdapter.getWidthField())) {
        throw std::invalid_argument("Недопустимое значение размеров поля\n");
    }
    if (dataAdapter.getWalls().size() / double(dataAdapter.getHeightField() * dataAdapter.getWidthField()) *
        100 > PERCENT_WALLS)
        throw std::invalid_argument("Недопустимое количество непроходимых клеток\n");
    // проверка валидности стартовой и финишной точки
    if (!Grid::isValidIndexes(dataAdapter.getStart().getX(), dataAdapter.getStart().getY(),
                              dataAdapter.getHeightField(), dataAdapter.getWidthField())
        || !Grid::isValidIndexes(dataAdapter.getFinish().getX(), dataAdapter.getFinish().getY(),
                                 dataAdapter.getHeightField(), dataAdapter.getWidthField())) {
        throw std::invalid_argument("Недопустимое значение стартовой и финишной точки\n");
    }
    // проверка здоровья и позиций персонажей
    for (const auto &enemy: dataAdapter.getEnemiesPos()) {
        if (enemy.second.first <= 0)
            throw std::invalid_argument("Недопустимый показатель здоровья у врагов\n");
        if (!Grid::isValidIndexes(enemy.second.second.getX(), enemy.second.second.getY(), dataAdapter.getHeightField(),
                                  dataAdapter.getWidthField()))
            throw std::invalid_argument("Недопустимая позиция врага\n");
    }
    if (dataAdapter.getHeroHealth() <= 0) {
        throw std::invalid_argument("Недопустимый показатель здоровья у героя\n");
    }
    if (!Grid::isValidIndexes(dataAdapter.getHeroPos().getX(), dataAdapter.getHeroPos().getY(),
                              dataAdapter.getHeightField(), dataAdapter.getWidthField())) {
        throw std::invalid_argument("Недопустимое значение стартовой и финишной точки\n");
    }
    // проверка количества шагов
    if (dataAdapter.getCntSteps() < 0)
        throw std::invalid_argument("Недопустимое значение количества шагов\n");
    // проверка уровня героя
    if (dataAdapter.getHeroLevel() <= 0)
        throw std::invalid_argument("Недопустимое значение уровня героя\n");
    // проверка позиции вещей
    for (const auto &thing: dataAdapter.getThingsPos()) {
        if (thing.second.first < 0 || thing.second.first > dataAdapter.getHeroLevel())
            throw std::invalid_argument("Недопустимое значение уровня вещи\n");
        if (!Grid::isValidIndexes(thing.second.second.getX(), thing.second.second.getY(),
                                  dataAdapter.getHeightField(), dataAdapter.getWidthField()))
            throw std::invalid_argument("Недопустимое значение позиции вещи\n");

    }
    // проверка уровня вещей героя
    for (const auto &thing: dataAdapter.getHeroThings()) {
        if (thing.second < 0 || thing.second > dataAdapter.getHeroLevel())
            throw std::invalid_argument("Недопустимое значение уровня вещи\n");
    }
    // проверка количества побеждённых врагов
    for (const auto &heroAchievement: dataAdapter.getHeroAchievements()) {
        if (heroAchievement.second < 0)
            throw std::invalid_argument("Недопустимое значение количества побеждённых врагов\n");
    }
}
