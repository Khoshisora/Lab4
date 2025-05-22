#include <iostream>
#include <vector>
using namespace std;

// Базовый класс для расчета стоимости доставки
class DeliveryCostCalculator {
public:
    virtual double calculateCost(double weight, double distance) = 0;
    virtual string getDeliveryType() = 0;
    virtual ~DeliveryCostCalculator() {}
};

// Стандартная доставка - самая дешевая, но медленная
class StandardDelivery : public DeliveryCostCalculator {
public:
    double calculateCost(double weight, double distance) {
        return weight * 10 + distance * 2; // 10 руб за кг + 2 руб за км
    }

    string getDeliveryType() {
        return "Стандартная доставка (5-7 дней)";
    }
};

// Экспресс доставка - быстрая, но дороже
class ExpressDelivery : public DeliveryCostCalculator {
public:
    double calculateCost(double weight, double distance) {
        return weight * 20 + distance * 5; // 20 руб за кг + 5 руб за км
    }

    string getDeliveryType() {
        return "Экспресс доставка (1-2 дня)";
    }
};

// Международная доставка - самая дорогая
class InternationalDelivery : public DeliveryCostCalculator {
public:
    double calculateCost(double weight, double distance) {
        return weight * 50 + distance * 10 + 500; // базовая плата 500 руб
    }

    string getDeliveryType() {
        return "Международная доставка (10-14 дней)";
    }
};

// НОВЫЙ тип доставки - добавляем БЕЗ изменения старого кода!
class PremiumDelivery : public DeliveryCostCalculator {
public:
    double calculateCost(double weight, double distance) {
        return weight * 30 + distance * 8 + 200; // премиум услуга
    }

    string getDeliveryType() {
        return "Премиум доставка (в тот же день)";
    }
};

// Класс для работы с доставкой - НЕ МЕНЯЕТСЯ при добавлении новых типов!
class DeliveryService {
private:
    vector<DeliveryCostCalculator*> deliveryOptions;

public:
    // Добавить новый способ доставки
    void addDeliveryOption(DeliveryCostCalculator* calculator) {
        deliveryOptions.push_back(calculator);
    }

    // Показать все варианты доставки с ценами
    void showDeliveryOptions(double weight, double distance) {
        cout << "\n=== ВАРИАНТЫ ДОСТАВКИ ===" << endl;
        cout << "Вес посылки: " << weight << " кг" << endl;
        cout << "Расстояние: " << distance << " км\n" << endl;

        for (int i = 0; i < deliveryOptions.size(); i++) {
            double cost = deliveryOptions[i]->calculateCost(weight, distance);
            cout << i + 1 << ". " << deliveryOptions[i]->getDeliveryType()
                << " - " << cost << " руб." << endl;
        }
        cout << "========================\n" << endl;
    }

    // Выбрать способ доставки
    void selectDelivery(int choice, double weight, double distance) {
        if (choice >= 1 && choice <= deliveryOptions.size()) {
            double cost = deliveryOptions[choice - 1]->calculateCost(weight, distance);
            cout << "Выбрано: " << deliveryOptions[choice - 1]->getDeliveryType() << endl;
            cout << "Стоимость: " << cost << " руб." << endl;
        }
        else {
            cout << "Неверный выбор!" << endl;
        }
    }
};

// Демонстрация работы
int main() {
    system("chcp 1251>nul");
    DeliveryService service;

    // Создаем объекты разных типов доставки
    StandardDelivery standard;
    ExpressDelivery express;
    InternationalDelivery international;

    // Добавляем их в сервис
    service.addDeliveryOption(&standard);
    service.addDeliveryOption(&express);
    service.addDeliveryOption(&international);

    // Параметры посылки
    double weight = 2.5; // кг
    double distance = 100; // км

    service.showDeliveryOptions(weight, distance);

    // Выбираем экспресс доставку
    service.selectDelivery(2, weight, distance);

    cout << "\n--- ДОБАВЛЯЕМ НОВЫЙ ТИП ДОСТАВКИ ---" << endl;

    // Создаем НОВЫЙ тип доставки БЕЗ изменения старого кода!
    PremiumDelivery premium;
    service.addDeliveryOption(&premium);

    service.showDeliveryOptions(weight, distance);

    // Выбираем новый премиум способ
    service.selectDelivery(4, weight, distance);

    return 0;
}