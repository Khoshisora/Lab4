#include <string>
#include <map>
#include <memory>
#include <vector>
#include <iostream>

class IWarehouse {
public:
    virtual ~IWarehouse() = default;

    // Добавить товар на склад
    virtual void addItem(const std::string& item, int quantity) = 0;

    // Удалить товар со склада
    virtual bool removeItem(const std::string& item, int quantity) = 0;

    // Получить текущий инвентарь
    virtual std::map<std::string, int> getInventory() const = 0;

    // Получить тип склада
    virtual std::string getWarehouseType() const = 0;
};

class LocalWarehouse : public IWarehouse {
private:
    std::map<std::string, int> inventory;

public:
    void addItem(const std::string& item, int quantity) override {
        inventory[item] += quantity;
    }

    bool removeItem(const std::string& item, int quantity) override {
        if (inventory.find(item) == inventory.end() || inventory[item] < quantity) {
            return false;
        }
        inventory[item] -= quantity;
        return true;
    }

    std::map<std::string, int> getInventory() const override {
        return inventory;
    }

    std::string getWarehouseType() const override {
        return "Local Warehouse";
    }
};

class InternationalWarehouse : public IWarehouse {
private:
    std::map<std::string, int> inventory;
    std::string country;

public:
    InternationalWarehouse(const std::string& country) : country(country) {}

    void addItem(const std::string& item, int quantity) override {
        // Для международного склада может быть дополнительная логика
        inventory[item] += quantity;
    }

    bool removeItem(const std::string& item, int quantity) override {
        if (inventory.find(item) == inventory.end() || inventory[item] < quantity) {
            return false;
        }
        inventory[item] -= quantity;
        return true;
    }

    std::map<std::string, int> getInventory() const override {
        return inventory;
    }

    std::string getWarehouseType() const override {
        return "International Warehouse (" + country + ")";
    }
};

class LogisticsManager {
private:
    std::vector<std::shared_ptr<IWarehouse>> warehouses;

public:
    void addWarehouse(std::shared_ptr<IWarehouse> warehouse) {
        warehouses.push_back(warehouse);
    }

    std::vector<std::shared_ptr<IWarehouse>> getWarehouses() {
        return warehouses;
    }

    void processShipment(const std::string& item, int quantity) {
        for (auto& warehouse : warehouses) {
            if (warehouse->removeItem(item, quantity)) {
                std::cout << "Item " << item << " x" << quantity
                    << " shipped from " << warehouse->getWarehouseType()
                    << std::endl;
                return;
            }
        }
        std::cout << "Failed to ship item " << item << " x" << quantity
            << " - not enough stock" << std::endl;
    }

    void printInventory() const {
        for (const auto& warehouse : warehouses) {
            std::cout << "\nInventory for " << warehouse->getWarehouseType() << ":\n";
            auto inventory = warehouse->getInventory();
            for (auto i = inventory.begin(); i != inventory.end(); i++) {
                std::cout << i->first << ": " << i->second << std::endl;
            }
        }
    }
};

int main() {
    // Создаем менеджер логистики
    LogisticsManager manager;

    // Добавляем склады разных типов
    manager.addWarehouse(std::make_shared<LocalWarehouse>());
    manager.addWarehouse(std::make_shared<InternationalWarehouse>("USA"));
    manager.addWarehouse(std::make_shared<InternationalWarehouse>("Germany"));

    // Заполняем склады
    auto warehouses = manager.getWarehouses();
    warehouses[0]->addItem("Laptop", 50);
    warehouses[1]->addItem("Laptop", 100);
    warehouses[2]->addItem("Smartphone", 200);

    // Обрабатываем отгрузки
    manager.processShipment("Laptop", 30);  // Отгрузится с локального склада
    manager.processShipment("Laptop", 80);  // Отгрузится с международного склада (USA)
    manager.processShipment("Smartphone", 50); // Отгрузится с международного склада (Germany)

    // Выводим инвентаризацию
    manager.printInventory();

    return 0;
}