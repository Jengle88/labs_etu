#include "LoadScreen.h"

LoadScreen::LoadScreen(const std::vector<std::string> &nameFiles) : nameFiles(nameFiles) {}

void LoadScreen::showUpdatedScreen(int selectedMenuItem, int fileRemovedState) const {
    Printer::printMenuWithChoice(nameFiles, selectedMenuItem);
    if (fileRemovedState != -1) {
        switch (fileRemovedState) {
            case FILE_SUCCESS_REMOVE:
                Printer::printMessage("Файл был успешно удалён\n");
                break;
            case FILE_NOT_FOUND:
                Printer::printMessage("Файл не был найден в директории\n");
                break;
            case FILE_HAVE_PROBLEM:
                Printer::printMessage("Возникли проблемы при удалении файла\n");
                break;
            default:
                Printer::printMessage("Состояние удаления файла не распознано\n");
                break;
        }
    }
}

std::string LoadScreen::getScreenName() const {
    return "loadScreen";
}

void LoadScreen::reloadNameFiles(const std::vector<std::string> &nameFiles) {
    this->nameFiles = nameFiles;
}

int LoadScreen::getMenuSize() const {
    return nameFiles.size();
}


void LoadScreen::showMessage(const std::string &message) const {
    Printer::printMessage(message);
}

void LoadScreen::clearScreen() const {
    system("clear");
}
