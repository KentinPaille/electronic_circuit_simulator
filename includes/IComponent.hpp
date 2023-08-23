/*
** EPITECH PROJECT, 2022
** bootstrap
** File description:
** ICompenent.hpp
*/

#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>

enum Tristate {
    UNDEFINED = -1,
    TRUE = 1,
    FALSE = 0,
};

class Pin;
class IComponent {
    public:
        virtual ~IComponent() = default;

        virtual void simulate(std::size_t tick) = 0;
        virtual Tristate compute(std::size_t test) = 0;
        virtual void setLink(std::size_t test, IComponent &other, std::size_t otherPin) = 0;

        //* Getters
        virtual std::vector<Pin*> getPins() const = 0;
        virtual Tristate getThirdPin(int nb) const = 0;
        virtual std::string getName() const = 0;
        virtual std::string getType() const = 0;

        //* Setters
        virtual void setState(Tristate nb) = 0;
};

class Pin {
    public:
        Pin(std::string name, Tristate state) : _name(name) , _state(state){};
        ~Pin() = default;
        Tristate compute(std::size_t pin);

        //* Getters
        Tristate getState() const;
        IComponent *getGate() const;
        std::string getName() const;
        std::size_t getPin() const;


        //* Setters
        void setState(Tristate state);
        void setGate(IComponent *gate);
        void setPin(std::size_t pin);

    private:
        Tristate _state = UNDEFINED;
        IComponent *_gate = nullptr;
        size_t _pin = 0;
        std::string _name;
};


class AComponent: public IComponent {
        public:
            AComponent() = default;
            AComponent(std::string name, std::string type) : _name(name), _type(type) {};
            virtual ~AComponent() = default;

            virtual void simulate(std::size_t tick) {
                (void)tick;
            };
            virtual Tristate compute(std::size_t pin) = 0;
            virtual void setLink(std::size_t pin, IComponent &other, std::size_t otherPin) = 0;

            //* Getters
            std::vector<Pin*> getPins() const {
                return _pins;
            }
            Tristate getThirdPin(int nb) const {
                return _pins[nb]->getState();
            }
            std::string getName() const {
                return _name;
            }
            std::string getType() const {
                return _type;
            }
            //* Setters
            virtual void setState(Tristate state) {
                _pins.at(1)->setState(state);
            }
            void setName(std::string name) {
                _name = name;
            }

        protected:
            std::vector<Pin*> _pins;
            std::string _name;
            std::string _type;
        private:
            friend class Pin;
};

class AndComponent : public AComponent {
    public:
        AndComponent(std::string name);
        ~AndComponent() = default;
        Tristate compute(std::size_t pin);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
    protected:
        std::string _name;
};
class OrComponent : public AComponent {
    public:
        OrComponent(std::string name);
        ~OrComponent() = default;
        Tristate compute(std::size_t pin) ;
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
};
class XorComponent : public AComponent {
    public:
        XorComponent(std::string name);
        ~XorComponent() = default;
        Tristate compute(std::size_t pin);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
};
class NotComponent : public AComponent {
    public:
        NotComponent(std::string name);
        ~NotComponent() = default;
        Tristate compute(std::size_t pin);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
};
class FalseComponent : public AComponent {
    public:
        FalseComponent(std::string name);
        ~FalseComponent() = default;
        Tristate compute(std::size_t pin);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
};
class TrueComponent : public AComponent {
    public:
        TrueComponent(std::string name);
        ~TrueComponent() = default;
        Tristate compute(std::size_t pin);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
};
class Gate4081 : public AComponent {
    public:
        Gate4081(std::string name);
        ~Gate4081() = default;
        Tristate compute(std::size_t pin);
        Tristate ANDLogic(std::size_t output, std::size_t input1, std::size_t input2);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
};
class Gate4071 : public AComponent {
    public:
        Gate4071(std::string name);
        ~Gate4071() = default;
        Tristate compute(std::size_t pin);
        Tristate ORLogic(std::size_t output, std::size_t input1, std::size_t input2);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
};
class InputComponent : public AComponent {
    public:
        InputComponent(std::string name);
        ~InputComponent();
        Tristate compute(std::size_t pin);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
    protected:
        std::string _name;
};
class OutputComponent : public AComponent {
    public:
        OutputComponent(std::string name);
        ~OutputComponent();
        Tristate compute(std::size_t pin);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
    protected:
        std::string _name;
};
class ClockComponent : public AComponent {
    public:
        ClockComponent(std::string name);
        ~ClockComponent() = default;
        Tristate compute(std::size_t pin);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
};
class Gate4069 : public AComponent {
    public:
        Gate4069(std::string name);
        ~Gate4069() = default;
        Tristate compute(std::size_t pin);
        Tristate NOTLogic(std::size_t output, std::size_t input);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
};
class Gate4030: public AComponent {
    public:
        Gate4030(std::string name);
        ~Gate4030() = default;
        Tristate compute(std::size_t pin);
        Tristate XORLogic(std::size_t output, std::size_t input1, std::size_t input2);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
};
class Gate4001: public AComponent {
    public:
        Gate4001(std::string name);
        ~Gate4001() = default;
        Tristate compute(std::size_t pin);
        Tristate NORLogic(std::size_t output, std::size_t input1, std::size_t input2);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
};
class Gate4011: public AComponent {
    public:
        Gate4011(std::string name);
        ~Gate4011() = default;
        Tristate compute(std::size_t pin);
        Tristate NANDLogic(std::size_t output, std::size_t input1, std::size_t input2);
        void setLink(std::size_t pin, IComponent &other, std::size_t otherPin);
};

