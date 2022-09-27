"""
    ispangram(input)

Return `true` if `input` contains every alphabetic character (case insensitive).

"""
function ispangram(input)
    regx = "^"
    input = lowercase(input)
    for char in collect('a':'z')
        regx *= string("(?=.*", char, ")")
    end
    regx = Regex(regx * ".*")
    return match(regx, input) === nothing ? false : true
end

