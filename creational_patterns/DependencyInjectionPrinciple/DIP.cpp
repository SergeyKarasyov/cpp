// DependencyInversionPrinciple

// 1.high level modules should not depend on low level modules. Both should depend on abstractions
// e.g. reporting component should depend on a consolelogger, but can depend on an Ilogger.
// Instead of concrete implementations need to use interfaces.

// 2. Abstractions should not depend upon details. Details should depend upon abstractions.
// Dependency on interface is better than dependency on concrete type.

// Inversion of Control(IoC) - creation abstractions and getting them to replace dependencies

// Dependency Injection - use of sw framewors to ensure that a component's dependencies are satisfied

//wget https://raw.githubusercontent.com/boost-experimental/di/cpp14/include/boost/di.hpp

#include "di.hpp"
#include <ostream>
#include <memory>
#include <iostream>

struct ILogger
{
    virtual ~ILogger(){};
    virtual void Log(const std::string &s) = 0;
};
struct ConsoleLogger : ILogger
{
    void Log(const std::string &s) { std::cout << "Logging : " << s << std::endl; };
};

struct Engine
{
    float volume = 5;
    int horse_power = 600;
    friend std::ostream &operator<<(std::ostream &os, const Engine &obj)
    {
        return os << " volume: " << obj.volume << "  horse power: " << obj.horse_power << std::endl;
    }
};

//car depends on engine
struct Car
{
    std::shared_ptr<ILogger> logger;
    std::shared_ptr<Engine> engine;
    explicit Car(const std::shared_ptr<Engine> &engine, const std::shared_ptr<ILogger> &logger) : engine{engine}, logger{logger}
    {
        logger->Log("created a car");
    };

    friend std::ostream &operator<<(std::ostream &os, const Car &obj)
    {
        return os << "car engine: " << *obj.engine << std::endl;
    };
};

int main()
{
    //let's use dependency injection
    using namespace boost;
    //initializes all the dependencies we have
    auto injector = di::make_injector(
        di::bind<ILogger>().to<ConsoleLogger>());
    //looks in constructor, and initializes an Engine for us automatically
    auto car = injector.create<std::shared_ptr<Car>>();
    std::cout << *car << std::endl;
}