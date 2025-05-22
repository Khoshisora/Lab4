#include <iostream>
#include <vector>
#include <string>

// Абстрактный базовый класс
class Transport
{
public:
    virtual double calculateDeliveryTime(double distance) const = 0;
    virtual std::string getType() const = 0;
    virtual ~Transport() = default;
};

// Грузовик
class Truck : public Transport
{
public:
    double calculateDeliveryTime(double distance) const override
	{
        double speed = 60.0; 
        return distance / speed;
    }

    std::string getType() const override
	{
        return "Truck";
    }
};

// Корабль
class Ship : public Transport
{
public:
    double calculateDeliveryTime(double distance) const override
	{
        double speed = 30.0;
        return distance / speed;
    }

    std::string getType() const override
	{
        return "Ship";
    }
};

// Самолёт
class Airplane : public Transport
{
public:
    double calculateDeliveryTime(double distance) const override
	{
        double speed = 800.0;
        return distance / speed;
    }

    std::string getType() const override
	{
        return "Airplane";
    }
};

void printDeliveryInfo(const Transport& transport, double distance)
{
    std::cout << transport.getType()
        << " will deliver over " << distance << " km in "
        << transport.calculateDeliveryTime(distance) << " hours.\n";
}

int main()
{
    std::vector<std::unique_ptr<Transport>> transports;
    transports.push_back(std::make_unique<Truck>());
    transports.push_back(std::make_unique<Ship>());
    transports.push_back(std::make_unique<Airplane>());

    double distance = 1200.0;

    for (const auto& t : transports) 
    {
        printDeliveryInfo(*t, distance);
    }

    return 0;
}
