#include <iostream>
#include <string>

class IStandardShipping
{
public:
    virtual void ShipStandard(const std::string& package) = 0;
    virtual ~IStandardShipping() = default;
};

class IFreightShipping
{
public:
    virtual void ShipFreight(const std::string& cargo) = 0;
    virtual ~IFreightShipping() = default;
};

class IInternationalShipping
{
public:
    virtual void ShipInternational(const std::string& package, const std::string& country) = 0;
    virtual ~IInternationalShipping() = default;
};

// Реализация: Стандартная доставка
class StandardShippingService : public IStandardShipping
{
public:
    void ShipStandard(const std::string& package) override
	{
        std::cout << "Shipping standard package: " << package << '\n';
    }
};

// Реализация: Грузовая доставка
class FreightShippingService : public IFreightShipping
{
public:
    void ShipFreight(const std::string& cargo) override
	{
        std::cout << "Shipping freight cargo: " << cargo << '\n';
    }
};

// Реализация: Международная доставка
class InternationalShippingService : public IInternationalShipping
{
public:
    void ShipInternational(const std::string& package, const std::string& country) override
	{
        std::cout << "Shipping international package: " << package
            << " to " << country << '\n';
    }
};

int main()
{
    StandardShippingService standard;
    FreightShippingService freight;
    InternationalShippingService international;

    standard.ShipStandard("Book");
    freight.ShipFreight("Machinery");
    international.ShipInternational("Documents", "Germany");

    return 0;
}
