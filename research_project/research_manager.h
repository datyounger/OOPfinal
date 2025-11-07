#ifndef RESEARCH_MANAGER_H
#define RESEARCH_MANAGER_H

#include "linked_list.h"
#include <fstream>
#include <vector>
#include <algorithm>

class ResearchManager {
private:
    LinkedList<ResearchProject*> projects;
    std::string filename;

    bool idExists(const std::string& id) {
        return projects.find(id) != nullptr;
    }

    ResearchProject* createProjectFromString(const std::string& line) {
        std::vector<std::string> tokens;
        size_t start = 0, end = 0;
        
        while ((end = line.find('|', start)) != std::string::npos) {
            tokens.push_back(line.substr(start, end - start));
            start = end + 1;
        }
        tokens.push_back(line.substr(start));

        if (tokens.size() < 6) return nullptr;

        std::string type = tokens[0];
        std::string id = tokens[1];
        std::string title = tokens[2];
        std::string author = tokens[3];
        int year = std::stoi(tokens[4]);

        if (type == "JOURNAL" && tokens.size() == 7) {
            return new JournalPaper(id, title, author, year, 
                                   tokens[5], std::stod(tokens[6]));
        } else if (type == "CONFERENCE" && tokens.size() == 7) {
            return new ConferencePaper(id, title, author, year,
                                      tokens[5], tokens[6]);
        } else if (type == "GRANT" && tokens.size() == 7) {
            return new ResearchGrant(id, title, author, year,
                                   std::stod(tokens[5]), std::stoi(tokens[6]));
        }
        return nullptr;
    }

public:
    ResearchManager(const std::string& file = "research.txt") : filename(file) {
        loadFromFile();
    }

    ~ResearchManager() {
        saveToFile();
        projects.clear();
    }

    void addProject(ResearchProject* project) {
        if (idExists(project->getId())) {
            throw DuplicateIDException(project->getId());
        }
        projects.add(project);
    }

    bool removeProject(const std::string& id) {
        return projects.remove(id);
    }

    ResearchProject* findProject(const std::string& id) {
        return projects.find(id);
    }

    void displayAllProjects() {
        projects.displayAll();
    }

    void displayStatistics() {
        int journalCount = 0, conferenceCount = 0, grantCount = 0;
        double totalBudget = 0, totalDuration = 0;

        for (auto it = projects.begin(); it != projects.end(); ++it) {
            ResearchProject* project = *it;
            switch (project->getType()) {
                case JOURNAL: journalCount++; break;
                case CONFERENCE: conferenceCount++; break;
                case GRANT: 
                    grantCount++; 
                    totalBudget += static_cast<ResearchGrant*>(project)->getBudget();
                    totalDuration += static_cast<ResearchGrant*>(project)->getDuration();
                    break;
            }
        }

        std::cout << "\n=== STATISTICS ===\n";
        std::cout << "Total Projects: " << projects.getSize() << "\n";
        std::cout << "Journal Papers: " << journalCount << "\n";
        std::cout << "Conference Papers: " << conferenceCount << "\n";
        std::cout << "Research Grants: " << grantCount << "\n";
        if (grantCount > 0) {
            std::cout << "Total Budget: " << totalBudget << " million VND\n";
            std::cout << "Average Duration: " << (totalDuration / grantCount) << " months\n";
        }
        std::cout << "==================\n";
    }

    void sortByYear() {
        // Convert to vector for sorting
        std::vector<ResearchProject*> projectList;
        for (auto it = projects.begin(); it != projects.end(); ++it) {
            projectList.push_back(*it);
        }

        std::sort(projectList.begin(), projectList.end(),
            [](ResearchProject* a, ResearchProject* b) {
                return a->getYear() < b->getYear();
            });

        // Rebuild linked list
        projects.clear();
        for (ResearchProject* project : projectList) {
            projects.add(project);
        }
    }

    void sortByAuthor() {
        std::vector<ResearchProject*> projectList;
        for (auto it = projects.begin(); it != projects.end(); ++it) {
            projectList.push_back(*it);
        }

        std::sort(projectList.begin(), projectList.end(),
            [](ResearchProject* a, ResearchProject* b) {
                return a->getAuthor() < b->getAuthor();
            });

        projects.clear();
        for (ResearchProject* project : projectList) {
            projects.add(project);
        }
    }

    void saveToFile() {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file for writing: " << filename << "\n";
            return;
        }

        for (auto it = projects.begin(); it != projects.end(); ++it) {
            file << (*it)->toFileString() << "\n";
        }
        file.close();
    }

    void loadFromFile() {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "No existing data file found. Starting fresh.\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            ResearchProject* project = createProjectFromString(line);
            if (project) {
                projects.add(project);
            }
        }
        file.close();
        std::cout << "Loaded " << projects.getSize() << " projects from file.\n";
    }
};

#endif