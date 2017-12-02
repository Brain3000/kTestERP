#include "stdafx.h"
#include "UnitImpl.h"

#include <unordered_map>

const std::string& kind_to_str(UnitKind kind) {
    using UnitKindMap = std::unordered_map<UnitKind, std::string>;
    static const UnitKindMap map = {
        {UnitKind::eCompany, "Компании"},
        {UnitKind::eDepartament, "Подразделению"},
        {UnitKind::eEmployer, "Сотруднику"},
    };
    return map.at(kind);
}
