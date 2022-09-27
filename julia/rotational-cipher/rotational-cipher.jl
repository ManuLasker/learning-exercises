function rotate(ro_index, target)
    upper_cases = collect('A':'Z')
    lower_cases = collect('a':'z')
    output = ""
    for raw in target
        db = isuppercase(raw) ? upper_cases : lower_cases
        ai = findfirst(x -> x == raw, db)
        if ai !== nothing
            idx = (ai + ro_index) % 26
            idx = idx == 0 ? idx + 26 : idx
            output *= db[idx]
        else
            output *= raw
        end
    end
    return typeof(target) == Char ? only(output) : output
end

for i in 0:26
    macro_name = Symbol(string("R", i, "_str"))
    @eval macro $macro_name(s)
        return rotate($i, s)
    end
end