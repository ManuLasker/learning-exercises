#[derive(Debug, PartialEq, Eq)]
pub enum Comparison {
    Equal,
    Sublist,
    Superlist,
    Unequal,
}

pub fn sublist<T: PartialEq>(_first_list: &[T], _second_list: &[T]) -> Comparison {
    match (_first_list.len(), _second_list.len()) {
        (0, 0) => Comparison::Equal,     // both empty so they are equals
        (0, _) => Comparison::Sublist,   // first empty, second whatever so first is sublist
        (_, 0) => Comparison::Superlist, // first whatever, second empty so first is superlist
        (m, n) if m > n => {
            if _first_list.windows(n).any(|v| v == _second_list) {
                Comparison::Superlist
            } else {
                Comparison::Unequal
            }
        }, 
        (m, n) if m < n => {
            if _second_list.windows(m).any(|v| v == _first_list) {
                Comparison::Sublist
            } else {
                Comparison::Unequal
            }
        },
        (_, _) => if _first_list.eq(_second_list) {Comparison::Equal} else {Comparison::Unequal}
    }
}
