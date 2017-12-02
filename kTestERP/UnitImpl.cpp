#include "stdafx.h"
#include "UnitImpl.h"

#include <unordered_map>

const std::string& kind_to_str(UnitKind kind) {
    using UnitKindMap = std::unordered_map<UnitKind, std::string>;
    static const UnitKindMap map = {
        {UnitKind::eCompany, "Компания"},
        {UnitKind::eDepartament, "Подразделение"},
        {UnitKind::eEmployer, "Сотрудник"},
    };
    return map.at(kind);
}
