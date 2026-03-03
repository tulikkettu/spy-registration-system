#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <algorithm>

using namespace std;

class SpyProgram {
private:
    int maxStarts = 5;
    int timeLimit = 10;
    string historyPath = "spy_usage_history.dat";
    string agentsPath = "spy_agents.dat";
    
    // Надежная функция для загрузки счетчика
    int loadCounter() {
        ifstream file(historyPath);
        if (file.is_open()) {
            int counter;
            file >> counter;
            file.close();
            return counter;
        }
        return 0;
    }
    
    // Надежная функция для сохранения счетчика
    void saveCounter(int counter) {
        system("attrib -h -s spy_usage_history.dat >nul 2>&1");
        
        ofstream file(historyPath, ios::trunc);
        if (file.is_open()) {
            file << counter;
            file.close();
            system("attrib +h +s spy_usage_history.dat >nul 2>&1");
        }
    }
    
    // Проверка на дублирование ФИО
    bool isDuplicate(const string& fullName) {
        system("attrib -h -s spy_agents.dat >nul 2>&1");
        
        ifstream file(agentsPath);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                // Ищем полное совпадение ФИО в строке
                if (line.find(fullName) != string::npos) {
                    file.close();
                    system("attrib +h +s spy_agents.dat >nul 2>&1");
                    return true;
                }
            }
            file.close();
        }
        system("attrib +h +s spy_agents.dat >nul 2>&1");
        return false;
    }
    
    // Добавление нового агента
    void addAgent(const string& fullName) {
        system("attrib -h -s spy_agents.dat >nul 2>&1");
        
        ofstream file(agentsPath, ios::app);
        if (file.is_open()) {
            time_t now = time(0);
            char timeStr[26];
            ctime_s(timeStr, sizeof(timeStr), &now);
            string cleanTimeStr = timeStr;
            cleanTimeStr.erase(cleanTimeStr.find_last_not_of("\n\r") + 1);
            file << fullName << " | Registered: " << cleanTimeStr << endl;
            file.close();
        }
        system("attrib +h +s spy_agents.dat >nul 2>&1");
    }
    
    string getInputWithTimeout(int seconds) {
        string input;
        time_t startTime = time(0);
        
        cout << "Enter your full name (you have " << seconds << " seconds): ";
        
        while (true) {
            // Проверяем истекло ли время
            if (time(0) - startTime >= seconds) {
                return ""; // Таймаут
            }
            
            // Проверяем ввод
            if (_kbhit()) {
                char c = _getch();
                
                if (c == '\r') {
                    cout << endl;
                    return input;
                }
                else if (c == '\b') {
                    if (!input.empty()) {
                        input.pop_back();
                        cout << "\b \b";
                    }
                }
                else if (c >= 32 && c <= 126) {
                    input += c;
                    cout << c;
                }
            }
            
            Sleep(50);
        }
    }
    
public:
    void run() {
        system("cls");
        cout << "==============================================" << endl;
        cout << "    SECRET AGENT REGISTRATION SYSTEM" << endl;
        cout << "    [FINAL VERSION]" << endl;
        cout << "==============================================" << endl;
        cout << endl;
        
        // 1. Загружаем счетчик
        int counter = loadCounter();
        
        // 2. Увеличиваем счетчик
        counter++;
        
        // 3. Сохраняем счетчик
        saveCounter(counter);
        
        // 4. Показываем статус
        cout << "[INFO] Launch count: " << counter << "/" << maxStarts << endl;
        
        // 5. Проверяем лимит
        if (counter > maxStarts) {
            cout << "[ERROR] LAUNCH LIMIT REACHED! (" << counter << "/" << maxStarts << ")" << endl;
            cout << endl;
            cout << "Please purchase full version or uninstall." << endl;
            cout << "Press Enter to exit...";
            cin.ignore();
            cin.get();
            return;
        }
        
        cout << endl;
        
        // 6. Получаем ввод с таймером (без отображения отсчета)
        string name = getInputWithTimeout(timeLimit);
        
        if (name.empty()) {
            cout << endl << "[ERROR] TIME LIMIT EXPIRED! Program will now exit." << endl;
            Sleep(2000);
            exit(0); // Автоматический выход без ожидания Enter
        }
        
        // Проверяем дубликат
        if (isDuplicate(name)) {
            cout << "[WARNING] Agent " << name << " is already registered!" << endl;
            cout << "[INFO] Duplicate entry detected - data not saved" << endl;
        } else {
            // Сохраняем нового агента
            addAgent(name);
            cout << "[SUCCESS] Agent " << name << " successfully registered!" << endl;
        }
        
        cout << "[INFO] Launch count: " << counter << "/" << maxStarts << endl;
        
        cout << endl;
        cout << "==============================================" << endl;
        cout << "SYSTEM STATUS:" << endl;
        cout << "- Total launches: " << counter << "/" << maxStarts << " (START-LIMITED)" << endl;
        cout << "- Time limit: " << timeLimit << " seconds (TIME-LIMITED)" << endl;
        cout << "- Remaining launches: " << (maxStarts - counter) << endl;
        cout << "==============================================" << endl;
        cout << endl;
        
        cout << "Press Enter to exit...";
        cin.ignore();
        cin.get();
    }
};

int main() {
    system("chcp 65001 > nul");
    SpyProgram program;
    program.run();
    return 0;
}