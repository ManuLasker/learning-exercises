function encode(input)
    # clean input
    input = lowercase(input)
    input = replace(input, r"([^\w]|\s)" => "")
    alphabet = collect('a':'z')
    result = ""
    for (i, c) in enumerate(input)
        ic = findfirst(x -> x == c, alphabet)
        ic !== nothing ? cc = alphabet[end:-1:1][ic] : cc = c
        (i % 5 == 0) ? result *= cc * " " : result *= cc
    end
    return strip(result)
end

function decode(input)
    # clean input
    return replace(encode(input), r"\s" => "")
end

