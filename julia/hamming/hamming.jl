"Your optional docstring here"
function distance(a, b)
    if length(a) == length(b)
        dif = [1 for (ai, bi) in zip(a, b) if ai != bi]
        return length(dif) > 0 ? sum(dif) : 0
    else
        throw(ArgumentError("DNA sequence are not equal length"))
    end
end
