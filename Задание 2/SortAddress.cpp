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
    Address() {}

    Address(const std::string& city, const std::string& street,
        int houseNumber, int apartmentNumber) {
        this->city = city;
        this->street = street;
        this->houseNumber = houseNumber;
        this->apartmentNumber = apartmentNumber;
    }

    std::string getOutputAddress() const {
        return city + ", " + street + ", " +
            std::to_string(houseNumber) + ", " +
            std::to_string(apartmentNumber);
    }

    std::string getCity() const {
        return city;
    }
};

// пузырьковая сортировка
void sort(Address* addresses, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (addresses[j].getCity() > addresses[j + 1].getCity()) {
                Address temp = addresses[j];
                addresses[j] = addresses[j + 1];
                addresses[j + 1] = temp;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    std::ifstream inputFile("in.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл in.txt!" << std::endl;
        return 1;
    }
    int n;
    inputFile >> n;
    inputFile.ignore(); 

    Address* addresses = new Address[n];

    for (int i = 0; i < n; i++) {
        std::string city, street;
        int houseNumber, apartmentNumber;

        std::getline(inputFile, city);
        std::getline(inputFile, street);
        inputFile >> houseNumber;
        inputFile >> apartmentNumber;
        inputFile.ignore();

        addresses[i] = Address(city, street, houseNumber, apartmentNumber);
    }
    inputFile.close();
    sort(addresses, n);

    std::ofstream outputFile("out.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Не удалось открыть файл out.txt!" << std::endl;
        delete[] addresses;
        return 1;
    }

    // Записываем количество адресов
    outputFile << n << std::endl;
    for (int i = 0; i < n; i++) {
        outputFile << addresses[i].getOutputAddress() << std::endl;
    }

    outputFile.close();
    delete[] addresses;

    std::cout << "Адреса успешно отсортированы и сохранены в файл out.txt" << std::endl;

    return 0;
}