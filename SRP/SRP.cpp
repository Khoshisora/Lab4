#include <iostream>
#include <map>
#include <string>
using namespace std;

// Класс Warehouse - отвечает ТОЛЬКО за управление запасами склада
class Warehouse {
private:
    map<string, int> products; // название товара -> количество

public:
    // Добавить товар на склад
    void addProduct(string name, int quantity) {
        products[name] += quantity;
        cout << "Добавлено " << quantity << " шт. товара: " << name << endl;
    }

    // Удалить товар со склада
    bool removeProduct(string name, int quantity) {
        if (products[name] >= quantity) {
            products[name] -= quantity;
            cout << "Удалено " << quantity << " шт. товара: " << name << endl;
            return true;
        }
        cout << "Недостаточно товара на складе!" << endl;
        return false;
    }

    // Проверить количество товара
    int getQuantity(string name) {
        return products[name];
    }

    // Показать все товары на складе
    void showStock() {
        cout << "\n=== СКЛАД ===" << endl;
        for (auto& item : products) {
            cout << item.first << ": " << item.second << " шт." << endl;
        }
        cout << "=============\n" << endl;
    }
};

// Класс OrderProcessor - отвечает ТОЛЬКО за обработку заказов
class OrderProcessor {
private:
    Warehouse* warehouse;

public:
    OrderProcessor(Warehouse* w) : warehouse(w) {}

    // Обработать заказ
    bool processOrder(string productName, int quantity) {
        cout << "Обработка заказа: " << productName << " - " << quantity << " шт." << endl;

        // Проверяем наличие товара
        if (warehouse->getQuantity(productName) >= quantity) {
            warehouse->removeProduct(productName, quantity);
            cout << "Заказ успешно обработан!" << endl;
            return true;
        }
        else {
            cout << "Заказ отклонен - недостаточно товара!" << endl;
            return false;
        }
    }
};

// Класс DeliveryManager - отвечает ТОЛЬКО за управление доставкой
class DeliveryManager {
public:
    // Организовать доставку
    void arrangeDelivery(string productName, int quantity, string address) {
        cout << "Доставка организована:" << endl;
        cout << "Товар: " << productName << " - " << quantity << " шт." << endl;
        cout << "Адрес: " << address << endl;
        cout << "Статус: Отправлено\n" << endl;
    }

    // Отследить доставку
    void trackDelivery(string orderInfo) {
        cout << "Отслеживание доставки: " << orderInfo << endl;
        cout << "Статус: В пути\n" << endl;
    }
};

// Демонстрация работы
int main() {
    system("chcp 1251>nul");
    // Создаем объекты системы
    Warehouse warehouse;
    OrderProcessor orderProcessor(&warehouse);
    DeliveryManager deliveryManager;

    // Заполняем склад
    warehouse.addProduct("Телефон", 20);
    warehouse.addProduct("Наушники", 50);
    warehouse.addProduct("Чехол", 100);

    warehouse.showStock();

    // Обрабатываем заказ
    bool orderSuccess = orderProcessor.processOrder("Телефон", 3);

    // Если заказ успешен, организуем доставку
    if (orderSuccess) {
        deliveryManager.arrangeDelivery("Телефон", 3, "ул. Пушкина, д. 10");
        deliveryManager.trackDelivery("Телефон - 3 шт.");
    }

    warehouse.showStock();

    return 0;
}