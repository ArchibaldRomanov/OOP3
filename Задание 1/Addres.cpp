#include <iostream>
#include <fstream>
#include <string>

class Address {
private:
    std::string city;
    std::string street;
    int houseNumber;
    int apartmentNumber;
    
public:
    // Конструктор с параметрами
    Address(const std::string& city, const std::string& street, 
            int houseNumber, int apartmentNumber) {
        this->city = city;
        this->street = street;
        this->houseNumber = houseNumber;
        this->apartmentNumber = apartmentNumber;
    }
    
    // Метод для получения строки для вывода
    std::string getOutputAddress() const {
        return city + ", " + street + ", " + 
               std::to_string(houseNumber) + ", " + 
               std::to_string(apartmentNumber);
    }
};

int main() {
    // Открываем файл для чтения
    std::ifstream inputFile("in.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл in.txt" << std::endl;
        return 1;
    }
    
    // Читаем количество адресов
    int n;
    inputFile >> n;
    inputFile.ignore(); // Игнорируем символ новой строки после числа
    
    // Создаём динамический массив указателей на Address
    Address** addresses = new Address*[n];
    
    // Читаем адреса из файла
    for (int i = 0; i < n; i++) {
        std::string city, street;
        int houseNumber, apartmentNumber;
        
        std::getline(inputFile, city);
        std::getline(inputFile, street);
        inputFile >> houseNumber;
        inputFile >> apartmentNumber;
        inputFile.ignore(); // Игнорируем символ новой строки
        
        // Создаём объект Address и сохраняем указатель на него в массиве
        addresses[i] = new Address(city, street, houseNumber, apartmentNumber);
    }
    
    // Закрываем входной файл
    inputFile.close();
    
    // Открываем файл для записи
    std::ofstream outputFile("out.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Не удалось открыть файл out.txt" << std::endl;
        
        // Освобождаем память перед выходом
        for (int i = 0; i < n; i++) {
            delete addresses[i];
        }
        delete[] addresses;
        
        return 1;
    }
    
    // Записываем количество адресов
    outputFile << n << std::endl;
    
    // Записываем адреса в обратном порядке
    for (int i = n - 1; i >= 0; i--) {
        outputFile << addresses[i]->getOutputAddress() << std::endl;
    }
    
    // Закрываем выходной файл
    outputFile.close();
    
    // Освобождаем память
    for (int i = 0; i < n; i++) {
        delete addresses[i];
    }
    delete[] addresses;
    
    std::cout << "Адреса успешно обработаны и сохранены в файл out.txt" << std::endl;
    
    return 0;
}