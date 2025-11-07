#ifndef RESEARCH_PROJECT_H
#define RESEARCH_PROJECT_H

#include <iostream>
#include <string>
#include "exceptions.h"

enum ProjectType { JOURNAL, CONFERENCE, GRANT };

class ResearchProject {
protected:
    std::string id;
    std::string title;
    std::string author;
    int year;

public:
    ResearchProject(const std::string& id, const std::string& title, 
                   const std::string& author, int year) 
        : id(id), title(title), author(author), year(year) {
        if (year < 2000 || year > 2025) {
            throw InvalidYearException(year);
        }
    }

    virtual ~ResearchProject() {}

    // Getter methods
    std::string getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    int getYear() const { return year; }

    // Pure virtual function
    virtual void display() const = 0;
    virtual ProjectType getType() const = 0;
    virtual std::string getTypeString() const = 0;

    // Virtual function for file output
    virtual std::string toFileString() const = 0;
};

class JournalPaper : public ResearchProject {
private:
    std::string journalName;
    double impactFactor;

public:
    JournalPaper(const std::string& id, const std::string& title, 
                const std::string& author, int year,
                const std::string& journal, double impact)
        : ResearchProject(id, title, author, year), 
          journalName(journal), impactFactor(impact) {
        if (impactFactor < 0) {
            throw InvalidValueException("impactFactor");
        }
    }

    void display() const override {
        std::cout << "Journal Paper - ID: " << id 
                  << "\nTitle: " << title
                  << "\nAuthor: " << author
                  << "\nYear: " << year
                  << "\nJournal: " << journalName
                  << "\nImpact Factor: " << impactFactor
                  << "\n----------------------------------------\n";
    }

    ProjectType getType() const override { return JOURNAL; }
    
    std::string getTypeString() const override { return "Journal Paper"; }

    std::string toFileString() const override {
        return "JOURNAL|" + id + "|" + title + "|" + author + "|" + 
               std::to_string(year) + "|" + journalName + "|" + 
               std::to_string(impactFactor);
    }
};

class ConferencePaper : public ResearchProject {
private:
    std::string conferenceName;
    std::string location;

public:
    ConferencePaper(const std::string& id, const std::string& title,
                   const std::string& author, int year,
                   const std::string& conference, const std::string& loc)
        : ResearchProject(id, title, author, year),
          conferenceName(conference), location(loc) {}

    void display() const override {
        std::cout << "Conference Paper - ID: " << id 
                  << "\nTitle: " << title
                  << "\nAuthor: " << author
                  << "\nYear: " << year
                  << "\nConference: " << conferenceName
                  << "\nLocation: " << location
                  << "\n----------------------------------------\n";
    }

    ProjectType getType() const override { return CONFERENCE; }
    
    std::string getTypeString() const override { return "Conference Paper"; }

    std::string toFileString() const override {
        return "CONFERENCE|" + id + "|" + title + "|" + author + "|" + 
               std::to_string(year) + "|" + conferenceName + "|" + location;
    }
};

class ResearchGrant : public ResearchProject {
private:
    double budget; // in million VND
    int duration;  // in months

public:
    ResearchGrant(const std::string& id, const std::string& title,
                 const std::string& author, int year,
                 double budget, int duration)
        : ResearchProject(id, title, author, year),
          budget(budget), duration(duration) {
        if (budget < 0) {
            throw InvalidValueException("budget");
        }
    }

    void display() const override {
        std::cout << "Research Grant - ID: " << id 
                  << "\nTitle: " << title
                  << "\nAuthor: " << author
                  << "\nYear: " << year
                  << "\nBudget: " << budget << " million VND"
                  << "\nDuration: " << duration << " months"
                  << "\n----------------------------------------\n";
    }

    ProjectType getType() const override { return GRANT; }
    
    std::string getTypeString() const override { return "Research Grant"; }

    std::string toFileString() const override {
        return "GRANT|" + id + "|" + title + "|" + author + "|" + 
               std::to_string(year) + "|" + std::to_string(budget) + "|" + 
               std::to_string(duration);
    }

    double getBudget() const { return budget; }
    int getDuration() const { return duration; }
};

#endif