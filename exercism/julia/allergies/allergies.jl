const map_allergens_score = [
    ("eggs", 1),
    ("peanuts", 2),
    ("shellfish", 4),
    ("strawberries", 8),
    ("tomatoes", 16),
    ("chocolate", 32),
    ("pollen", 64),
    ("cats", 128)
]

function allergic_to(score, allergen)
    allergen ∈ allergy_list(score)
end

function allergy_list(score)
    allergies = [key for (key, val) in map_allergens_score if val & score != 0]
    return Set(allergies)
end
