#pragma once

#include <string>
#include <set>
#include <memory>

class MainUtil;

class MenuBase {
protected:
    enum class OptionAction {
        eGoBack,
        eRunItem,
    };

    struct Option {
        Option(const std::string& cap, uint8_t keyCode, OptionAction action);
        void show();

        const std::string m_caption;
        const uint8_t m_keyCode = ' ';
        const OptionAction m_action;

    private:
        std::string printableKey() const;

    };

    struct OptionLess : std::binary_function<Option, Option, bool>  {
        bool operator()(const Option& op1, const Option& op2) const {
            return op1.m_keyCode < op2.m_keyCode;
        }
    };
    using Options = std::set<Option, OptionLess>;
public:
    virtual ~MenuBase(){}
    void run() const;
    const MainUtil* mainUtil() const;

protected:
    MenuBase(MainUtil* mainUtil, const std::string& caption);
    //void addOption(const MenuOption& option);
    virtual void runOption(const Option& opt) const = 0;

protected:
    MainUtil* m_mainUtil;
    const std::string m_caption;
    Options m_options;
};

