get_dict(str, val) = Dict((only(key), val) for key in map(strip, split(str, ","))) 

function calculate_score(score_mapping, str)
    score = 0
    for char in str
        score += get(score_mapping, char, 0)
    end
    return score
end

function score(str)
    # construct score mapping
    score_mapping = merge(
        get_dict("A, E, I, O, U, L, N, R, S, T", 1),
        get_dict("D, G", 2),
        get_dict("B, C, M, P", 3),
        get_dict("F, H, V, W, Y", 4),
        get_dict("K", 5),
        get_dict("J, X", 8),
        get_dict("Q, Z", 10)
    )
    # uppercase input
    str = uppercase(str)
    return calculate_score(score_mapping, str)
end
