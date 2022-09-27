function encode(s)
    s = split(s, "")
    new_s = ""
    temp_cache = s[1]
    c = 0
    while ~(isempty(s))
        re_elem = popfirst!(s)
        if temp_cache == re_elem
            c += 1
        else
            new_s *= c != 1 ? string(c, temp_cache) : string(temp_cache)
            temp_cache = re_elem
            c = 1
        end
    end
    new_s *= c != 1 ? string(c, temp_cache) : string(temp_cache)
    return new_s
end
    


function decode(s)
    s = split(s, "")
    new_s = ""
    temp_cache = s[1]
    c = 0
    while ~(isempty(s))
        re_elem = popfirst!(s)
        try
            c = (c == 0 || re_elem == " ") ?
                parse(Int, re_elem) : parse(Int, string(c) * re_elem)
        catch
            new_s *= c != 0 ? re_elem^c : re_elem
            c = 0
        end
    end
    return new_s
end
