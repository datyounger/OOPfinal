#include <iostream>
#include <limits>
#include "research_manager.h"

void displayMenu() {
    std::cout << "\n=========== RESEARCH PROJECT MANAGEMENT ===========\n";
    std::cout << "1. Them cong trinh moi\n";
    std::cout << "2. Xoa cong trinh theo ID\n";
    std::cout << "3. Tim kiem cong trinh theo ID\n";
    std::cout << "4. Hien thi toan bo cong trinh\n";
    std::cout << "5. Thong ke\n";
    std::cout << "6. Sap xep theo nam\n";
    std::cout << "7. Sap xep theo tac gia\n";
    std::cout << "8. Thoat\n";
    std::cout << "===================================================\n";
    std::cout << "Chon chuc nang (1-8): ";
}

ResearchProject* createProjectFromInput() {
    std::string id, title, author;
    int year, type;
    
    std::cout << "Nhap ma cong trinh: ";
    std::cin.ignore();
    std::getline(std::cin, id);
    
    std::cout << "Nhap tieu de: ";
    std::getline(std::cin, title);
    
    std::cout << "Nhap tac gia chinh: ";
    std::getline(std::cin, author);
    
    std::cout << "Nhap nam (2000-2025): ";
    std::cin >> year;
    
    std::cout << "Chon loai cong trinh:\n";
    std::cout << "1. Journal Paper\n";
    std::cout << "2. Conference Paper\n";
    std::cout << "3. Research Grant\n";
    std::cout << "Chon (1-3): ";
    std::cin >> type;
    
    try {
        if (type == 1) {
            std::string journal;
            double impact;
            std::cout << "Nhap ten tap chi: ";
            std::cin.ignore();
            std::getline(std::cin, journal);
            std::cout << "Nhap chi so anh huong: ";
            std::cin >> impact;
            return new JournalPaper(id, title, author, year, journal, impact);
        } else if (type == 2) {
            std::string conference, location;
            std::cout << "Nhap ten hoi nghi: ";
            std::cin.ignore();
            std::getline(std::cin, conference);
            std::cout << "Nhap dia diem: ";
            std::getline(std::cin, location);
            return new ConferencePaper(id, title, author, year, conference, location);
        } else if (type == 3) {
            double budget;
            int duration;
            std::cout << "Nhap kinh phi (trieu VND): ";
            std::cin >> budget;
            std::cout << "Nhap thoi gian (thang): ";
            std::cin >> duration;
            return new ResearchGrant(id, title, author, year, budget, duration);
        }
    } catch (const std::exception& e) {
        std::cerr << "Loi khi tao cong trinh: " << e.what() << "\n";
        return nullptr;
    }
    
    return nullptr;
}

int main() {
    ResearchManager manager;
    int choice;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                ResearchProject* project = createProjectFromInput();
                if (project) {
                    try {
                        manager.addProject(project);
                        std::cout << "Them cong trinh thanh cong!\n";
                    } catch (const std::exception& e) {
                        std::cerr << "Loi: " << e.what() << "\n";
                        delete project;
                    }
                }
                break;
            }
            case 2: {
                std::string id;
                std::cout << "Nhap ID can xoa: ";
                std::cin.ignore();
                std::getline(std::cin, id);
                if (manager.removeProject(id)) {
                    std::cout << "Xoa cong trinh thanh cong!\n";
                } else {
                    std::cout << "Khong tim thay cong trinh voi ID: " << id << "\n";
                }
                break;
            }
            case 3: {
                std::string id;
                std::cout << "Nhap ID can tim: ";
                std::cin.ignore();
                std::getline(std::cin, id);
                ResearchProject* project = manager.findProject(id);
                if (project) {
                    std::cout << "Tim thay cong trinh:\n";
                    project->display();
                } else {
                    std::cout << "Khong tim thay cong trinh voi ID: " << id << "\n";
                }
                break;
            }
            case 4:
                manager.displayAllProjects();
                break;
            case 5:
                manager.displayStatistics();
                break;
            case 6:
                manager.sortByYear();
                std::cout << "Da sap xep theo nam!\n";
                break;
            case 7:
                manager.sortByAuthor();
                std::cout << "Da sap xep theo tac gia!\n";
                break;
            case 8:
                std::cout << "Cam on da su dung chuong trinh!\n";
                break;
            default:
                std::cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 8);
    
    return 0;
}