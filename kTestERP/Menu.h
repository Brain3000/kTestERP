#pragma once

#include <string>
#include <list>
#include <memory>

class Page;

class MenuOptionBase {
protected:
    MenuOptionBase(Page* page, const std::string& cap, uint8_t keyCode);

public:
    virtual ~MenuOptionBase();
    virtual void show();

private:
    std::string printableKey() const;

private:
    Page* m_page;
    const std::string m_caption;
    const uint8_t m_keyCode = ' ';
};

class MainUtil;

class MenuOption : public MenuOptionBase {
    using FuncType = void(MainUtil::*)();
public:
    explicit MenuOption(const FuncType func,
                        Page* page,
                        const std::string& cap,
                        uint8_t keyCode);
    ~MenuOption();
private:
    const FuncType m_func;
};

using OptionPtr = std::shared_ptr<MenuOptionBase>;
using Options = std::list<OptionPtr>;

class Page
{
public:
    Page(MainUtil* mainUtil, const std::string& caption);
    ~Page();
    void addOption(OptionPtr option);
    const MainUtil* mainUtil() const;
    void run() const;

private:
    MainUtil* m_mainUtil;
    const std::string m_caption;
    Options m_options;
};

