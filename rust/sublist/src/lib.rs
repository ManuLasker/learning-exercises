#[derive(Debug, PartialEq, Eq)]
pub enum Comparison {
    Equal,
    Sublist,
    Superlist,
    Unequal,
}

pub fn is_super_list<T: PartialEq>(_first_list: &[T], _second_list: &[T]) -> bool {
    if _second_list.is_empty() {
        return true;
    } else {
        for i in 0.._first_list.len() {
            if (_first_list[i] == _second_list[0]) && (i + _second_list.len() <= _first_list.len()) {
                if (&_first_list[i..i+_second_list.len()]).eq(_second_list) {
                    return true;
                }
            }
        }
    }
    return false;
}

pub fn is_sublist<T: PartialEq>(_first_list: &[T], _second_list: &[T]) -> bool {
    return is_super_list(_second_list, _first_list);
}

pub fn sublist<T: PartialEq>(_first_list: &[T], _second_list: &[T]) -> Comparison {
    let result:Comparison;
    if _first_list.eq(_second_list) {
        result = Comparison::Equal;
    } else {
        if _first_list.len() == _second_list.len() {
            result = Comparison::Unequal;
        } else if _first_list.len() > _second_list.len() {
            match is_super_list(_first_list, _second_list) {
                true => result = Comparison::Superlist,
                false => result = Comparison::Unequal
            }
        } else {
            match is_sublist(_first_list, _second_list) {
                true => result = Comparison::Sublist,
                false => result = Comparison::Unequal
            }
        }
    }
    return result;
}
